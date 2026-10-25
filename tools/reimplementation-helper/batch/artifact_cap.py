"""Say which functions are held below 100% only by things the source cannot change.

Three differences are not ours to fix:

* a colour immediate the original also carries, which reccmp annotates as a data symbol
  because the address happens to land inside a resolved global (`push 0xc2f0eb` against
  `push ImageHeaders::instance+616795`);
* `__security_cookie` and `__security_check_cookie`, which the original reads through a
  resolved global and ours through the CRT's own symbol;
* a call whose target reccmp resolves on one side only.

A function whose entire diff is of those kinds is already as close as a .cpp can get. This
prints those, and the points they cost, so the number is in the report rather than chased.

usage: artifact_cap.py [PATH-FILTER]
"""

import re
import sys

import common

ARTIFACT = (
    re.compile(r'^push (0x[0-9a-f]+|StructResolver::|I<[^>]+>::instance\+\d+ \(OFFSET\))'),
    re.compile(r'security_cookie|security_check_cookie'),
)

path_filter = sys.argv[1] if len(sys.argv) > 1 else ''
byaddr = common.load_diff()

capped = []
for f, entry, address in common.entries(byaddr):
    if entry is None or path_filter not in f.replace(chr(92), '/'):
        continue
    pct = float(entry['matching']) * 100
    if pct >= 100:
        continue
    orig, recomp = common._asm_lines(entry)
    import difflib
    sm = difflib.SequenceMatcher(None, [common._normalize(x) for x in orig],
                                 [common._normalize(x) for x in recomp], autojunk=False)
    bad = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            continue
        bad += [orig[i] for i in range(i1, i2)] + [recomp[j] for j in range(j1, j2)]
    if not bad:
        continue
    if all(any(p.search(b.split('\t')[0].strip()) for p in ARTIFACT) for b in bad):
        capped.append((pct, entry['name'].split('::')[-1], len(bad)))

capped.sort()
for pct, name, n in capped:
    print('  %5.1f  %-58s %d artifact line(s)' % (pct, name, n))
print('%d function(s) capped by resolver artifacts alone' % len(capped))
