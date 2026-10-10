"""Find comparisons we compile unsigned where the original compiles them signed.

`diff_jcc.py` reports a *strictness* step (`jl` against `jle`); this reports a
**signedness** mismatch (`jl` against `jb`), which is the `undefined4`/`uint`
resolver field being compared without an `(int)` cast. AGENTS records one such
sweep as 51 sites, 10 functions better and no regressions, so the seam is worth
re-scanning after every batch of rewrites.

Pairs each signed jump on the original's side of a slice with any unsigned jump
of the same direction on ours, which is deliberately loose: it is what found all
44 real sites in `UI::MenuItems`, but it leaves a residue of false positives
once the real ones are fixed (a function whose comparisons are all already
`int` can still pair two unrelated jumps). Confirm a hit by reading the
comparison and the field's declared type before casting anything.
"""
import json
import re
import sys

SIGNED = {"jl": "jb", "jle": "jbe", "jg": "ja", "jge": "jae"}
RX = re.compile(r"^(\w+)")

d = json.load(open("reccmp/dll/diff.json"))
total = 0
for e in d["data"]:
    if "MenuItems" not in e["name"]:
        continue
    rows = []
    for hdr, slices in (e.get("diff") or []):
        for sl in slices:
            orig = [x for x in (sl.get("orig") or [])]
            ours = [x for x in (sl.get("recomp") or [])]
            if not orig or not ours:
                continue
            for a in orig:
                ta = a[-1] if isinstance(a, (list, tuple)) else str(a)
                ma = RX.match(str(ta).strip())
                if not ma or ma.group(1) not in SIGNED:
                    continue
                want = SIGNED[ma.group(1)]
                for b in ours:
                    tb = b[-1] if isinstance(b, (list, tuple)) else str(b)
                    mb = RX.match(str(tb).strip())
                    if mb and mb.group(1) == want:
                        rows.append("%s -> %s" % (ma.group(1), want))
                        break
    if rows:
        total += len(rows)
        sys.stdout.write("%6.1f%% %-3d %s\n" % (e.get("matching", 0) * 100, len(rows),
                                                e["name"].split("::")[-1]))
sys.stdout.write("%d site(s)\n" % total)
