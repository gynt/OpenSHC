# OpenSHC - AI Agent Guide

## Overview

OpenSHC is an open-source reimplementation of **Stronghold Crusader 1.41**.

The project builds as a DLL that hooks into the original game, progressively replacing original functions with native C++ implementations. The long-term goal is a complete, maintainable, binary-compatible reimplementation.

## Repository Layout

```text
src/
    OpenSHC/       Reimplemented game code
    core/          Runtime infrastructure
    precomp/       Shared headers and compile infrastructure
    symbols/       Original symbol declarations

tools/
    mcp/           MCP server and Ghidra integration
    import/        Ghidra import and synchronization utilities
    reimplementation-control/
                   Project maintenance scripts

reccmp/            Binary comparison tooling

dependencies/      Third-party libraries

status/            Address lists and project progress
```

## Build

- Build system: **CMake**
- Compiler: **MSVC (x86)**

A compatible MSVC toolchain (`MSVC1400-SP1`) is included for consistent code generation. It corresponds to **Visual Studio 2005 SP1**.

Building requires an original **Stronghold Crusader 1.41** installation linked through `_original/`.

## Development Principles

OpenSHC is both a software project and a reverse-engineering effort.

Prioritize:

- correct game behaviour
- binary compatibility
- maintainable C++

Decompiler output, imported symbols, and reconstructed types are valuable references, but are not always authoritative.

Preserve the existing project structure and coding style. Avoid architectural changes or refactoring that alter the existing file and directory structure.

When reimplementing a function, first inspect neighboring implementations and established project patterns. Use decompiler output as a reference, but do not rely on it as the only source of truth.

The C++ level and style is C++98/C++03. Do not use features and structures of C++11 or later.

## Reimplementation Structure

Function and struct resolvers are used as proxies in place of the original game functions and structs.

Reimplementation code interacts with resolvers rather than directly referencing the original symbols. Address identity mismatches are expected when resolvers are inactive and use the original game's addresses.

The following files are primarily generated and should only be modified when explicitly requested:

- `.hpp` files mostly contain generated headers per namespace or class.
- `.hpp` files in `src/OpenSHC/Globals` contain struct resolvers.
- `.func.hpp` files contain function resolvers for functions belonging to a namespace or class.

Implementation code belongs in `.cpp` files:

- Files are named after the function or function group they implement.
- Files are placed in a folder matching the namespace or class of the corresponding header.

## Development Tools

### Implementation Cheat Sheet

The [Implementation Cheat Sheet](IMPLEMENTATION_CHEAT_SHEET.md) is a reference for patterns and oddities of the compiler that are found during the reimplementation process.
Scan this document if you are instructed to reimplement a function.

### MCP Server (`tools/mcp`)

Provides project-specific utilities including:

- retrieving Ghidra decompilations
- compiling individual functions
- comparing generated assembly
- updating local source lists

### Ghidra Import (`tools/import`)

Imports and synchronizes Ghidra-exported data.

### Reimplementation Control (`tools/reimplementation-control`)

Scripts for enabling implementations and maintaining project state.

### Reimplementation Control (`tools/reimplementation-helper`)

Scripts for supporting implementation. Usually already integrated into skills.

### Batch Helpers (`tools/reimplementation-helper/batch`)

Python scripts for working on every function listed in `cmake/openshc-sources.txt.local` at once (see its README):
quiet builds, `/Zs` syntax checks, a reccmp report (match %, normalized % ignoring call targets, snapshots, compact diffs),
showing and splicing many function bodies, one progress commit per changed function, and repairing sources after
`*_Func` namespace refactors. Prefer them over ad-hoc scripts when a task spans many functions.

To pick the next target, `rank_functions.py` orders by lines x (1 - match) rather than by percentage, and
`scan_dispatch.py` lists every function whose dispatch form disagrees with the original (a jump table on one side and an
if/else-if chain on the other), with `scan_chains.py` finding the chains to convert. `try_styles.py` compiles and
measures several hand-written variants of one function and keeps the best, which is the only reliable way to settle a
style question - see the note on unpredictable styles below. `declare_at_use.py`, `decast.py`, `deparen.py` and
`undiv.py` undo decompiler artefacts across a whole selection; run `test_deparen.py` and `test_undiv.py` after
touching the precedence table or the division patterns those two rely on.

The rewriting scripts take a path filter and default to a dry run. Read the diff before building, then run
`syntax_check.py` on what you touched: reviewing a diff catches a wrong transformation but not a rewrite that leaves
the surrounding text unparseable, and `/Zs` finds that in seconds instead of a full build.

**`build.bat` exits 0 even when compilation failed**, which leaves the previous DLL and the previous `diff.json` in
place, so every reccmp number then describes the code as it was before the edit. An "unchanged" percentage is the
symptom. `build_quiet.py` now exits non-zero on `BUILD_FAIL` so `build && report` stops, and `load_diff()` warns when a
source file is newer than `diff.json`; `reccmp_report.py` also warns when the last run covers only part of the build
list, which is what `try_styles.py` leaves behind while it narrows the list to one function. `try_styles.py` now
restores the list *and* rebuilds before exiting, because restoring the list alone is not enough - the DLL is still
the narrowed one, so `diff.json` keeps reporting a single function at the last variant's score and `--run` cannot
repair it. That rebuild costs a few minutes per invocation and is worth paying.

