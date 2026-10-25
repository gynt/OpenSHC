"""Per-branch summary of the combined UI build list.

The eight `reimpl/UI-*` branches own disjoint sets of .cpp files, so they can be measured in one
worktree and one reccmp run. `ui_own.json` at the repo root maps branch -> owned files, which is
what tells this script which numbers belong to which branch.

usage:
    ui_status.py                 # per-branch summary
    ui_status.py --list [N]      # the N worst functions, with their branch
    ui_status.py --branch NAME   # one branch, every function
"""

import argparse
import json
import os
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

parser = argparse.ArgumentParser()
parser.add_argument("--list", nargs="?", type=int, const=40, default=None)
parser.add_argument("--branch")
parser.add_argument("--at100", action="store_true", help="list the ones already at 100%%")
args = parser.parse_args()

own = json.loads(Path("ui_own.json").read_text())
f2b = {f: b for b, fs in own.items() for f in fs}

rows = []
for f, entry, addr in common.entries(common.load_diff()):
    key = f.replace("\\", "/")
    branch = f2b.get(key)
    if branch is None:
        continue
    pct = float(entry["matching"]) * 100 if entry else None
    name = entry["name"].split("::")[-1] if entry else Path(f).stem
    lost = 0
    if entry:
        lost = sum(len(b.get("orig", [])) + len(b.get("recomp", []))
                   for h in (entry.get("diff") or []) for b in h[1])
    rows.append((pct, branch, name, key, lost))

if args.branch:
    sel = sorted((r for r in rows if args.branch in r[1]), key=lambda r: (r[0] is not None, r[0]))
    for pct, b, name, f, lost in sel:
        print("  %6s %-52s lost %4d" % ("n/a" if pct is None else "%5.1f" % pct, name, lost))
    print("%d function(s) in %s" % (len(sel), args.branch))
elif args.list is not None:
    sel = [r for r in rows if r[0] is not None and r[0] < 100]
    sel.sort(key=lambda r: (r[0], -r[4]))
    for pct, b, name, f, lost in sel[: args.list]:
        print("  %5.1f %-22s %-46s lost %4d" % (pct, b[3:], name, lost))
    print("%d of %d below 100%%" % (len(sel), len(rows)))
elif args.at100:
    for pct, b, name, f, lost in sorted(r for r in rows if r[0] is not None and r[0] >= 100):
        print("  %-22s %s" % (b[3:], name))
else:
    by = {}
    for pct, b, name, f, lost in rows:
        by.setdefault(b, []).append(pct)
    tot = []
    print("%-24s %4s %6s %6s %6s %6s" % ("branch", "n", "avg", "at100", "<100", "nodata"))
    for b in sorted(by, key=lambda k: -len(by[k])):
        v = [x for x in by[b] if x is not None]
        nod = sum(1 for x in by[b] if x is None)
        print("%-24s %4d %6.2f %6d %6d %6d"
              % (b[3:], len(by[b]), (sum(v) / len(v)) if v else 0,
                 sum(1 for x in v if x >= 100), sum(1 for x in v if x < 100), nod))
        tot += by[b]
    v = [x for x in tot if x is not None]
    print("%-24s %4d %6.2f %6d %6d %6d"
          % ("TOTAL", len(tot), sum(v) / len(v), sum(1 for x in v if x >= 100),
             sum(1 for x in v if x < 100), sum(1 for x in tot if x is None)))
