"""Flip the operand order of a comparison, per site, keeping only the sites that measure better.

Ghidra renders a comparison with whichever operand it likes on the left, usually the constant
(`0 < x`, `10 <= clickY`). The original source had the other order, and the order is visible in the
code: `cmp a, b` reads `a` into the register the condition destroys, so `x > 0` and `0 < x` compile
to different register assignments and `diff_jcc.py` reports the pair as `ORDER`. Flipping also
inverts the operator, so the condition is unchanged by construction - this cannot alter behaviour,
only code generation.

Two pattern sets, both over `cmake/openshc-sources.txt.local`:

  --literal   a decimal or hex literal on the left (the decompiler's habit), the default
  --vars      two simple operands, either of which may be the variable the original named first

Each site is tried on its own with `quick_diff.py` (about a second) and kept only on a strict gain,
so the result is a per-site measurement rather than a sweep. Over `UI/MenuItems` 25 of 314 sites
paid, and several paid a lot: `MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick`
67.7% -> 80.5% from `7 < iVar3` becoming `iVar3 > 7`, `MenuItemRenderFunction_InGameMenu_MainButtons`
47.6% -> 57.7% from one `10 < param_1`, and `MenuItemActionHandler_CrusadeMap_Main` 33.0% -> 34.8%
over four sites. Confirm the batch with `reccmp_report.py --run cmp` as usual: a `quick_diff` gain
under about 0.005 has not been worth a commit.

usage:
  flipcmp.py [--literal|--vars] [FILE.cpp...]
"""

import os
import re
import subprocess
import sys

import common

QD = str(common.ROOT / "tools" / "reimplementation-helper" / "batch" / "quick_diff.py")
OPERAND = r"(?:\((?:int|short|uint|ushort)\))?[A-Za-z_][\w:]*(?:(?:\.|->)\w+|\[[\w:.\[\]+ ]+\])*"
LITERAL = re.compile(r"(0x[0-9a-fA-F]+|\d+) (<=|<|>=|>) (" + OPERAND + r")(?=[)\s])")
VARS = re.compile(r"(?<![\w)\]]) *(" + OPERAND + r") (<=|<|>=|>) (" + OPERAND + r")(?=[)\s])")
INV = {"<": ">", "<=": ">=", ">": "<", ">=": "<="}


def ratio(rel):
    out = subprocess.run([sys.executable, QD, rel, "-q"], capture_output=True, text=True,
                         cwd=str(common.ROOT)).stdout
    m = re.search(r"ratio ([0-9.]+)", out)
    return float(m.group(1)) if m else None


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    pat = VARS if "--vars" in sys.argv else LITERAL
    files = args or common.list_files()
    kept = tried = 0
    for rel in files:
        path = common.ROOT / rel
        src = common.read_text(path)
        if not pat.search(src):
            continue
        current = src
        base = ratio(rel)
        if base is None:
            continue
        i = 0
        while True:
            sites = list(pat.finditer(current))
            if i >= len(sites):
                break
            site = sites[i]
            tried += 1
            flipped = "%s %s %s" % (site.group(3), INV[site.group(2)], site.group(1))
            trial = current[:site.start()] + flipped + current[site.end():]
            common.write_text(path, trial)
            now = ratio(rel)
            if now is not None and now > base + 1e-9:
                print("KEEP  %+.4f  %.4f -> %.4f  %-52s  %s"
                      % (now - base, base, now, os.path.basename(rel), site.group(0).strip()[:50]))
                current, base, kept = trial, now, kept + 1
            else:
                i += 1
            common.write_text(path, current)
            sys.stdout.flush()
    print("kept %d of %d site(s) tried" % (kept, tried))
    return 0


if __name__ == "__main__":
    sys.exit(main())
