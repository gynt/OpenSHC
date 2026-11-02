"""Cases for untrailing_return.py.

The point of the tool is the near-misses: every `return;` that a regex over `return;\n}`
would eat although it is control flow.

usage:
  test_untrailing_return.py
"""

import untrailing_return as utr

BODY = """void C::f()
{
%s
}
"""

CASES = [
    # the trailing one goes
    (BODY % "    a = 1;\n    return;", BODY % "    a = 1;"),
    # ... even as the only statement
    (BODY % "    return;", "void C::f()\n{\n}\n"),
    # an early return inside an if stays, trailing brace or not
    (BODY % "    if (a) {\n        return;\n    }\n    b = 1;",
     BODY % "    if (a) {\n        return;\n    }\n    b = 1;"),
    # the last statement of an if arm is still control flow
    (BODY % "    if (a) {\n        b = 1;\n        return;\n    }",
     BODY % "    if (a) {\n        b = 1;\n        return;\n    }"),
    # both at once: the arm keeps its return, the body loses its own
    (BODY % "    if (a) {\n        return;\n    }\n    b = 1;\n    return;",
     BODY % "    if (a) {\n        return;\n    }\n    b = 1;"),
    # a loop arm
    (BODY % "    for (int i = 0; i < 8; ++i) {\n        return;\n    }",
     BODY % "    for (int i = 0; i < 8; ++i) {\n        return;\n    }"),
    # an else arm
    (BODY % "    if (a) {\n        b = 1;\n    } else {\n        return;\n    }",
     BODY % "    if (a) {\n        b = 1;\n    } else {\n        return;\n    }"),
    # a switch arm, whose brace is the switch's
    (BODY % "    switch (a) {\n    case 1:\n        return;\n    }",
     BODY % "    switch (a) {\n    case 1:\n        return;\n    }"),
    # a `}` in a string literal must not shift the depth
    (BODY % '    strcpy(s, "}");\n    return;', BODY % '    strcpy(s, "}");'),
    # a `}` in a comment must not shift it either
    (BODY % "    // }\n    return;", BODY % "    // }"),
    # a value return is not ours
    ("int C::f()\n{\n    return 0;\n}\n", "int C::f()\n{\n    return 0;\n}\n"),
    # a word ending in return is not a return
    (BODY % "    noreturn;", BODY % "    noreturn;"),
    # two functions in one file: each loses only its own
    (BODY % "    a = 1;\n    return;" + BODY % "    b = 2;\n    return;",
     BODY % "    a = 1;" + BODY % "    b = 2;"),
    # a label's statement stays: a label must be followed by one before C++23, so dropping
    # this leaves `switchD_004b9c26_caseD_26: }` and MSVC1400 rejects the file outright
    (BODY % "    a = 1;\nswitchD_004b9c26_caseD_26:\n    return;",
     BODY % "    a = 1;\nswitchD_004b9c26_caseD_26:\n    return;"),
    # the same for a goto target at the end of the body
    (BODY % "    goto LAB_Return;\nLAB_Return:\n    return;",
     BODY % "    goto LAB_Return;\nLAB_Return:\n    return;"),
    # a label that already carries its own null statement is not in the way
    (BODY % "    a = 1;\nLAB_Return:;\n    return;", BODY % "    a = 1;\nLAB_Return:;"),
    # scope resolution is not a label
    (BODY % "    a = N::k;\n    return;", BODY % "    a = N::k;"),
    # a ternary's colon is not a label either
    (BODY % "    a = c ? 1 : 2;\n    return;", BODY % "    a = c ? 1 : 2;"),
]

if __name__ == "__main__":
    failures = 0
    for src, want in CASES:
        got, _ = utr.process(src)
        ok = got == want
        failures += not ok
        print("%-4s %s" % ("ok" if ok else "FAIL", src.split("\n")[2].strip()[:70]))
        if not ok:
            print("       got  %r\n       want %r" % (got, want))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
