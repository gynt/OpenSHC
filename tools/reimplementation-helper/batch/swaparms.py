"""Swap the two arms of a simple `if (A op B) {X} else {Y}`, inverting the operator, per site,
keeping only the sites that measure better with quick_diff.

Ghidra picks the arm order from the jump it decompiled, and it picks it the wrong way round often:
where the original takes `je` over a cmp we take `jne`, our source has put the original's
fall-through arm in the `else`. Inverting the operator and swapping the arms leaves behaviour
unchanged by construction - like the operand-order flip `flipcmp.py` does - so it is safe to try at
every site and keep per site.

Over `UI/MenuItems` 39 of 210 sites paid on quick_diff and 25 of them confirmed on reccmp, which
makes this the most productive mechanical lever found so far:
`MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay` 68.4% -> 97.5%,
`MenuItemRenderFunction_General_MenuMiniMap` 56.7% -> 83.9%,
`MenuItemRenderFunction_EditScenario_EventAndInvasionList` 57.5% -> 79.2%,
`MenuItemRenderFunction_MainMenu_Main` 66.9% -> 81.4%. Ten of the hits were one shape: a
`DAT_ButtonCurrentlyInteracting::instance == FALSE` guard over two render calls differing only in
the colour literal, where the original always falls through into the *interacting* arm.

Only simple conditions are touched (one comparison, no `&&`), since inverting those is a single
operator flip. Confirm with `reccmp_report.py --run cmp` as usual and revert every WORSE: two sites
that gained on quick_diff lost on reccmp.

usage:
  swaparms.py [FILE.cpp...]
"""
import io
import os
import re
import subprocess
import sys

BATCH = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, BATCH)
import common

INV = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
OPERAND = r"[^;{}()]*(?:\([^;{}()]*\))?[^;{}()]*"
HEAD = re.compile(r"\bif \(" + OPERAND + r" (==|!=|<=|>=|<|>) " + OPERAND + r"\) \{")


def block(s, open_brace):
    depth = 0
    for i in range(open_brace, len(s)):
        if s[i] == "{":
            depth += 1
        elif s[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return -1


def sites(s):
    out = []
    for m in HEAD.finditer(s):
        a_open = m.end() - 1
        a_close = block(s, a_open)
        if a_close < 0:
            continue
        em = re.match(r" else \{", s[a_close + 1:])
        if not em:
            continue
        b_open = a_close + em.end()
        b_close = block(s, b_open)
        if b_close < 0:
            continue
        out.append((m.start(), m.end(), a_open, a_close, b_open, b_close, m.group(1)))
    return out


def swapped(s, site):
    start, head_end, a_open, a_close, b_open, b_close, op = site
    head = s[start:head_end - 1].replace(" %s " % op, " %s " % INV[op], 1)
    return (s[:start] + head + s[b_open:b_close + 1] + " else " + s[a_open:a_close + 1]
            + s[b_close + 1:])


def score(path):
    r = subprocess.run([sys.executable, os.path.join(BATCH, "quick_diff.py"), path],
                       capture_output=True, text=True)
    m = re.search(r"ratio (\d+\.\d+)", r.stdout)
    return float(m.group(1)) if m else None


files = sys.argv[1:] or [str(p) for p in common.list_files()]
kept = tried = 0
for path in files:
    text = io.open(path, encoding="utf-8", newline="").read()
    base = score(path)
    if base is None:
        continue
    i = 0
    while True:
        found = sites(text)
        if i >= len(found):
            break
        cand = swapped(text, found[i])
        io.open(path, "w", encoding="utf-8", newline="").write(cand)
        new = score(path)
        tried += 1
        if new is not None and new > base + 1e-9:
            print("KEEP  %+.4f  %.4f -> %.4f  %s  %s" % (
                new - base, base, new, os.path.basename(path), text[found[i][0]:found[i][1] - 1].strip()))
            text, base, kept = cand, new, kept + 1
        io.open(path, "w", encoding="utf-8", newline="").write(text)
        i += 1
print("kept %d of %d site(s) tried" % (kept, tried))
