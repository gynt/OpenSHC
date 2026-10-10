"""Cast the `undefined4`/`uint` resolver fields of one relational comparison to `int`.

`<`, `>`, `<=` and `>=` against an `undefined4` field compile to `jb`/`jae` where
the original has `jl`/`jge`; `==` and `!=` are unaffected. This rewrites only the
field names it is given, and only where they appear in a relational comparison,
so the edit cannot change a condition by accident.

usage: signcast.py FILE.cpp FIELD [FIELD...]
"""
import io
import re
import sys

path = sys.argv[1]
fields = sys.argv[2:]
text = io.open(path, encoding="utf-8").read()
n = 0
for field in fields:
    # `0 < X.field` / `0 > X.field` and friends
    pat = re.compile(r"([<>]=? *\n? *)((?:\w+::)*instance\.%s)\b" % re.escape(field))
    text, k = pat.subn(lambda m: m.group(1) + "(int)" + m.group(2), text)
    n += k
    # `X.field < ...` where the field is the left-hand side
    pat = re.compile(r"(?<!\(int\))\b((?:\w+::)*instance\.%s)(\s*\n?\s*[<>]=? )" % re.escape(field))
    text, k = pat.subn(lambda m: "(int)" + m.group(1) + m.group(2), text)
    n += k
io.open(path, "w", encoding="utf-8", newline="\n").write(text)
sys.stdout.write("%s: %d cast(s)\n" % (path.split("/")[-1], n))
