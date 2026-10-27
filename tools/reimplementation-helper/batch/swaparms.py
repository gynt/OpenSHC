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
  swaparms.py [--structural] [FILE.cpp...]

`--structural` scores with `structural_diff.py --score` (minimise `delta`, then maximise
`kind`) instead of quick_diff's line ratio. It sounds like the better gate - a swap moves
every later instruction, which quick_diff's line diff punishes and `delta`'s mnemonic census
does not - and it is **measurably worse**: over the 51 UI/MenuItems functions whose
`structural_diff.py` report carries a POLARITY block it kept 22 swaps in 17 files, and on
reccmp 24 functions came out WORSE and one better by 0.1 (`InGameMenu_MainButtons` 86.3% ->
72.2%, `ReturnToBuildMenu` 75.2% -> 68.4%). The reason is that `delta` is a histogram: an arm
swap barely changes which mnemonics are emitted, so a swap that lowers `delta` by one is
mostly being rewarded for noise while it scrambles the register assignment. Prefer the default
quick_diff gate, and keep this one for a transform that really does change the instruction mix.

`structural_diff.py NAME` is still worth reading first - its POLARITY block names every branch
where the original falls through and we jump, including the ones written as an early return
with no `else` for `sites()` to match - but a located site is a candidate, not a win.
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


STRUCTURAL = False


def score(path):
    """A number to maximise. quick_diff's line ratio by default; with --structural, the
    structural objective from structural_diff.py - `-delta` first, then `kind`.

    The structural score is the better gate when a transform can change the function's length,
    because `delta` counts mismatched mnemonics instead of diffing lines: quick_diff punishes
    every shifted instruction, which is why it rated the arm swap that took VideoOptions_Main
    4.3 points on reccmp at +0.0002. `structural_diff.py NAME` also *locates* the sites worth
    trying - its POLARITY block names every branch where the original falls through and we
    jump, which is exactly this transform, and it finds the ones written as an early return
    with no `else` for `sites()` to match.
    """
    if STRUCTURAL:
        name = os.path.basename(path)[:-4]
        r = subprocess.run([sys.executable, os.path.join(BATCH, "structural_diff.py"),
                            name, "--score"], capture_output=True, text=True)
        out = r.stdout.strip()
        m = re.search(r"^(\d+\.\d+) (\d+)$", out.splitlines()[-1]) if out else None
        if m is None:
            return None
        # delta dominates; `kind` only breaks ties between two orders of the same mnemonics
        return -int(m.group(2)) + float(m.group(1)) / 1000.0
    r = subprocess.run([sys.executable, os.path.join(BATCH, "quick_diff.py"), path],
                       capture_output=True, text=True)
    m = re.search(r"ratio (\d+\.\d+)", r.stdout)
    return float(m.group(1)) if m else None


def main():
    global STRUCTURAL
    STRUCTURAL = "--structural" in sys.argv[1:]
    files = [a for a in sys.argv[1:] if not a.startswith("--")] or [str(p) for p in common.list_files()]
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


if __name__ == "__main__":
    main()
