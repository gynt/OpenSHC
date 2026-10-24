"""Find global fields we read more often than the original does.

usage: diff_reloads.py [NAME-SUBSTRING] [--min N]

MSVC cannot keep a global field in a register across a store through a pointer,
because the store may alias it.  The original therefore reads such a field once
into a local and uses the local afterwards; Ghidra turns that local back into
repeated field accesses, and every one of them costs a reload.  The fix is to
name the value once:

    int borderWidth = WindowAndDirectDraw.mainMenuBorderWidth;
    menu->xPosition = borderWidth;
    MenuHandlerState.x = borderWidth;

That single pattern took eighteen UI::MenuViews functions to 100%.

This counts every `[I<Type>::instance+N]` (and `[I<Type>::instance]`) read per
side of the reccmp diff and reports the fields where our count is higher.  It
is a count, not a pairing, so it also fires when the streams have drifted for
an unrelated reason - read the diff before editing.
"""

import collections
import pathlib
import re
import sys

import common

READ = re.compile(r"^(?:mov|movzx|movsx|cmp|add|sub|test|lea|and|or|xor|imul)\s+[^,]+,\s*(?:dword|word|byte)?\s*ptr\s*\[([^\]]+)\]")
RESOLVER = re.compile(r"StructResolver::Instance<(.+?),\d+>::instance")

args = [a for a in sys.argv[1:] if not a.startswith("--")]
want = args[0] if args else ""
minimum = int(sys.argv[sys.argv.index("--min") + 1]) if "--min" in sys.argv else 1


def key(text):
    m = READ.match(text.split("	")[0].strip())
    if not m:
        return None
    inside = m.group(1).replace(" (OFFSET)", "").replace(" (DATA)", "").strip()
    if "StructResolver::Instance<" not in inside:
        return None
    if "+" in inside and not inside.split("+")[-1].strip().startswith("0x")             and not inside.split("+")[-1].strip().isdigit():
        return None
    return RESOLVER.sub(lambda m: m.group(1).split("::")[-1], inside)


for f, e, address in common.entries(common.load_diff()):
    if e is None:
        continue
    name = pathlib.Path(f).stem
    if want and want not in name:
        continue
    side = {"orig": collections.Counter(), "recomp": collections.Counter()}
    for hunk in e.get("diff") or []:
        for block in hunk[1]:
            for kind, rows in block.items():
                for row in rows:
                    k = key(row[1])
                    if k is None:
                        continue
                    if kind == "both":
                        side["orig"][k] += 1
                        side["recomp"][k] += 1
                    else:
                        side[kind][k] += 1
    extra = {k: n - side["orig"].get(k, 0) for k, n in side["recomp"].items()
             if n - side["orig"].get(k, 0) >= minimum}
    if extra:
        print("### %s %.1f%%" % (name, e.get("matching", 0) * 100))
        for k, n in sorted(extra.items(), key=lambda kv: -kv[1]):
            print("  +%d  %s" % (n, k))
