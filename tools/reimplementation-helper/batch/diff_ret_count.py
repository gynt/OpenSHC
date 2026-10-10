"""Rank functions by how many `ret` instructions the original has that we do not.

A `ret` in the binary is one exit the source wrote. Counting them against our
`return;` statements plus the implicit one is direct evidence, and unlike the
epilogue-jump deficit it does not over-report structured exits: a conditional
jump to a shared epilogue is one `ret`, not many.

Tail calls make the count an undercount (a `jmp` to the callee shows no `ret`),
so a function where the two numbers are equal still needs reading; a function
where the original has *more* is missing that many exits.
"""
import io
import os
import re
import subprocess
import sys

TOOL = "tools/reimplementation-helper/batch/orig_disasm.py"
RET = re.compile(r"\bret\b")
rows = []
for rel in io.open("cmake/openshc-sources.txt.local", encoding="utf-8").read().split():
    if not rel.endswith(".cpp"):
        continue
    try:
        out = subprocess.check_output([sys.executable, TOOL, rel],
                                      stderr=subprocess.DEVNULL).decode("utf-8", "replace")
    except Exception:
        continue
    rets = sum(1 for line in out.split("\n")
               if RET.search(line.split("  ")[-1].strip()) and "retn" not in line)
    src = io.open(rel, encoding="utf-8").read()
    ours = len(re.findall(r"\breturn;", src)) + 1
    if rets > ours:
        rows.append((rets - ours, rets, ours, os.path.basename(rel)))
rows.sort(reverse=True)
sys.stdout.write("%5s %5s %5s  %s\n" % ("short", "ret", "ours", "function"))
for d, r, o, name in rows[:30]:
    sys.stdout.write("%5d %5d %5d  %s\n" % (d, r, o, name))
sys.stdout.write("%d function(s) short of the original's exits\n" % len(rows))
