"""Compare against zero where the original does, not against -1.

Ghidra prints a non-negative test as `-1 < x`. MSVC takes that literally and emits
`cmp eax, -1; jle`, while the original has the two-byte `test eax, eax; jl` that `0 <= x`
produces - two instructions different in every function that carries one.

Only a `-1` that is the whole left operand is rewritten. `x + -1 < y` is an addition followed
by a comparison, so a `-1` preceded by an arithmetic operator is left alone.

usage: unminusone.py [PATH-FILTER] [--apply]
"""

import argparse
import re
from pathlib import Path

# the -1 must open the comparison: after `(`, a logical operator, a comma, a semicolon or `=`
PAT = re.compile(r'(?P<before>[(&|,;=]\s*|^\s*)-1 (?P<op><=?) ')

parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

files = sorted(p for p in Path('src/OpenSHC/UI').rglob('*.cpp')
               if args.filter in str(p).replace(chr(92), '/'))
total = touched = 0
for p in files:
    raw = p.read_bytes().decode()
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    out = []
    hits = 0
    for line in raw.split(nl):
        new, n = PAT.subn(lambda m: '%s0 %s ' % (m.group('before'),
                                                 '<=' if m.group('op') == '<' else '<'), line)
        hits += n
        out.append(new)
    if hits:
        total += hits
        touched += 1
        print('  %-58s %d' % (p.name, hits))
        if args.apply:
            p.write_bytes(nl.join(out).encode())
print('%d comparison(s) in %d file(s)%s' % (total, touched, '' if args.apply else ' (dry run)'))