`try_styles.py` reports four decimals, and its tie test is exact. It used to parse the one-decimal percentage
`reccmp_report.py` prints, so anything sharing a first decimal compared as a tie - which is how a variant 0.02
points *below* its baseline got kept as "identical, so pick the readable one". Treat a tie from an older run as
unverified.

`orig_asm.py NAME` prints the **original** instruction stream of one function from the last reccmp run, rather than the
interleaved diff `reccmp_report.py diff` gives you. Use it when the diff comes back truncated, or when you need the
original's own jump targets and fall-through order to reconstruct control flow. It reads `reccmp/dll/diff.json`, so it
works with no Ghidra connection.

reccmp cuts the original's stream at the length of *our* function, so when ours is shorter the original's tail is
simply missing from the diff (it reads as "the original has no `ret`"). `quick_diff.py FILE.cpp` disassembles the whole
original function from `_original/` and diffs it against a `/FA` compile of that one file in about six seconds, with
no link and no reccmp run. Use it to try source variants - it is what broke the `AI::AICState` plateau that
`try_styles.py` at several minutes per variant had declared allocator-bound - and confirm the result with reccmp.

`orig_asm.py NAME --stats` reports the signals that decide *how* a function has to be reimplemented. Check it before
restyling anything large:

- `mov reg, 0` - no compiler materialises zero that way, so that block is handwritten assembly and belongs in an
  `__asm` block rather than C++. Functions are never `__declspec(naked)`: write a normal function, keep the
  compiler-generated statements as C++, and refer to parameters, locals and `this` by name. Prettify offsets with
  MSVC's struct-member asm syntax (`mov esi, dword ptr [eax]TileMapState.ptr_LogicLayer`) - `::` is not parseable in an
  asm operand, so a resolver global cannot be named there.
