"""Inline a decompiler temp that only feeds the first argument of the next call.

usage: inline_arg.py [PATH-SUBSTRING] [--apply]

Ghidra hoists a nested call out of its argument list:

    pcVar5 = getTextStringInGroupAtOffset(TEXT_MONTHS, month);
    renderTextToScreen(pcVar5, x, y, ...);

MSVC pushes arguments right to left, so the original evaluates that inner call
*after* the outer call's later arguments.  With the temp in the way we evaluate
it first, which reorders every push and costs a large part of the match; three
functions in UI::MenuViews went from 77-87% to 100% on this alone.  Writing the
call back where it belongs restores the order:

    renderTextToScreen(getTextStringInGroupAtOffset(TEXT_MONTHS, month), x, y, ...);

A temp is only rewritten when *every* reference to it is one of these pairs and
it has exactly one declaration, so the move cannot change evaluation order
relative to anything else; the declaration is then dropped.  Dry run unless
--apply; the result is re-formatted with clang-format.
"""

import pathlib
import re
import sys

import common

ASSIGN = re.compile(r"^(\s*)([A-Za-z_]\w*) = (MACRO_CALL\w*\()")
CALL = re.compile(r"^(\s*)MACRO_CALL\w*\(")


def statement(lines, i):
    """End index (exclusive) of the statement starting at line i, or None."""
    depth = 0
    for j in range(i, len(lines)):
        depth += lines[j].count("(") - lines[j].count(")")
        if depth == 0 and lines[j].rstrip().endswith(";"):
            return j + 1
        if depth < 0:
            return None
    return None


def candidates(lines):
    """[(start, use_end, var, replacement)] for every assign-then-use-as-first-arg pair."""
    out, i = [], 0
    while i < len(lines):
        m = ASSIGN.match(lines[i])
        end = statement(lines, i) if m else None
        if not m or end is None:
            i += 1
            continue
        var = m.group(2)
        use_end = statement(lines, end) if end < len(lines) else None
        if use_end is None or not CALL.match(lines[end]):
            i = end
            continue
        expr = "".join(lines[i:end]).strip()[len(var) + 3:].rstrip(";").strip()
        use = "".join(lines[end:use_end]).strip()
        callee, _, rest = use.partition("(")
        args = rest.rstrip(";").rstrip()
        split = args.find(")(")
        if not args.endswith(")") or split < 0:
            i = end
            continue
        obj, arglist = args[:split + 2], args[split + 2:-1]
        first, sep, tail = arglist.partition(",")
        if first.strip() != var or not sep:
            i = end
            continue
        joined = re.sub(r"\s+", " ",
                        m.group(1) + callee + "(" + obj + expr + sep + tail)
        out.append((i, use_end, var, joined + ");\n"))
        i = use_end
    return out


def rewrite(text):
    lines = text.splitlines(True)
    groups = {}
    for c in candidates(lines):
        groups.setdefault(c[2], []).append(c)
    drop, replace = set(), {}
    for var, group in groups.items():
        decl = re.compile(r"^\s*[A-Za-z_][\w:*&<>, ]*?\*?\s*" + re.escape(var) + r";\s*$")
        at = [k for k, line in enumerate(lines) if decl.match(line)]
        refs = len(re.findall(r"\b" + re.escape(var) + r"\b", text))
        if len(at) != 1 or refs != 1 + 2 * len(group):
            continue
        drop.add(at[0])
        for start, use_end, _, new in group:
            replace[start] = (use_end, new)
    if not replace:
        return text, 0
    out, i, n = [], 0, 0
    while i < len(lines):
        if i in drop:
            i += 1
        elif i in replace:
            use_end, new = replace[i]
            out.append(new)
            n += 1
            i = use_end
        else:
            out.append(lines[i])
            i += 1
    return "".join(out), n


apply = "--apply" in sys.argv
want = next((a for a in sys.argv[1:] if not a.startswith("--")), "")
total = 0
for f in common.list_files():
    p = pathlib.Path(f)
    if want and want not in p.as_posix():
        continue
    new, n = rewrite(common.read_text(p))
    if not n:
        continue
    total += n
    print("%s  %d site(s)" % (p.as_posix(), n))
    if apply:
        common.write_text(p, new)
        common.format_file(p)
print("%d site(s)%s" % (total, "" if apply else " (dry run, pass --apply)"))
