"""Keep the frame pointer where the original keeps one.

The original builds an ebp frame in a great many functions - `push ebp; mov ebp, esp; sub esp,
N` - while our build omits it and addresses locals off esp. That changes the prologue, every
local reference and the epilogue, which is why a function can read 6% while being structurally
right. `#pragma optimize("y", off)` turns frame-pointer omission off for one function and
leaves every other optimisation on.

The opposite pragma, `optimize("", off)`, disables optimisation outright: it reloads `this`
from a stack slot for every member access and matches nothing. Four files carried it.

A function is reported when the original's prologue has `mov ebp, esp` and ours does not.

usage: frame_pointer.py [PATH-FILTER] [--apply]
"""

import argparse
import re
import sys

import common

PRAGMA_OFF = '#pragma optimize("y", off)'
PRAGMA_ON = '#pragma optimize("y", on)'
MARKER = re.compile(r'^(\s*)// FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)')


def has_frame(lines):
    return any('mov ebp, esp' in l for l in lines[:6])


parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

byaddr = common.load_diff()
wanted = {}
for f, entry, address in common.entries(byaddr):
    if entry is None or args.filter not in f.replace(chr(92), '/'):
        continue
    if float(entry['matching']) >= 1:
        continue
    orig, recomp = common._asm_lines(entry)
    if has_frame(orig) and not has_frame(recomp):
        wanted.setdefault(f, []).append((int(address, 16), float(entry['matching']) * 100,
                                         entry['name'].split('::')[-1]))

touched = 0
for f, funcs in sorted(wanted.items()):
    p = common.source_path(f) if hasattr(common, 'source_path') else None
    import pathlib
    p = pathlib.Path(f) if pathlib.Path(f).exists() else pathlib.Path('src') / f
    raw = p.read_bytes().decode()
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    L = raw.split(nl)
    if any(PRAGMA_OFF in l for l in L):
        continue
    addrs = {a for a, _pct, _n in funcs}
    # bottom-up so the inserted lines never move a marker we have not handled yet
    sites = [i for i, l in enumerate(L)
             if MARKER.match(l) and int(MARKER.match(l).group(2), 16) in addrs]
    for i in reversed(sites):
        # the body opens at the first `{` at or after the signature and closes when the
        # brace count returns to zero
        j = i + 1
        while j < len(L) and '{' not in L[j]:
            j += 1
        depth = 0
        end = j
        for k in range(j, len(L)):
            depth += L[k].count('{') - L[k].count('}')
            if depth == 0:
                end = k
                break
        L.insert(end + 1, PRAGMA_ON)
        L.insert(i + 1, PRAGMA_OFF)
    if sites:
        touched += 1
        print('  %-58s %s' % (p.name, ' '.join('%s %.1f%%' % (n, pct) for _a, pct, n in funcs)))
        if args.apply:
            p.write_bytes(nl.join(L).encode())
print('%d file(s)%s' % (touched, '' if args.apply else ' (dry run)'))
