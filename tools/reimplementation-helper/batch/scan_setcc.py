"""Find `flag = (a == b)` sites whose original never uses `setcc`.

`flag = (uint)(a == b);` compiles to `sete`. Where the original's disassembly
contains no `setcc` at all, every such site in that function was written as a
default assignment plus a one-armed `if` instead
(`xor edx, edx; cmp ...; jne; mov edx, 1`). AGENTS records this as worth 10-20
points per function, so the check is: our source has the comparison-assignment
form and the original has no `setcc`.

Prints the candidate functions with their site count, and separately the ones
where the original *does* use `setcc`, which are to be left alone.
"""
import io
import os
import re
import subprocess
import sys

TOOL = "tools/reimplementation-helper/batch/orig_disasm.py"
# `x = (uint)(a == b);`, `x = (BOOLEnum)(a != b);`, `bVar1 = a == b;`
SITE = re.compile(r"=\s*(?:\([A-Za-z_][\w:]*\)\s*)?\(?[^;=]*[^!<>=]([=!]=)[^;]*\)?;\s*$")
SETCC = re.compile(r"\bset(e|ne|l|le|g|ge|b|be|a|ae|z|nz)\b")

cands, leave = [], []
for rel in io.open("cmake/openshc-sources.txt.local", encoding="utf-8").read().split():
    if not rel.endswith(".cpp"):
        continue
    src = io.open(rel, encoding="utf-8").read()
    sites = [l.strip() for l in src.split("\n")
             if SITE.search(l) and "if (" not in l and "while (" not in l]
    if not sites:
        continue
    try:
        out = subprocess.check_output([sys.executable, TOOL, rel],
                                      stderr=subprocess.DEVNULL).decode("utf-8", "replace")
    except Exception:
        continue
    row = (len(sites), os.path.basename(rel), sites[0][:70])
    (leave if SETCC.search(out) else cands).append(row)

cands.sort(reverse=True)
sys.stdout.write("# original has NO setcc - every site wants the branch form\n")
for n, name, first in cands:
    sys.stdout.write("%3d  %-62s %s\n" % (n, name, first))
sys.stdout.write("\n%d candidate function(s), %d function(s) left alone (original uses setcc)\n"
                 % (len(cands), len(leave)))
