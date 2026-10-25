"""Wrap a switch arm in braces where an initialised declaration is jumped over.

An imported body often declares a local with an initialiser directly inside a switch arm:

    case M_MAPPER_BATTERING_RAM:
        int iVar3 = piVar6->x;        // C2360 once a later `case` can jump past it
        ...
        break;
    case M_MAPPER_MANGONEL:

C++ forbids that: the later label is in the same scope and would skip the initialisation. The
arm needs a block of its own. The compiler reports the *label that does the skipping*, so the
arm to brace is the one that ends just above it.

Driven by a compiler log so that only real errors are touched - `syntax_check.py` output or
`build-RelWithDebInfo/batch/build.log` both work. Arms are braced bottom-up, which keeps the
reported line numbers valid while editing.

usage:
    brace_switch_arms.py --log syntax_rest.log [--dry-run]
"""

import argparse
import re
import sys
from collections import defaultdict
from pathlib import Path

ERROR = re.compile(
    r"^(?P<file>[^(]+\.cpp)\((?P<line>\d+)\) : error C236[01]: initialization of '\w+' "
    r"is skipped by '(?P<kind>case|default)' label"
)
LABEL = re.compile(r"^(?P<indent>\s*)(case\b.*:|default\s*:)\s*$")

parser = argparse.ArgumentParser()
parser.add_argument("--log", required=True)
parser.add_argument("--dry-run", action="store_true")
args = parser.parse_args()

sites = defaultdict(set)
for line in Path(args.log).read_text(errors="replace").splitlines():
    m = ERROR.match(line.strip())
    if m:
        sites[m.group("file").replace("\\", "/")].add(int(m.group("line")))
if not sites:
    sys.exit("no C2360/C2361 errors in " + args.log)

braced = files = 0
for f, lines_1 in sorted(sites.items()):
    p = Path("src/OpenSHC") / f if not f.startswith("src/") else Path(f)
    if not p.exists():
        hits = list(Path("src").rglob(Path(f).name))
        if len(hits) != 1:
            print("  skipped, cannot locate %s" % f)
            continue
        p = hits[0]
    L = p.read_text(newline="").split("\n")
    n = 0
    for ln in sorted(lines_1, reverse=True):
        i = ln - 1                      # the label that does the skipping
        if i >= len(L) or not LABEL.match(L[i]):
            # the compiler points at the label; if it does not, leave it to a human
            print("  %s:%d is not a case label, skipped" % (p.name, ln))
            continue
        indent = LABEL.match(L[i]).group("indent")
        # walk up past the arm body to the run of labels that opens it
        j = i - 1
        while j >= 0 and not LABEL.match(L[j]):
            j -= 1
        if j < 0:
            print("  %s:%d has no opening label, skipped" % (p.name, ln))
            continue
        while j - 1 >= 0 and LABEL.match(L[j - 1]):
            j -= 1
        body_start = j
        while body_start < i and LABEL.match(L[body_start]):
            body_start += 1
        if body_start >= i:
            continue                     # an empty arm cannot skip anything
        if L[body_start].strip() == "{":
            continue                     # already a block
        L.insert(i, indent + "}")
        L.insert(body_start, indent + "{")
        n += 1
    if n:
        braced += n
        files += 1
        print("  %-56s %d arm(s)" % (p.name, n))
        if not args.dry_run:
            p.write_text("\n".join(L), newline="")
print("%d switch arm(s) braced in %d file(s)%s"
      % (braced, files, " (dry run)" if args.dry_run else ""))
