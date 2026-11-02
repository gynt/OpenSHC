"""Style guide rule 1: drop the decompiler's trailing `return;`.

A `void` function does not need a `return;` as its last statement. Only the *trailing* one
goes: an early `return;` inside an `if`, a loop or a `switch` arm is control flow and stays.

The guide warns that a regex over `return;\n}` eats those early returns, because a nested
block's closing brace looks exactly like the function's. So this walks braces instead: a
`return;` is trailing only when the brace depth at it is the function body's own depth and
the next statement is the body's closing brace. String and character literals and both
comment forms are skipped while counting, so a `}` inside one cannot shift the depth.

usage:
  untrailing_return.py [path-filter] [--apply]
"""

import argparse
import re

import common

RETURN = re.compile(r"(?<![\w:])return\s*;")


def depths(text):
    """Brace depth before each character, with literals and comments masked out.

    Returns (depths, masked) where `masked` has every comment and literal body replaced by
    spaces, so a caller can match code against it without seeing a `}` in a string.
    """
    out = [0] * len(text)
    masked = list(text)
    depth = 0
    i = 0
    n = len(text)
    while i < n:
        c = text[i]
        out[i] = depth
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            while i < n and text[i] != "\n":
                out[i] = depth
                masked[i] = " "
                i += 1
            continue
        if c == "/" and i + 1 < n and text[i + 1] == "*":
            end = text.find("*/", i + 2)
            end = n if end < 0 else end + 2
            while i < end:
                out[i] = depth
                masked[i] = " "
                i += 1
            continue
        if c in "\"'":
            quote = c
            i += 1
            out[i - 1] = depth
            while i < n:
                out[i] = depth
                if text[i] == "\\":
                    masked[i] = " "
                    if i + 1 < n:
                        out[i + 1] = depth
                        masked[i + 1] = " "
                    i += 2
                    continue
                if text[i] == quote:
                    i += 1
                    break
                masked[i] = " "
                i += 1
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            out[i] = depth
        i += 1
    return out, "".join(masked)


# a label immediately in front of the statement: `LAB_x:`, `switchD_..._caseD_26:`,
# `case 3:`, `default:`. A `::` is scope resolution, not a label, and `?:` is the ternary.
LABEL_BEFORE = re.compile(r"(?:^|[;{}:])\s*(?:case\s[^;{}:]+|default|[A-Za-z_]\w*)\s*:\s*\Z", re.M)
ARM_KEYWORD = re.compile(r"(?:\A|[^\w:])(if|for|while|switch|catch)\s*\Z")
ARM_TAIL = re.compile(r"(\belse\b|\bdo\b|\btry\b|:)\s*\Z")


def block_opener(masked, depth, at):
    """Index of the `{` opening the block that holds the statement at `at`."""
    want = depth[at] - 1
    for i in range(at, -1, -1):
        if masked[i] == "{" and depth[i] == want:
            return i
    return None


def is_arm(before):
    """True when the `{` following `before` opens a control-flow arm, not a function body.

    A function signature also ends in `)`, so a bare `)` says nothing: what decides it is the
    word in front of the bracket that `)` closes.
    """
    before = before.rstrip()
    if ARM_TAIL.search(before):
        return True
    if not before.endswith(")"):
        return False
    level = 0
    for i in range(len(before) - 1, -1, -1):
        if before[i] == ")":
            level += 1
        elif before[i] == "(":
            level -= 1
            if level == 0:
                return bool(ARM_KEYWORD.search(before[:i]))
    return False


def process(text):
    """Remove every trailing `return;`, innermost-last so earlier indices stay valid."""
    n = 0
    while True:
        depth, masked = depths(text)
        for m in RETURN.finditer(masked):
            # the function body is depth 1 inside its namespaces; what matters is only that
            # the next non-space character after the statement closes the block the
            # `return;` sits in, and that nothing follows it in that block.
            rest = masked[m.end():]
            stripped = rest.lstrip()
            if not stripped.startswith("}"):
                continue
            close = m.end() + (len(rest) - len(stripped))
            if depth[close] != depth[m.start()] - 1:
                continue
            # keep it when the block is a control-flow arm rather than a function body
            open_brace = block_opener(masked, depth, m.start())
            if open_brace is None or is_arm(masked[:open_brace]):
                continue
            # keep it when it is a label's statement. A label must be followed by one before
            # C++23, so dropping it leaves `switchD_004b9c26_caseD_26: }`, which MSVC1400
            # rejects outright - and `label: ;` reads no better than `label: return;`.
            if LABEL_BEFORE.search(masked[:m.start()]):
                continue
            # cut the statement and the blank line it leaves behind
            start = m.start()
            while start > 0 and text[start - 1] in " \t":
                start -= 1
            end = m.end()
            if text[start - 1:start] == "\n":
                start -= 1
            text = text[:start] + text[end:]
            n += 1
            break
        else:
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
    print("%d trailing return(s) dropped in %d file(s)%s"
          % (total, files, "" if args.apply else " (dry run, pass --apply)"))
