"""Find a store repeated as the first statement of the guard that follows it.

`X = V;` immediately followed by `if (cond) { X = V; ... }` is Ghidra duplicating
one store across a branch it could not see the shape of: the original stored once
before the test (`cmp edi, ebx; mov dword ptr [..], ebx; jl`, 0x427941). The inner
copy is redundant in our source too, so removing it is behaviour-preserving, and
it takes the guard back to the shape the original compiled.
"""
import io
import os
import re
import sys

hits = 0
for rel in io.open("cmake/openshc-sources.txt.local", encoding="utf-8").read().split():
    if not rel.endswith(".cpp"):
        continue
    lines = io.open(rel, encoding="utf-8").read().split("\n")
    for i in range(len(lines) - 2):
        a = lines[i].strip()
        if not re.match(r"^[\w:.\[\]>-]+ = [^;]+;$", a):
            continue
        if not re.match(r"^if \(.*\) \{$", lines[i + 1].strip()):
            continue
        if lines[i + 2].strip() != a:
            continue
        sys.stdout.write("%s:%d  %s\n" % (os.path.basename(rel), i + 1, a))
        hits += 1
sys.stdout.write("%d site(s)\n" % hits)
