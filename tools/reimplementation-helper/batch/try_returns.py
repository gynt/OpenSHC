"""Hill-climb the dropped `return` statements Ghidra leaves out.

The decompiler turns `if (guard) { ...; return; }` into a plain `if (guard) { ... }`,
because a `return` at the end of a block carries no data flow. The result still
compiles, and when the guard's last statement is a store that the code after the `if`
repeats, MSVC deletes that store as dead - so the whole guard disappears from our
binary. That is the single largest source of mismatch across `UI::MenuItems`:
restoring one `return` took `MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol`
from 72.7% to normalized 100%.

This tries a `return;` at the end of every `if` body in the function that could carry
one (no `else`, and statements follow the `if` in the enclosing block) and keeps the
ones `quick_diff.py` scores better. Each trial is one `/FA` compile of one file, about
six seconds, so a function with a handful of candidates settles in a minute.

The pass is semantics-preserving only if the original really did return there, which is
what the score decides; a site that does not improve is reverted. Confirm a run with
`reccmp_report.py --run cmp`, as always.

usage:
  try_returns.py FILE.cpp...            # hill-climb each file, keep what helps
  try_returns.py FILE.cpp... --dry      # just list the candidate sites
  try_returns.py FILE.cpp... --min 0.02 # required gain per site (default 0.005)
"""

import io
import os
import re
import sys

import difflib

import common

# quick_diff parses sys.argv at import time; hide ours from it.
_argv, sys.argv = sys.argv, [sys.argv[0], "-q"]
import quick_diff  # noqa: E402

sys.argv = _argv

MIN_GAIN = 0.005


def ratio_for(path):
    """quick_diff's own ratio for one file, or None when the compile failed."""
    a, b = quick_diff.streams(path)
    if b is None:
        return None
    return difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()


def body_span(lines):
    """Line range [start, end) of the reimplemented function's body."""
    for i, line in enumerate(lines):
        if line.lstrip().startswith("// FUNCTION:"):
            break
    else:
        return None
    depth = 0
    start = None
    for j in range(i, len(lines)):
        for ch in lines[j]:
            if ch == "{":
                depth += 1
                if depth == 1:
                    start = j + 1
            elif ch == "}":
                depth -= 1
                if depth == 0 and start is not None:
                    return start, j
    return None


def candidates(lines):
    """Closing braces of `if` bodies that could have carried a `return`.

    A site qualifies when the brace closes a block at the body's own indent or deeper,
    no `else` follows it, and the enclosing block still has statements after it - a
    `return` as the last statement of a function is what the compiler emits anyway.
    """
    span = body_span(lines)
    if not span:
        return []
    start, end = span
    base = None
    for j in range(start, end):
        if lines[j].strip():
            base = len(lines[j]) - len(lines[j].lstrip())
            break
    if base is None:
        return []

    out = []
    for j in range(start, end):
        s = lines[j].strip()
        if s != "}":
            continue
        ind = len(lines[j]) - len(lines[j].lstrip())
        if ind < base:
            continue
        k = j + 1
        while k < end and not lines[k].strip():
            k += 1
        if k >= end:
            continue
        nxt = lines[k].strip()
        if nxt.startswith("else") or nxt.startswith("}") or nxt.startswith("while"):
            continue
        # the matching `if` must not be a loop or a switch arm
        depth = 0
        opener = None
        for m in range(j, start - 1, -1):
            depth += lines[m].count("}") - lines[m].count("{")
            if depth == 0:
                opener = m
                break
        if opener is None:
            continue
        head = " ".join(lines[max(start, opener - 2):opener + 1])
        if re.search(r"\b(for|while|switch|do)\b\s*\(", head) and "if (" not in head:
            continue
        if "if" not in head and "else" not in head:
            continue
        out.append((j, ind))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    gain = MIN_GAIN
    if "--min" in sys.argv:
        gain = float(sys.argv[sys.argv.index("--min") + 1])

    for rel in args:
        path = os.path.join(common.ROOT, rel.replace("/", os.sep)) if not os.path.isabs(rel) else rel
        text = io.open(path, encoding="utf-8").read()
        lines = text.split("\n")
        sites = candidates(lines)
        print("##### %s  %d candidate site(s)" % (os.path.basename(path), len(sites)))
        if dry:
            for j, ind in sites:
                print("   line %d" % (j + 1))
            continue

        base = ratio_for(path)
        print("   base %.4f" % base)
        kept = []
        # work bottom-up so earlier line numbers stay valid
        for j, ind in sorted(sites, reverse=True):
            cur = io.open(path, encoding="utf-8").read().split("\n")
            trial = cur[:j] + [" " * (ind + 4) + "return;"] + cur[j:]
            io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(trial))
            r = ratio_for(path)
            if r is not None and r > base + gain:
                print("   line %-5d %.4f  KEEP" % (j + 1, r))
                base = r
                kept.append(j + 1)
            else:
                print("   line %-5d %s" % (j + 1, "%.4f" % r if r is not None else "fail"))
                io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(cur))
        print("   final %.4f  kept %s" % (base, kept or "none"))


if __name__ == "__main__":
    main()
