"""Put a `switch`'s arms in the order the original's jump table says they were written in.

MSVC lays a jump-table `switch` out in source order, so the physical order of the arm
bodies in the binary is the order of the original's `case` labels. When ours differs every
arm sits at a different offset and the comparison drifts from the dispatch onwards, which
on a large switch is most of what is left to win - and no amount of work inside the arms
recovers it.

`switch_order.py` reads the order out of the byte and dword tables. This permutes our arm
groups to match, keeping each group's labels and body exactly as they are. An arm the
original reaches from several values keeps all of its labels; `default:` travels with the
group it belongs to.

Only the one `switch` whose label set matches the table is touched, and only when every
arm in the table can be paired with one in the source, so a function whose dispatch has
drifted further than ordering is left alone and reported.

One table per function, on purpose. A generalisation that paired every table in a function
with its switch corrupted `MenuItemActionHandler_TextEditor_Buttons`, whose 28-arm switch
contains a second switch: rewriting the outer arms moves the inner one, and the second
pass then spliced at stale offsets. Verifying that each rewrite is a pure permutation of
the switch region is what caught it, so keep that check if you extend this to nested
switches.

usage:
  reorder_switch.py FILE.cpp... [--apply] [--add-break] [--loose]
"""

import io
import os
import re
import sys

import common  # noqa: F401
import orig_disasm as od
import switch_order as so

CASE = re.compile(r"^(\s*)case\s+(.+?)\s*:\s*$")
DEFAULT = re.compile(r"^(\s*)default\s*:\s*$")


def value_of(label, path_text):
    """The integer a `case` label denotes, following one level of enum constant."""
    label = label.strip()
    # strip any number of `(Type)` casts and wrapping brackets, then read the literal.
    # the prefix must be a bracketed type, not `\w*`, or it eats digits out of `0x57`.
    m = re.match(r"^(?:\(\s*[A-Za-z_][\w:]*\s*\)\s*)*\(?\s*"
                 r"(-?0x[0-9a-fA-F]+|-?\d+)\s*\)?$", label)
    if m:
        v = int(m.group(1), 0)
        # a decompiled label is written as the unsigned bit pattern; the table's index
        # arithmetic is signed, so fold 32-bit values back to their signed value
        return v - 0x100000000 if v >= 0x80000000 else v
    name = label.rsplit("::", 1)[-1]
    m = re.search(r"\b" + re.escape(name) + r"\s*=\s*(-?\d+|-?0x[0-9a-fA-F]+)", path_text)
    if m:
        return int(m.group(1), 0)
    return None


def enum_text():
    """Every enum definition under src/OpenSHC, concatenated, for label lookup."""
    parts = []
    for base, _, files in os.walk(os.path.join(common.ROOT, "src", "OpenSHC")):
        for f in files:
            if f.endswith(".hpp"):
                try:
                    parts.append(io.open(os.path.join(base, f), encoding="utf-8").read())
                except (IOError, UnicodeDecodeError):
                    pass
    return "\n".join(parts)


FLOW = ("break;", "return", "goto ", "continue;")


def falls_through(body):
    """True when the arm runs off its end into the next one."""
    for line in reversed(body):
        t = line.strip()
        if not t or t.startswith(("//", "/*", "*", "*/")):
            continue
        return not (t.startswith(FLOW) or t == "}")
    return False            # a label-only arm shares the next arm's body, which is fine


def chains(groups):
    """Group indices welded together because an arm falls into the next.

    Reordering arms is only safe where each one ends in `break`/`return`/`goto`. An arm
    that runs off its end into its successor - which Ghidra emits whenever the original
    shared a tail - must keep that successor immediately after it, so the two move as one
    unit or not at all.
    """
    out = []
    cur = []
    for n, (labels, body) in enumerate(groups):
        cur.append(n)
        if not (body and falls_through(body)):
            out.append(cur)
            cur = []
    if cur:
        out.append(cur)
    return out


def arms(lines, start):
    """[(label_lines, body_lines)] for the switch whose `switch (` is at `start`."""
    ind = len(lines[start]) - len(lines[start].lstrip())
    depth = 0
    end = None
    for j in range(start, len(lines)):
        depth += lines[j].count("{") - lines[j].count("}")
        if depth == 0 and j > start:
            end = j
            break
    if end is None:
        return None, None
    # clang-format puts `case` at the same column as `switch`; other styles indent it
    label_ind = None
    for j in range(start + 1, end):
        if CASE.match(lines[j]) or DEFAULT.match(lines[j]):
            label_ind = len(lines[j]) - len(lines[j].lstrip())
            break
    if label_ind is None or label_ind < ind:
        return None, None
    groups = []
    cur_labels, cur_body = [], []
    for j in range(start + 1, end):
        line = lines[j]
        if (CASE.match(line) or DEFAULT.match(line)) and \
                len(line) - len(line.lstrip()) == label_ind:
            if cur_body:
                groups.append((cur_labels, cur_body))
                cur_labels, cur_body = [], []
            cur_labels.append(line)
        else:
            cur_body.append(line)
    if cur_labels or cur_body:
        groups.append((cur_labels, cur_body))
    return groups, end


