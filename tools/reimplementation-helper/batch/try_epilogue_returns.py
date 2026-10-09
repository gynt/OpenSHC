"""Restore the `return` Ghidra drops from a guard whose body ends in the epilogue's store.

`try_empty_returns.py` handles the guard whose body was *only* a `return`. This handles
the other half of the same artefact, which is far more common and which
`find_dead_store.py` cannot see: the original's epilogue is not a bare `pop`/`ret` but
carries a store - a menu render function sets `drawBufferChoiceValue = RT_MAP_GAME` on the
way out - so a guard that jumps there appears in the decompilation as

    if (cond) { ...; DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = RT_MAP_GAME; }
    <more code>

with the `return` gone. The store survives, so the guard is not empty and the following
code does not repeat the store, which is why the dead-store scan misses it. Our build then
runs everything after the guard that the original returns before - a behaviour difference,
not a style question.

`epilogue_jumps.py` supplies the evidence: it reports which globals the original's `ret`
blocks store. This takes those globals and appends `return;` to every guard body in the
source whose last statement assigns one of them and which is followed by more code.

A guard ending in that store but genuinely falling through would be mis-rewritten, so read
the diff and gate on reccmp; across `UI::MenuItems` 49 functions show the deficit.

usage:
  try_epilogue_returns.py FILE.cpp... [--apply]
"""

import io
import os
import re
import sys

import common
import epilogue_jumps as ej
import orig_disasm as od


def epilogue_globals(va):
    """Resolver names the original's `ret` blocks store into."""
    ins = od.disasm(va)
    eps = ej.epilogue_blocks(ins)
    globals_, _ = od.symbols()
    names = set()
    for addr, stores in eps.items():
        for text in stores:
            for m in re.finditer(r"0x[0-9a-f]{6,8}", text):
                name = od.resolve_global(int(m.group(0), 16), globals_)
                if name:
                    names.add(name.split("+")[0])
    return names


def sites(lines, names):
    """Lines holding `<store>;` as the last statement of a guard with code after it."""
    store = re.compile(r"^(\s*)(?:" + "|".join(re.escape(n) for n in names) + r")::instance\b.*;\s*$")
    out = []
    for j, line in enumerate(lines):
        m = store.match(line)
        if not m:
            continue
        # the statement may be wrapped over several lines; find its first line
        k = j
        while k > 0 and not lines[k - 1].rstrip().endswith((";", "{", "}")):
            k -= 1
        ind = len(lines[k]) - len(lines[k].lstrip())
        if ind < 4 or j + 1 >= len(lines):
            continue
        close = lines[j + 1]
        if close.strip() != "}" or len(close) - len(close.lstrip()) != ind - 4:
            continue
        nxt = lines[j + 2].strip() if j + 2 < len(lines) else ""
        if nxt.startswith("else") or nxt in ("}", "") or nxt.startswith("return"):
            continue
        out.append((j, ind))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    if not args:
        raise SystemExit(__doc__)
    total = 0
    for rel in args:
        path = rel if os.path.isabs(rel) else os.path.join(common.ROOT, rel.replace("/", os.sep))
        src = io.open(path, encoding="utf-8").read()
        try:
            names = epilogue_globals(od.address_of(path))
        except Exception as exc:                                  # noqa: BLE001
            print("--     %s  (%s)" % (os.path.basename(path), exc))
            continue
        if not names:
            print("--     %s  (no store in the epilogue)" % os.path.basename(path))
            continue
        lines = src.split("\n")
        found = sites(lines, names)
        print("##### %-62s %d site(s)  [%s]"
              % (os.path.basename(path), len(found), ", ".join(sorted(names))))
        for j, ind in found:
            print("   line %-5d %s" % (j + 1, lines[j].strip()[:80]))
        if apply_ and found:
            for j, ind in sorted(found, reverse=True):
                lines.insert(j + 1, " " * ind + "return;")
            io.open(path, "w", encoding="utf-8", newline="\n").write("\n".join(lines))
        total += len(found)
    print("---- %d site(s)%s" % (total, "" if apply_ else " (dry run, pass --apply)"))


if __name__ == "__main__":
    main()
