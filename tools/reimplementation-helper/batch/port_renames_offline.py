"""Resolve stale placeholder field names without the compiler, by walking the access path.

`port_renames.py` needs a build log, which costs a compile per round. Most stale references can be
resolved from the source text alone: the access names its own struct.

    DAT_GameState::instance.mapAndTime.siegeInformation.field18_0x48
    ^ global -> GameState           ^ MapAndTimeState  ^ SiegeUnitCounts

The global's type comes from `MACRO_STRUCT_RESOLVER(<Type>, ...)` in `src/OpenSHC/Globals/DAT_*.hpp`,
each `.member` is looked up in that struct's generated header to get the next type, and the final
placeholder carries its own byte offset in its name. Whatever the current header calls the field at
that offset is the answer - a subscript when several scalars have become one array.

A placeholder that is still declared in the struct it is used on is left alone, so this is safe to
run over a whole tree.

usage:
    port_renames_offline.py [path-filter...] [--apply]
"""

import re
import sys
from collections import defaultdict
from pathlib import Path

import common

PLACEHOLDER = re.compile(r"\b(?:field\w*|mbr)_0x([0-9A-Fa-f]+)\b")
FIELD = re.compile(
    r"^\s*(?P<type>[\w:]+)(?P<ptr>\s*\*)?\s+(?P<name>\w+)\s*(?P<arr>(?:\[[^\]]*\])*)\s*;"
    r"\s*//\s*0x(?P<off>[0-9A-Fa-f]+)(?:\s*length:\s*(?P<len>\d+))?"
)
RESOLVER = re.compile(r"MACRO_STRUCT_RESOLVER\(\s*([\w:]+)\s*,")

apply = "--apply" in sys.argv
filters = [a for a in sys.argv[1:] if not a.startswith("--")]

headers = {}
for p in Path("src/OpenSHC").rglob("*.hpp"):
    headers.setdefault(p.stem, []).append(p)


def fields_of(struct):
    """[(offset, name, type, length, elements)] for a struct name, or None."""
    for p in headers.get(struct, []):
        text = p.read_text(errors="replace")
        if "struct %s" % struct not in text and "class %s" % struct not in text:
            continue
        out = []
        for line in text.splitlines():
            m = FIELD.match(line)
            if not m or m.group("name").startswith("padding"):
                continue
            extents = [int(x) for x in re.findall(r"\[(\d+)\]", m.group("arr") or "")]
            n = 1
            for x in extents:
                n *= x
            out.append((int(m.group("off"), 16), m.group("name"),
                        m.group("type").split("::")[-1], int(m.group("len") or 0), n))
        if out:
            return out
    return None


def global_type(name):
    for p in headers.get(name, []):
        m = RESOLVER.search(p.read_text(errors="replace"))
        if m:
            return m.group(1).split("::")[-1]
    return None


def member_at(flds, off):
    for base, name, _t, length, n in flds:
        if base == off and n == 1:
            return name
        if length and base <= off < base + length and n > 1:
            elem = length // n
            if elem and (off - base) % elem == 0:
                return "%s[%d]" % (name, (off - base) // elem)
        if base == off:
            return name
    return None


def resolve(path, off, own_class):
    """Walk `DAT_X::instance.a.b` (or `this`) to the struct the placeholder sits in."""
    parts = [p for p in re.split(r"\.|->", path) if p]
    struct = None
    for part in parts:
        part = part.strip()
        m = re.match(r"^(\w+)::(?:instance|ptr)$", part)
        if m:
            struct = global_type(m.group(1))
            continue
        if part == "this":
            struct = own_class
            continue
        if struct is None:
            return None
        flds = fields_of(struct)
        if not flds:
            return None
        base = re.sub(r"\[.*", "", part)
        nxt = next((t for _o, n, t, _l, _e in flds if n == base), None)
        if nxt is None:
            return None
        struct = nxt
    return struct


files = [f for f in common.list_files() if not filters or any(s in f for s in filters)]
edits = defaultdict(list)
unresolved = defaultdict(int)
for f in files:
    own_class = None
    text = Path(f).read_text(newline="", errors="replace")
    m = re.search(r"\bvoid |\bint |\bshort |\bBOOLEnum |\bundefined4 ", text)
    m = re.search(r"\n\s*\w[\w:]*\s+(\w+)::\w+\s*\(", text)
    if m:
        own_class = m.group(1)
    lines = text.split("\n")
    for i, line in enumerate(lines):
        for ph in PLACEHOLDER.finditer(line):
            name = ph.group(0)
            off = int(ph.group(1), 16)
            # the access path is whatever precedes the placeholder on this line, possibly wrapped
            prefix = line[:ph.start()].rstrip()
            j = i
            while prefix.endswith(".") is False and prefix.endswith("->") is False and j > 0:
                # the member access may start on an earlier line
                if re.search(r"(\.|->)\s*$", lines[j - 1].rstrip()):
                    prefix = lines[j - 1].rstrip()
                    j -= 1
                    continue
                break
            chain = re.search(r"([\w:]+(?:::instance|::ptr)?(?:\s*(?:\.|->)\s*[\w\[\]\.]+)*)\s*(?:\.|->)\s*$", prefix)
            if not chain:
                unresolved["no access path"] += 1
                continue
            struct = resolve(chain.group(1), off, own_class)
            if struct is None:
                unresolved["path not walkable"] += 1
                continue
            flds = fields_of(struct)
            if not flds:
                unresolved["no header for " + struct] += 1
                continue
            if any(n == name for _o, n, _t, _l, _e in flds):
                continue  # still a real field of that struct
            new = member_at(flds, off)
            if not new:
                unresolved["no field at offset in " + struct] += 1
                continue
            edits[f].append((i, name, new, struct))

total = 0
for f, items in sorted(edits.items()):
    lines = Path(f).read_text(newline="").split("\n")
    for i, old, new, struct in items:
        lines[i] = re.sub(r"\b%s\b" % re.escape(old), new, lines[i], count=1)
        total += 1
        print("  %-44s %s::%s -> %s" % (Path(f).name, struct, old, new))
    if apply:
        Path(f).write_text("\n".join(lines), newline="")
print("%d reference(s) in %d file(s)%s" % (total, len(edits), "" if apply else " (dry run, pass --apply)"))
for k, v in sorted(unresolved.items()):
    print("  skipped, %s: %d" % (k, v))
