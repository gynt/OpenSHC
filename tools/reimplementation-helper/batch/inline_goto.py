"""Replace a forward `goto LAB;` with a copy of the block it jumps to, per site, keeping only the
sites that measure better.

Only the safe shape is touched: the label's enclosing block runs to the end of the function, so
falling out of it is the same as returning, and the copy is the label block's body followed by
`return;`. That is behaviour-preserving by construction (and only compiles in a void function - a
non-void one fails the compile and the site is dropped). A body containing a `case`, a `default:` or
another label is skipped, since copying one of those redefines it. The label itself stays where it
is unless no `goto` to it is left.

Expect most sites to lose: a `goto` in the decompiler output usually marks a block the original
compiler emitted once and jumped to, so writing it out twice makes MSVC emit it twice. Over
`UI/MenuItems` the quick_diff gate kept 9 of 46 sites and only 4 of those confirmed on reccmp -
`MenuItemRenderFunction_GameplayOptions_Buttons` 68.5% -> 76.5%,
`MenuItemActionHandler_General_ToolbarButtonPressed` 65.0% -> 67.6%,
`MenuItemRenderFunction_VideoOptions_Main` 75.7% -> 80.0% and
`MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons` 53.8% -> 54.4%. A second pass that applied
one site per file blind and measured on reccmp alone paid at 1 of 21
(`MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick` 46.4% -> 47.3%) and was ruinous
elsewhere: `MenuItemRenderFunction_RankingGames_Main` 97.6% -> 7.6%,
`MenuItemRenderFunction_SingleplayerMapChoice_MapTable` 96.8% -> 51.0%.

quick_diff also *underrates* this transform - `VideoOptions_Main` gained 0.0002 there and 4.3 points
on reccmp - so treat the gate as a filter against disasters rather than a predictor, and confirm
every kept site with `reccmp_report.py --run cmp`.

usage:
  inline_goto.py [FILE.cpp...]            dry run: list the eligible sites
  inline_goto.py --apply [FILE.cpp...]    measure each site with quick_diff and keep the gains
  inline_goto.py --blind=N [FILE.cpp...]  apply the Nth eligible site per file, for a reccmp pass

MAXLINES (default 40) caps the body size: a long shared tail is shared on purpose.
"""
import io
import os
import re
import subprocess
import sys

BATCH = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, BATCH)
import common

MAXLINES = int(os.environ.get("MAXLINES", "40"))
GOTO = re.compile(r"^([ \t]*)goto ([A-Za-z_]\w*);[ \t]*\r?\n", re.M)
LABELS = re.compile(r"^[ \t]*(case\b|default:|[A-Za-z_]\w*:[ \t]*$)", re.M)


def label_block(s, name):
    """Return (match, indent, body) for `name:` if its enclosing block ends the function."""
    m = re.search(r"^([ \t]*)" + name + r":[ \t]*\r?\n", s, re.M)
    if not m:
        return None
    depth = 0
    i = m.end()
    while i < len(s):
        c = s[i]
        if c == "{":
            depth += 1
        elif c == "}":
            if depth == 0:
                break
            depth -= 1
        i += 1
    else:
        return None
    if re.sub(r"[\s}]", "", s[i:]) != "":
        return None                       # the block does not run to the end of the function
    return m, m.group(1), s[m.end():i]


def reindent(body, src_indent, dst_indent):
    out = []
    for line in body.splitlines(True):
        if line.strip() and line.startswith(src_indent):
            line = dst_indent + line[len(src_indent):]
        out.append(line)
    return "".join(out)


def sites(s):
    out = []
    for g in GOTO.finditer(s):
        lb = label_block(s, g.group(2))
        if not lb:
            continue
        lm, indent, body = lb
        if lm.start() < g.end():          # forward jumps only
            continue
        if body.count("\n") > MAXLINES:   # a long tail is shared on purpose
            continue
        if LABELS.search(body):           # copying a label or a case would redefine it
            continue
        out.append((g, lm, indent, body))
    return out


def inlined(s, site):
    g, lm, indent, body = site
    copy = reindent(body, indent, g.group(1)) + g.group(1) + "return;\n"
    s = s[:g.start()] + copy + s[g.end():]
    if not re.search(r"\bgoto " + g.group(2) + r";", s):
        s = re.sub(r"^[ \t]*" + g.group(2) + r":[ \t]*\r?\n", "", s, count=1, flags=re.M)
    return s


def score(path):
    r = subprocess.run([sys.executable, os.path.join(BATCH, "quick_diff.py"), path],
                       capture_output=True, text=True)
    m = re.search(r"ratio (\d+\.\d+)", r.stdout)
    return float(m.group(1)) if m else None


def blind(files, n):
    """Apply the nth eligible site in each file with no quick_diff gate, for a reccmp pass."""
    for path in files:
        text = io.open(path, encoding="utf-8", newline="").read()
        found = sites(text)
        if n >= len(found):
            continue
        io.open(path, "w", encoding="utf-8", newline="").write(inlined(text, found[n]))
        common.format_file(path)
        print("applied  %-62s goto %s" % (os.path.basename(path), found[n][0].group(2)))


def main():
    args = [a for a in sys.argv[1:] if a != "--apply"]
    apply = "--apply" in sys.argv[1:]
    blindn = [a for a in args if a.startswith("--blind=")]
    if blindn:
        args = [a for a in args if not a.startswith("--blind=")]
        blind(args or [str(p) for p in common.list_files()], int(blindn[0].split("=")[1]))
        return
    files = args or [str(p) for p in common.list_files()]
    kept = tried = 0
    for path in files:
        text = io.open(path, encoding="utf-8", newline="").read()
        found = sites(text)
        if not found:
            continue
        if not apply:
            for g, lm, indent, body in found:
                print("%-60s goto %s  (%d lines)" % (
                    os.path.basename(path), g.group(2), body.count("\n")))
            continue
        base = score(path)
        if base is None:
            print("SKIP  %s (baseline compile failed)" % os.path.basename(path))
            continue
        i = 0
        while True:
            found = sites(text)
            if i >= len(found):
                break
            cand = inlined(text, found[i])
            io.open(path, "w", encoding="utf-8", newline="").write(cand)
            common.format_file(path)
            cand = io.open(path, encoding="utf-8", newline="").read()
            new = score(path)
            tried += 1
            label = found[i][0].group(2)
            if new is not None and new > base + 1e-9:
                print("KEEP  %+.4f  %.4f -> %.4f  %s  goto %s" % (
                    new - base, base, new, os.path.basename(path), label))
                text, base, kept = cand, new, kept + 1
            else:
                print("drop  %s  %.4f -> %s  goto %s" % (
                    os.path.basename(path), base, "fail" if new is None else "%.4f" % new, label))
                i += 1
            io.open(path, "w", encoding="utf-8", newline="").write(text)
    if apply:
        print("kept %d of %d site(s) tried" % (kept, tried))


if __name__ == "__main__":
    main()
