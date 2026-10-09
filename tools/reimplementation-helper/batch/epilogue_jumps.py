"""Every conditional jump in one original function that lands on a `ret` block.

An empty `if (cond) {}` in our source is the `return` Ghidra dropped only when the
original's conditional jump goes to a block that just pops and returns. `try_returns.py`
and `try_empty_returns.py` decide such a site by score, which is a proxy: a guard that
should branch somewhere else compiles just as happily and usually, but not always, scores
worse. This answers the question from the binary instead, so a whole file's sites can be
confirmed before anything is compiled.

Read it together with the source: the jumps come out in address order, which is the order
the guards appear in, and one line per site is normally enough to pair them up. When our
source has fewer `return;`s than this prints jumps, the difference is missing control flow
rather than a style question - across `UI::MenuItems` that gap was worth 10-30 points per
function.

usage:
  epilogue_jumps.py FILE.cpp...
  epilogue_jumps.py 0x4476b0
"""

import os
import sys

import common  # noqa: F401  (chdir to the repository root)
import orig_disasm as od


def epilogue_blocks(ins):
    """Addresses belonging to a block that only pops and returns."""
    out = set()
    for n, i in enumerate(ins):
        if i.mnemonic != "ret":
            continue
        k = n
        while k > 0 and ins[k - 1].mnemonic in ("pop", "leave"):
            k -= 1
        for j in range(k, n + 1):
            out.add(ins[j].address)
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        raise SystemExit(__doc__)
    for arg in args:
        va = od.address_of(arg)
        ins = od.disasm(va)
        eps = epilogue_blocks(ins)
        print("##### 0x%x  (%s)" % (va, os.path.basename(arg)))
        for i in ins:
            if not i.mnemonic.startswith("j") or i.mnemonic == "jmp":
                continue
            try:
                t = int(i.op_str, 16)
            except ValueError:
                continue
            if t in eps:
                print("  %08x  %-4s -> 0x%x  RETURNS" % (i.address, i.mnemonic, t))


if __name__ == "__main__":
    main()
