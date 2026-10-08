"""Find pointer walks that advance by a MEMBER offset rather than by sizeof(struct).

    pIVar9 = (InGameEventExtra*)&pIVar9->conditionTwoIsTrue;

re-casts a pointer to its own struct type but aims it at a non-first member, so it
steps by that member's offset. Ghidra emits this when the real object is a flat array
it has split into named fields. arrayscan.py cannot see these: there is no constant
index to compare against a declared length.
"""
import io, os, re, sys
from collections import defaultdict

ROOT = 'src/OpenSHC'
PAT = re.compile(
    r'(\b[A-Za-z_][A-Za-z0-9_]*)\s*=\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*\*\s*\)\s*'
    r'&\s*\1\s*->\s*([A-Za-z_][A-Za-z0-9_]*)')
hits = defaultdict(list)
for dp, _, fns in os.walk(ROOT):
    for fn in fns:
        if not fn.endswith('.cpp'):
            continue
        fp = os.path.join(dp, fn)
        t = io.open(fp, encoding='utf-8', errors='replace').read()
        for m in PAT.finditer(t):
            var, typ, member = m.groups()
            ln = t.count(chr(10), 0, m.start()) + 1
            hits[(typ, member)].append(fp.replace(chr(92), '/') + ':' + str(ln))

if not hits:
    print('no member-offset pointer walks found')
    sys.exit(0)
print('%-32s %-28s %s' % ('struct', 'member walked to', 'sites'))
for (typ, member), sites in sorted(hits.items(), key=lambda kv: -len(kv[1])):
    print('%-32s %-28s %-3d %s' % (typ, member, len(sites), sites[0]))
