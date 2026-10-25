"""Spell an absolute loop bound as an offset from the global it belongs to.

A walking-pointer loop in an imported body ends on a raw address:

    } while ((int)pCVar1 < 0xec0828);

The original's instruction is `cmp esi, <global>+0x4e0` - a relocation, not an immediate - so
reccmp annotates it with the global's symbol and our bare constant never matches, however
right the arithmetic is. Writing the bound as `(int)&G::instance + 0x4e0` emits the same
relocation and costs nothing at runtime.

The global is the one the loop pointer was initialised from, which is in the source a few
lines up (`pCVar1 = DAT_ARRAY_00ec0348::instance;`); its original address comes from the
`// GLOBAL: STRONGHOLDCRUSADER` marker in its header. A bound that is not above its global's
address, or whose pointer has no visible initialiser, is left alone.

usage:
    symbolize_bounds.py [PATH-FILTER] [--apply]
"""

import argparse
import re
import sys
from pathlib import Path

BOUND = re.compile(r'\(int\)(?P<ptr>[A-Za-z_]\w*)\s*(?P<op><=?|>=?)\s*(?P<addr>0x[0-9a-fA-F]{6,})')
GLOBAL_ADDR = re.compile(r'// GLOBAL: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)')

parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

addresses = {}
for h in Path('src/OpenSHC/Globals').glob('*.hpp'):
    m = GLOBAL_ADDR.search(h.read_text(errors='replace'))
    if m:
        addresses[h.stem] = int(m.group(1), 16)

files = sorted(p for p in Path('src/OpenSHC/UI').rglob('*.cpp')
               if args.filter in str(p).replace(chr(92), '/'))
total = touched = 0
for p in files:
    raw = p.read_bytes().decode()
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    lines = raw.split(nl)
    hits = 0
    for i, line in enumerate(lines):
        m = BOUND.search(line)
        if not m:
            continue
        ptr, addr = m.group('ptr'), int(m.group('addr'), 16)
        # the nearest assignment above that names a global
        src = None
        for j in range(i - 1, max(-1, i - 60), -1):
            a = re.search(r'\b%s\s*=\s*[^;]*?\b(DAT_\w+|INT_\w+|[A-Z]\w*_\w+)::instance' % re.escape(ptr),
                          lines[j])
            if a:
                src = a.group(1)
                break
        if src is None or src not in addresses:
            print('  %-54s:%d  %s -> no global for %s' % (p.name, i + 1, m.group('addr'), ptr))
            continue
        base = addresses[src]
        if addr <= base:
            print('  %-54s:%d  %s is not above %s (%#x)' % (p.name, i + 1, m.group('addr'), src, base))
            continue
        repl = '(int)%s < (int)&%s::instance + %#x' % (ptr, src, addr - base)
        if m.group('op') != '<':
            repl = repl.replace(' < ', ' %s ' % m.group('op'))
        lines[i] = line[:m.start()] + repl + line[m.end():]
        hits += 1
        print('  %-54s:%d  %s -> &%s::instance + %#x' % (p.name, i + 1, m.group('addr'), src, addr - base))
    if hits:
        total += hits
        touched += 1
        if args.apply:
            p.write_bytes(nl.join(lines).encode())
print('%d bound(s) in %d file(s)%s' % (total, touched, '' if args.apply else ' (dry run)'))
