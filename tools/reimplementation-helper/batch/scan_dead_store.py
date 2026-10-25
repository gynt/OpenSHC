"""Find `if (...) { X = a; }` immediately followed by an unconditional `X = b;`.

The store inside the branch is dead, so the condition has no effect - which is never what the
original did. It is a decompiler artefact: the original ends the branch with its own `ret`, and
Ghidra renders the two exits as one fall-through. `MenuItemRenderFunction_BuildMenu_MiniMapInteraction`
is the worked case - 0x00434328 stores 1 and returns, 0x0043432e stores 0 and returns, and without
the `return` the flag is never set.

Both a correctness bug and a match bug, so it is worth scanning for across a whole selection.

usage:
    scan_dead_store.py [path-filter...]
"""

import re
import sys
from pathlib import Path

import common

ASSIGN = re.compile(r"^(?P<lhs>[\w:\.\[\]\->]+)\s*=\s*(?P<rhs>[^=][^;]*);$")

filters = [a for a in sys.argv[1:] if not a.startswith("--")]
files = [f for f in common.list_files() if not filters or any(s in f for s in filters)]

hits = 0
for f in files:
    lines = Path(f).read_text(errors="replace").split("\n")
    for i, line in enumerate(lines):
        s = line.strip()
        if s != "}":
            continue
        # the single statement of the block above, and the statement after the block
        prev = lines[i - 1].strip() if i else ""
        nxt = next((lines[j].strip() for j in range(i + 1, min(i + 3, len(lines))) if lines[j].strip()), "")
        mp, mn = ASSIGN.match(prev), ASSIGN.match(nxt)
        if not mp or not mn or mp.group("lhs") != mn.group("lhs"):
            continue
        if mp.group("rhs").strip() == mn.group("rhs").strip():
            continue
        # the closing brace has to belong to an `if`, not to a loop or a function
        depth = 0
        opener = None
        for j in range(i - 1, max(-1, i - 60), -1):
            depth += lines[j].count("}") - lines[j].count("{")
            if depth < 0:
                opener = lines[j]
                break
        if opener is None or not re.search(r"^\s*(\}\s*else\s+)?if\s*\(|&&|\|\|", opener):
            continue
        if re.search(r"\b(for|while|do|switch)\b", opener):
            continue
        hits += 1
        print("  %-54s:%d  %s   then unconditionally %s"
              % (Path(f).name, i, prev[:48], mn.group("rhs").strip()[:20]))
print("%d dead conditional store(s)" % hits)
