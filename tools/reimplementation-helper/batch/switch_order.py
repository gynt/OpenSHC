"""The order a jump-table `switch`'s arms appear in, read from the original's tables.

MSVC emits the arms of a `switch` in source order, so the physical order of the arm
bodies in the binary *is* the order the original's `case` labels were written in. When our
`case` order differs, every arm lands at a different offset and the comparison drifts for
the whole function - on a hundred-arm dispatch that is most of what is left to win.

This reads the dispatch itself rather than guessing: the `cmp` that bounds the index, the
byte table that maps index to slot, and the dword table that maps slot to address. It then
groups the case values that share a target and orders the groups by target address, which
is the order to put them in.

Values are printed relative to the switch expression, so they can be matched against the
`case` labels in the source directly. A group holding several values is one arm with
several labels; `default` is the group whose target is the `ja` destination.

usage:
  switch_order.py FILE.cpp
  switch_order.py 0x4c1770
"""

import io
import os
import re
import struct
import sys

import common  # noqa: F401
import orig_disasm as od


def dispatches(ins):
    """One (base, count, byte_table, dword_table, default) per jump table found."""
    out = []
    for n, i in enumerate(ins):
        if not (i.mnemonic == "jmp" and "dword ptr [" in i.op_str and "*4" in i.op_str):
            continue
        m = re.search(r"\*4 \+ (0x[0-9a-f]+)\]", i.op_str)
        if not m:
            continue
        dword_table = int(m.group(1), 16)
        base = 0
        count = None
        byte_table = None
        default = None
        for j in range(n - 1, max(-1, n - 12), -1):
            t = ins[j].mnemonic + " " + ins[j].op_str
            if byte_table is None:
                mb = re.search(r"movzx \w+, byte ptr \[\w+ \+ (0x[0-9a-f]+)\]", t)
                if mb:
                    byte_table = int(mb.group(1), 16)
            if count is None:
                mc = re.match(r"cmp \w+, (0x[0-9a-f]+|\d+)$", t)
                if mc:
                    count = int(mc.group(1), 16 if mc.group(1).startswith("0x") else 10) + 1
            if ins[j].mnemonic in ("ja", "jae", "jg", "jge"):
                try:
                    default = int(ins[j].op_str, 16)
                except ValueError:
                    pass
            # the index adjustment is the *closest* one walking back from the jump;
            # keep the first hit. Scanning on used to overwrite it with an unrelated
            # `add esp, 8` or `add eax, 0x92` further up, which shifted every value the
            # table reports by a constant and stopped the switch matching at all.
            if base == 0:
                ml = re.match(r"lea \w+, \[\w+ ([-+]) (0x[0-9a-f]+|\d+)\]$", t)
                if ml:
                    v = int(ml.group(2), 16 if ml.group(2).startswith("0x") else 10)
                    # a large displacement is a global's address, not an index adjustment
                    if v < 0x10000:
                        base = v if ml.group(1) == "-" else -v
                ms = re.match(r"sub (?!esp)(\w+), (0x[0-9a-f]+|\d+)$", t)
                if ms:
                    v = int(ms.group(2), 16 if ms.group(2).startswith("0x") else 10)
                    if v < 0x10000:
                        base = v
                ma = re.match(r"add (?!esp)(\w+), (0x[0-9a-f]+|-?\d+)$", t)
                if ma:
                    v = int(ma.group(2), 16 if ma.group(2).startswith("0x") else 10)
                    if v > 0x7FFFFFFF:
                        v -= 0x100000000
                    if abs(v) < 0x10000:
                        base = -v
        if count is None:
            continue
        out.append((base, count, byte_table, dword_table, default))
    # A second dispatch on the same value reuses the register the first one adjusted, so
    # its `lea`/`sub` is far above and the walk-back cannot see it. Where another table in
    # the function has the same bound, that table's base is this one's too - without this
    # the values come out as raw indices and the switch never matches
    # (`MenuItemActionHandler_General_EventSlider`'s second switch, base -10).
    known = {}
    for base, count, bt, dt, default in out:
        if base and count not in known:
            known[count] = base
    return [(base or known.get(count, 0), count, bt, dt, default)
            for base, count, bt, dt, default in out]


def read(va, size):
    o = od.file_off(va)
    d = od._d
    if size == 1:
        return d[o]
    return struct.unpack_from("<I", d, o)[0]


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        raise SystemExit(__doc__)
    for arg in args:
        va = od.address_of(arg)
        ins = od.disasm(va)
        ds = dispatches(ins)
        print("##### 0x%x  (%s)  %d jump table(s)" % (va, os.path.basename(arg), len(ds)))
        for base, count, bt, dt, default in ds:
            groups = {}
            for k in range(count):
                slot = read(bt + k, 1) if bt else k
                target = read(dt + 4 * slot, 4)
                groups.setdefault(target, []).append(k + base)
            print("  index base %d, %d value(s), %d arm(s)%s"
                  % (base, count, len(groups), "" if default is None else ", default -> 0x%x" % default))
            for rank, (target, values) in enumerate(sorted(groups.items()), 1):
                tag = "  (default)" if target == default else ""
                vs = ", ".join(("%d" % v) if abs(v) < 10 else ("0x%x" % v if v >= 0 else "-0x%x" % -v)
                               for v in values)
                print("   %3d  0x%08x  %s%s" % (rank, target, vs, tag))


if __name__ == "__main__":
    main()
