"""Classify the `if (...) {}` sites, where an imported body lost the statement a guard held.

Ghidra prints a guard whose body it could not place as an empty `if`. The condition then
evaluates to nothing, the compiler drops it, and whatever it used to protect now runs
unconditionally - a behaviour difference, not only a matching one.

What the guard held is usually readable from what follows it in the source:

  break / continue / return  the next statement is that jump, and the guard belongs on it. The
                             imported body jumps unconditionally, so this is the shape that
                             actually changes behaviour.
  tail                       the guard is the last thing before the function's closing brace,
                             so it held a `return` and the body below it is already gone.
  wraps                      statements follow inside the same block; the guard may wrap some
                             or all of them, which the original's branch target decides.
  nested                     the next line opens another `if`, so the two conditions were one.

Only the first kind is mechanically safe to merge, and --apply does only that. The rest are
listed for a human with the disassembly.

usage: empty_guards.py [PATH-FILTER] [--apply]
"""

import argparse
import re
from collections import Counter
from pathlib import Path

EMPTY_IF = re.compile(r'^(?P<indent>\s*)(?P<head>(?:\}\s*else\s+)?if\s*\(.*\)\s*)\{\}\s*$')
JUMP = re.compile(r'^\s*(break|continue|return)\s*;\s*$')
OPENS_IF = re.compile(r'^\s*(?:\}\s*else\s+)?if\s*\(')

parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

kinds = Counter()
merged = 0
files = 0
for p in sorted(Path('src/OpenSHC/UI').rglob('*.cpp')):
    if args.filter not in str(p).replace(chr(92), '/'):
        continue
    raw = p.read_bytes().decode()
    if ') {}' not in raw:
        continue
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    L = raw.split(nl)
    hits = [i for i, l in enumerate(L) if EMPTY_IF.match(l)]
    if not hits:
        continue
    touched = 0
    for i in reversed(hits):
        m = EMPTY_IF.match(L[i])
        # the next line that is not blank or a comment
        j = i + 1
        while j < len(L) and (not L[j].strip() or L[j].lstrip().startswith(('//', '/*', '*'))):
            j += 1
        nxt = L[j] if j < len(L) else ''
        jm = JUMP.match(nxt)
        if jm:
            kinds['%s' % jm.group(1)] += 1
            print('  %-54s:%-5d %s -> %s' % (p.name, i + 1, m.group('head').strip(), jm.group(1)))
            L[i] = '%s%s{' % (m.group('indent'), m.group('head'))
            L[j] = '%s    %s' % (m.group('indent'), nxt.strip())
            L.insert(j + 1, '%s}' % m.group('indent'))
            touched += 1
            merged += 1
        elif nxt.strip() in ('}', '') or j >= len(L):
            kinds['tail'] += 1
        elif OPENS_IF.match(nxt):
            kinds['nested'] += 1
        else:
            kinds['wraps'] += 1
    if touched:
        files += 1
        if args.apply:
            p.write_bytes(nl.join(L).encode())

print()
for k, n in kinds.most_common():
    print('  %-10s %d' % (k, n))
print('%d guard(s) merged onto their jump in %d file(s)%s; %d left for a human'
      % (merged, files, '' if args.apply else ' (dry run)',
         sum(n for k, n in kinds.items() if k not in ('break', 'continue', 'return'))))
