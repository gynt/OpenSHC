"""Write `(-(uint)(c) & MASK) + BASE` back as the conditional it is.

The decompiler turns a conditional constant into mask-and-add, which hides both constants:
`(-(uint)(d != 1) & 0xffffffce) + 200` is `d == 1 ? 200 : 150`. Writing the conditional out
recovers the same instructions and makes the two values readable, and it closes the small
gap mask-and-add leaves - `RepairBuildingButton` went 0.613 -> 0.631 and 0.642 -> 0.662 on
`quick_diff.py`'s ratio, with the instruction count a step closer on both.

The condition is emitted in the sense that puts `BASE` first (`c == k ? BASE : BASE+MASK`),
since that is the arm the original falls through to. Where the result is a call's argument,
follow this with `split_ternary_call.py`.

usage:
  unmask.py FILE.cpp... [--apply]
"""

import io
import os
import re
import sys

import common  # noqa: F401


def _fold(mask, base):
    """The value of the masked arm, as a signed literal."""
    v = (mask + base) & 0xFFFFFFFF
    if v >= 0x80000000:
        v -= 0x100000000
    return "0x%x" % v if v >= 0 else "-0x%x" % -v


def _invert(cond):
    """`c` in the opposite sense, so that BASE is the first arm."""
    cond = cond.strip()
    if " != " in cond and cond.count(" != ") == 1 and "&&" not in cond and "||" not in cond:
        return cond.replace(" != ", " == ")
    if " == " in cond and cond.count(" == ") == 1 and "&&" not in cond and "||" not in cond:
        return cond.replace(" == ", " != ")
    return None


PAT = re.compile(
    r"\(\s*-\(uint\)\((?P<cond>.+?)\)\s*&\s*(?P<mask>0x[0-9a-fA-F]+)\s*\)\s*\+\s*"
    r"(?P<base>0x[0-9a-fA-F]+|\d+)",
    re.S)


def rewrite(text):
    """-> (text, n) with every mask-and-add written as a conditional."""
    done = 0
    while True:
        m = PAT.search(text)
        if not m:
            return text, done
        cond = " ".join(m.group("cond").split())
        inverted = _invert(cond)
        if inverted is None:
            # leave anything whose sense cannot be flipped cleanly
            return text, done
        base = m.group("base")
        masked = _fold(int(m.group("mask"), 16),
                       int(base, 16 if base.startswith("0x") else 10))
        text = (text[:m.start()]
                + "(%s ? %s : %s)" % (inverted, base, masked)
                + text[m.end():])
        done += 1


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    if not args:
        raise SystemExit(__doc__)
    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        text = io.open(path, encoding="utf-8").read()
        out, n = rewrite(text)
        if not n:
            continue
        print("%-62s %d site(s)" % (os.path.basename(path), n))
        if apply_:
            io.open(path, "w", encoding="utf-8", newline="\n").write(out)


if __name__ == "__main__":
    main()
