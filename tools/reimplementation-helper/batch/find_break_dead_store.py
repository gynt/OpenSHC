"""Find arms whose store a `break` makes dead, because the switch's tail repeats it.

The documented dead-store tells are `if (c) { ...; X = A; }` followed immediately
by `X = B;`, and an empty `if (c) {}`. There is a third: an arm that stores `X = A`
and then **breaks**, where the statement after the switch's closing brace is
`X = B`. MSVC deletes the arm's store, so the flag ends up B where the original
leaves it A - and the original ends that arm with `mov [X], A; pop; ret`.

`find_dead_store.py` cannot see it (the stores are not adjacent), the `ret` count
cannot (both `break` and `return` are exits) and `quick_diff`'s ratio does not move.
Each hit has to be confirmed by reading the arm's last instruction in the binary.

Reports one line per (arm, store) pair for hand checking.
"""
import io
import os
import re
import sys

STORE = re.compile(r"^\s*([\w:]+::instance(?:\.\w+)*) = ([^;=]+);$")
CASE = re.compile(r"^\s*(case .*|default) *:$")

hits = 0
for rel in io.open("cmake/openshc-sources.txt.local", encoding="utf-8").read().split():
    if not rel.endswith(".cpp"):
        continue
    lines = io.open(rel, encoding="utf-8").read().split("\n")
    for i, line in enumerate(lines):
        m = re.match(r"^(\s*)switch \(", line)
        if not m:
            continue
        ind = len(m.group(1))
        depth, end = 0, None
        for j in range(i, len(lines)):
            depth += lines[j].count("{") - lines[j].count("}")
            if j > i and depth == 0:
                end = j
                break
        if end is None or end + 1 >= len(lines):
            continue
        t = STORE.match(lines[end + 1])
        if not t:
            continue
        name, tail = t.group(1), t.group(2).strip()
        # walk the arms; report a store of a different value in an arm that breaks
        arm, stores = None, []
        for j in range(i + 1, end + 1):
            if CASE.match(lines[j]) and (len(lines[j]) - len(lines[j].lstrip())) <= ind + 4:
                arm, stores = lines[j].strip(), []
                continue
            s = STORE.match(lines[j])
            if s and s.group(1) == name and s.group(2).strip() != tail:
                stores.append((j + 1, s.group(2).strip()))
            if lines[j].strip() == "return;" or lines[j].strip().startswith("goto "):
                stores = []
            if lines[j].strip() == "break;" and stores:
                for ln, val in stores:
                    sys.stdout.write("%s:%d  %s = %s  in %s  (tail sets %s)\n"
                                     % (os.path.basename(rel), ln, name, val, arm, tail))
                    hits += 1
                stores = []
sys.stdout.write("%d site(s)\n" % hits)
