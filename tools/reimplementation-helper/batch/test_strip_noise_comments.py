"""Cases for strip_noise_comments.py's noise test.

A block goes only when every content line is a Ghidra complaint or the import's provenance
marker. The cases that must survive are the ones the indiscriminate version ate: a plain note,
a `fixme:` entry, and a block that mixes a note with a noise line.

usage:
  test_strip_noise_comments.py
"""

import strip_noise_comments as strip

CASES = [
    # a single analysis complaint
    (["    /*", '      WARNING: Enum "MappersEnum": Some values do not have unique names', "     */"], True),
    # the import's provenance marker
    (["    /*", "      decompilerscript: committed: 2025-01-30 21:57:43.216000", "     */"], True),
    # several complaints in one block
    (["    /*", "      WARNING: Type propagation algorithm not settling",
      "      WARNING: Restarted to delay deadcode elimination for space: ram", "     */"], True),
    # a hand-written note
    (["    /*", "      returns area (a value >= 1) if the unit can get there, if not, 0", "     */"], False),
    # a fixme entry
    (["    /*", "      fixme:bug: the index parameter is off by -1 for brush indices larger than 6", "     */"], False),
    # a note sharing a block with a noise line: the note wins, the block stays
    (["    /*", "      called when placing a wall in the editor",
      "      decompilerscript: committed: 2025-01-30 21:57:43.216000", "     */"], False),
    # a note that merely mentions a warning is still a note
    (["    /*", "      the WARNING: above is wrong, the enum is fine", "     */"], False),
    # an empty block carries nothing to judge, so it is not noise
    (["    /*", "     */"], False),
]

if __name__ == "__main__":
    failures = 0
    for block, want in CASES:
        got = strip.is_noise(block)
        ok = got == want
        failures += not ok
        print("%-4s %-6s %s" % ("ok" if ok else "FAIL", "noise" if want else "keep",
                                " / ".join(strip.content_lines(block))[:90]))
    print("\n%d/%d passed" % (len(CASES) - failures, len(CASES)))
    raise SystemExit(1 if failures else 0)
