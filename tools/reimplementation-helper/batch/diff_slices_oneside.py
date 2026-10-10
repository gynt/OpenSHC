"""Rank functions by their largest one-sided block in the reccmp diff.

A long run of instructions present on only one side is a block of source the
original does not have, or one we are missing - structural, and the only kind of
loss that restyling cannot touch. Printing the first instruction of that run says
where to look without reading the whole diff.
"""
import json
import sys

d = json.load(open("reccmp/dll/diff.json"))
rows = []
for e in d["data"]:
    if "MenuItems" not in e["name"]:
        continue
    best = (0, "", "")
    for hdr, slices in (e.get("diff") or []):
        for sl in slices:
            if sl.get("both"):
                continue
            for key in ("orig", "recomp"):
                run = sl.get(key) or []
                if len(run) > best[0]:
                    first = run[0]
                    text = first[-1] if isinstance(first, (list, tuple)) else str(first)
                    best = (len(run), key, str(text)[:60])
    if best[0]:
        rows.append((best[0], best[1], best[2], e["name"].split("::")[-1]))
rows.sort(reverse=True)
sys.stdout.write("%5s %-7s %-62s %s\n" % ("len", "side", "first instruction", "function"))
for n, side, text, name in rows[:25]:
    sys.stdout.write("%5d %-7s %-62s %s\n" % (n, side, text, name))
