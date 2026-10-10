"""Write a call out in both arms of an `if`/`else` that only chooses some of its arguments.

Ghidra renders `if (c) { X = k1; } else { X = k2; }` followed by one call that passes `X`,
but that is its *merge* of two calls: the original pushes the argument list inside each arm
and converges only on the shared tail. In
`MenuItemRenderFunction_General_GameOptionsTextButton` both arms push five arguments and
meet at `push 0x4a; call getTextStringInGroupAtOffset` (0x493544), and writing the call out
twice took it from 0.647 to 0.889 on `quick_diff.py`'s ratio with the instruction count
exactly equal (36 = 36), where a ternary at the argument only reached 0.706. reccmp agreed:
`Chat_TauntButtons` 65.5% -> 100%, `GameOptionsTextButton` 70.0% -> 94.4%,
`UnusedChooseGameType_Main` 58.8% -> 90.2%, `NextAndBackHands` 79.5% -> 90.7%.

Tell the two apart in the original: the constants *pushed*
(`push DAT_GMImageSizes+0x3556f`) mean an argument per arm and this rewrite; the constants
moved into a register (`mov edi, DAT_GMImageHeaders+0x9695b` then a conditional second
`mov`, as in `MenuItemRenderFunction_NewEventCondition_Main` at 0x4c0365) mean a default
assignment followed by a one-armed `if` instead.

Rewrites only when both arms are the same run of plain assignments to the same locals, and
every one of those locals is read exactly once afterwards, in the same single statement,
and never written again - so the statements before that one can be hoisted above the `if`
without changing their order. Run `undrop_fallthrough.py` first: the `return;` Ghidra puts
at the end of the second arm hides the shape.

usage:
  split_call_arms.py FILE.cpp... [--apply]
"""

import io
import os
import re
import sys

import common  # noqa: F401

ASSIGN = re.compile(r"^ *(?P<var>[A-Za-z_]\w*) = (?P<val>[^;]+);$")
IF = re.compile(r"^(?P<ind> *)if \((?P<cond>.*)\) \{$")


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


def _statements(lines, n, ind):
    """[(start, end)] line ranges of the statements at column `ind` from n on."""
    out = []
    start = None
    while n < len(lines):
        line = lines[n]
        if line and len(line) - len(line.lstrip()) < ind:
            break
        if start is None:
            start = n
        if line.rstrip().endswith(";"):
            out.append((start, n + 1))
            start = None
        n += 1
    return out


def rewrite(text):
    """-> (text, [variable]) for every arm pair whose call was written out twice."""
    lines = text.split("\n")
    done = []
    i = 0
    while i < len(lines):
        m = IF.match(lines[i])
        if not m:
            i += 1
            continue
        ind, cond = len(m.group("ind")), m.group("cond")
        hot, n = _arm(lines, i + 1, ind)
        if not hot or n >= len(lines) or lines[n] != " " * ind + "} else {":
            i += 1
            continue
        cold, k = _arm(lines, n + 1, ind)
        if (not cold or k >= len(lines) or lines[k] != " " * ind + "}"
                or [v for v, _ in hot] != [v for v, _ in cold] or len(hot) > 3):
            i += 1
            continue
        stmts = _statements(lines, k + 1, ind)
        words = [(v, re.compile(r"\b" + re.escape(v) + r"\b")) for v, _ in hot]
        target = None
        ok = True
        for v, w in words:
            hits = [s for s in stmts if w.search("\n".join(lines[s[0]:s[1]]))]
            if len(hits) != 1 or (target is not None and hits[0] != target):
                ok = False
                break
            target = hits[0]
        if not ok or target is None:
            i += 1
            continue
        body = lines[target[0]:target[1]]
        joined = "\n".join(body)
        if any(re.search(r"\b" + re.escape(v) + r"\s*=[^=]", joined) for v, _ in hot):
            i += 1
            continue
        after = "\n".join(lines[target[1]:])
        if any(w.search(after) for _, w in words):
            i += 1
            continue
        arms = []
        for arm in (hot, cold):
            out = joined
            for (v, w), (_, value) in zip(words, arm):
                out = w.sub(value, out)
            arms.append(["    " + l if l.strip() else l for l in out.split("\n")])
        new = (lines[k + 1:target[0]]
               + [" " * ind + "if (%s) {" % cond]
               + arms[0]
               + [" " * ind + "} else {"]
               + arms[1]
               + [" " * ind + "}"])
        lines = lines[:i] + new + lines[target[1]:]
        done += [v for v, _ in hot]
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
        out, done = rewrite(text)
        if not done:
            continue
        print("%-62s %s" % (os.path.basename(path), ", ".join(done)))
        if apply_:
            io.open(path, "w", encoding="utf-8", newline="\n").write(out)


if __name__ == "__main__":
    main()
