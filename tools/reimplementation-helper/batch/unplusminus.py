"""Style guide rule 15: write `- 1`, not `+ -1`.

The decompiler writes "plus minus one" wherever the original subtracted a constant, and
the same for `- -1` where it added one. The compiler sees one value either way, so this is
match neutral; it only stops the arithmetic reading backwards.

    screenHorizontalResolutionInPixels + -1   ->   screenHorizontalResolutionInPixels - 1
    basenameEnd + -0x20                       ->   basenameEnd - 0x20
    count - -4                                ->   count + 4

Only a literal operand is folded. `a + -b` is left alone: negating a variable is a real
operation that the original may well have spelled that way, and `a - b` is not the same
expression when `b` is unsigned.

usage:
  unplusminus.py [path-filter] [--apply]
"""

import argparse
import re

import common

# a decimal or hex literal, optionally suffixed, with nothing in front of it that could make
# the sign part of a larger token (`e-1` in a float, `->-1`, `<<-1` are not ours)
LITERAL = r"(0[xX][0-9a-fA-F]+|\d+)([uUlL]*)\b"
PLUS = re.compile(r"\+ -" + LITERAL)
MINUS = re.compile(r"- -" + LITERAL)


def process(text):
    text, plus = PLUS.subn(r"- \1\2", text)
    text, minus = MINUS.subn(r"+ \1\2", text)
    return text, plus + minus


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path_filter", nargs="?", default="")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()

    total = files = 0
    for f in common.list_files():
        if args.path_filter not in f:
            continue
        new, n = process(common.read_text(f).replace("\r\n", "\n"))
        if not n:
            continue
        print("%-52s %d" % (f.rsplit("/", 1)[-1][:-4], n))
        total += n
        files += 1
        if args.apply:
            common.write_text(f, new)
    print("%d signed literal(s) folded in %d file(s)%s"
          % (total, files, "" if args.apply else " (dry run, pass --apply)"))
