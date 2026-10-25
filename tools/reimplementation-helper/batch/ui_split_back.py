"""Write the improved UI sources back onto their own `reimpl/UI-*` branches.

The eight branches are measured together in one worktree (see ui_status.py), so the improvements all
sit in one tree and have to be handed back to the branch each file came from. This builds one commit
per branch with git plumbing and a temporary index, which means no checkout is disturbed and the
branches need not be checked out at all.

Each commit carries only that branch's own files plus its status lines, so the branches stay disjoint
exactly as they were before.

usage:
    ui_split_back.py --base-remote origin [--only UI-Core] [--message "..."] [--dry-run]

Afterwards push with `git push origin reimpl/UI-Core:reimpl/UI-Core` (or --push).
"""

import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

parser = argparse.ArgumentParser()
parser.add_argument("--base-remote", default="origin")
parser.add_argument("--base-ref",
                    help="base every branch on this single ref instead of "
                         "<base-remote>/reimpl/<branch>. The reimpl/UI-* branches are 2309 "
                         "commits behind development and do not have the field names the ported "
                         "sources use, so a commit written on them would not compile; basing on "
                         "development gives a branch that builds.")
parser.add_argument("--ref-suffix", default="",
                    help="appended to the written ref name, so a development-based result does "
                         "not overwrite the branch it came from.")
parser.add_argument("--only")
parser.add_argument("--message", default="")
parser.add_argument("--push", action="store_true")
parser.add_argument("--dry-run", action="store_true")
parser.add_argument("--extra", action="append", default=[],
                    help="a shared file (a header, say) to include in every branch's commit; "
                         "repeatable. Use it for a header the owned sources depend on, which "
                         "ui_own.json does not list.")
args = parser.parse_args()

STATUS = "status/addresses-SHC-3BB0A8C1.txt"


def git(*a, **kw):
    r = subprocess.run(["git"] + list(a), capture_output=True, text=True, **kw)
    if r.returncode:
        sys.exit("git %s failed:\n%s%s" % (" ".join(a), r.stdout, r.stderr))
    return r.stdout


own = json.loads(Path("ui_own.json").read_text())
diff = common.load_diff()
pct = {}
for f, entry, addr in common.entries(diff):
    if entry:
        pct[f.replace("\\", "/")] = (addr.lower(), float(entry["matching"]),
                                     common.normalized_ratio(entry))

for branch, files in sorted(own.items()):
    if args.only and args.only not in branch:
        continue
    ref = "refs/heads/reimpl/%s%s" % (branch, args.ref_suffix)
    base = args.base_ref or "%s/reimpl/%s" % (args.base_remote, branch)
    base_sha = git("rev-parse", base).strip()

    env = dict(os.environ)
    with tempfile.TemporaryDirectory() as td:
        env["GIT_INDEX_FILE"] = os.path.join(td, "index")
        subprocess.run(["git", "read-tree", base_sha], env=env, check=True)

        # the branch's own sources, as they now stand in this worktree
        changed = []
        for f in list(files) + args.extra:
            new = Path(f).read_bytes()
            old = subprocess.run(["git", "show", "%s:%s" % (base_sha, f)], capture_output=True)
            if old.returncode == 0 and old.stdout == new:
                continue
            sha = subprocess.run(["git", "hash-object", "-w", "--stdin"], input=new,
                                 capture_output=True, check=True).stdout.decode().strip()
            subprocess.run(["git", "update-index", "--add", "--cacheinfo", "100644,%s,%s" % (sha, f)],
                           env=env, check=True)
            changed.append(f)

        # that branch's status lines, from the current measurement
        status_text = subprocess.run(["git", "show", "%s:%s" % (base_sha, STATUS)],
                                     capture_output=True, text=True).stdout
        lines = status_text.split("\n")
        touched = 0
        for i, line in enumerate(lines):
            m = re.match(r"(SHC_3BB0A8C1_)(0x[0-9A-Fa-f]+)( \| )([0-9.]+)%( \| )(.*)$", line.rstrip("\r"))
            if not m:
                continue
            addr = m.group(2).lower()
            for f in files:
                if f in pct and pct[f][0] == addr:
                    raw, norm = pct[f][1], pct[f][2]
                    note = "Reimplemented" if norm >= 1.0 else "Reimplemented, asm differs"
                    new_line = "%s%s | %.1f%% | %s" % (m.group(1), m.group(2), raw * 100, note)
                    if new_line != line.rstrip("\r"):
                        lines[i] = new_line + ("\r" if line.endswith("\r") else "")
                        touched += 1
                    break
        if touched:
            blob = "\n".join(lines).encode()
            sha = subprocess.run(["git", "hash-object", "-w", "--stdin"], input=blob,
                                 capture_output=True, check=True).stdout.decode().strip()
            subprocess.run(["git", "update-index", "--add", "--cacheinfo", "100644,%s,%s" % (sha, STATUS)],
                           env=env, check=True)

        if not changed and not touched:
            print("  %-24s unchanged" % branch)
            continue
        if args.dry_run:
            print("  %-24s would commit %d source(s), %d status line(s)" % (branch, len(changed), touched))
            continue

        tree = subprocess.run(["git", "write-tree"], env=env, capture_output=True, text=True,
                              check=True).stdout.strip()
        msg = args.message or "reimplement: improve %d %s function(s)" % (len(changed), branch[3:])
        msg += ("\n\nMeasured in a combined worktree with every UI branch's files in one build list and\n"
                "both resolver sets enabled, which is the configuration the status percentages were\n"
                "taken in.\n")
        commit = subprocess.run(["git", "commit-tree", tree, "-p", base_sha, "-m", msg],
                                capture_output=True, text=True, check=True).stdout.strip()
        git("update-ref", ref, commit)
        print("  %-24s %s  %d source(s), %d status line(s)" % (branch, commit[:9], len(changed), touched))
        if args.push:
            git("push", args.base_remote,
                "%s:refs/heads/reimpl/%s%s" % (commit, branch, args.ref_suffix))
