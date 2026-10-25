"""Inline the decompiler's single-assignment constant locals.

Ghidra turns an argument that the original pushed as an immediate into a local:

    int fontSize;
    BOOLEnum keepOffsetX;
    ...
    fontSize = 0x10;
    keepOffsetX = FALSE;
    renderTextToScreen(text, x, y, alignment, color, fontSize, keepOffsetX, blendStrength);

The original's own code is `push 0; push 0; push 0x10; ...` - five immediates - so these are
not variables the source had. Only locals that are declared in the Ghidra declaration block,
assigned exactly once, and assigned a literal or an enum constant are inlined, which is the
shape above and nothing else.

This is a readability change, not a match lever: `RenderBuildingMenu_Applefarm` carries the
same five locals and is already at 100%, so MSVC propagates the constants either way. It is
still worth doing - the style list asks for direct use over a local the compiler invented - and
it is worth measuring once over a whole selection to confirm the neutrality.

usage:
    inline_const_locals.py [path-filter...] [--apply]
"""

import re
import sys
from pathlib import Path

import common

TYPES = r"int|uint|short|ushort|BOOLEnum|BGR24|TextAlignment|byte|char|undefined4|dword"
ASSIGN = re.compile(r"^(?P<indent>\s*)(?P<name>\w+)\s*=\s*(?P<value>[^;=]+);\s*$", re.M)
CONST = re.compile(r"^(0x[0-9a-fA-F]+|\d+|FALSE|TRUE|OpenSHC::[\w:]+|\w+::[\w:]+)$")

apply = "--apply" in sys.argv
filters = [a for a in sys.argv[1:] if not a.startswith("--")]
files = [f for f in common.list_files() if not filters or any(s in f for s in filters)]

total = changed = 0
for f in files:
    text = Path(f).read_text(newline="")
    start = text.find("// FUNCTION:")
    if start < 0:
        continue
    head, body = text[:start], text[start:]
    inlined = []
    for m in list(ASSIGN.finditer(body)):
        name, value = m.group("name"), m.group("value").strip()
        if not CONST.match(value):
            continue
        if len(re.findall(r"\b%s\s*=[^=]" % re.escape(name), body)) != 1:
            continue
        decl = re.search(r"^[ \t]*(?:%s)[ \t]+%s;[ \t]*\n" % (TYPES, re.escape(name)), body, re.M)
        if not decl:
            continue
        inlined.append((name, value, decl.group(0), m.group(0)))
    for name, value, decl_line, assign_line in inlined:
        body = body.replace(decl_line, "", 1)
        body = re.sub(r"[ \t]*%s[ \t]*\n" % re.escape(assign_line.strip()), "", body, count=1)
        body = re.sub(r"\b%s\b" % re.escape(name), value, body)
    if inlined:
        total += len(inlined)
        changed += 1
        print("  %-54s %s" % (Path(f).name, ", ".join(n for n, _v, _d, _a in inlined)))
        if apply:
            Path(f).write_text(head + body, newline="")
print("%d constant local(s) inlined in %d file(s)%s"
      % (total, changed, "" if apply else " (dry run, pass --apply)"))
