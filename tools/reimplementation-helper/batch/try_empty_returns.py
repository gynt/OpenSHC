"""Fill every empty `if (cond) {}` body in a function with `return;`, all at once.

An empty `if` body in Ghidra's output means the block held nothing that carries data
flow, and in the original that is almost always a `return` - the `jne` goes straight to
the function's shared `pop/ret` epilogue. Three such sites were confirmed against the
binary in `MenuItemRenderFunction_VideoOptions_Main` alone (`L15` there *is* the
epilogue), and our build emits nothing at all for the guard, so the whole branch is
missing from the comparison.

`try_returns.py` already offers these sites, but it accepts them one at a time, and a
single one often does not move the score: VideoOptions needed all three before the match
shifted, because every intermediate state still had the control flow wrong somewhere.
This tries the whole set together, then - if that does not pay - each site on its own, so
the combination is not missed.

A `return` here is only right when the original jumped to the epilogue; a jump to some
other block compiles just as happily and is wrong. The score is evidence, not proof:
filling a guard that should branch elsewhere moves every following block and normally
scores worse, which is what the revert catches, but confirm a large winner against
`orig_disasm.py` before trusting it.

usage:
  try_empty_returns.py FILE.cpp... [--dry] [--min G]
"""

import io
import os
import sys

import common
import try_returns

MIN_GAIN = 0.005


def sites(lines):
    """Lines holding an `if (...) {}` with an empty body, inside the function body."""
    span = try_returns.body_span(lines)
    if not span:
        return []
    start, end = span
    out = []
    for j in range(start, end):
        s = lines[j].rstrip()
        if not s.endswith("{}"):
            continue
        head = " ".join(lines[max(start, j - 3):j + 1])
        if "if" not in head:
            continue
        out.append(j)
    return out


def fill(lines, js):
    """Replace each `... {}` at the given lines with a block holding `return;`."""
    out = list(lines)
    for j in sorted(js, reverse=True):
        ind = len(out[j]) - len(out[j].lstrip())
        out[j:j + 1] = [
            out[j].rstrip()[:-2] + "{",
            " " * (ind + 4) + "return;",
            " " * ind + "}",
        ]
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    gain = MIN_GAIN
    if "--min" in sys.argv:
        gain = float(sys.argv[sys.argv.index("--min") + 1])

    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        original = io.open(path, encoding="utf-8").read()
        lines = original.split("\n")
        js = sites(lines)
        print("##### %s  %d empty site(s)" % (os.path.basename(path), len(js)))
        if dry or not js:
            for j in js:
                print("   line %d" % (j + 1))
            continue

        base = try_returns.ratio_for(path)
        if base is None:
            print("   compile failed, skipped")
            continue
        print("   base %.4f" % base)

        def write(ls):
            io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(ls))

        # all of them together first
        write(fill(lines, js))
        r = try_returns.ratio_for(path)
        if r is not None and r > base + gain:
            print("   all %-2d      %.4f  KEEP" % (len(js), r))
            continue
        print("   all %-2d      %s" % (len(js), "%.4f" % r if r is not None else "fail"))

        # otherwise greedily, one site at a time
        write(lines)
        best = base
        kept = []
        for j in sorted(js, reverse=True):
            cur = io.open(path, encoding="utf-8").read().split("\n")
            fresh = sites(cur)
            # the same site, located again after earlier edits shifted the file
            cand = [x for x in fresh if cur[x].strip() == lines[j].strip()]
            if not cand:
                continue
            write(fill(cur, [cand[-1]]))
            r = try_returns.ratio_for(path)
            if r is not None and r > best + gain:
                print("   line %-5d %.4f  KEEP" % (j + 1, r))
                best = r
                kept.append(j + 1)
            else:
                print("   line %-5d %s" % (j + 1, "%.4f" % r if r is not None else "fail"))
                write(cur)
        print("   final %.4f  kept %s" % (best, kept or "none"))


if __name__ == "__main__":
    main()
