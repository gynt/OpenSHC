"""Cases for unplusminus.py.

The rewrites are the shapes the import left behind; the near-misses are the ones where the
minus sign is not a sign at all, or where folding it would change the expression.

usage:
  test_unplusminus.py
"""

import unplusminus

CASES = [
    # the common form
    ("x = basenameEnd + -1;", "x = basenameEnd - 1;"),
    # a hex constant keeps its spelling
    ("x = p + -0x20;", "x = p - 0x20;"),
    # a suffixed literal keeps its suffix
    ("x = p + -1U;", "x = p - 1U;"),
    # the other direction
    ("x = count - -4;", "x = count + 4;"),
    # several in one line, including inside an index
    ("a[i + -1] = b[j + -2];", "a[i - 1] = b[j - 2];"),
    # in a condition
    ("if (this->cursorPosX >= res + -1) {", "if (this->cursorPosX >= res - 1) {"),
    # negating a variable is a real operation, not a written-out sign
    ("x = a + -b;", "x = a + -b;"),
    # a negative literal that is not being added to anything
    ("int x = -1;", "int x = -1;"),
    # a float exponent is not an addition
    ("double d = 1.5e-1 + 2.0;", "double d = 1.5e-1 + 2.0;"),
    # pre-decrement is not ours either
    ("x = a + --b;", "x = a + --b;"),
]

if __name__ == "__main__":
    failures = 0
    for src, want in CASES:
        got, _ = unplusminus.process(src)
        ok = got == want
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", src))
        if not ok:
            print("       got  %s\n       want %s" % (got, want))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
