"""Remove the locals an imported body declares and never uses.

Ghidra names a slot for every value it saw, including ones whose only use the decompiler then
folded into an expression, so a typical render body opens with a `char* textAddress;` that
nothing ever reads. The compiler eliminates them, which is why this is safe, and says so:
204 C4101 warnings in a full build of the UI selection.

Only a declaration whose name appears exactly once in the file is removed, so a variable used
anywhere - including in a comment - is left alone. The build log supplies the file and the name,
so nothing is removed that the compiler did not already call unused.

An uninitialised local the body *does* read is a different thing and is not touched here: that
is C4700, a real defect, and it needs the original to say what the value should be.

usage: drop_unused_locals.py [--log build-RelWithDebInfo/batch/build.log] [--apply]
"""

import argparse
import re
from collections import defaultdict
from pathlib import Path

WARN = re.compile(r"^(?P<file>[^(]+\.cpp)\((?P<line>\d+)\) : warning C4101: "
                  r"'(?P<name>\w+)' : unreferenced local variable")
DECL = re.compile(r"^\s*[\w:*&\[\]() ]*?\b(?P<name>\w+)\s*(?:\[[^\]]*\])*\s*;\s*$")

parser = argparse.ArgumentParser()
parser.add_argument('--log', default='build-RelWithDebInfo/batch/build.log')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

sites = defaultdict(set)
for line in Path(args.log).read_text(errors='replace').split('\n'):
    m = WARN.match(line.strip())
    if m:
        sites[m.group('file').replace(chr(92), '/')].add((int(m.group('line')), m.group('name')))

removed = files = kept = 0
for f, found in sorted(sites.items()):
    p = Path(f)
    if not p.exists():
        hits = [h for h in Path('src').rglob(Path(f).name)]
        if len(hits) != 1:
            continue
        p = hits[0]
    raw = p.read_bytes().decode()
    nl = chr(13) + chr(10) if chr(13) in raw else chr(10)
    L = raw.split(nl)
    drop = []
    for ln, name in sorted(found, reverse=True):
        i = ln - 1
        if i >= len(L):
            continue
        m = DECL.match(L[i])
        if not m or m.group('name') != name:
            kept += 1
            continue
        if sum(len(re.findall(r'(?<![\w])%s(?![\w])' % re.escape(name), l)) for l in L) != 1:
            kept += 1
            continue
        drop.append(i)
    if drop:
        L = [l for i, l in enumerate(L) if i not in set(drop)]
        removed += len(drop)
        files += 1
        if args.apply:
            p.write_bytes(nl.join(L).encode())
print('%d declaration(s) removed from %d file(s)%s; %d left alone'
      % (removed, files, '' if args.apply else ' (dry run)', kept))
