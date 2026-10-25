"""Find branches whose polarity is inverted, i.e. the two arms of an `if` are swapped.

usage: diff_polarity.py [NAME-SUBSTRING]

MSVC lays the arm it falls through to first and jumps to the other one, so which arm
is written first in the source decides the whole block's placement. When Ghidra picks
the other arm, every jump in the function moves and the branch itself comes out as the
logical inverse of the original's:

    orig   cmp edx, 1;  jle <far>     ->  if (1 < missionNumber) { loop } else { copy }
    ours   cmp edx, 2;  jge <far>     ->  if (missionNumber < 2)  { copy } else { loop }

Both are correct code; only the order differs.  Swapping the arms in the source (and
writing the original's literal and operator) was worth 9.5 points on
`MenuView_CampaignUnk_Prepare` and 13.7 on `MenuView_MainMenu_DoEveryFrame`.

This pairs conditional jumps positionally inside one replacement block and reports the
pairs that are logical inverses.  Confirm against `reccmp_report.py diff` before editing:
an inverse pair also shows up when the condition itself is wrong, which is a different
fix, and the pairing is positional so a drifted stream produces noise.
"""

import pathlib
import re
import sys

import common

JCC = re.compile(r"^(j[a-z]+)\b")
INVERSE = {("je", "jne"), ("jne", "je"), ("jl", "jge"), ("jge", "jl"),
           ("jle", "jg"), ("jg", "jle"), ("jb", "jae"), ("jae", "jb"),
           ("jbe", "ja"), ("ja", "jbe"), ("js", "jns"), ("jns", "js")}

want = sys.argv[1] if len(sys.argv) > 1 else ""


def branches(rows):
    out = []
    for row in rows:
        text = row[1]
        m = JCC.match(text.split("\t")[0].strip())
        if m and m.group(1) != "jmp":
            src = text.split("\t")[1].strip() if "\t" in text else ""
            out.append((m.group(1), src))
    return out


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
            o, r = branches(block["orig"]), branches(block["recomp"])
            for (oj, _), (rj, rs) in zip(o, r):
                if (oj, rj) in INVERSE:
                    hits.append((oj, rj, rs))
    if hits:
        print("### %s %.1f%%" % (name, e.get("matching", 0) * 100))
        for oj, rj, rs in hits:
            print("  INVERTED  orig %-4s ours %-4s  %s" % (oj, rj, rs))