def tables_of(ins):
    """(values, ranked, default_rank, arm_count) per jump table in the function."""
    out = []
    for base, count, bt, dt, default in so.dispatches(ins):
        order = {}
        for k in range(count):
            slot = so.read(bt + k, 1) if bt else k
            order.setdefault(so.read(dt + 4 * slot, 4), []).append(k + base)
        ranked = {}
        default_rank = None
        for rank, target in enumerate(sorted(order)):
            if target == default:
                default_rank = rank
            for v in order[target]:
                ranked[v] = rank
        non_default = set(v for v in ranked
                          if default_rank is None or ranked[v] != default_rank)
        out.append((non_default, ranked, default_rank, len(order)))
    return out


def keys_for(groups, table, enums, loose=False):
    """One rank per arm group, or None when this table does not describe this switch.

    The switch's own `case` values must cover exactly the table's non-default values.
    Matching on "every label is somewhere in the table" is not enough: a nested switch
    over the same small range matches its parent's table and gets reordered instead.
    """
    non_default, ranked, default_rank, arm_count = table
    keys = []
    seen = set()
    for labels, _ in groups:
        vals = []
        for lab in labels:
            m = CASE.match(lab)
            if not m:
                continue
            v = value_of(m.group(2), enums)
            if v is None or v not in ranked:
                return None
            vals.append(v)
            seen.add(v)
        if not vals:
            if any(DEFAULT.match(l) for l in labels):
                keys.append(arm_count if default_rank is None else default_rank)
                continue
            if keys:
                return None
            keys.append(-1)
            continue
        keys.append(min(ranked[v] for v in vals))
    if seen != non_default:
        # `--loose`: the original gave a block of values an arm of its own where our
        # source leaves them to the end of the switch, so our `case` labels cover every
        # arm but that one. Accept it only when the values we do not name all belong to
        # that single arm - which still rules out a nested switch matching its parent's
        # table, because a nested switch leaves several arms unaccounted for.
        if not loose or len(groups) < 6:
            return None
        missing = set(ranked[v] for v in non_default - seen)
        if not seen or not seen <= non_default or len(missing) != 1:
            return None
        if missing & set(ranked[v] for v in seen):
            return None
    return keys if len(set(keys)) == len(keys) else None


def reorder_one(lines, tables, used, enums, name, add_break=False, loose=False):
    """Reorder the first switch that matches an unused table. -> (lines, changed, note)."""
    for start in [j for j, l in enumerate(lines) if re.match(r"^\s*switch \(", l)]:
        groups, end = arms(lines, start)
        if not groups:
            continue
        for ti in range(len(tables)):
            if ti in used:
                continue
            keys = keys_for(groups, tables[ti], enums, loose)
            if keys is None:
                continue
            used.add(ti)
            # A last arm that runs off its end falls out of the switch. That is harmless
            # only while it stays last: move it and it falls into whatever follows, which
            # is a silent behaviour change and exactly the bug this guard exists for.
            # Falling out of the switch is what `break;` means, so say so explicitly and
            # the arm becomes free to move; without the statement, refuse the switch.
            if groups[-1][1] and falls_through(groups[-1][1]):
                if not add_break:
                    return lines, False, ("the last arm falls out of the switch"
                                          " (pass --add-break to close it)")
                labs, body = groups[-1]
                k = len(body) - 1
                while k >= 0 and not body[k].strip():
                    k -= 1
                ind = len(body[k]) - len(body[k].lstrip())
                groups[-1] = (labs, body[:k + 1] + [" " * ind + "break;"] + body[k + 1:])
            ch = chains(groups)
            if any(sorted(keys[i] for i in c) != [keys[i] for i in c] for c in ch):
                return lines, False, "a fall-through chain is out of the table's order"
            if keys == sorted(keys):
                return lines, False, None
            new = []
            for c in sorted(ch, key=lambda c: keys[c[0]]):
                for i in c:
                    new += groups[i][0] + groups[i][1]
            out = lines[:start + 1] + new + lines[end:]
            # a rewrite that is not a pure permutation of the region is a bug, not a
            # reordering: refuse it rather than write it out
            if sorted(l.strip() for l in lines) != sorted(l.strip() for l in out):
                return lines, False, "rewrite would not be a pure permutation, refused"
            return out, True, "switch at %-5d %d arm(s), %d chain(s)" % (
                start + 1, len(groups), len(ch))
    return lines, False, ""


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    add_break = "--add-break" in sys.argv
    loose = "--loose" in sys.argv
    if not args:
        raise SystemExit(__doc__)
    enums = enum_text()
    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        name = os.path.basename(path)
        try:
            ins = od.disasm(od.address_of(path))
        except Exception as exc:                                   # noqa: BLE001
            print("--     %s  (%s)" % (name, exc))
            continue
        tables = tables_of(ins)
        if not tables:
            print("--     %s  (no jump table)" % name)
            continue
        lines = io.open(path, encoding="utf-8").read().split(chr(10))
        used = set()
        any_change = False
        for _ in range(len(tables)):
            lines, changed, note = reorder_one(lines, tables, used, enums, name, add_break, loose)
            if note:
                print(("reorder %-58s " % name) + note if changed else "--     %s  (%s)" % (name, note))
            if changed:
                any_change = True
            if note == "":
                break
        if any_change and apply_:
            io.open(path, "w", encoding="utf-8", newline=chr(10)).write(chr(10).join(lines))
        if not any_change and not used:
            print("--     %s  (no switch matches a table)" % name)


if __name__ == "__main__":
    main()
