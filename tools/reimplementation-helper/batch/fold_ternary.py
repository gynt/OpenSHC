"""Fold `if (c) { X = a; } else { X = b; }` into a ternary at X's single use.

The two-arm assignment is how Ghidra renders a conditional *argument*, and keeping it as a
local costs the match badly: the original pushes the whole argument list inside each arm
and converges on the shared tail of the call
(`MenuItemRenderFunction_General_GameOptionsTextButton`, where both paths reach
`push 0x4a; call getTextStringInGroupAtOffset` at 0x493544). A ternary at the use site is
what lets MSVC duplicate the pushes that way.

Both arms must be the same run of plain assignments to the same locals in the same order,
and each of those locals must be read exactly once before it is written again, so the
rewrite cannot change evaluation order. The condition is kept exactly as it stands: its
sense decides which arm MSVC places first.

usage:
  fold_ternary.py FILE.cpp... [--apply]
"""

import io
import os
import re
import sys

import common  # noqa: F401

ASSIGN = re.compile(r"^ *(?P<var>[A-Za-z_]\w*) = (?P<val>[^;]+);$")


def _arm(lines, n, ind):
    """([(var, value)], next_index) for a run of plain assignments at ind + 4."""
    out = []
    while n < len(lines) and len(lines[n]) - len(lines[n].lstrip()) == ind + 4:
        m = ASSIGN.match(lines[n])
        if not m:
            return None, n
        out.append((m.group("var"), m.group("val")))
        n += 1
    return (out or None), n


def _single_read(rest, var):
    """True when `var` is read exactly once before it is written again."""
    reads = 0
    for occ in re.finditer(r"\b" + re.escape(var) + r"\b(\s*=[^=])?", rest):
        if occ.group(1):
            break
        reads += 1
        if reads > 1:
            return False
    return reads == 1


def fold(text):
    """-> (text, [variable]) for every arm pair folded into ternaries."""
    lines = text.split("\n")
    done = []
    i = 0
    while i < len(lines):
        m = re.match(r"^( *)if \((.*)\) \{$", lines[i])
        if not m:
            i += 1
            continue
        ind, cond = len(m.group(1)), m.group(2)
        hot, n = _arm(lines, i + 1, ind)
        if not hot or n >= len(lines) or lines[n] != " " * ind + "} else {":
            i += 1
            continue
        cold, k = _arm(lines, n + 1, ind)
        if not cold or k >= len(lines) or lines[k] != " " * ind + "}":
            i += 1
            continue
        if [v for v, _ in hot] != [v for v, _ in cold] or len(hot) > 3:
            i += 1
            continue
        rest = "\n".join(lines[k + 1:])
        if not all(_single_read(rest, v) for v, _ in hot):
            i += 1
            continue
        for (var, a), (_, b) in zip(hot, cold):
            rest = re.sub(r"\b" + re.escape(var) + r"\b",
                          "(%s ? %s : %s)" % (cond, a, b), rest, count=1)
            done.append(var)
        lines = lines[:i] + rest.split("\n")
        i = 0
    return "\n".join(lines), done


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    if not args:
        raise SystemExit(__doc__)
    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        text = io.open(path, encoding="utf-8").read()
        out, done = fold(text)
        if not done:
            continue
        print("%-62s %s" % (os.path.basename(path), ", ".join(done)))
        if apply_:
            io.open(path, "w", encoding="utf-8", newline="\n").write(out)


if __name__ == "__main__":
    main()