- a frame pointer plus a `this` spill - the original was built without optimisation. Add `#pragma optimize(, off)`
  around the function; inline asm alone does not disable optimisation. Then match the reported **frame size** exactly,
  which is usually the single biggest win, because every local displacement shifts otherwise. Merge locals that share a
  slot and reproduce dead stores. At `/Od` prefer a nested `if` over an early `continue` (the original inverts the test
  and jumps to the loop's continue trampoline), and declare locals together at the top of the function.
- a jump table - Ghidra usually renders the dispatch as a call through an unnamed pointer array and drops the arms, so
  rebuild the `switch` from the byte and jump tables instead of restyling the decompiler output.

`diff_triage.py` gives one line per function in the build list and says whether more source work can pay at all: it
flags a `sub esp` frame-size mismatch (`FRAME`), byte-sized stack slots we have and the original does not (`BYTE`), a
cold return block we inline where the original outlines it (`RET`), and the case where only register and stack-slot
*naming* is left (`alloc-only`). Chase a `FRAME` flag with `diff_slots.py NAME`, which lists every `[esp + N]` slot per
side: one extra slot is one local the original does not have, and removing it has been worth 10-30 points.
`diff_jcc.py` finds comparisons whose operator is one strictness step off the original (`jl`/`jle`, `jg`/`jge`) - these
are real off-by-one bugs where Ghidra decompiled the condition wrongly, so confirm a fix by re-running that tool rather
than by the percentage. `diff_types.py` is its counterpart away from comparisons: `movsx` against `movzx` for one field
means the field's signedness is wrong in the generated header, and `add` against `sub` of the same magnitude is a sign
error in a formula - that is how `2400 / n + 40` was caught being `- 40`, which Ghidra had decompiled with the wrong
sign. It carries only those two rules on purpose: a third, "same instruction with a different constant", was tried and
dropped because every hit it produced was a loop-induction stride rather than a constant the source chose.
`reorder_search.py FILE NAME` hill-climbs the match % by reordering independent statements,
which is the only lever left once a function is `alloc-only`; it pays about one move in ten, and mostly where the
statements sit between two calls or on a loop back-edge.

### Binary Comparison (`reccmp`)

Compares generated binaries against the original executable.

**Check the struct resolver flags before trusting any comparison.** The global data
reimplementations are enabled by flipping the boolean in every `MACRO_STRUCT_RESOLVER` in
`src/OpenSHC/Globals/*.hpp`, which is deliberately never committed, so a rebase, a fresh clone or a
`git checkout` silently turns them all off. With them off, absolute addresses stop being
distinguishable and the raw match drops across the whole namespace while the normalized match barely
moves - which reads exactly like a catastrophic self-inflicted regression. One rebase cost ~3 points
of namespace average this way, and a snapshot taken on one side of that change cannot be compared
with anything measured on the other. `tools/reimplementation-control/enable_reimplemented_data.py`
turns them back on; `git checkout -- src/OpenSHC/Globals/` turns them off again.

## Working on Many Functions

When restyling or improving a large set of functions, work in batches (e.g. per folder) and verify each batch:

0. Switch the global data reimplementations on (the `MACRO_STRUCT_RESOLVER` flag in `src/OpenSHC/Globals/*.hpp`)
   before measuring anything, and never commit those files. With the resolvers inactive, reccmp collapses every
   absolute address to one token, so a `this->` that should be the global instance, and a wrong field offset, both
   look like a match.
1. Save a baseline: `reccmp_report.py --run save base.json`.
2. Rewrite the bodies (`show_functions.py` -> edit -> `splice_functions.py`), then `syntax_check.py` and `build_quiet.py`.
3. Compare with `reccmp_report.py --run cmp base.json`; revert or rework every `WORSE` function and inspect the rest with `diff`.
4. Commit with `commit_progress_batch.py` (100% "Reimplemented" when only call targets differ, otherwise the % with a short blocker remark).
   Field and parameter type changes to generated headers go in a commit of their own, separate from the `.cpp` work.

Replace a function body whole. Do not patch one by slicing its existing text: a scripted edit that cuts the body at
some marker and splices a fragment back silently loses brace balance, and `clang-format` then reflows the damage into
something that still looks plausible - a `do { ... } while (cond);` comes back as a bare `while (cond);` with the loop
body detached above it. `syntax_check.py` does catch it, but the rewrite is wasted and the cause is not obvious from
the error. This is why `splice_functions.py` replaces whole bodies; when editing by hand or from your own script, emit
the function from its signature through its closing brace, keeping the `// FUNCTION:` line above it untouched.

Style expected of reimplemented code:

- Declare variables where they are first used; access fields repeatedly instead of copying them into locals
  (the compiler created the locals), unless the diff shows the original really used a local. Whether naming a
  repeatedly read field helps is not predictable and has to be measured per function: it gained 18% in one function
  where the value fed distance arithmetic and lost 12% in another where it fed a chain of `== constant` tests, which
  MSVC compiles against the memory operand directly. The same applies to other style choices - reusing one pointer for
  two rows helped one function and hurt its near-identical neighbour. Use `try_styles.py` rather than reasoning about it.
- Use `for` loops (loop variable declared in the `for`), early returns instead of nested if/else, no `goto`,
  no pointer variables walking over arrays or structs, named fields and enum constants instead of offsets and magic numbers.
  The early-return preference has one known exception, still tentative - see the note on arms sharing a tail among the
  diff patterns below.
- Never change the `// FUNCTION:` address line; keep generated headers untouched unless asked.
- Write sources as UTF-8 with LF line endings.

When removing the decompiler's `goto`s, check how many predecessors the target block has. A `LAB_*` reached from
several places has to be **duplicated** into each path; dropping it instead still compiles and is silent. Three such
bugs sat in one function (`processEntityDamageToUnit`): a damage value never assigned so the variable still held an
unrelated height, a `break` left outside its `if` that made six `switch` arms unreachable, and a `case` that fell out
of the switch leaving the value it should have set uninitialised. Fixing them was also worth 7.7% of match, so a
suspicious dead store is worth decompiling for rather than deleting. Note this is the opposite of the duplicate-tail
pattern below, where our shared block should have been two separate branches - check the predecessor count either way.

Ghidra also drops the `return` at the end of an `if` body, because a `return` there carries no data flow. The guard
survives as a plain `if (cond) { ... }`, which still compiles - and when the body's last statement is a store that the
code after the `if` repeats, MSVC deletes that store as dead and the *whole guard disappears from our binary*. An
"unchanged" guard that generates no instructions at all is the symptom. This was the largest single source of
mismatch across `UI::MenuItems`, worth 10-30 points per function and two normalized 100%s on its own
(`MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol` 72.7% -> 100%,
`MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusReturn` 83.9% -> 100%). Two shapes give it away:

- `if (cond) { ...; X = A; }` immediately followed by `X = B;` at the enclosing level - the inner store is dead, so
  the original returned out of the guard.
- `if (cond) {}` with an *empty* body - the `return` was the block's only statement.

`try_returns.py` tries a `return;` at every `if` body that could carry one and keeps the sites `quick_diff.py` scores
better, so a function settles in about a minute. Where the guard wraps the rest of the function, prefer the inverted
`if (hot) { ...; return; } cold;` shape over a guard at the top - and when the original's arm sits
*after* the fall-through path, write the condition in the `!=` sense with the special case in an `else`:
`if (param_1 != -5) { hot } else { cold }` is what makes MSVC emit the original's forward `je` and place the arm out of
line, where `if (param_1 == -5) { cold; return; } hot;` emits `jne` and inlines it.
`MenuItemRenderFunction_EditScenario_StartDate` went 0.41 -> 0.80 on `quick_diff.py`'s ratio from that one change of
sense, with nothing else altered: the original's `je` jumps *forward* to the cold block,
which is what MSVC emits only when the cold path is written last (same lever as `diff_triage.py`'s `RET` flag).

These returns often only pay **in combination**, which a greedy per-site search misses.
`MenuItemRenderFunction_VideoOptions_Main` needed three at once - two from empty bodies and one after a render call -
because every intermediate state still had the control flow wrong somewhere, so no single site improved the score and
`try_returns.py` accepted none of them. `try_empty_returns.py` tries a whole file's empty bodies together first and
falls back to one at a time. Read the jump target before trusting a big winner: an empty body is a `return` only when
the original's `jne` goes to the shared `pop/ret` epilogue (`orig_disasm.py` labels it, and in VideoOptions all three
went to `L15`, which *is* the epilogue). A jump to any other block compiles just as happily and is simply wrong.

The epilogue is often not a bare `pop`/`ret`. A menu render function sets
`drawBufferChoiceValue = RT_MAP_GAME` on the way out, so that store sits in the same block, and a guard jumping there
decompiles as `if (cond) { ...; X = <epilogue value>; }` with the `return` gone. The store survives, the following code
does not repeat it, and `find_dead_store.py` therefore cannot see any of these - 49 functions across `UI::MenuItems`
had the deficit. `epilogue_jumps.py` reports what each `ret` block stores, and `try_epilogue_returns.py` appends the
`return;` at every guard body in the source that ends in one of those stores.

Unlike the empty-body case this one **must be gated per function and most of it thrown away**: an empty
`if (cond) {}` compiles to nothing, so filling it is unambiguous, but a guard that already emits the store is valid
code either way and the counting argument is not per-site evidence. Of 195 sites, 21 functions improved and 29
measured worse; keeping only the 21 was worth 0.5 of namespace average (`AiLordSelect_Main` 84.4% -> 95.3%,
`EngineerAndMonkPortraits` 44.8% -> 67.1%) while the blanket application lost 0.65. Do not keep a site the
measurement does not support.

`epilogue_jumps.py FILE.cpp` answers that question for a whole file at once, from the binary rather than from a
score: it prints every conditional jump in the original that lands on a `pop`/`ret` block, in address order, which is
the order the guards appear in. Compare the count with our `return;` count before trying anything - a function with
more epilogue jumps than we have returns is missing control flow, and the empty bodies can simply be filled. This
turned the lever from a search into a check and cleared 63 sites across `UI::MenuItems` in one pass, including every
site `try_empty_returns.py` had rejected on its quick_diff gate. The same guard shape also hides at the top of a
function as one `if (A && B && C) { entire body }`: where the original shows one epilogue jump per conjunct, the
original wrote them as separate early returns (`MenuItemActionHandler_InGameMenu_TriggerPlaceWallCommand`), and the
nested form costs the whole prologue.

Ghidra drops the fall-through out of a block as readily as the `return` out of a guard. In
`MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange` the time-gated animation block ends in `jmp` to the
function's `switch`, and Ghidra had closed it with a `return` instead, so our build was 94 instructions against the
original's 129 and the whole switch ran only for one value of the variable it dispatches on. The tell is a `switch`
whose value a preceding guard has already constrained - here `if (x != 0) { ...; return; } switch (x) { case 0: ...`,
where every other `case` is unreachable. Rebuilding it from the original's jump targets took the function from 0.41 to
0.54 on `quick_diff.py`'s ratio with the lengths nearly equal.

Diff patterns that were reliable (more in the cheat sheet):

- Absolute `DAT_*` addresses in the original asm where the source uses `this->` mean the original accessed the global instance.
- Signed `jl/jge` vs our unsigned `jb/jae` on `undefined4`/`uint` fields: compare through `(int)`. This is worth
  sweeping rather than chasing one diff at a time. Collect the resolvers declared `MACRO_STRUCT_RESOLVER(undefined4`
  or `(uint`, then cast every relational comparison against one: 51 sites across `UI::MenuItems` gained 10
  functions with **no regressions at all**, including two normalized 100%s
  (`MenuItemRenderFunction_BuildingAndStatusMenu_HorizontalSlider`, and `MapDescriptionScrollbar` 79.1% -> 88.2%).
  `==` and `!=` are unaffected, so only `<`, `>`, `<=`, `>=` need it.
- `cmp x, N; ja` means `<= N`; write the literal the asm shows.
- `mov r, [x]; sub r, 1; je` inside a loop is a `switch` on `x`.
- A tail call to the same callee from our code but a jump back to a shared block in the original means separate
  `if` branches with identical bodies, not a combined condition.
- Callee-saved registers reused after a call without reload (`ecx`/`edx`) indicate LTCG (`cmake/compiler-flags-gl.txt`),
  not a source difference.
- A mismatching argument count or `ret N` usually means the generated header is wrong; report it instead of working around it.
- Instruction order is not statement order: the compiler schedules freely inside a boundary, so a long run of
  independent stores into one object says nothing about the order the fields were assigned in the original source
  (see the cheat sheet's *Statement Order*). Reordering the body to follow the asm makes the match worse.
- Diffs can reveal real bugs in existing reimplementations (wrong constants, wrong strides); fix those.
- `(-(uint)(c) & MASK) + BASE` in the decompiler output is a conditional it has already turned into mask-and-add:
  it is `c ? BASE + MASK : BASE`. Writing the conditional out recovers the same instructions and stops the constants
  being unreadable - `(-(uint)(d != 1) & 0xffffffce) + 200` is `d == 1 ? 200 : 150`.
- `(x + (x >> 0x1f & 7U)) >> 3` is a signed division by 8, not a shift: shifting alone rounds towards negative
  infinity, so the compiler biases the value first and the decompiler reports the bias. Any mask `2^k - 1` paired
  with a shift of `k` is `x / 2^k`. Writing the division back recovers the same instructions and has been worth a
  great deal - 22 sites in one namespace, up to +22% on a single function (`undiv.py` rewrites them). The bias also
  proves the dividend is signed, so a surrounding `(int)` cast is redundant once the division is back. Measure
  anyway: one site out of 22 came out 0.1% worse and kept the shift.
- `v = x & 0x8000000f;` followed by `if ((int)v < 0) v = (v - 1 | 0xfffffff0) + 1;` is `v = x % 16` - the low bits and
  the sign bit masked together, then the negative case repaired (`unmod.py`). The mask's low bits and the `|` constant
  always complement each other. The repair proves the operand is signed, so the dividend has to stay signed in our
  source too: the decompiler's `uint` locals and its `+ 4U` make the sum unsigned, and an unsigned `%` compiles to a
  bare `and` with no repair, which loses the match instead of gaining it.
- `piVar1 = &x.field; *piVar1 = *piVar1 + 1;` is `x.field = x.field + 1` (`unptr.py`), worth 1.2% over 60 sites in one
  function. Only rewrite it when the store immediately follows the pointer: a pointer freezes the address while the
  field form re-evaluates the index, so with a call or a write to the index in between the two forms differ.
- Our `movzx` against the original's `movsx` on a `ushort` layer (`PathConnectionLayer`) means the original cast the
  read: `dword x = (short)layer[i]`, one `movsx`. Declaring the local `short` does not do it - the signedness comes
  from the cast on the array access, not from the destination.
- `diff_types.py`'s `EXTEND` hint usually does **not** mean the header is wrong. Every field it flagged across
  `Map::Units::UnitsState` was already correctly signed (`short OrganismLayer`, `short owner`,
  `typedef short UnitTypeShort`). What it detects is a 16-bit load that needs a second instruction to sign-extend,
  where the original does one `movsx`, and that arises three ways with three different fixes. This was the most
  productive seam in that namespace, ten functions and most of a point of namespace average, after hand analysis of
  the same functions had concluded they were allocator-bound:
  - **A local declared `short` (or `ushort`) that holds a field read** - widen it to `int`. The safest of the three:
    it cannot add a memory read, only change the extension width of one that already happens. One such local took
    `resetUnitMovementState` from 85.7% to 95.2% and normalized 100%. 17 of 18 candidates gained.
  - **A byte-sized local** (`diff_triage.py`'s `BYTE` column, nonzero on our side only) - widen it to `int`, worth
    +12 points on `updateUnitFadeAndVisibilityNearStructures` alone. But only when the flag is set from constants:
    one initialised from a `BOOLEnum`-returning call lost 3 points, because `bool x = call()` emits the test that
    normalises the result to 0/1 while `int x = call()` stores it raw, so there the `bool` is load-bearing.
  - **A field read repeatedly with no local at all** - give it one `int` local, but only when the value feeds
    arithmetic, indexing, or a comparison against another variable (+4.7 on `calculateUnitMovementSpeed`). When it
    feeds comparisons against *constants*, leave it alone: MSVC compares against the memory operand directly, and
    introducing the local cost 11.8 points on `playHurtSFXForUnit` and 0.3 on `updateUnits`. This is the
    unpredictable case the style notes above warn about; the `EXTEND` hint plus how the value is used is what makes
    it decidable.
  Signedness is what matters, not width: a `ushort` local widened to `int` zero-extends either way and gained
  nothing. An `EXTEND` on an *array element* is weaker evidence than on a scalar - declaring a `ushort` scratch
  array `short` and dropping fifteen `(short)` read casts was an exact tie.
- `diff_triage.py`'s `FRAME` column is worth checking but, unlike `BYTE`, is not mechanically actionable. Every
  cheap hypothesis for the frame mismatches in `Map::Units::UnitsState` came back an exact tie or worse: local
  declaration order, array element type, widening unsigned locals, and splitting a local the decompiler had reused
  for two values. `diff_slots.py` says the lowest-access extra slot is usually the culprit, so a function whose
  extra slots are all heavily used has genuine live values rather than a stray local, and needs structural
  understanding rather than a rule.
- When both sides have a jump table, the **order of the arms** still has to match. MSVC emits them in source order,
  so the physical order of the arm bodies in the binary is the original's `case` order, and `switch_order.py` reads it
  out of the byte and dword tables. A different order moves every arm and the comparison drifts from the dispatch
  onwards, which no work inside the arms recovers: `reorder_switch.py` was worth 19 functions with no regressions,
  including `MenuItemActionHandler_General_CreateEventCallbackFunction` 27.8% -> 45.9%,
  `MenuItemActionHandler_SaveLoadMap_Scrollbar` 64.2% -> 96.3%, `OptionsMenu_Buttons` 44.9% -> 77.0% and
  `TacticalPowerBar_Main` to 100%. Three cautions. An arm that falls through into the next must move with it - Ghidra
  emits that shape wherever the original shared a tail, and 16 such arms across 11 files would otherwise be reordered
  past the arm they fall into, which is a silent behaviour change; reassuringly, every fall-through chain turned out to
  be consecutively ranked in the original's table too. And the rule has exceptions for very small arms: six
  scrollbar-style functions measured worse and were reverted, so gate per function. The **last** arm needs
  its own guard: running off its end there falls out of the switch, which is harmless only while it stays
  last, and moving it makes it fall into whatever follows. Five committed functions had that bug before it
  was caught, in arms the original ends with `ret`. The repair keeps both the behaviour and the gain, because
  falling out of a switch is what `break;` means: closing the arm explicitly frees it to move and *improved*
  the match (`OptionsMenu_SubOptionsButtons` to normalized 100%, `UnusedChooseAvailableKeeps_Main` 77.2% ->
  89.5%), which is what one expects if the original terminates those arms too. Verify any such rewrite by
  comparing **token** multisets rather than lines: `clang-format` reflows the moved code, so a line-level
  comparison reports a false difference.
  Two things stopped `switch_order.py` matching a switch at all and are worth knowing about if a large
  jump-table function still reads as unordered. The index adjustment is the instruction *closest* to the
  dispatch (`lea edx, [esi - 0x19]`, or a `sub`), and the walk-back used to keep scanning past it and
  overwrite the base with an unrelated `add esp, 8` or `add eax, 0x92`, which shifts every value the table
  reports by a constant - the arms are still in the right order, so a hand reordering off the printed values
  works, but `keys_for` rejects the switch. And where the original gave a block of values an arm of its own
  that our source leaves to the end of the switch, our `case` labels cover every arm but that one; the
  strict "cover exactly the table's non-default values" test refuses it, and `--loose` accepts it when the
  values we do not name all belong to that *single* missing arm (still enough to keep a nested switch from
  matching its parent's table, since a nested switch leaves several arms unaccounted for). Between them
  these unlocked `MenuItemActionHandler_General_ToolbarButtonPressed` 42.3% -> 53.6% on `quick_diff.py`'s
  ratio with a 202-instruction block in the wrong place, `LobbyMenu_NonBoxedButtons` 0.20 -> 0.41, and
  `MenuItemRenderFunction_BuildMenu_UnitActionButtons`. A third case: a *second* dispatch on the same value
  reuses the register the first one adjusted, so its own `lea` is far above the walk-back's reach and the
  base reads as 0; the base of another table in the function with the same bound is this one's too
  (`MenuItemActionHandler_General_EventSlider`'s second switch, base -10, whose arms turned out to be in a
  different order from ours). A printed base of 0 on a function with several tables is the tell.
  Where the original has a jump table and we do not, the usual cause is that our `switch` leaves a block of
  the table's values to `default:`, so the remaining labels are sparse and MSVC emits compares. Give each of
  those values a `case` of its own on the `default:` arm - 24 of them in
  `MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus`, where the table covers
  `BT_IRONMINE`..`BT_MILL` - and keep `default:` for what is outside the table's range.
- An assignment whose branch then ends in `return;`, where the code *after* the enclosing block is what reads
  the variable, is a dropped fall-through: the store is dead, so the original cannot have returned there.
  The shape is all over the render functions -
  `if (interacting == FALSE) { color = 0xc2f0eb; } else { color = 0xccfaff; return; }` followed by the one
  render call that wants `color` - and where it is real it is a **behaviour bug**, not just a mismatch: the
  button draws nothing at all while it is hovered. It is confirmed in
  `MenuItemRenderFunction_General_GameOptionsTextButton`, which is 36 instructions with a single `ret`: both
  colour paths converge on `push 0x4a; call getTextStringInGroupAtOffset` at 0x493544, and in
  `MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands`, where they converge at 0x42d28c.
  **Do not sweep it.** `undrop_fallthrough.py` finds the sites (43 across `UI::MenuItems`) and removing all
  of them measured **worse in every single function**, several of them disastrously
  (`WorkshopWeaponSelection` 31.2% -> 7.1%, `MapEditorProperties_MainButtons` 53.2% -> 17.6%): the `return`
  goes away but the source form that matches what the original did with those two arms is still unknown, so
  the whole function re-schedules. `fold_ternary.py` folds the pair into a ternary at the argument, which is
  what makes MSVC push the argument list inside each arm and share only the call's tail - it took
  `GameOptionsTextButton` from 0.647 to 0.706 on `quick_diff.py`'s ratio and recovered 21 functions, but
  still left 40 below where they started, so it is a thing to try per function and not a pass to run. This
  is also the clearest case so far of `quick_diff.py`'s ratio disagreeing with reccmp: it liked the fold
  everywhere, reccmp liked it in half the functions.
  The per-function evidence that settles whether the `return` belongs is a **`ret` count**: disassemble the
  original (`orig_disasm.py`) and count its `ret`s against our exits (`return;` plus the implicit one at the
  end of a `void`). `MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection`,
  `Chat_TauntButtons` and `GreatestLord_Main` each have exactly **one** `ret` in the binary where our source
  had two exits, which is direct evidence and needs no score; `MenuItemActionHandler_InGameMenu_MainButtons`
  has 15 against our 12, so there the extra `return;` is ours to keep. Tail calls make the count an
  undercount (`HistoricAndEconomicMissionSelect_NextAndBackHands` jumps instead of returning and shows 0),
  so read the function when the two numbers are equal.
  **The form that actually matches is the call written out in both arms.** Ghidra's
  `if (c) { X = k1; } else { X = k2; }` plus one call is its *merge* of two calls: the original pushes the
  argument list inside each arm and converges only on the shared tail, which is why neither the local nor a
  ternary reproduces it. `MenuItemRenderFunction_General_GameOptionsTextButton` is the clean example - both
  arms push five arguments and meet at `push 0x4a; call getTextStringInGroupAtOffset` (0x493544) - and
  writing the call twice took it from 0.647 to **0.889** on `quick_diff.py`'s ratio with the instruction
  count exactly equal (36 = 36), against 0.706 for the ternary. `Chat_TauntButtons`, where the arms choose
  an *x coordinate* rather than a colour, went 0.721 -> **0.941** and 27 instructions -> 34 = 34.
  `split_call_arms.py` does the rewrite; run `undrop_fallthrough.py` first, since the stray `return;` hides
  the `if`/`else` from it. `split_ternary_call.py` is the same rewrite for an argument that is *already* a
  ternary - whether Ghidra emitted one or an earlier pass folded one - and that pass was 11 functions better
  with **no regressions at all**: `DisableEuroTroops_Main` 84.6% -> 93.4%, `DisableArabTroops_Main`
  82.9% -> 92.7%, `TutorialBox_Main` 84.5% -> 91.7%, `SendReceiveMap_Main` 82.7% -> 89.2%,
  `LobbyMenu_MapSelectHeader` 52.9% -> 61.7%. It is the one pass in this family that can be run blind.
  Which form a given function used is decidable from the original: the constants **pushed**
  (`push DAT_GMImageSizes+0x3556f`, `push DAT_GMImageHeaders+0x9695b`) mean one argument per arm and this
  rewrite, while the constants moved into a **register** - `mov edi, <colour>` followed by a conditional
  second `mov`, as in `MenuItemRenderFunction_NewEventCondition_Main` at 0x4c0365 - mean a default
  assignment and then a one-armed `if`, which is a third shape again. Classify before rewriting: grep the
  disassembly for `mov \w+, DAT_GMImage` against `push DAT_GMImage`.
  The mirror image also exists and is *not* a dropped return: a guard that ends in
  `drawBufferChoiceValue = RT_MAP_GAME` looks identical but in `MenuItemRenderFunction_General_MenuMiniMap`
  the original continues the loop (`mov [..+4], 1; add esi, 1; cmp esi, 8; jl`). Read the instruction after
  the store before adding a `return;` there; a `return` that skips a countdown or a `switch` the arms share
  (`MenuItemRenderFunction_NewEventAction_Main`) is a silent behaviour change, so only the sites where the
  block really ends in `pop`/`ret` qualify, plus the free ones where an `if` arm's `return` is reached at the
  end of the function or before a mutually exclusive test.
- Which arm of an `if`/`else` the source wrote first is **readable straight off the branch**, and Ghidra gets
  it wrong often enough to be worth a sweep: for `if (DAT_ButtonCurrentlyInteracting::instance == FALSE)` with
  an `else`, a `je` after the original's `cmp` puts the `== FALSE` body *out of line*, so the interacting arm
  is the one written first and our source has them backwards. Scan it by pairing each
  `cmp ... DAT_ButtonCurrentlyInteracting` in the printed disassembly with the instruction after it; 9 of the
  45 functions with that shape came back `je` and swapping them was 5 better with no regressions
  (`NewMapMaptype_Buttons` 85.1% -> 94.1%, `UnusedOldTitleMenu_ContinueButton` and `_TestMapButton`
  78.4% -> 91.9%, `UnusedOldTitleMenu_ExitButton` 75.7% -> 89.2%, `NewMapMapsize_Buttons` 67.0% -> 74.9%).
  The four that did not move are still worth keeping for being the shape the binary shows. Note the operand
  text only carries the global's name in `orig_disasm.py`'s *output* - capstone's own `op_str` has the raw
  address - so match on the printed line.
- `flag = (uint)(a == b);` compiles to `sete`, and the original usually **branches** instead
  (`xor edx, edx; cmp ...; jne; mov edx, 1`). Decide it per function with one grep: no `setcc` anywhere in
  the original's disassembly means every such site wants the default-plus-one-armed-`if` form. It was worth
  `DrawbridgeOpenClose` and `GatehouseOpenClose` 33.8% -> 51.9% each,
  `MenuItemRenderFunction_General_CrusadeMapAndEndscreen` 44.6% -> 64.3% and
  `MenuItemActionHandler_Chat_MostButtons` 47.1% -> 57.6%, where the original zeroes all nine slots of
  `DAT_ChatMessageReceiverArray` and then sets each with its own branch (0x48f6af..0x48f741) - Ghidra had
  kept the branch for the last slot only, which is the tell. Where the original *does* use `setcc`
  (`OnlineVoteQuitAndQuitGame_Main` has eight of them for eight sites) leave it alone.
- A chain of `sub reg, K; je` with no loop around it is MSVC's **sparse switch**, not an if/else chain:
  `sub eax, 0xd; je; sub eax, 5; je; sub eax, 2; je` is `switch (x) { case 0xd: case 0x12: case 0x14: }`.
  The arm that is reached by falling through the chain is `default:`, and the physical order of the bodies
  is still the source order, so read it off the addresses. `MenuItemActionHandler_HistoricMissionSelect_General`
  and its twin `UnusedEconomicMissionSelect_General` went **24.7% -> 91.1%** from that alone.
- Two bools compared against each other - `bVar2 = (x < K); bVar1 = (x - K) < 0; if (bVar2 != bVar1)` - is the
  decompiler's rendering of one `cmp` whose `jl` is **shared** between the arms of an `if`/`else` chain, each
  arm comparing its own value against its own bound. The bound travels with the value, so the source holds
  both: `if (trail == TT_EXTREME) { mission = extremeTrailProgress; missionCount = 20; } else if (...)` and
  then one `if (mission < missionCount)`. Finding it is also how you find the control flow Ghidra lost around
  it: `MenuItemActionHandler_CrusadeMissionIntro_Main` ran its `field22_0x64` check for both button values and
  the trail dispatch unconditionally, where the original returns out of each arm (0x4d8c35 and 0x4d8c9d are
  both tail calls), and `MenuItemRenderFunction_CrusadeMissionIntro_Main` had the whole thing wrapped so that
  a trail type outside the three still reached the comparison. Rebuilding both from the instruction stream was
  worth 46.2% -> 76.4% and **6.9% -> 60.9%**. `bVar2 == bVar1` is the same thing in the other sense (the `jl`
  not taken, i.e. `>=`).
  Where the original instead compares inside each arm and shares only the branch
  (`MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits`, 0x466efd and 0x466f16 both
  `cmp [gold], <literal>` before a common `jl`), Ghidra's two-bool form already *is* the matching shape and
  only its `goto` is an artefact - leave it alone. Read which of the two the original did before rewriting.
- Ghidra puts a `return;` inside a bubble sort's swap, right after the "something moved" counter
  (`iVar7 = iVar7 + 1; return;`), which aborts the sort after its first swap. The original has `add esi, 1`
  and falls into the loop increment. Two such bugs sat in the map-list sorts
  (`MenuItemActionHandler_LobbyMenu_MapSelectHeader`, `SingleplayerMapChoice_MapTableHeader`); grep for an
  increment immediately followed by `return;`.
- Where several arms each store *their own* field and then share a tail, Ghidra merges the stores into one
  block that writes all of them, and preloads the other fields' current values so the merge is harmless.
  `MenuItemActionHandler_CrusadeMap_Main` wrote all three trail-progress fields on every hit; the original
  has one `mov` per arm (0x4d90ea, 0x4d913b, ...) and no preloads. Move the store into its arm and leave only
  the genuinely shared tail behind the label.
- `jmp dword ptr [reg*4 + table]` on one side only is a dispatch-form mismatch: a `switch` over contiguous values
  becomes a jump table, an if/else-if chain becomes compares. Both directions have been worth several percent
  (`scan_dispatch.py` finds them). Handing some of a switch's values to `default:` and re-testing them with an `if`
  drops them out of the table, so give every value its own `case` and lift a shared tail out behind a flag instead.
- `x < 1` compiles to `cmp x, 1; jl` but the original usually shows `test x, x; jle`, i.e. `x <= 0`. The two are
  identical for signed and unsigned alike; write the form the asm shows.
- A range's upper bound is half-open when the original ends it with `jge` and inclusive when it ends with `jg`.
  Writing `<= N-1` where the original has `< N` is a real off-by-one whenever the bound is a player or slot count -
  `processSingleTimeTick` had five, each calling a per-player routine one index out of range.
- Trust the asm over the decompilation for constants and their sign. Ghidra rendered `2400 / n + 40` where the binary
  has `sub eax, 0x28`, so the formula is `- 40`; the function reached 100% once corrected (`diff_types.py` finds these).
  A `(longlong)` in a Ghidra division is usually spurious too - it emits `_alldiv` where the original has a plain `idiv`.
- A long run of single-byte assignments between two array rows is a **dword** copy in the original: MSVC copies a
  20-byte entry as five `mov`s through registers, and Ghidra renders each byte separately. 80 byte statements shifting
  four 20-byte entries became 20 `((int*)row)[w] = ...` statements, which is also what the binary does - that alone was
  most of `MenuItemActionHandler_ChooseNetworkServiceProvider_Buttons` going from 18.9% to 72.8%, together with its
  dispatch. The tell is our function being far longer than the original (335 instructions against 234) with the excess
  all in one block. The cast is raw, but a byte loop and a `memcpy` both compile to something the original does not
  have, and the generated header cannot express the row as a struct.
- MSVC1400 at `/O2` never unrolls a loop, so a body repeated N times in the asm means the source was written out N
  times. A plain loop where the original is unrolled has cost 80 points on its own.
- A flag stored with `mov dword ptr [..], 0/1` is an `int`, not a `bool`, which stores a byte.
- Tentative, one clear case so far: where two arms of a condition share a tail, the nested `if/else` shape the
  decompiler emits can beat the early returns the style list above asks for, because it decides *which* arm holds the
  physical copy of the shared block. In `calculateTaxIncomeForPlayer` the original keeps the shared `(tax * 150) / 100`
  in the second arm and jumps forward into it from the first; early returns put the copy in the first arm and made the
  second jump backwards, and switching to nested `if/else` was worth 17 points. Read the original's own jump direction
  with `orig_asm.py NAME` to see which arm should hold it. Treat this as a thing to try, not a rule: the same change
  measured *worse* on `updateCrowding` (all three nested variants lost 9-14 points) and made no difference at all on
  `showPopAndGoldPopup` and `createStatsPopUpEntities`, where every shape tied to the decimal because the gap there is
  the loop base-pointer anchor. `try_styles.py` settles it per function; prefer the early-return form on a tie.

## Agent Skills

Task-specific guidance is available under `.agents/skills/`.

When a relevant skill exists, prefer it over this document, as it contains more detailed workflows and repository-specific guidance.

## Agent Maintenance

If you discover undocumented conventions, missing workflows, or repeated guidance, suggest updates to this guide or the relevant skill.
