"""Prune the build list of files that define a symbol another listed file already defines.

A list built by globbing a namespace can name both sides of style guide rule 13's
exception. Most `.cpp` here hold one function, but a few hold a main function *plus* the
helpers only it calls (`fillMemory.cpp` defines `fillMemory_ByteValue`, `_ShortValue`,
`_IntegerValue`, ...), and separate per-helper files exist alongside them
(`fillMemory_ByteValue.cpp`). Both define the same symbol, so the link fails with

    fatal error LNK1169: one or more multiply defined symbols found

`syntax_check.py` cannot catch this: every file compiles on its own and only the link
objects, so the first sign is a failed build after the whole list has been compiled.

Two detectors, because neither alone is enough:

  --markers   addresses that appear in more than one file's `// FUNCTION:` line. Cheap,
              runs without building, and found 11 collisions across IO. Blind to a
              grouped file that carries no markers at all.
  --log       the `LNK2005 ... already defined in` lines of the last build log. Needs a
              failed build first, but sees exactly what the linker saw - which is how
              `OS/OS.cpp` was caught defining `isEqualGUID` and `_wcsncpy` with no
              markers anywhere in it.

Run `--markers` before the first build of a new selection and `--log` if it fails anyway.
In each collision the file holding more functions is kept, since that is the file rule
13's exception exists for; with `--log` the file the linker names as "already defined in"
is kept.

usage:
  prune_duplicate_defs.py [--markers] [--log] [--apply]
"""

import argparse
import collections
import re
from pathlib import Path

import common

FUNCTION = re.compile(r"//\s*FUNCTION:\s*STRONGHOLDCRUSADER\s+(0x[0-9A-Fa-f]+)")
ALREADY = re.compile(r"^(\S+\.cpp)\.obj : error LNK2005: .* already defined in (\S+\.cpp)\.obj", re.M)


def by_markers(files):
    """{address: [files]} for every address more than one listed file claims."""
    addr = collections.defaultdict(list)
    count = {}
    for rel in files:
        try:
            found = FUNCTION.findall(common.read_text(rel))
        except OSError:
            continue
        count[rel] = len(found)
        for a in found:
            addr[a.lower()].append(rel)
    drop = set()
    for a, fs in addr.items():
        if len(fs) < 2:
            continue
        keep = max(fs, key=lambda f: count[f])
        drop.update(f for f in fs if f != keep)
        print("  %s  also in %s" % (a, ", ".join(Path(f).name for f in fs)))
    return drop


def by_log(files):
    """Files the linker reported as redefining a symbol another file already defined."""
    log = common.BUILD_DIR / "batch" / "build.log"
    if not log.exists():
        print("  no build log at %s" % log)
        return set()
    byname = {}
    for rel in files:
        byname.setdefault(Path(rel).name, rel)
    drop = set()
    for loser, winner in set(ALREADY.findall(log.read_text(errors="replace"))):
        if loser in byname:
            drop.add(byname[loser])
            print("  %-46s already defined in %s" % (loser, winner))
    return drop


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--markers", action="store_true", help="scan // FUNCTION: addresses")
    parser.add_argument("--log", action="store_true", help="scan the last build log for LNK2005")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    if not args.markers and not args.log:
        args.markers = args.log = True

    files = [f for f in common.list_files()]
    drop = set()
    if args.markers:
        print("by // FUNCTION: address:")
        drop |= by_markers(files)
    if args.log:
        print("by LNK2005 in the last build log:")
        drop |= by_log(files)

    print("\n%d file(s) to drop of %d%s"
          % (len(drop), len(files), "" if args.apply else "  (dry run; pass --apply)"))
    for f in sorted(drop):
        print("   %s" % f)
    if args.apply and drop:
        common.SOURCES_LIST.write_text(
            "\n".join(f for f in files if f not in drop) + "\n", newline="\n")
        print("wrote %s with %d file(s)" % (common.SOURCES_LIST, len(files) - len(drop)))


main()
