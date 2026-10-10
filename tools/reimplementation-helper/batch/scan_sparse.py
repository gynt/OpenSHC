"""Find MSVC sparse switches in the originals, tolerating interleaved instructions.

A chain of `sub reg, K` each followed - within a few instructions, because MSVC
schedules the prologue's pushes in between - by a `je`/`jne` is a sparse switch.
Report every function with at least three such links and say whether our source
already has a `switch`.
"""
import io
import os
import re
import subprocess
import sys

ROOT = os.getcwd()
TOOL = os.path.join(ROOT, "tools/reimplementation-helper/batch/orig_disasm.py")
SUB = re.compile(r"^sub (?!esp)(\w+), (0x[0-9a-f]+|\d+)$")
JCC = re.compile(r"^(je|jne) ")

rows = []
for rel in io.open("cmake/openshc-sources.txt.local", encoding="utf-8").read().split():
    if not rel.endswith(".cpp"):
        continue
    try:
        out = subprocess.check_output([sys.executable, TOOL, rel],
                                      stderr=subprocess.DEVNULL).decode("utf-8", "replace")
    except Exception:
        continue
    ins = []
    for line in out.split("\n"):
        m = re.match(r"^(?:L\d+:)?\s+[0-9a-f]{8}  (.*)$", line)
        if m:
            ins.append(m.group(1).strip())
    links = 0
    for i, t in enumerate(ins):
        if not SUB.match(t):
            continue
        if any(JCC.match(u) for u in ins[i + 1:i + 7]):
            links += 1
    if links >= 3:
        src = io.open(rel, encoding="utf-8").read()
        rows.append((links, "switch" if re.search(r"\bswitch \(", src) else "NO-SWITCH",
                     os.path.basename(rel)))
rows.sort(reverse=True)
for links, has, name in rows:
    sys.stdout.write("%3d  %-10s %s\n" % (links, has, name))
sys.stdout.write("%d candidate(s)\n" % len(rows))
