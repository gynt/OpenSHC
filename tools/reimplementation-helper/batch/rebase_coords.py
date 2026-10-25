"""Spell screen coordinates relative to the base local the original actually keeps.

`base_offsets.py` reads, off the original, which coordinate base a function holds in a
register or stack slot and which offsets it then adds to it. An imported Ghidra body has every
coordinate absolute instead - `y + 0x1e7`, `y + 0x23c` where the original has `_base + 0x28`,
`_base + 0x7d` off `y + 0x1bf`. This rewrites those absolute forms into the relative ones and
declares the base local, which is what lets the compiler keep one register for the base the
way the original does.

Only offsets the original actually derives from the base are rewritten; an absolute coordinate
the original also computes absolutely is left alone. A file whose base carries fewer than
--min-uses offsets is skipped, since a base used once is just an addition.

usage:
    rebase_coords.py FILE.cpp... [--apply] [--min-uses 2] [--name _base]
"""

import argparse
import re
import sys

import base_offsets
import orig_body

ROOT_EXPR = {
    'y': 'DAT_MenuHandlerState::instance.y',
    'x': 'DAT_MenuHandlerState::instance.x',
}


def hexes(n):
    """Every spelling of a constant that a Ghidra body might use."""
    return {'%#x' % n, '%d' % n, '%#X' % n}


def local_aliases(text, root_expr):
    """Names of locals that hold a plain copy of the root global."""
    return set(re.findall(r'(\w+)\s*=\s*' + re.escape(root_expr) + r'\s*;', text))


def rewrite(path, min_uses, apply):
    start, end, chains = base_offsets.chains_for(path)
    bases = {}
    for (root, ks), addrs in chains.items():
        if len(ks) >= 2:
            bases.setdefault((root, ks[0]), set()).add(sum(ks[1:]))
    # one base per root - the one carrying the most offsets. A function that keeps both a y
    # and an x base gets both locals.
    best = {}
    for (root, base), offsets in bases.items():
        if len(offsets) < min_uses:
            continue
        if root not in best or len(offsets) > len(best[root][1]):
            best[root] = (base, offsets)
    if not best:
        return None

    text = open(path, newline='').read()
    results = []
    for root in sorted(best):
        base, offsets = best[root]
        name = '_%sBase' % root
        text, hits = rewrite_one(text, root, base, offsets, name)
        results.append((root, base, sorted(offsets), hits, name))
    if apply and any(h for _r, _b, _o, h, _n in results):
        with open(path, 'w', newline='') as f:
            f.write(text)
    return results


def rewrite_one(text, root, base, offsets, name):
    root_expr = ROOT_EXPR[root]
    aliases = local_aliases(text, root_expr) | {root_expr}
    # longest first so `DAT_...instance.y` is not matched inside a longer alias
    alt = '|'.join(re.escape(a) for a in sorted(aliases, key=len, reverse=True))

    hits = 0
    for off in sorted(offsets, reverse=True):
        total = base + off
        for spelling in hexes(total):
            pat = re.compile(r'(?<![\w.])(?:%s)\s*\+\s*%s(?![\w])' % (alt, re.escape(spelling)))
            repl = name if off == 0 else '%s %s %#x' % (name, '+' if off > 0 else '-', abs(off))
            text, n = pat.subn(repl, text)
            hits += n
    if not hits:
        return text, 0

    # declare the base as the first statement of the body, right after the opening brace of
    # the function the `// FUNCTION:` marker names
    m = re.search(r'// FUNCTION: STRONGHOLDCRUSADER [^\n]*\n(?:[^\n]*\n)*?\s*\{\n', text)
    if not m:
        sys.exit('cannot find the function body')
    decl = '%sint %s = %s + %#x;' % (' ' * 8, name, root_expr, base) + chr(10)
    return text[:m.end()] + decl + text[m.end():], hits


parser = argparse.ArgumentParser()
parser.add_argument('files', nargs='+')
parser.add_argument('--apply', action='store_true')
parser.add_argument('--min-uses', type=int, default=2)
a = parser.parse_args()

touched = 0
for f in a.files:
    results = rewrite(f, a.min_uses, a.apply)
    if results is None:
        print('  %-58s no base local' % f.split('/')[-1])
        continue
    for root, base, offsets, hits, name in results:
        print('  %-58s %s+%#x  %d/%d rewritten  (%s)'
              % (f.split('/')[-1], root, base, hits, len(offsets),
                 ' '.join('%+#x' % o for o in offsets)))
    touched += 1 if any(h for _r, _b, _o, h, _n in results) else 0
print('%d file(s) rewritten%s' % (touched, '' if a.apply else ' (dry run)'))
