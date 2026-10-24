"""Find comparisons where both the literal and the operator are one step off.

usage: diff_offbyone.py [NAME-SUBSTRING]

`diff_jcc.py` pairs an orig `jcc` with the recomp line that immediately
follows it, so it only sees a pair when the two `cmp` instructions matched and
just the branch differs.  The commonest shape in this tree hides from that: a
guard written `K < x` compiles to `cmp x, K; jle`-inverted, while the original
wrote `x < K + 1` and compiled to `cmp x, K+1; jl`.  Both the literal *and* the
strictness differ, so the `cmp` lines also diverge and the pairing never
lines up.

This pairs `cmp`/`jcc` pairs positionally inside one replacement block and
reports those whose second operand differs by exactly one while the branch
differs by one strictness step.  The fix is always to write the original's
literal and operator: `cmp x, 0x3b; jl` is `x < 0x3b`, not `0x3a < x`.
"""

import pathlib
import re
import sys

import common

CMP = re.compile(r"^cmp (.+?), (-?(?:0x[0-9a-fA-F]+|\d+))$")
JCC = re.compile(r"^(j[a-z]+)\b")
STEP = {("jl", "jle"), ("jle", "jl"), ("jg", "jge"), ("jge", "jg"),
        ("ja", "jae"), ("jae", "ja"), ("jb", "jbe"), ("jbe", "jb")}


def value(text):
    return int(text, 16) if text.lower().startswith(("0x", "-0x")) else int(text)


def pairs(rows):
    """(operand, literal, branch, source) for every cmp-with-literal + jcc."""
    out, pending = [], None
    for text, src in rows:
        m = CMP.match(text)
        if m:
            pending = (m.group(1), value(m.group(2)), src)
            continue
        m = JCC.match(text)
        if m and pending:
            out.append((pending[0], pending[1], m.group(1), pending[2] or src))
        pending = None
    return out


want = sys.argv[1] if len(sys.argv) > 1 else ""

for f, e, address in common.entries(common.load_diff()):
    if e is None:
        continue
    name = pathlib.Path(f).stem
    if want and want not in name:
        continue
    hits = []
    for hunk in e.get("diff") or []:
        for block in hunk[1]:
            if "orig" not in block or "recomp" not in block:
                continue
            side = {}
            for kind in ("orig", "recomp"):
                rows = []
                for row in block[kind]:
                    text = row[1]
                    rows.append((text.split("\t")[0].strip(),
                                 text.split("\t")[1].strip() if "\t" in text else ""))
                side[kind] = pairs(rows)
            for (oa, ok, oj, _), (ra, rk, rj, rs) in zip(side["orig"], side["recomp"]):
                if oa == ra and abs(ok - rk) == 1 and (oj, rj) in STEP:
                    hits.append((oa, ok, oj, rk, rj, rs))
    if hits:
        print("### %s %.1f%%" % (name, e.get("matching", 0) * 100))
        for oa, ok, oj, rk, rj, rs in hits:
            print("  OFFBY1  orig `cmp %s, %#x; %s`  ours `cmp %s, %#x; %s`  %s"
                  % (oa, ok, oj, oa, rk, rj, rs))
