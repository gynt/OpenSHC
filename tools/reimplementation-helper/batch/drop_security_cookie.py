"""Let the compiler emit the /GS cookie instead of writing it in the source.

Ghidra prints the stack-cookie prologue as if it were code:

    uint local_4;
    local_4 = MSVC_SecurityCookie::instance ^ (uint)local_3f4;

That is the compiler's own work. Keeping it in the source gives a dead local, and the
compiler's cookie is a *different* slot from the hand-written one, so neither the frame nor the
prologue can match. RenderBuildingMenu_RenderTowerAndGateHealth has had the line removed and
reads 98%; the functions that still carry it reserve no frame at all against the original's.

Ghidra also splits the buffer the cookie sits above into two declarations, the second of which
is never referenced. Where that is so, the two are merged back into one array.

Only files where the cookie local is used nowhere else are touched.

usage: drop_security_cookie.py [PATH-FILTER] [--apply]
"""

import argparse
import re
from pathlib import Path

ASSIGN = re.compile(r'^(\s*)(\w+) = MSVC_SecurityCookie::instance \^ \(uint\)&?(\w+);\s*$')
ARRAY = re.compile(r'^(\s*)(char|uchar|undefined|byte) (\w+)\[(\d+)\];\s*$')

parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

done = skipped = merged = 0
for p in sorted(Path('src/OpenSHC/UI').rglob('*.cpp')):
    if args.filter not in str(p).replace(chr(92), '/'):
        continue
    raw = p.read_bytes().decode()
    if 'MSVC_SecurityCookie::instance' not in raw:
        continue
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    L = raw.split(nl)
    sites = [(i, m) for i, m in ((i, ASSIGN.match(l)) for i, l in enumerate(L)) if m]
    if len(sites) != 1:
        print('  %-58s %d cookie assignment(s), left alone' % (p.name, len(sites)))
        skipped += 1
        continue
    i, m = sites[0]
    name, buf = m.group(2), m.group(3)
    uses = sum(len(re.findall(r'(?<![\w])%s(?![\w])' % re.escape(name), l)) for l in L)
    if uses != 2:
        print('  %-58s cookie local %s used %d times, left alone' % (p.name, name, uses))
        skipped += 1
        continue
    drop = {i}
    for k, l in enumerate(L):
        if re.match(r'^\s*(uint|undefined4|int)\s+%s;\s*$' % re.escape(name), l):
            drop.add(k)
        if 'Globals/MSVC_SecurityCookie.hpp' in l:
            drop.add(k)
    # Ghidra's split buffer: the declaration right after `buf` is an array nothing references
    this_merged = False
    ai = next((k for k, l in enumerate(L) if ARRAY.match(l) and ARRAY.match(l).group(3) == buf), None)
    if ai is not None:
        am = ARRAY.match(L[ai])
        nm = ARRAY.match(L[ai + 1]) if ai + 1 < len(L) else None
        if nm and nm.group(2) == am.group(2):
            second = nm.group(3)
            if sum(len(re.findall(r'(?<![\w])%s(?![\w])' % second, l)) for l in L) == 1:
                L[ai] = '%s%s %s[%d];' % (am.group(1), am.group(2), buf,
                                          int(am.group(4)) + int(nm.group(4)))
                drop.add(ai + 1)
                merged += 1
                this_merged = True
    L = [l for k, l in enumerate(L) if k not in drop]
    done += 1
    print('  %-58s dropped %d line(s)%s' % (p.name, len(drop), ', buffer merged' if this_merged else ''))
    if args.apply:
        p.write_bytes(nl.join(L).encode())
print('%d file(s), %d left alone%s' % (done, skipped, '' if args.apply else ' (dry run)'))
