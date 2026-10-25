"""Compare against the constant the original compares against.

Ghidra shifts a comparison's constant by one to make the test strict on the left:
`if (399 < x)` where the original has `cmp eax, 0x190; jb` - that is, `if (400 <= x)` - and
`if (x <= 0x3a)` where the original has `cmp eax, 0x3b; jl`. MSVC takes the source literally,
so both the immediate and the branch condition come out different.

Which spelling a site wants is not a matter of taste: the original's `cmp` immediates settle
it. For every `K < x` and `x <= K` in the source, if K+1 is among them and K is not, the
comparison is rewritten with K+1.

This is the asm-verified form of `unminusone.py`, whose `-1 < x` to `0 <= x` is the same rule
with K = -1.

usage: uncmp_offby1.py [PATH-FILTER] [--apply]
"""

import argparse
import re
from pathlib import Path

import orig_body

CMP = re.compile(r'^cmp\s+[^,]+,\s*(0x[0-9a-f]+|-?\d+)$')
TERM = r'[\w.:()\[\]>-]+'
K_LT = re.compile(r'(?<![\w.])(?P<k>0x[0-9a-fA-F]+|\d+) < (?P<rhs>%s)' % TERM)
LE_K = re.compile(r'(?<![\w.])(?P<lhs>%s) <= (?P<k>0x[0-9a-fA-F]+|\d+)(?![\w.])' % TERM)
LT_K = re.compile(r'(?<![\w.])(?P<lhs>%s) < (?P<k>0x[0-9a-fA-F]+|\d+)(?![\w.])' % TERM)
K_LE = re.compile(r'(?<![\w.])(?P<k>0x[0-9a-fA-F]+|\d+) <= (?P<rhs>%s)' % TERM)


def num(s):
    return int(s, 16) if s.lower().startswith('0x') else int(s)


def fmt(n, like):
    return ('%#x' % n) if like.lower().startswith('0x') else str(n)


parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

image = orig_body.Image()
total = touched = 0
for p in sorted(Path('src/OpenSHC/UI').rglob('*.cpp')):
    if args.filter not in str(p).replace(chr(92), '/'):
        continue
    raw = p.read_bytes().decode()
    if ' < ' not in raw and ' <= ' not in raw:
        continue
    try:
        start = orig_body.address_of(str(p))
        stream = orig_body.disassemble(start, orig_body.find_end(image, start), image)
    except Exception:
        continue
    consts = set()
    for _a, m, ops in stream:
        c = CMP.match('%s %s' % (m, ops))
        if c:
            consts.add(num(c.group(1)))
    if not consts:
        continue
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    L = raw.split(nl)
    hits = []

    def want(k):
        return k + 1 in consts and k not in consts

    def want_down(k):
        return k - 1 in consts and k not in consts

    def fix_lt(mo):
        k = num(mo.group('k'))
        if not want(k):
            return mo.group(0)
        hits.append('%s < -> %s <=' % (mo.group('k'), fmt(k + 1, mo.group('k'))))
        return '%s <= %s' % (fmt(k + 1, mo.group('k')), mo.group('rhs'))

    def fix_le(mo):
        k = num(mo.group('k'))
        if not want(k):
            return mo.group(0)
        hits.append('<= %s -> < %s' % (mo.group('k'), fmt(k + 1, mo.group('k'))))
        return '%s < %s' % (mo.group('lhs'), fmt(k + 1, mo.group('k')))

    def fix_lt_down(mo):
        k = num(mo.group('k'))
        if not want_down(k):
            return mo.group(0)
        hits.append('< %s -> <= %s' % (mo.group('k'), fmt(k - 1, mo.group('k'))))
        return '%s <= %s' % (mo.group('lhs'), fmt(k - 1, mo.group('k')))

    def fix_le_down(mo):
        k = num(mo.group('k'))
        if not want_down(k):
            return mo.group(0)
        hits.append('%s <= -> %s <' % (mo.group('k'), fmt(k - 1, mo.group('k'))))
        return '%s < %s' % (fmt(k - 1, mo.group('k')), mo.group('rhs'))

    for i, line in enumerate(L):
        line = K_LT.sub(fix_lt, LE_K.sub(fix_le, line))
        L[i] = K_LE.sub(fix_le_down, LT_K.sub(fix_lt_down, line))
    if hits:
        total += len(hits)
        touched += 1
        print('  %-50s %s' % (p.name, '; '.join(hits[:3])))
        if args.apply:
            p.write_bytes(nl.join(L).encode())
print('%d comparison(s) in %d file(s)%s' % (total, touched, '' if args.apply else ' (dry run)'))
