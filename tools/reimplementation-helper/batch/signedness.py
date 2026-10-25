"""Find where our types are signed and the original's are not, or the other way round.

Signedness is not a style question: it picks the instruction. `idiv` against `div`, `sar`
against `shr`, `jge` against `jae`, `movsx` against `movzx` - each pair is the same C
expression over a differently declared field, and each costs one or two instructions plus,
through `cdq`/`xor edx, edx`, a register. The fix is in the header, not the .cpp.

This pairs the opcodes across each function's diff and prints the memory operand involved, so
the field to re-declare can be read off.

usage: signedness.py [PATH-FILTER]
"""

import difflib
import re
import sys

import common

# (original mnemonic, our mnemonic) -> what our side should become
PAIRS = {
    ('idiv', 'div'): 'signed', ('div', 'idiv'): 'unsigned',
    ('sar', 'shr'): 'signed', ('shr', 'sar'): 'unsigned',
    ('movsx', 'movzx'): 'signed', ('movzx', 'movsx'): 'unsigned',
    ('jge', 'jae'): 'signed', ('jl', 'jb'): 'signed',
    ('jle', 'jbe'): 'signed', ('jg', 'ja'): 'signed',
    ('jae', 'jge'): 'unsigned', ('jb', 'jl'): 'unsigned',
    ('jbe', 'jle'): 'unsigned', ('ja', 'jg'): 'unsigned',
}
OPERAND = re.compile(r'\[([^\]]+)\]')

path_filter = sys.argv[1] if len(sys.argv) > 1 else ''
byaddr = common.load_diff()

found = []
for f, entry, address in byaddr and common.entries(byaddr):
    if entry is None or path_filter not in f.replace(chr(92), '/'):
        continue
    if float(entry['matching']) >= 1:
        continue
    orig, recomp = common._asm_lines(entry)
    sm = difflib.SequenceMatcher(None, [common._normalize(x) for x in orig],
                                 [common._normalize(x) for x in recomp], autojunk=False)
    hits = []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'replace':
            continue
        for o in orig[i1:i2]:
            om = o.split('\t')[0].strip().split(' ')[0]
            for r in recomp[j1:j2]:
                rm = r.split('\t')[0].strip().split(' ')[0]
                want = PAIRS.get((om, rm))
                if not want:
                    continue
                operand = OPERAND.search(o) or OPERAND.search(r)
                hits.append('%s/%s %s%s' % (om, rm, want,
                                            ' on [%s]' % operand.group(1) if operand else ''))
    if hits:
        found.append((float(entry['matching']) * 100, entry['name'].split('::')[-1],
                      sorted(set(hits))))

found.sort()
for pct, name, hits in found:
    print('  %5.1f  %-52s %s' % (pct, name, '; '.join(hits[:3])))
print('%d function(s) with a signedness mismatch' % len(found))
