"""Reshape the scroll clamp so the field is stored once behind the branch.

Ghidra renders

    if (v < (M - S)) { v = v + S; if (v <= M) { FIELD = v; return; } }
    FIELD = M;

but the original stores `FIELD` once, at the label both paths converge on
(`mov [DAT_TextEditorState+0xa8], ecx` at 0x4623c9 and 0x4615ee), so the clamp belongs
inside the arm and the store behind it:

    if (v < (M - S)) { v = v + S; if (M < v) { v = M; } } else { v = M; }
    FIELD = v;

usage: merge_clamp.py FILE.cpp...
"""
import io
import re
import sys

JOIN = re.compile(r"if \((\w+)\n *< ")

PAT = re.compile(
    r"(?P<i0> *)if \((?P<v>\w+) < \((?P<m>.+?) - (?P<s>[^()]+?)\)\) \{\n"
    r" *(?P=v) = (?P=v) \+ (?P=s);\n"
    r" *if \((?P=v) <= (?P=m)\) \{\n"
    r" *(?P<f>[\w:.]+)\n? *= (?P=v);\n"
    r" *return;\n"
    r" *\}\n"
    r" *\}\n"
    r" *(?P=f)\n? *= (?P<mv>.+?);\n",
    re.M)


def rewrite(text):
    # clang-format wraps some of these conditions; join them back up first
    text = JOIN.sub(lambda m: "if (%s < " % m.group(1), text)
    out = []
    n = 0
    pos = 0
    for m in PAT.finditer(text):
        i0, v, mm, s, f, mv = (m.group("i0"), m.group("v"), m.group("m"),
                               m.group("s"), m.group("f"), m.group("mv"))
        out.append(text[pos:m.start()])
        out.append(
            "%sif (%s < (%s - %s)) {\n"
            "%s    %s = %s + %s;\n"
            "%s    if (%s < %s) {\n"
            "%s        %s = %s;\n"
            "%s    }\n"
            "%s} else {\n"
            "%s    %s = %s;\n"
            "%s}\n"
            "%s%s = %s;\n"
            % (i0, v, mm, s, i0, v, v, s, i0, mm, v, i0, v, mv, i0, i0, i0, v, mv, i0, i0, f, v))
        pos = m.end()
        n += 1
    out.append(text[pos:])
    return "".join(out), n


for rel in sys.argv[1:]:
    text = io.open(rel, encoding="utf-8").read()
    new, n = rewrite(text)
    if n:
        io.open(rel, "w", encoding="utf-8", newline="\n").write(new)
    print("%-64s %d site(s)" % (rel.split("/")[-1], n))
