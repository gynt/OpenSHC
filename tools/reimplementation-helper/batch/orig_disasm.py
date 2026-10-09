"""Disassemble one original function from `_original/`, annotated with project symbols.

The authority on the original is the binary, not Ghidra's decompilation: Ghidra's C is a
reconstruction and has been wrong about constants, signs, comparison operators and whole
dropped blocks, while its (and our) disassembly of the same bytes is not in doubt. This
reads the instruction stream straight out of `_original/Stronghold Crusader.exe` with
capstone, so it needs no Ghidra instance and no reccmp run.

Unlike `quick_diff.py`, which normalizes globals to `G` and call targets to `F` so a
difflib ratio means something, this keeps every operand and resolves it:

  * a global address becomes its `src/OpenSHC/Globals/*.hpp` resolver name
  * a call target becomes the `*.func.hpp` name of the function at that address
  * a struct instance plus offset is printed as `<Name>+N`
  * jump targets inside the function become `L<n>:` labels, so the control flow reads

`--ours` disassembles our own build of the same function next to it (from the `/FA`
listing `quick_diff.py` produces), which is the view to use when a diff has drifted far
enough that reccmp's interleaving stops being readable.

usage:
  orig_disasm.py 0x466d10
  orig_disasm.py FILE.cpp              # takes the address from its // FUNCTION: line
  orig_disasm.py FILE.cpp --raw        # no symbol resolution, no labels
"""

import io
import os
import re
import struct
import sys

import capstone

import common

EXE = os.path.join(common.ROOT, "_original", "Stronghold Crusader.exe")

_d = io.open(EXE, "rb").read()
_pe = struct.unpack_from("<I", _d, 0x3C)[0]
_nsec = struct.unpack_from("<H", _d, _pe + 6)[0]
_opt = struct.unpack_from("<H", _d, _pe + 20)[0]
_ibase = struct.unpack_from("<I", _d, _pe + 24 + 28)[0]
_secs = [struct.unpack_from("<IIII", _d, _pe + 24 + _opt + 40 * i + 8) for i in range(_nsec)]
_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def file_off(va):
    r = va - _ibase
    for vs, vaddr, rs, rp in _secs:
        if vaddr <= r < vaddr + max(vs, rs):
            return r - vaddr + rp
    return None


def _scan(pattern, *dirs):
    """{address: name} from every header under the given source directories."""
    out = {}
    for d in dirs:
        root = os.path.join(common.ROOT, "src", d.replace("/", os.sep))
        for base, _, files in os.walk(root):
            for f in files:
                if not f.endswith(".hpp"):
                    continue
                try:
                    text = io.open(os.path.join(base, f), encoding="utf-8").read()
                except (IOError, UnicodeDecodeError):
                    continue
                for m in pattern.finditer(text):
                    gd = m.groupdict()
                    out.setdefault(int(gd["addr"], 16), gd["name"])
    return out


GLOBAL_RE = re.compile(
    r"MACRO_STRUCT_RESOLVER\([^,]+,[^,]+,\s*Address::SHC_3BB0A8C1_(?P<addr>0x[0-9A-Fa-f]+)\)\s*(?P<name>\w+)")
FUNC_RE = re.compile(
    r"Address::SHC_3BB0A8C1_(?P<addr>0x[0-9A-Fa-f]+),\s*&(?:[\w:]*::)?(?P<name>\w+)\s*\)")


def symbols():
    globals_ = _scan(GLOBAL_RE, "OpenSHC/Globals")
    funcs = _scan(FUNC_RE, "OpenSHC", "symbols")
    return globals_, funcs


def resolve_global(va, globals_):
    """The resolver covering `va`, as `Name` or `Name+N`."""
    if va in globals_:
        return globals_[va]
    # a field inside a struct instance: take the nearest resolver below it
    # a game state struct can be megabytes wide, so the window is generous; the
    # printed +N is the struct offset, which the type header maps to a field name.
    near = [a for a in globals_ if 0 < va - a <= 0x800000]
    if not near:
        return None
    a = max(near)
    return "%s+0x%x" % (globals_[a], va - a)


def disasm(va, limit=0x6000):
    """Instructions of the function at `va`, up to its last `ret`/`jmp`."""
    o = file_off(va)
    if o is None:
        raise SystemExit("address 0x%x is not in any section" % va)
    out = []
    maxtarget = va
    prev = None
    for i in _md.disasm(_d[o:o + limit], va):
        if prev in ("ret", "jmp") and i.address > maxtarget:
            break
        out.append(i)
        if i.mnemonic.startswith("j") or i.mnemonic == "call":
            try:
                t = int(i.op_str, 16)
                if i.mnemonic != "call" and va <= t < va + limit:
                    maxtarget = max(maxtarget, t)
            except ValueError:
                pass
        prev = i.mnemonic
    return out


def render(va, raw=False):
    ins = disasm(va)
    globals_, funcs = ({}, {}) if raw else symbols()

    labels = {}
    if not raw:
        targets = set()
        for i in ins:
            if i.mnemonic.startswith("j"):
                try:
                    targets.add(int(i.op_str, 16))
                except ValueError:
                    pass
        for n, t in enumerate(sorted(x for x in targets if any(i.address == x for i in ins))):
            labels[t] = "L%d" % (n + 1)

    lines = []
    for i in ins:
        text = (i.mnemonic + " " + i.op_str).rstrip()
        if not raw:
            if i.mnemonic == "call" or i.mnemonic.startswith("j"):
                try:
                    t = int(i.op_str, 16)
                    if t in labels:
                        text = i.mnemonic + " " + labels[t]
                    elif t in funcs:
                        text = i.mnemonic + " " + funcs[t]
                    else:
                        text = "%s 0x%x" % (i.mnemonic, t)
                except ValueError:
                    pass
            else:
                def sub(m):
                    v = int(m.group(0), 16)
                    if v < 0x400000:
                        return m.group(0)
                    return resolve_global(v, globals_) or m.group(0)

                text = re.sub(r"0x[0-9a-f]{6,8}", sub, text)
        pre = (labels.get(i.address, "") + ":") if i.address in labels else ""
        lines.append("%-5s %08x  %s" % (pre, i.address, text))
    return lines


def address_of(arg):
    if re.match(r"^(0x)?[0-9A-Fa-f]+$", arg) and not os.path.exists(arg):
        return int(arg, 16)
    path = arg if os.path.isabs(arg) else os.path.join(common.ROOT, arg.replace("/", os.sep))
    src = io.open(path, encoding="utf-8").read()
    m = re.search(r"FUNCTION: STRONGHOLDCRUSADER (0x[0-9A-Fa-f]+)", src)
    if not m:
        raise SystemExit("no // FUNCTION: line in " + arg)
    return int(m.group(1), 16)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        raise SystemExit(__doc__)
    raw = "--raw" in sys.argv
    for arg in args:
        va = address_of(arg)
        print("##### 0x%x  (%s)" % (va, os.path.basename(arg)))
        for line in render(va, raw):
            print(line)


if __name__ == "__main__":
    main()
