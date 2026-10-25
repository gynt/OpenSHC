"""Scan every function in the current diff for the mismatch patterns that have a known fix.

Each pattern here is one of the levers written up in IMPLEMENTATION_CHEAT_SHEET.md, reduced to
something that can be recognised in a reccmp diff. The point is triage over a large build list: run
this once and work the patterns with the best documented payoff first, instead of opening functions
in percentage order.

    RET-VALUE   the original sets eax immediately before a `ret` and we do not, with no eax-setting
                instruction anywhere on our side of that block - the function returns something our
                signature calls void. (0x004039B0, 36.4% -> 100%)
    LTCG        the original keeps ecx or edx live across a call and reloads nothing; we reload. Add
                the file to cmake/compiler-flags-gl.txt. (0x00504EE0, 38.5% -> 100%)
    IMUL-SHARED the original repeats the same `imul reg, reg, N` in several blocks where we compute
                it once: the index was a variable the optimizer later found constant, so give it a
                local. (eight AICState functions, 38-62% -> 100%)
    CMP-RELOAD  the original compares a memory operand and then loads the same address again, where
                we compare a register we already hold: the two uses had different types, so cast the
                indexing use to (uint). (aiPlaceWoodcuttershut, 91.4% -> 100%)
    EXTEND      movsx against movzx on the same operand - a local or field width.
    CONST-OFF1  the same comparison against K and K+-1 with the matching jcc pair.
    WIDTH       the original compares 16 bits where we compare 32.

usage:
    scan_patterns.py [pattern...]      # default: a count per pattern, then the hits
    scan_patterns.py --files           # one line per (function, pattern)
"""

import argparse
import os
import re
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

parser = argparse.ArgumentParser()
parser.add_argument("pattern", nargs="*")
parser.add_argument("--files", action="store_true")
args = parser.parse_args()

W16 = set("ax bx cx dx si di bp sp".split())
W32 = set("eax ebx ecx edx esi edi ebp esp".split())
CMP = re.compile(r"^cmp (\w+), (0x[0-9a-f]+|\d+)$")
JCC = ("jg", "jge", "jl", "jle", "ja", "jae", "jb", "jbe")
PAIR = {("jg", "jge"), ("jle", "jl"), ("jge", "jg"), ("jl", "jle"),
        ("ja", "jae"), ("jbe", "jb"), ("jae", "ja"), ("jb", "jbe")}
IMUL = re.compile(r"^imul (\w+), (\w+), (0x[0-9a-f]+|\d+)$")
SETEAX = re.compile(r"^(mov eax, |xor eax, eax|lea eax|movsx eax|movzx eax|or eax, )")


def jcc_after(rows, i):
    for r in rows[i + 1:i + 3]:
        w = r.split()
        if w and w[0] in JCC:
            return w[0]
    return None


def blocks(entry):
    for hunk in entry.get("diff") or []:
        for b in hunk[1]:
            o = [common._normalize(r[1]).strip() for r in b.get("orig", [])]
            u = [common._normalize(r[1]).strip() for r in b.get("recomp", [])]
            yield o, u


hits = defaultdict(set)
for f, entry, addr in common.entries(common.load_diff()):
    if not entry or float(entry["matching"]) >= 1.0:
        continue
    name = entry["name"].split("::")[-1]
    key = "%5.1f %-46s" % (float(entry["matching"]) * 100, name)
    O, U = [], []
    for o, u in blocks(entry):
        O += o
        U += u
        # --- RET-VALUE: eax set right before a ret on the original side only
        for i, l in enumerate(o):
            if l.startswith("ret") and i and SETEAX.match(o[i - 1]):
                if not any(SETEAX.match(x) for x in u):
                    hits["RET-VALUE"].add(key)
        # --- CMP-RELOAD
        for i, l in enumerate(o):
            m = re.match(r"^cmp (?:dword|word|byte) ptr \[([^\]]+)\], ", l)
            if m and any(re.match(r"^mov \w+, (?:dword|word|byte) ptr \[%s\]" % re.escape(m.group(1)), x)
                         for x in o[i + 1:i + 8]):
                if not any(re.match(r"^cmp (?:dword|word|byte) ptr \[%s\]" % re.escape(m.group(1)), x) for x in u):
                    hits["CMP-RELOAD"].add(key)
        # --- EXTEND / WIDTH / CONST-OFF1
        for ol in o:
            mo = re.match(r"^(movsx|movzx) (\w+), (\w+ ptr \[[^\]]+\])$", ol)
            if mo:
                for ul in u:
                    mu = re.match(r"^(movsx|movzx) (\w+), (\w+ ptr \[[^\]]+\])$", ul)
                    if mu and mu.group(3) == mo.group(3) and mu.group(1) != mo.group(1):
                        hits["EXTEND"].add(key)
            m = re.match(r"^(cmp|test) (\w+), (\w+)$", ol)
            if m and m.group(2) in W16 and m.group(3) in W16:
                for ul in u:
                    mu = re.match(r"^(cmp|test) (\w+), (\w+)$", ul)
                    if mu and mu.group(1) == m.group(1) and mu.group(2) in W32 and mu.group(3) in W32:
                        hits["WIDTH"].add(key)
    # --- CONST-OFF1 (per function, across blocks)
    oc = [(int(m.group(2), 0), jcc_after(O, i)) for i, l in enumerate(O) if (m := CMP.match(l))]
    uc = [(int(m.group(2), 0), jcc_after(U, i)) for i, l in enumerate(U) if (m := CMP.match(l))]
    for ko, jo in oc:
        for ku, ju in uc:
            if abs(ku - ko) == 1 and jo and ju and (jo, ju) in PAIR:
                hits["CONST-OFF1"].add(key)
    # --- LTCG: a call on the original side with ecx/edx used after it and never reloaded
    for i, l in enumerate(O):
        if l.startswith("call "):
            after = O[i + 1:i + 4]
            for reg in ("ecx", "edx"):
                if any(re.match(r"^\w+ .*\b%s\b" % reg, x) and not re.match(r"^mov %s," % reg, x) for x in after):
                    if any(re.match(r"^mov %s, " % reg, x) for x in U[max(0, i - 2):i + 4]):
                        hits["LTCG"].add(key)
    # --- IMUL-SHARED
    co = Counter(m.group(3) for l in O if (m := IMUL.match(l)))
    cu = Counter(m.group(3) for l in U if (m := IMUL.match(l)))
    for k, n in co.items():
        if n >= 2 and cu.get(k, 0) < n:
            hits["IMUL-SHARED"].add(key)

order = ["RET-VALUE", "LTCG", "IMUL-SHARED", "CMP-RELOAD", "EXTEND", "CONST-OFF1", "WIDTH"]
want = [p for p in order if not args.pattern or any(a.upper() in p for a in args.pattern)]
for p in want:
    print("## %-12s %d function(s)" % (p, len(hits[p])))
    if args.files or args.pattern:
        for k in sorted(hits[p]):
            print("   ", k)
