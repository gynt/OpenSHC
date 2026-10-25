"""Repair `field<N>_0x<off>` references that a struct rename has broken.

A reimplementation branch written against an older header refers to a field by the decompiler's
placeholder name; the header has since been renamed to something meaningful. The compiler says so
precisely:

    UI\\Actions\\X.cpp(478) : error C2039: 'field16_0x40' : is not a member of 'A::B::SiegeUnitCounts'

That names the file, the line, the dead member and the struct, which is everything needed: look the
member up in the *old* header to get its byte offset, then take whatever the current header calls the
field at that offset. The offset is in a trailing comment on every generated field
(`int fireThrowers; // 0x00000040 length: 4`), so no C++ parsing is involved.

usage:
    port_renames.py --old <git-ref> [--log build-RelWithDebInfo/batch/build.log] [--dry-run]

`--old` is the ref the sources were written against, normally the merge-base of the branch they came
from. Only lines the compiler complained about are touched, so a placeholder name that is still
correct elsewhere in the same file is left alone.
"""

import argparse
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ERROR = re.compile(
    r"^(?P<file>[^(]+\.cpp)\((?P<line>\d+)\) : error C2039: '(?P<member>\w+)' : "
    r"is not a member of '(?P<struct>[\w:]+)'"
)
FIELD = re.compile(
    r"^\s*[\w:<>*]+[\w\s:<>*]*?\b(?P<name>\w+)\s*(?P<arr>(?:\[[^\]]*\])*)\s*;\s*//\s*0x(?P<off>[0-9A-Fa-f]+)"
    r"(?:\s*length:\s*(?P<len>\d+))?"
)

parser = argparse.ArgumentParser()
parser.add_argument("--old", required=True, help="git ref the sources were written against")
parser.add_argument("--log", default="build-RelWithDebInfo/batch/build.log")
parser.add_argument("--dry-run", action="store_true")
args = parser.parse_args()


def header_for(struct: str) -> Path | None:
    """The generated header of a struct, from its fully qualified name."""
    name = struct.split("::")[-1]
    hits = [p for p in Path("src").rglob(name + ".hpp")]
    if len(hits) == 1:
        return hits[0]
    # several files with that basename: prefer the one whose directory matches the namespace
    ns = "/".join(struct.split("::")[:-1])
    for p in hits:
        if ns and ns in p.as_posix():
            return p
    return hits[0] if hits else None


def fields(text: str) -> list:
    """(offset, name, length, elements) for one generated header, in declaration order."""
    out = []
    for line in text.splitlines():
        m = FIELD.match(line)
        if not m or m.group("name").startswith("padding"):
            continue
        extents = [int(x) for x in re.findall(r"\[(\d+)\]", m.group("arr") or "")]
        n = 1
        for x in extents:
            n *= x
        out.append((int(m.group("off"), 16), m.group("name"), int(m.group("len") or 0), n))
    return out


def member_at(flds: list, off: int) -> str | None:
    """What the current header calls the thing at a byte offset - `name` or `name[i]`.

    A rename is not always one-for-one: six scalars can become one array, which is the same
    bytes under one name, so an offset inside a field resolves to a subscript.
    """
    for base, name, length, n in flds:
        if base == off and n == 1:
            return name
        if length and base <= off < base + length:
            if n <= 1:
                return name if base == off else None
            elem = length // n
            if elem and (off - base) % elem == 0:
                return "%s[%d]" % (name, (off - base) // elem)
    return None


def by_name(text: str) -> dict:
    out = {}
    for line in text.splitlines():
        m = FIELD.match(line)
        if m:
            out[m.group("name")] = int(m.group("off"), 16)
    return out


log = Path(args.log).read_text(errors="replace")
errors = [m.groupdict() for m in (ERROR.match(l.strip()) for l in log.splitlines()) if m]
if not errors:
    sys.exit("no C2039 errors in " + args.log)

cache = {}
renames = {}
unresolved = defaultdict(set)
for e in errors:
    key = e["struct"]
    if key not in cache:
        hpp = header_for(key)
        if hpp is None:
            cache[key] = None
        else:
            old = subprocess.run(["git", "show", f"{args.old}:{hpp.as_posix()}"], capture_output=True, text=True)
            cache[key] = (hpp, by_name(old.stdout if old.returncode == 0 else ""), fields(hpp.read_text()))
    if cache[key] is None:
        unresolved["no header"].add(f'{e["struct"]}::{e["member"]}')
        continue
    hpp, old_off, new_at = cache[key]
    off = old_off.get(e["member"])
    if off is None:
        # the decompiler's placeholder carries its own offset, which is enough when the old
        # header is not the one the source was written against either
        m = re.search(r"_0x([0-9A-Fa-f]+)$", e["member"])
        off = int(m.group(1), 16) if m else None
    if off is None:
        unresolved["not in the old header"].add(f'{e["struct"]}::{e["member"]}')
        continue
    new = member_at(new_at, off)
    if new is None:
        unresolved["no field at that offset now"].add(f'{e["struct"]}::{e["member"]} @ 0x{off:x}')
        continue
    if new == e["member"]:
        unresolved["unchanged name"].add(f'{e["struct"]}::{e["member"]}')
        continue
    renames[(e["struct"], e["member"])] = new

edits = defaultdict(list)
for e in errors:
    new = renames.get((e["struct"], e["member"]))
    if new:
        edits[e["file"].replace("\\", "/")].append((int(e["line"]), e["member"], new))

changed = 0
for f, items in sorted(edits.items()):
    p = Path("src/OpenSHC") / f if not f.startswith("src/") else Path(f)
    if not p.exists():
        hits = list(Path("src").rglob(Path(f).name))
        if len(hits) != 1:
            unresolved["no source file"].add(f)
            continue
        p = hits[0]
    lines = p.read_text(newline="").split("\n")
    n = 0
    for ln, old, new in items:
        pat = re.compile(r"\b%s\b" % re.escape(old))
        # MSVC reports the line the statement starts on, which for a wrapped expression is not the
        # line the member sits on, so look either side of it.
        for i in [ln - 1] + [ln - 1 + d for k in range(1, 7) for d in (k, -k)]:
            if 0 <= i < len(lines) and pat.search(lines[i]):
                lines[i] = pat.sub(new, lines[i])
                n += 1
                break
        else:
            unresolved["line did not hold the member"].add(f"{p.name}:{ln} {old}")
    if n and not args.dry_run:
        p.write_text("\n".join(lines), newline="")
    changed += n

for (struct, member), new in sorted(renames.items()):
    print(f"  {struct.split('::')[-1]}::{member} -> {new}")
print(f"{changed} reference(s) in {len(edits)} file(s){' (dry run)' if args.dry_run else ''}")
for why, items in sorted(unresolved.items()):
    print(f"  unresolved, {why}: {', '.join(sorted(items)[:6])}{' ...' if len(items) > 6 else ''}")
