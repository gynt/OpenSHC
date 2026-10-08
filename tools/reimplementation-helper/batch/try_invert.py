"""Hill-climb `diff_triage.py`'s RET flag by inverting a guard-with-return.

    if (COND) { A...; return; }      ->      if (!(COND)) { B...; return; }
    B...                                     A...

The two forms are exactly equivalent - no condition is dropped and no block is
duplicated - but they decide which block MSVC places out of line. The original's `je`
jumps *forward* to its cold block, which is what the compiler emits only when the cold
path is written last; a guard at the top instead inlines it and shifts every following
instruction. That is what `RET` reports, and the inversion was most of the 22.6% -> 54.1%
on the portrait render functions.

Only top-level guards qualify: the `if` has to sit directly in the function body, carry
no `else`, and end in a bare `return;`, so that "everything after it" is a block that can
move inside the inverted arm. Each trial is one `/FA` compile, about six seconds, and
anything that does not score better is reverted.

usage:
  try_invert.py FILE.cpp... [--dry] [--min G]
"""

import io
import os
import sys

import common
import try_returns

MIN_GAIN = 0.005


def guards(lines):
    """Top-level `if (COND) { ...; return; }` guards with code after them.

    Returns (if_line, open_brace_line, body_end_line, tail_end_line) per guard, where
    the tail is everything from after the closing brace to the end of the function body.
    """
    span = try_returns.body_span(lines)
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
    j = start
    while j < end:
        line = lines[j]
        s = line.strip()
        ind = len(line) - len(line.lstrip())
        if ind != base or not s.startswith("if ("):
            j += 1
            continue
        # find the `{` that opens the body and the `}` that closes it
        depth = 0
        opened = False
        close = None
        for m in range(j, end):
            depth += lines[m].count("{") - lines[m].count("}")
            if "{" in lines[m]:
                opened = True
            if opened and depth == 0:
                close = m
                break
        if close is None:
            j += 1
            continue
        nxt = lines[close + 1].strip() if close + 1 < end else ""
        if nxt.startswith("else"):
            j = close + 1
            continue
        # body must end in a bare `return;`
        k = close - 1
        while k > j and not lines[k].strip():
            k -= 1
        if lines[k].strip() != "return;":
            j = close + 1
            continue
        # there has to be a tail worth moving
        tail = [m for m in range(close + 1, end) if lines[m].strip()]
        if len(tail) < 2:
            j = close + 1
            continue
        out.append((j, close, k, end))
        j = close + 1
    return out


FLIP = {"==": "!=", "!=": "==", "<=": ">", ">": "<=", ">=": "<", "<": ">="}


def negate(cond):
    """`!(cond)`, with the double negative folded away for a plain comparison.

    Only a condition that is one top-level comparison is folded; anything carrying a
    top-level `&&` or `||` keeps the explicit `!(...)`, because De Morgan on a mixed
    chain is where a rewrite silently changes the expression.
    """
    depth = 0
    hits = []
    i = 0
    while i < len(cond):
        c = cond[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0:
            if cond.startswith("&&", i) or cond.startswith("||", i):
                return "!(" + cond + ")"
            for op in ("==", "!=", "<=", ">="):
                if cond.startswith(op, i):
                    hits.append((i, op))
                    i += 1
                    break
            else:
                if c in "<>" and not cond.startswith("<<", i) and not cond.startswith(">>", i):
                    hits.append((i, c))
        i += 1
    if len(hits) != 1:
        return "!(" + cond + ")"
    at, op = hits[0]
    return (cond[:at].rstrip() + " " + FLIP[op] + " " + cond[at + len(op):].lstrip()).strip()


def invert(lines, site):
    """Rewrite one guard into its inverted form."""
    if_line, close, ret_line, end = site
    ind = len(lines[if_line]) - len(lines[if_line].lstrip())
    pad = " " * ind

    # the condition text, from `if (` up to the line carrying the opening brace
    head = lines[if_line:close]
    brace = next(i for i, l in enumerate(head) if "{" in l)
    cond_lines = head[:brace + 1]
    cond = " ".join(l.strip() for l in cond_lines)
    cond = cond[cond.index("(") + 1:cond.rindex("{")].rstrip()
    assert cond.endswith(")")
    cond = cond[:-1].strip()

    body = [l for l in lines[if_line + brace + 1:ret_line]]
    tail = lines[close + 1:end]
    while tail and not tail[-1].strip():
        tail.pop()

    extra = 4
    moved = [(" " * extra + l if l.strip() else l) for l in tail]
    need_ret = bool(tail) and tail[-1].strip() != "return;"

    out = lines[:if_line]
    out.append(pad + "if (" + negate(cond) + ") {")
    out.extend(moved)
    if need_ret:
        out.append(pad + " " * extra + "return;")
    out.append(pad + "}")
    out.extend(l[extra:] if l.startswith(" " * extra) else l for l in body)
    out.extend(lines[end:])
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    gain = MIN_GAIN
    if "--min" in sys.argv:
        gain = float(sys.argv[sys.argv.index("--min") + 1])

    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        lines = io.open(path, encoding="utf-8").read().split("\n")
        sites = guards(lines)
        print("##### %s  %d guard(s)" % (os.path.basename(path), len(sites)))
        if dry:
            for s in sites:
                print("   line %d" % (s[0] + 1))
            continue
        if not sites:
            continue

        base = try_returns.ratio_for(path)
        if base is None:
            print("   compile failed, skipped")
            continue
        print("   base %.4f" % base)
        kept = []
        # one guard at a time, bottom-up; re-read so earlier keeps are included
        for s in sorted(sites, key=lambda t: t[0], reverse=True):
            cur = io.open(path, encoding="utf-8").read().split("\n")
            fresh = [g for g in guards(cur) if g[0] == s[0]]
            if not fresh:
                continue
            try:
                trial = invert(cur, fresh[0])
            except (AssertionError, ValueError, StopIteration):
                print("   line %-5d unparsed" % (s[0] + 1))
                continue
            io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(trial))
            r = try_returns.ratio_for(path)
            if r is not None and r > base + gain:
                print("   line %-5d %.4f  KEEP" % (s[0] + 1, r))
                base = r
                kept.append(s[0] + 1)
            else:
                print("   line %-5d %s" % (s[0] + 1, "%.4f" % r if r is not None else "fail"))
                io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(cur))
        print("   final %.4f  kept %s" % (base, kept or "none"))


if __name__ == "__main__":
    main()
