"""Re-declare the struct fields whose signedness the original's instructions contradict.

A narrow-width field tells you its own signedness every time the original reads it: `movsx` for
a signed one, `movzx` for an unsigned one. That is a statement about the game, not about our
build, so this judges the declaration against the original alone and never compares the two
sides. Pairing instructions across a diff pairs coincidences as readily as counterparts, and
our own instruction only reports what our source currently says - where that reaches the right
instruction through a cast at the use site, the declaration is still wrong for every other
reader, and this still finds it.

A field the original reads both ways is left alone and reported: the source casts somewhere,
and which declaration it wants cannot be settled from the instructions.

The member is found by offset: the generated headers carry one on every member
(`ushort GfxLayer[80400]; // 0x00052480 length: 160800`), so the member containing an offset can
be looked up directly, and a member whose own type has a header is recursed into - through an
array of structs by taking the offset modulo the element size. The member's width is checked
against the operand's `byte`/`word ptr` before anything is rewritten.

usage: signed_fields.py [PATH-FILTER] [--apply]
"""

import argparse
import re
from collections import defaultdict
from pathlib import Path

import common

SIGNED = {'uint': 'int', 'ushort': 'short', 'uchar': 'char', 'byte': 'char',
          'undefined4': 'int', 'undefined2': 'short', 'undefined1': 'char',
          'dword': 'int', 'word': 'short', 'DWORD': 'int'}
UNSIGNED = {'int': 'uint', 'short': 'ushort', 'char': 'uchar',
            'undefined4': 'uint', 'undefined2': 'ushort', 'undefined1': 'uchar'}
WIDTH = {1: ('char', 'uchar', 'byte', 'undefined1'),
         2: ('short', 'ushort', 'word', 'undefined2'),
         4: ('int', 'uint', 'dword', 'undefined4', 'DWORD')}
SCALARS = sum(WIDTH.values(), ())

EXTEND = re.compile(r'^(movsx|movzx)\b.*\b(byte|word) ptr\b')
GLOBAL = re.compile(r'I<([\w:]+)>::instance(?:\+(\d+))?'
                    r'|StructResolver::Instance<([\w:]+),\d+>::instance(?:\+(\d+))?')
FIELD = re.compile(r'^(?P<indent>\s*)(?P<type>[\w:]+)\s+(?P<name>\w+)'
                   r'(?P<dims>(?:\[\d+\])*)\s*;\s*//\s*(?P<off>0x[0-9A-Fa-f]+)'
                   r'\s+length:\s*(?P<len>\d+)')
PTR_WIDTH = {'byte': 1, 'word': 2}


def header_for(type_name):
    """src/OpenSHC/Map/TileMapState.hpp for OpenSHC::Map::TileMapState."""
    parts = type_name.split('::')
    p = Path('src').joinpath(*parts).with_suffix('.hpp')
    if p.exists():
        return p
    hits = list(Path('src').rglob(parts[-1] + '.hpp'))
    return hits[0] if len(hits) == 1 else None


_fields = {}


def fields_of(path):
    if path not in _fields:
        _fields[path] = [(i, m) for i, m in
                         ((i, FIELD.match(l)) for i, l in
                          enumerate(path.read_text(errors='replace').split('\n'))) if m]
    return _fields[path]


def locate(type_name, offset, depth=0):
    """(header, line index, match, element size) for the member at `offset`."""
    path = header_for(type_name)
    if path is None or depth > 4:
        return None
    best = None
    for i, m in fields_of(path):
        start = int(m.group('off'), 16)
        if start <= offset < start + int(m.group('len')):
            best = (i, m, start)
    if best is None:
        return None
    i, m, start = best
    inner = offset - start
    count = 1
    for d in re.findall(r'\d+', m.group('dims')):
        count *= int(d)
    elem = int(m.group('len')) // count if count else int(m.group('len'))
    ftype = m.group('type')
    if ftype not in SCALARS and header_for(ftype):
        sub = locate(ftype, inner % elem, depth + 1)
        if sub:
            return sub
    return path, i, m, elem


parser = argparse.ArgumentParser()
parser.add_argument('filter', nargs='?', default='')
parser.add_argument('--apply', action='store_true')
args = parser.parse_args()

byaddr = common.load_diff()
# (type, offset, width) -> extensions the ORIGINAL uses, and where it reads it
reads = defaultdict(lambda: {'ext': set(), 'in': set()})
for f, entry, address in common.entries(byaddr):
    if entry is None or args.filter not in f.replace(chr(92), '/'):
        continue
    orig, _ours = common._asm_lines(entry)
    name = entry['name'].split('::')[-1]
    for line in orig:
        s = line.split(chr(9))[0].strip()
        e = EXTEND.match(s)
        if not e:
            continue
        g = GLOBAL.search(s)
        if not g:
            continue
        key = (g.group(1) or g.group(3), int(g.group(2) or g.group(4) or 0),
               PTR_WIDTH[e.group(2)])
        reads[key]['ext'].add(e.group(1))
        reads[key]['in'].add(name)

wanted = {}
skipped = []
for (type_name, offset, width), r in sorted(reads.items()):
    if len(r['ext']) != 1:
        skipped.append((type_name, offset, 'the original reads it both ways'))
        continue
    want = 'signed' if r['ext'] == {'movsx'} else 'unsigned'
    hit = locate(type_name, offset)
    if not hit:
        skipped.append((type_name, offset, 'no member at that offset'))
        continue
    path, i, m, elem = hit
    if elem != width:
        skipped.append((type_name, offset, '%s is %d bytes, operand %d'
                        % (m.group('name'), elem, width)))
        continue
    wanted.setdefault((str(path), i), (want, m, set()))[2].update(r['in'])

changed = 0
for (path_s, i), (want, m, funcs) in sorted(wanted.items()):
    path = Path(path_s)
    old = m.group('type')
    new = (SIGNED if want == 'signed' else UNSIGNED).get(old)
    if new is None:
        continue  # already declared the way the original reads it
    where = '%s::%s' % (path.stem, m.group('name'))
    lines = path.read_text(errors='replace').split('\n')
    lines[i] = re.sub(r'\b%s\b' % re.escape(old), new, lines[i], count=1)
    print('  %-44s %-11s -> %-9s read in %s' % (where, old, new, ' '.join(sorted(funcs))))
    changed += 1
    if args.apply:
        path.write_text('\n'.join(lines))

for type_name, offset, why in sorted(set(skipped)):
    print('  skipped: %s+%d: %s' % (type_name.split('::')[-1], offset, why))
print('%d field(s)%s, %d skipped, out of %d narrow field read(s) in the original'
      % (changed, '' if args.apply else ' (dry run)', len(set(skipped)), len(reads)))
