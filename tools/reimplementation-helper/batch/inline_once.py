"""Inline a local that is assigned a `DAT_Button*` read and then used exactly once.

Ghidra invents a local for every value it sees in a register, and where that value
is a button coordinate consumed by one argument of a call, the local forces the
value **live across any nested call in that argument list** - which costs a stack
slot the original does not have. The original reads the field straight into the
push (`mov eax, dword ptr [DAT_ButtonY]; push eax` at 0x464746), so inlining the
local removes the slot.

Found by `diff_slots.py`: an extra slot of ours with one or two uses. It was worth
`MenuItemRenderFunction_InGameMenu_MainButtons` 0.4992 -> 0.5975 and
`BuildingAndStatusMenu_AvailablePeasantsTextUpperRight` 0.7778 -> 0.8333 (36 = 36
instructions), so gate per function but expect it to pay where the slot is real.

usage: inline_once.py FILE.cpp... [--apply]
"""
import io
import re
import sys

ASSIGN = re.compile(r"^(?P<ind> *)(?:int |uint )?(?P<name>\w+) = (?P<val>[^;]*DAT_Button[XYWH]::instance[^;]*);$")
DECL = re.compile(r"^ *(?:int|uint) (?P<name>\w+);$")

apply = "--apply" in sys.argv
hits = 0
for path in [a for a in sys.argv[1:] if a.endswith(".cpp")]:
    lines = io.open(path, encoding="utf-8").read().split("\n")
    changed = False
    for i, line in enumerate(lines):
        m = ASSIGN.match(line)
        if not m:
            continue
        name, val = m.group("name"), m.group("val")
        uses = [j for j, l in enumerate(lines)
                if j != i and re.search(r"\b%s\b" % re.escape(name), l) and not DECL.match(l)]
        if len(uses) != 1:
            continue
        j = uses[0]
        # only inline into an argument list, which is where the slot comes from
        if not (lines[j].rstrip().endswith(",") or lines[j].rstrip().endswith(");")):
            continue
        sys.stdout.write("%s:%d  %s = %s  -> line %d\n"
                         % (path.split("/")[-1], i + 1, name, val[:40], j + 1))
        hits += 1
        if apply:
            lines[j] = re.sub(r"\b%s\b" % re.escape(name), val, lines[j], count=1)
            lines[i] = None
            for k, l in enumerate(lines):
                if l is not None and DECL.match(l) and DECL.match(l).group("name") == name:
                    lines[k] = None
                    break
            changed = True
    if apply and changed:
        io.open(path, "w", encoding="utf-8", newline="\n").write(
            "\n".join(l for l in lines if l is not None))
sys.stdout.write("%d site(s)%s\n" % (hits, "" if apply else " (dry run)"))
