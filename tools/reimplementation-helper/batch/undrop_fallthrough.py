"""Drop a `return;` that follows an assignment the code after the `if` is waiting for.

Ghidra ends a branch with `return;` where the original fell through, and the tell is that
the branch's last statement then assigns a local that nothing in the branch reads - the
store is dead, so the original cannot have returned there. The shape is everywhere in
`UI::MenuItems` render functions:

    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
        color = 0xc2f0eb;
    } else {
        color = 0xccfaff;
        return;              <- wrong: the render call after the `if` wants `color`
    }
    render(..., color, ...);

which makes the button render nothing at all while it is hovered. Confirmed against the
binary in `MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands`, where both
colour paths converge on one `renderTextFromTextGroup` (0x42d28c).

Only a branch whose last assignment targets a local that is read *after* the enclosing
block qualifies, which is what makes the store dead and the `return` impossible.

usage:
  undrop_fallthrough.py FILE.cpp... [--apply]
"""

import io
import os
import re
import sys

import common  # noqa: F401

ASSIGN = re.compile(r"^(\s*)([A-Za-z_]\w*) = [^;]+;$")


def body_end(lines, n):
    """Index of the `}` closing the block the `return;` at n sits in, or None."""
    ind = len(lines[n]) - len(lines[n].lstrip())
    for j in range(n + 1, len(lines)):
        t = lines[j].strip()
        if not t:
            continue
        if t.startswith("}") and len(lines[j]) - len(lines[j].lstrip()) < ind:
            return j
        return None
    return None


def sites(text):
    """[(return_line_index, variable)] for every droppable `return;`."""
    lines = text.split("\n")
    out = []
    for n, line in enumerate(lines):
        if line.strip() != "return;" or n == 0:
            continue
        m = ASSIGN.match(lines[n - 1])
        if not m:
            continue
        close = body_end(lines, n)
        if close is None:
            continue
        var = m.group(2)
        # the local has to be read after the block, or the store is not dead and the
        # `return` may well be the original's own
        rest = "\n".join(lines[close + 1:])
        nxt = re.search(r"\b" + re.escape(var) + r"\b(\s*=[^=])?", rest)
        if not nxt:
            continue
        # when the first thing the code after the block does with it is assign it
        # again, the store is dead for a reason unrelated to the control flow
        if nxt.group(1):
            continue
        # and it must be a local, not a resolver global or a field
        if "::" in var:
            continue
        out.append((n, var))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    if not args:
        raise SystemExit(__doc__)
    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        text = io.open(path, encoding="utf-8").read()
        found = sites(text)
        if not found:
            continue
        lines = text.split("\n")
        for n, var in found:
            print("%-62s line %-5d dead store to %s" % (os.path.basename(path), n + 1, var))
        if apply_:
            for n, _ in reversed(found):
                del lines[n]
            io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(lines))


if __name__ == "__main__":
    main()
