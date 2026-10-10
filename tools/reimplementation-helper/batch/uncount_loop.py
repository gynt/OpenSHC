"""Put back the counted inner loop of a bubble sort.

Ghidra renders MSVC's zero-trip test as a `break` inside the outer loop:

    do { moved = 0; i = 0; if (bound < 1) break; do { ... i = i + 1; } while (i < bound); }
    while (moved != 0);

but `test edi, edi; jle` (0x440ad4, 0x492e67) is the inner loop's own entry test, so the
inner loop is a counted `for` and the outer one has no early exit at all:

    do { moved = 0; for (i = 0; i < bound; i = i + 1) { ... } } while (moved != 0);

usage:
  uncount_loop.py FILE.cpp... [--apply]
"""
import io
import re
import sys

PAT = re.compile(
    r"(?P<i0> *)do \{\n"
    r"(?P<i1> *)(?P<moved>\w+) = 0;\n"
    r" *(?P<idx>\w+) = 0;\n"
    r" *if \((?P<bound>[\w.:]+) < 1\)\n"
    r" *break;\n"
    r" *do \{\n"
    r"(?P<body>.*?)\n"
    r" *(?P=idx) = (?P=idx) \+ 1;\n"
    r" *\} while \((?P=idx) < (?P=bound)\);\n"
    r" *\} while \((?P=moved) != 0\);\n",
    re.S)


def rewrite(text):
    out = []
    pos = 0
    n = 0
    for m in PAT.finditer(text):
        g = m.groupdict()
        body = "\n".join(("    " + l if l.strip() else l)
                         for l in g["body"].split("\n"))
        out.append(text[pos:m.start()])
        out.append("%(i0)sdo {\n%(i1)s%(moved)s = 0;\n"
                   "%(i1)sfor (%(idx)s = 0; %(idx)s < %(bound)s; %(idx)s = %(idx)s + 1) {\n"
                   % g
                   + body + "\n"
                   + "%(i1)s}\n%(i0)s} while (%(moved)s != 0);\n" % g)
        pos = m.end()
        n += 1
    out.append(text[pos:])
    return "".join(out), n


apply_ = "--apply" in sys.argv
for rel in [a for a in sys.argv[1:] if not a.startswith("--")]:
    text = io.open(rel, encoding="utf-8").read()
    new, n = rewrite(text)
    print("%-62s %d loop(s)" % (rel.split("/")[-1], n))
    if n and apply_:
        io.open(rel, "w", encoding="utf-8", newline="\n").write(new)
