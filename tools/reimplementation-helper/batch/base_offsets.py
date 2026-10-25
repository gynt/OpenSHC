"""Report the base-plus-offset locals the original builds out of a global.

A menu render function almost never computes a screen coordinate from scratch twice. The
original loads the menu y once, keeps `y + 0x1bf` in a register or stack slot, and spells every
later coordinate as an offset off *that*: `lea eax, [ebp + 0x28]`, `add ebp, 0x19`. An imported
Ghidra body instead writes every coordinate absolutely - `y + 0x1e7`, `y + 0x23c`, `y + 0x1d8`
- which costs one `lea` per use and, worse, a different register assignment throughout.

This walks the original's instruction stream with a tiny symbolic state per register (and per
stack slot), rooted at the globals named with --root, and prints every derived value as
`<root> + <chain>`. A chain of more than one constant is the lever: the first constant is a
local the source must have, and the rest are the offsets to spell relative to it.

usage:
    base_offsets.py FILE.cpp [--root 0xf2b3a4=y] [--root 0xf2b3a0=x]

Defaults to the two DAT_MenuHandlerState coordinates, which is what the render families use.
"""

import re
import sys
from collections import OrderedDict

import orig_body

DEFAULT_ROOTS = {0xf2b3a4: 'y', 0xf2b3a0: 'x'}

REGS = ('eax', 'ebx', 'ecx', 'edx', 'esi', 'edi', 'ebp')
MEM = re.compile(r'^\[(?:dword ptr )?(.*)\]$')
GLOBAL = re.compile(r'^(?:dword ptr )?\[(0x[0-9a-f]+)\]$')
LEA_RK = re.compile(r'^\[(\w+) ([+-]) (0x[0-9a-f]+|\d+)\]$')
SLOT = re.compile(r'^\[esp(?: \+ (0x[0-9a-f]+|\d+))?\]$')


def num(s):
    return int(s, 16) if s.startswith('0x') else int(s)


def chains_for(path, roots=None, image=None):
    """(start, end, OrderedDict[(root, constants)] -> [addresses]) for one source file."""
    roots = roots or DEFAULT_ROOTS
    image = image or orig_body.Image()
    start = orig_body.address_of(path)
    end = orig_body.find_end(image, start)
    stream = orig_body.disassemble(start, end, image)

    # state[reg] = (root_name, (k1, k2, ...)) ; stack slots keyed by their esp offset are
    # deliberately approximate - esp moves on every push - so a slot only carries a value
    # forward until the next push/pop, which is enough for the locals we are after.
    state = {}
    slots = {}
    # chains[(root, tuple_of_constants)] = [addresses]
    chains = OrderedDict()

    def record(val, addr):
        if val is None:
            return
        root, ks = val
        if ks:
            chains.setdefault((root, ks), []).append(addr)

    for addr, mnemonic, ops in stream:
        dst, _, src = ops.partition(', ')
        if mnemonic == 'mov' and dst in REGS:
            g = GLOBAL.match(src)
            if g and num(g.group(1)) in roots:
                state[dst] = (roots[num(g.group(1))], ())
                continue
            s = SLOT.match(src)
            if s:
                state[dst] = slots.get(num(s.group(1)) if s.group(1) else 0)
                continue
            state[dst] = state.get(src) if src in REGS else None
            continue
        if mnemonic == 'mov' and SLOT.match(dst):
            key = num(SLOT.match(dst).group(1) or '0')
            slots[key] = state.get(src) if src in REGS else None
            continue
        if mnemonic == 'lea' and dst in REGS:
            m = LEA_RK.match(src)
            if m and m.group(1) in REGS:
                base = state.get(m.group(1))
                if base:
                    k = num(m.group(3)) * (1 if m.group(2) == '+' else -1)
                    val = (base[0], base[1] + (k,))
                    state[dst] = val
                    record(val, addr)
                    continue
            state[dst] = None
            continue
        if mnemonic == 'add' and dst in REGS and (src.startswith('0x') or src.isdigit()):
            base = state.get(dst)
            if base:
                val = (base[0], base[1] + (num(src),))
                state[dst] = val
                record(val, addr)
            continue
        if mnemonic in ('push', 'pop', 'call'):
            # esp moves, so stack-slot keys stop meaning anything; registers survive a push
            slots.clear()
            if mnemonic == 'call':
                for r in ('eax', 'ecx', 'edx'):
                    state[r] = None
            continue
        if dst in REGS:
            state[dst] = None

    return start, end, chains


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    if not args:
        sys.exit(__doc__)
    roots = {}
    argv = sys.argv[1:]
    for i, a in enumerate(argv):
        if a == '--root' and i + 1 < len(argv):
            addr, _, name = argv[i + 1].partition('=')
            roots[int(addr, 16)] = name or addr
    start, end, chains = chains_for(args[0], roots or None)
    print('# %s   %#x .. %#x' % (args[0], start, end))
    for (root, ks), addrs in chains.items():
        total = sum(ks)
        print('%-5s %-28s = %s + %#x   (%s)'
              % (root,
                 ' '.join('%+#x' % k for k in ks),
                 root, total,
                 ' '.join('%#x' % a for a in addrs)))


if __name__ == '__main__':
    main()
