"""Compare the original's stack frame with ours.

The frame size is the cheapest summary of stage 1 (locals and slots). A frame that is too
small means our build enregistered locals the original kept in memory - the typical cause is
that the original was compiled with global optimisations off for that function, which
`#pragma optimize("g", off)` reproduces while leaving inlining and frame-pointer omission
alone. A frame that is too large means we have locals the original does not, usually because a
helper the original inlined is still a call, or a value is split in two.

usage: frame_size.py [PATH-FILTER] [--min 8]
"""

import argparse
import re

import common

SUB = re.compile(r'^sub esp, (0x[0-9a-f]+|\d+)')


def frame(lines):
    for l in lines[:14]:
        m = SUB.match(l.split('\t')[0].strip())
        if m:
            return int(m.group(1), 16) if m.group(1).startswith('0x') else int(m.group(1))
    return 0


parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--min', type=int, default=8)
args = parser.parse_args()

byaddr = common.load_diff()
rows = []
for f, entry, address in common.entries(byaddr):
    if entry is None or args.filter not in f.replace(chr(92), '/'):
        continue
    if float(entry['matching']) >= 1:
        continue
    orig, recomp = common._asm_lines(entry)
    o, r = frame(orig), frame(recomp)
    if abs(o - r) >= args.min:
        rows.append((o - r, float(entry['matching']) * 100, entry['name'].split('::')[-1], o, r))

rows.sort(key=lambda t: -abs(t[0]))
for d, pct, name, o, r in rows:
    print('  %5.1f  %-54s orig %#-6x ours %#-6x  %+#x' % (pct, name, o, r, d))
print('%d function(s) whose frame differs by %#x or more' % (len(rows), args.min))
