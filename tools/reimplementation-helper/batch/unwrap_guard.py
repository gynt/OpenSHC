"""Turn a function whose whole body is one `if (COND) { ... }` into an early return.

Ghidra renders a run of early-return guards as one nested condition, because a `return`
carries no data flow and the conjunction is what is left of it. The original wrote

    if (!A) return;  if (!B) return;  body

which MSVC compiles as one epilogue jump per conjunct; the nested form compiles the whole
body one level deeper and costs the prologue's register allocation as well. `epilogue_jumps.py`
says how many of those jumps the original has, so a function with no `return;` at all and
several epilogue jumps is this shape.

This does the outermost level only - `if (COND) { <entire body> }` becomes
`if (!COND) { return; }` plus the body dedented - and leaves splitting `COND` on its `&&`s
to the caller, since that is where a condition can be changed by accident. Run it, read the
diff, then split the condition by hand where the original's jumps say to.

usage:
  unwrap_guard.py FILE.cpp... [--apply]
"""

import io
import os
import sys

import common
import try_invert
import try_returns


def wrapping_guard(lines):
    """(if_line, open_line, close_line) when the body is a single top-level `if`."""
    span = try_returns.body_span(lines)
    if not span:
        return None
    start, end = span
    # skip the leading declaration block: the guard is the function's first statement
    first = None
    for j in range(start, end):
        s = lines[j].strip()
        if not s:
            continue
        if s.startswith("if ("):
            first = j
            break
        if s.endswith(";") and "(" not in s and "=" not in s:
            continue     # a plain declaration
        return None
    if first is None:
        return None
    depth = 0
    opened = False
    close = None
    for m in range(first, end):
        depth += lines[m].count("{") - lines[m].count("}")
        if "{" in lines[m]:
            opened = True
        if opened and depth == 0:
            close = m
            break
    if close is None:
        return None
    if lines[close].strip() != "}":
        return None
    if close + 1 < end and lines[close + 1].strip():
        return None          # something follows the guard, so it is not the whole body
    for j in range(first + 1, close):
        if lines[j].strip().startswith("else"):
            pass
    return first, close


def _balanced(text):
    depth = 0
    for c in text:
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
            if depth < 0:
                return False
    return depth == 0


def conjuncts(cond):
    """Top-level `&&` operands, or None when the condition cannot safely be split.

    A top-level `||` makes De Morgan ambiguous, and an embedded assignment or comma
    operator - Ghidra writes `(x = y, cond)` inside a conjunction - carries a side effect
    whose position relative to the other tests matters, so both are left alone.
    """
    parts = []
    depth = 0
    last = 0
    i = 0
    while i < len(cond):
        c = cond[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0:
            if cond.startswith("||", i):
                return None
            if cond.startswith("&&", i):
                parts.append(cond[last:i])
                last = i + 2
                i += 1
        i += 1
    parts.append(cond[last:])
    parts = [p.strip() for p in parts]
    if len(parts) < 2:
        return None
    for p in parts:
        if "," in p:
            return None
        stripped = p
        for op in ("==", "!=", "<=", ">=", "&&", "||"):
            stripped = stripped.replace(op, "")
        if "=" in stripped:
            return None
    return parts


def flatten(cond):
    """Every top-level `&&` operand, recursively, with redundant brackets dropped."""
    while cond.startswith("(") and cond.endswith(")") and _balanced(cond[1:-1]):
        cond = cond[1:-1].strip()
    parts = conjuncts(cond)
    if parts is None:
        return [cond]
    out = []
    for p in parts:
        out += flatten(p)
    return out


def rewrite(lines):
    found = wrapping_guard(lines)
    if not found:
        return None
    first, close = found
    # the condition spans every line up to the one ending in `{`
    k = first
    while "{" not in lines[k]:
        k += 1
    cond = " ".join(l.strip() for l in lines[first:k + 1])
    cond = cond[cond.index("(") + 1:cond.rindex("{")].rstrip()
    assert cond.endswith(")"), cond
    cond = cond[:-1]       # the `)` that closes the `if`, not one of the condition's own
    ind = " " * (len(lines[first]) - len(lines[first].lstrip()))
    parts = flatten(cond.strip())
    head = []
    for part in parts:
        head += [ind + "if (" + try_invert.negate(part) + ") {",
                 ind + "    return;",
                 ind + "}"]
    body = [l[4:] if l.startswith("    ") else l for l in lines[k + 1:close]]
    return lines[:first] + head + body + lines[close + 1:]


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        lines = io.open(path, encoding="utf-8").read().split("\n")
        new = rewrite(lines)
        name = os.path.basename(path)
        if new is None:
            print("--     %s  (body is not a single guard)" % name)
            continue
        print("unwrap %s" % name)
        if apply_:
            io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(new))


if __name__ == "__main__":
    main()
