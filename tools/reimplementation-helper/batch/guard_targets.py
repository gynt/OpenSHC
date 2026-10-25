"""Say what statement each `if (...) {}` guard used to hold, from the original's branch target.

An imported body prints a guard whose body Ghidra could not place as an empty `if`. The
condition then compiles to nothing and whatever it protected runs unconditionally. What it held
is not readable from the source - `if (10 <= i) {}` as the last line of a loop is a `break`, the
same line at the top of a function is a `return` - but it is readable from the original: find
the conditional jump that tests the same thing and look at where it goes.

The pairing is by address. A condition naming `DAT_X::instance.a.b` resolves to the global's
address from its `// GLOBAL:` marker plus the member offsets from the generated headers, and the
original is searched for a `cmp`/`test`/`mov` on that address followed within a few
instructions by a conditional jump. The jump's target then says what the guard held:

  return    it lands anywhere in the run of pops that ends in the last `ret`
  break     it lands just past a backward jump, i.e. immediately after a loop
  continue  it lands backwards, on the loop head
  wraps N   it lands forward inside the body, so the guard wrapped N instructions

A site whose condition names no resolvable global, or whose address the original never tests,
is reported as unpaired rather than guessed at.

usage: guard_targets.py [PATH-FILTER]
"""

import argparse
import re
from collections import Counter
from pathlib import Path

import orig_body

EMPTY_IF = re.compile(r'^(?P<indent>\s*)(?:\}\s*else\s+)?if\s*\((?P<cond>.*)\)\s*\{\}\s*$')
PATH = re.compile(r'\b(DAT_\w+|INT_\w+|BOOL_\w+|TIME_\w+|COL_\w+)::instance((?:\.\w+)*)')
GLOBAL_ADDR = re.compile(r'// GLOBAL: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)')
RESOLVER = re.compile(r'MACRO_STRUCT_RESOLVER\(\s*([\w:]+?)\s*(?:\[[^\]]*\])?\s*,')
FIELD = re.compile(r'^\s*(?P<type>[\w:]+)\s+(?P<name>\w+)(?P<dims>(?:\[\d+\])*)\s*;'
                   r'\s*//\s*(?P<off>0x[0-9A-Fa-f]+)\s+length:\s*(?P<len>\d+)')
COND_JUMP = re.compile(r'^j(?!mp)\w+$')
TESTS = ('cmp', 'test', 'mov', 'movsx', 'movzx')

globals_map = {}
for h in Path('src/OpenSHC/Globals').glob('*.hpp'):
    text = h.read_text(errors='replace')
    a = GLOBAL_ADDR.search(text)
    t = RESOLVER.search(text)
    if a:
        globals_map[h.stem] = (int(a.group(1), 16), t.group(1) if t else None)

_fields = {}


def header_for(type_name):
    parts = type_name.split('::')
    p = Path('src').joinpath(*parts).with_suffix('.hpp')
    if p.exists():
        return p
    hits = list(Path('src').rglob(parts[-1] + '.hpp'))
    return hits[0] if len(hits) == 1 else None


def fields_of(path):
    if path not in _fields:
        out = {}
        for line in path.read_text(errors='replace').split('\n'):
            m = FIELD.match(line)
            if m:
                out[m.group('name')] = (int(m.group('off'), 16), m.group('type'))
        _fields[path] = out
    return _fields[path]


def resolve(global_name, members):
    """The original address of DAT_X::instance.a.b, or None."""
    if global_name not in globals_map:
        return None
    addr, type_name = globals_map[global_name]
    for name in [m for m in members.split('.') if m]:
        if not type_name:
            return None
        h = header_for(type_name)
        if h is None or name not in fields_of(h):
            return None
        off, type_name = fields_of(h)[name]
        addr += off
    return addr


