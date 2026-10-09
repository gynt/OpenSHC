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
  reorder_switch.py FILE.cpp... [--apply]
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


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
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
        ds = so.dispatches(ins)
        if len(ds) != 1:
            print("--     %s  (%d jump tables)" % (name, len(ds)))
            continue
        base, count, bt, dt, default = ds[0]
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

        lines = io.open(path, encoding="utf-8").read().split("\n")
        starts = [j for j, l in enumerate(lines) if re.match(r"^\s*switch \(", l)]
        done = False
        for start in starts:
            groups, end = arms(lines, start)
            if not groups:
                continue
            keys = []
            ok = True
            for labels, _ in groups:
                vals = []
                for lab in labels:
                    m = CASE.match(lab)
                    if not m:
                        continue
                    v = value_of(m.group(2), enums)
                    if v is None:
                        ok = False
                    else:
                        vals.append(v)
                if not vals and any(DEFAULT.match(l) for l in labels):
                    # values outside the table's range do not appear in it, so the
                    # `default` arm has no rank of its own: MSVC emits it last
                    keys.append(len(order) if default_rank is None else default_rank)
                    continue
                if not vals or any(v not in ranked for v in vals):
                    ok = False
                keys.append(min(ranked[v] for v in vals) if ok and vals else None)
            if not ok or len(set(keys)) != len(keys):
                continue
            if keys == sorted(keys):
                print("--     %s  (already in the original's order)" % name)
                done = True
                break
            # weld fall-through arms to their successors and order the chains by the
            # rank of their first arm; a chain whose members are not ranked in order
            # cannot be placed faithfully, so the function is skipped
            ch = chains(groups)
            if any(any(k is None for k in (keys[i] for i in c)) for c in ch):
                continue
            if any(sorted(keys[i] for i in c) != [keys[i] for i in c] for c in ch):
                print("--     %s  (a fall-through chain is out of order in the table)" % name)
                done = True
                break
            new = []
            for c in sorted(ch, key=lambda c: keys[c[0]]):
                for i in c:
                    new += groups[i][0] + groups[i][1]
            print("reorder %-62s %d arm(s), %d chain(s)" % (name, len(groups), len(ch)))
            if apply_:
                lines[start + 1:end] = new
                io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(lines))
            done = True
            break
        if not done:
            print("--     %s  (no switch matches the table)" % name)


if __name__ == "__main__":
    main()
