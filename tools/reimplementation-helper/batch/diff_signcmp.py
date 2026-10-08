"""Find comparisons the original makes SIGNED where we make them UNSIGNED.

AGENTS.md records the symptom: "Signed jl/jge vs our unsigned jb/jae on
undefined4/uint fields: compare through (int)".  The cast at the read site is one
fix; the other is that the field's declared type is unsigned when the game treats
it as signed, and fixing the header fixes every site at once.

This pairs the conditional jumps inside one reccmp replacement block, in the same
restricted way diff_types.py does, and reports only blocks where the two sides have
the same number of jumps -- otherwise the pairing invents differences.  Hits are
LEADS: confirm each against `reccmp_report.py diff` before editing a header.

usage: diff_signcmp.py [NAME-SUBSTRING]
"""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

SIGNED = {'jl': '<', 'jge': '>=', 'jg': '>', 'jle': '<='}
UNSIGNED = {'jb': '<', 'jae': '>=', 'ja': '>', 'jbe': '<='}

JMP = re.compile(r'^\s*(j[a-z]+)\b')


def jumps(lines):
    out = []
    for s in lines:
        m = JMP.match(s)
        if m:
            out.append(m.group(1))
    return out


def main():
    want = sys.argv[1] if len(sys.argv) > 1 else ''
    byaddr = common.load_diff()
    total = 0
    for entry in byaddr.values():
        name = entry.get('name', '')
        if want and want not in name:
            continue
        hits = []
        for hunk in entry.get('diff') or []:
            for block in hunk[1]:
                o = [r[1] for r in block.get('orig', [])]
                r = [r[1] for r in block.get('recomp', [])]
                oj, rj = jumps(o), jumps(r)
                if not oj or len(oj) != len(rj):
                    continue
                for a, b in zip(oj, rj):
                    # original signed, ours unsigned, same relational meaning
                    if a in SIGNED and b in UNSIGNED and SIGNED[a] == UNSIGNED[b]:
                        hits.append(('UNSIGNED-OURS', a, b))
                    elif a in UNSIGNED and b in SIGNED and UNSIGNED[a] == SIGNED[b]:
                        hits.append(('SIGNED-OURS', a, b))
        if hits:
            seen, uniq = set(), []
            for h in hits:
                if h not in seen:
                    seen.add(h); uniq.append(h)
            print('### %s %.1f%%' % (name, 100.0 * entry.get('matching', 0)))
            for cls, a, b in uniq[:6]:
                print('  %-14s orig: %-5s ours: %s' % (cls, a, b))
            total += len(uniq)
    print('\n%d paired sign-mismatched comparisons' % total)


main()
