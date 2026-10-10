"""Reorder a switch whose `case` labels are enum constants into the original's arm order.

`reorder_switch.py` matches a switch to a jump table by the numeric values it names, so a
switch written with enum constants never matches one. This resolves the constants from the
enum header first, then reorders by the physical order of the arm bodies in the binary,
which is the order the original's source wrote them.

Arms that do not end in `break`/`return`/`goto` fall into the next arm and are kept
attached to it, and the reorder is rejected unless the token multiset is unchanged.

usage:
  reorder_enum_switch.py FILE.cpp ENUM.hpp [--apply]
"""
import io
import os
import re
import subprocess
import sys

import common

ROOT = common.ROOT
TOOL = "tools/reimplementation-helper/batch/switch_order.py"
LABEL = re.compile(r"^(?P<ind> *)(case (?P<val>.*)|default) *:$")
TERM = ("break;", "return;", "continue;")


def enum_values(path):
    out = {}
    for line in io.open(path, encoding="utf-8"):
        m = re.match(r"\s*([A-Za-z_]\w*)\s*=\s*(-?\d+|0x[0-9a-fA-F]+)\s*,", line)
        if m:
            out[m.group(1)] = int(m.group(2), 0)
    return out


def table_order(rel):
    """[[value, ...], ...] in the physical order of the arm bodies, default last."""
    out = subprocess.check_output([sys.executable, TOOL, rel],
                                  stderr=subprocess.STDOUT).decode("utf-8", "replace")
    arms = []
    for line in out.split("\n"):
        m = re.match(r"\s*\d+\s+0x[0-9a-f]+\s+(.*)$", line)
        if not m:
            continue
        body = m.group(1)
        default = "(default)" in body
        vals = [int(v.strip(), 0) for v in body.replace("(default)", "").split(",")
                if v.strip()]
        arms.append((vals, default))
    return arms


def split_arms(lines, start, end, ind):
    """[(labels, body_lines, falls_through)] for the switch body between start and end."""
    arms = []
    cur = None
    for i in range(start, end):
        m = LABEL.match(lines[i])
        if m and len(m.group("ind")) == ind:
            if cur is None or cur[1]:
                # a new arm, unless the previous arm had no body yet (stacked labels)
                cur = [[], [], i]
                arms.append(cur)
            cur[0].append(lines[i])
            continue
        if cur is None:
            return None
        cur[1].append(lines[i])
    out = []
    for labels, body, _ in arms:
        text = "\n".join(body).rstrip()
        falls = not (text.endswith(TERM) or text.rstrip().endswith("*/")
                     or re.search(r"goto \w+;$", text))
        out.append((labels, body, falls))
    return out


def main():
    rel, enum = sys.argv[1], sys.argv[2]
    apply_ = "--apply" in sys.argv
    path = os.path.join(ROOT, rel.replace("/", os.sep))
    text = io.open(path, encoding="utf-8").read()
    lines = text.split("\n")
    names = enum_values(os.path.join(ROOT, enum.replace("/", os.sep)))
    order = table_order(rel)

    # the switch is the outermost one whose first label indent we can find
    si = next(i for i, l in enumerate(lines) if re.match(r"^ *switch \(", l))
    # the labels may sit at the switch's own indent or one level in
    nxt = next(l for l in lines[si + 1:] if LABEL.match(l))
    ind = len(nxt) - len(nxt.lstrip())
    depth = 0
    ei = None
    for i in range(si, len(lines)):
        depth += lines[i].count("{") - lines[i].count("}")
        if depth == 0 and i > si:
            ei = i
            break
    arms = split_arms(lines, si + 1, ei, ind)
    if not arms:
        raise SystemExit("could not split the switch")

    # merge fall-through chains
    merged = []
    for arm in arms:
        if merged and merged[-1][2]:
            merged[-1] = (merged[-1][0] + arm[0], merged[-1][1] + arm[1], arm[2])
        else:
            merged.append(arm)

    def values(arm):
        vals = set()
        default = False
        for l in arm[0]:
            m = LABEL.match(l)
            v = m.group("val")
            if v is None:
                default = True
                continue
            v = v.strip().split("::")[-1]
            if v in names:
                vals.add(names[v])
            else:
                try:
                    vals.add(int(v, 0))
                except ValueError:
                    pass
        return vals, default

    # switch_order.py reads the index base from the adjustment closest to the dispatch,
    # which a second adjustment can still shift; recover it by finding the offset that
    # matches every one of our arms to exactly one table arm
    best, shift = -1, 0
    for cand in sorted(range(-16, 17), key=abs):
        hits = 0
        for arm in merged:
            vals, default = values(arm)
            if default or not vals:
                continue
            got = [n for n, (tv, td) in enumerate(order)
                   if not td and vals & set(v + cand for v in tv)]
            if len(got) == 1:
                hits += 1
        if hits > best:
            best, shift = hits, cand
    print("  index base offset %+d (%d arm(s) matched uniquely)" % (shift, best))

    def key(arm):
        vals, default = values(arm)
        for n, (tv, td) in enumerate(order):
            if default and td:
                return n
            if not default and vals & set(v + shift for v in tv):
                return n
        return len(order)

    ranked = sorted(range(len(merged)), key=lambda n: (key(merged[n]), n))
    print("%s  %d arm(s), %d table arm(s)" % (rel.split("/")[-1], len(merged), len(order)))
    print("  order: " + " ".join(str(key(merged[n])) for n in ranked))
    if ranked == list(range(len(merged))):
        print("  already in the original's order")
        return
    body = []
    for n in ranked:
        body += merged[n][0] + merged[n][1]
    out = "\n".join(lines[:si + 1] + body + lines[ei:])
    if sorted(out.split()) != sorted(text.split()):
        raise SystemExit("token multiset changed - refusing")
    if apply_:
        io.open(path, "w", encoding="utf-8", newline="\n").write(out)
        print("  applied")


if __name__ == "__main__":
    main()