def epilogue_start(stream):
    """The first instruction of the run of pops that ends in the last `ret`.

    Landing anywhere in that run is a return. Comparing against the `ret` itself is not
    enough: renderCurrentlyDisplayedTextConstructionCost's three guards all jump to the
    `pop esi` five bytes above it, which read as a forward wrap.
    """
    addrs = [a for a, _m, _o in stream]
    last_ret = max((a for a, m, _o in stream if m == 'ret'), default=addrs[-1])
    k = addrs.index(last_ret)
    while k > 0 and stream[k - 1][1] in ('pop', 'leave') or (
            k > 0 and stream[k - 1][1] in ('add', 'mov') and 'esp' in stream[k - 1][2]):
        k -= 1
    return addrs[k]


def classify(stream, jump_index, target):
    """What the guard held, from where its jump lands."""
    addrs = [a for a, _m, _o in stream]
    if target >= epilogue_start(stream):
        return 'return'
    if target <= addrs[jump_index]:
        return 'continue'
    try:
        k = addrs.index(target)
    except ValueError:
        return 'return'          # inside the epilogue, between instructions
    prev = stream[k - 1] if k else None
    if prev and prev[1] in ('jmp', 'je', 'jne', 'jl', 'jle', 'jg', 'jge', 'jb', 'jbe', 'ja', 'jae'):
        tgt = prev[2]
        if tgt.startswith('0x') and int(tgt, 16) < prev[0]:
            return 'break'
    if k > jump_index:
        return 'wraps %d' % (k - jump_index - 1)
    return 'wraps ?'


parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
args = parser.parse_args()

image = orig_body.Image()
kinds = Counter()
for p in sorted(Path('src/OpenSHC/UI').rglob('*.cpp')):
    if args.filter not in str(p).replace(chr(92), '/'):
        continue
    raw = p.read_bytes().decode()
    if ') {}' not in raw:
        continue
    L = raw.split(chr(13) + chr(10) if chr(13) in raw else chr(10))
    sites = [(i, m) for i, m in ((i, EMPTY_IF.match(l)) for i, l in enumerate(L)) if m]
    if not sites:
        continue
    try:
        start = orig_body.address_of(str(p))
        stream = orig_body.disassemble(start, orig_body.find_end(image, start), image)
    except Exception as e:
        print('  %-50s cannot disassemble: %s' % (p.name, e))
        continue
    for i, m in sites:
        cond = m.group('cond')
        addrs = set()
        for g, members in PATH.findall(cond):
            a = resolve(g, members)
            if a is not None:
                addrs.add(a)
        # Every site in the original that *reads* one of those addresses and then branches.
        # A store to the address is not the test - taking it paired BuildEnemyPlayerList's
        # `6 <= index` guard to the loop's entry test and called a break a 21-instruction wrap.
        found = []
        for k, (a, mn, ops) in enumerate(stream):
            if not any('%#x' % x in ops for x in addrs):
                continue
            dst, _, src = ops.partition(', ')
            if mn in ('mov', 'movsx', 'movzx') and not any('%#x' % x in src for x in addrs):
                continue
            if mn not in TESTS:
                continue
            # the next conditional jump after the read, with nothing jumping in between;
            # five instructions was one short of BuildEnemyPlayerList's `cmp eax, 6; jge`
            for j in range(k, min(k + 12, len(stream))):
                if COND_JUMP.match(stream[j][1]) and stream[j][2].startswith('0x'):
                    found.append(classify(stream, j, int(stream[j][2], 16)))
                    break
        held = None
        if found:
            # one classification for every read is the clear case; otherwise say what was seen
            held = found[0] if len(set(found)) == 1 else '|'.join(sorted(set(found)))
        kinds[held or ('unpaired' if addrs else 'no global')] += 1
        print('  %-46s:%-5d %-22s %s' % (p.name, i + 1, held or
                                         ('unpaired' if addrs else 'no global in condition'),
                                         cond.strip()[:58]))
print()
for k, n in kinds.most_common():
    print('  %-12s %d' % (k.split(' ')[0] if k.startswith('wraps') else k, n))
