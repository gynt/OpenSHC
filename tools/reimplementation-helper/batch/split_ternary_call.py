"""Turn a ternary inside a call's argument into the two calls the original wrote.

The companion to `split_call_arms.py` for the shape that is already a ternary - either
because Ghidra emitted one or because a previous pass folded an `if`/`else` into it. The
original pushes the argument list inside each arm and converges on the call's tail, so the
ternary has to come back out: `MenuItemRenderFunction_General_GameOptionsTextButton`
reached 0.706 on `quick_diff.py`'s ratio as a ternary and 0.889 as two calls, and reccmp
put it at 94.4%.

Only statements holding exactly one ternary are rewritten, and the condition must be free
of assignments and commas so that evaluating it once per arm is the same as evaluating it
once.

usage:
  split_ternary_call.py FILE.cpp... [--apply]
"""

import io
import os
import re
import sys

import common  # noqa: F401


def _split(text):
    """(cond, a, b, prefix, suffix) for the one ternary in `text`, or None."""
    marks = [m.start() for m in re.finditer(r"\?", text)]
    if len(marks) != 1:
        return None
    q = marks[0]
    # the ternary's opening bracket is the innermost unclosed one before `?`
    depth = 0
    start = None
    for i in range(q - 1, -1, -1):
        if text[i] == ")":
            depth += 1
        elif text[i] == "(":
            if depth == 0:
                start = i
                break
            depth -= 1
    if start is None:
        return None
    depth = 0
    end = None
    for i in range(q, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            if depth == 0:
                end = i
                break
            depth -= 1
    if end is None:
        return None
    cond = text[start + 1:q].strip()
    rest = text[q + 1:end]
    colons = [i for i, c in enumerate(rest)
              if c == ":" and rest[i - 1:i] != ":" and rest[i + 1:i + 2] != ":"]
    if len(colons) != 1:
        return None
    a = rest[:colons[0]].strip()
    b = rest[colons[0] + 1:].strip()
    if not cond or not a or not b:
        return None
    if re.search(r"[^=!<>]=[^=]", cond) or "," in cond:
        return None
    return cond, a, b, text[:start], text[end + 1:]


def rewrite(text):
    """-> (text, n) with every single-ternary statement written out as two calls."""
    lines = text.split("\n")
    done = 0
    i = 0
    while i < len(lines):
        if "?" not in lines[i]:
            i += 1
            continue
        # walk back to the first line of this statement, then forward to its `;`
        s = i
        while s > 0 and not lines[s - 1].rstrip().endswith((";", "{", "}", "*/")):
            s -= 1
        e = i
        while e < len(lines) and not lines[e].rstrip().endswith(";"):
            e += 1
        if e >= len(lines):
            i += 1
            continue
        e += 1
        ind = len(lines[s]) - len(lines[s].lstrip())
        body = "\n".join(lines[s:e])
        # a statement that carries a label cannot be duplicated
        if re.search(r"^ *[A-Za-z_]\w*:", body, re.M):
            i = e
            continue
        if not body.rstrip().endswith(");"):
            i = e
            continue
        parts = _split(body)
        if not parts:
            i = e
            continue
        cond, a, b, pre, post = parts
        arms = []
        for value in (a, b):
            arm = (pre + value + post).split("\n")
            arms.append(["    " + l if l.strip() else l for l in arm])
        lines = (lines[:s]
                 + [" " * ind + "if (%s) {" % cond] + arms[0]
                 + [" " * ind + "} else {"] + arms[1]
                 + [" " * ind + "}"]
                 + lines[e:])
        done += 1
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
        out, n = rewrite(text)
        if not n:
            continue
        print("%-62s %d ternary call(s)" % (os.path.basename(path), n))
        if apply_:
            io.open(path, "w", encoding="utf-8", newline="\n").write(out)


if __name__ == "__main__":
    main()
