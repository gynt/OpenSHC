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
# A pointer cast whose bracket opens the group the match sits in: `*(int*)(`, `(undefined4*)(`.
PTR_CAST_OPEN = re.compile(r"\*\s*\)\s*$")


def in_pointer_address(text, at):
    """True when the match at `at` sits inside a `(T*)( ... )` address computation.

    Folding the sign there is not neutral, which is the one exception measured so far and
    it is measured twice: `*(int*)((int)base + index + -8)` written with `- 8` cost
    `Map::Buildings::UpdateBrewery` 5.8 points, and five `Map::Units::TroopValueState`
    setters 6.4 to 7.3 each, with no other change in those files. The value is identical
    either way, so this is code generation and not semantics - MSVC evidently picks a
    different addressing mode for the two spellings in this shape. These lines are the
    decompiler's raw pointer arithmetic anyway, which rules 7 and 11 would rather replace
    with a named field than tidy, so skipping them costs little readability.
    """
    depth = 0
    for i in range(at, -1, -1):
        if text[i] == ")":
            depth += 1
        elif text[i] == "(":
            if depth == 0:
                return bool(PTR_CAST_OPEN.search(text[:i]))
            depth -= 1
        elif text[i] == "\n":
            break
    return False


def process(text, all_sites=False):
    n = 0
    for pattern, sign in ((PLUS, "-"), (MINUS, "+")):
        out = []
        last = 0
        for m in pattern.finditer(text):
            if not all_sites and in_pointer_address(text, m.start()):
                continue
            out.append(text[last:m.start()])
            out.append("%s %s%s" % (sign, m.group(1), m.group(2)))
            last = m.end()
            n += 1
        out.append(text[last:])
        text = "".join(out)
    return text, n


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
