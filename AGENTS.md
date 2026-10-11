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

`try_invert.py`'s own gate is `quick_diff.py`'s ratio, so its keeps still have to be
confirmed with reccmp: of the six it kept across the 102 `RET`-flagged functions in `UI::MenuItems`,
two measured worse on raw match and were reverted
(`MenuItemRenderFunction_MissionEndscreen_Main` 43.1% -> 42.9%,
`MenuItemRenderFunction_SiegeAttackingForceAndStartGoods_Main` 52.8% -> 52.6%, both with normalized
match *rising*). The four that held were worth a great deal -
`MenuItemRenderFunction_AlliesSendAndRequestGoods_Main` 28.9% -> 48.6%,
`MenuItemRenderFunction_BuildingAvailability_Buttons` 55.3% -> 60.1%,
`MenuItemActionHandler_General_ToolbarButtonPressed` 54.3% -> 56.9% - so the flag is worth sweeping,
at about one function in six, with a reccmp gate behind it.

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
 One more confirmation of that, this time with a concrete
  hypothesis that failed: `MenuItemRenderFunction_Allies_Main` reported `FRAME 0xc`, exactly three
  slots more than the original, and had exactly three locals that Ghidra had invented for a shared
  `renderText2` call (a text section, an x coordinate and a flag). Writing the call out in both arms
  removed all three locals - and the function still had six slots to the original's four, with the
  extra ones now heavily used (7 and 8 accesses), while the match fell 47.1% -> 38.3%. The slots were
  genuine live values all along; the local count and the slot count are not the same quantity.
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
  scrollbar-style functions measured worse and were reverted, so gate per function.
  `MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus` is a settled exception: its
  five-arm switch has been reordered into its table's order twice, once before the index-base fix and
  once after, and both times measured exactly 39.7% -> 39.5%. Reproducing to the decimal is the
  evidence that it is not a tooling artefact - that switch simply does not follow source order, so
  leave it alone and look elsewhere in the function. The **last** arm needs
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
  Two more things stop a jump table from being read correctly, and both are silent. The index
  adjustment's operand can be a **register**: these functions pin small constants
  (`xor ebx, ebx; mov esi, 1; lea edi, [ebx + 2]`), so the dispatch is `mov edi, 2` followed by
  `sub edx, edi` rather than a `sub` against an immediate, the walk-back matched neither, and the base
  read as 0 - which shifts every value the table reports by a constant and stops the switch matching.
  `switch_order.py` now resolves such an operand from the `mov` that loaded it. And a switch written
  with **enum constants** can never match a table, because the match compares the numeric values the
  switch names: `reorder_enum_switch.py` resolves them from the enum header first, and recovers the
  base by finding the offset that maps each of our arms to exactly one table arm. Between them these
  two uncovered `MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback`, whose 34 arms were
  all in the wrong order behind a base that was 2 too low; reordering them was 16.4% -> 22.8% and it
  was the second-largest single loss in the namespace. A function that is both large and far below the
  namespace average, with a `switch` the reorder pass says has "no switch matches a table", is the
  shape to re-check.
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
  **Writing the call out twice only works for two arms.** Where the original's arms each push some of
  a call's arguments and then meet part-way down the argument list, that convergence can be MSVC
  cross-jumping identical call sites rather than the source having written the call once. With two
  arms the rewrite reproduces it exactly (`GameOptionsTextButton` 36 = 36 instructions); with three it
  does not, because MSVC1400 merges the tails of two successors and not of three.
  `MenuItemRenderFunction_OptionsMenu_Buttons` has three sites pushing blend strength, keepOffsetX,
  font size and colour and meeting at `push 1` (0x491904), and writing the call out at all three went
  0.745 -> 0.653 on `quick_diff.py`'s ratio while *growing* our function from 139 to 151 instructions
  against the original's 143 - so there the `goto` and the locals Ghidra invented are the closer match
  and should be left alone. Count the predecessors of the shared tail before rewriting.
  A related shape is the clamp whose store Ghidra duplicated into the inner arm:
  `if (v < M - S) { v = v + S; if (v <= M) { FIELD = v; return; } } FIELD = M;` is one store at the
  label both paths converge on (0x4623c9, 0x4615ee), so the clamp belongs inside the arm and the store
  behind it (`merge_clamp.py`). Gate it per function - it was worth
  `MenuItemActionHandler_TextEditor_TextInputRelatedUnk` 27.4% -> 31.8% and cost
  `MenuItemActionHandler_TextEditor_Buttons` 71.5% -> 68.0%.
  A clamp is also a place to check for the dropped fall-through itself, because the arm that clamps
  usually continues: both brush blocks of
  `MenuItemActionHandler_MapEditorLandscaping_GeneralButtons` fall out of `mov eax, 1` / `mov eax, 7`
  (0x431565, 0x4317d5) into the big-rock adjustment, where Ghidra returns, so a brush that wrapped
  past 7 or below 1 skipped that adjustment, the `unknownBrushRelated` update and
  `StopHandlingMenuItems = 0` entirely.
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
  `scan_setcc.py` lists every function with a comparison-assignment and no `setcc` in the original,
  but the absence of `setcc` is necessary and **not** sufficient, and the extra condition is what makes
  the check decidable: the flag has to be used as a *number*. A flag that is only **tested**
  (`if (bVar4)`, `if (!bVar4)`) folds into a branch by itself, emits no `setcc` either way and has
  nothing to fix - that is what `InGameMenu_MainButtons`, `BuildingAndStatusMenu_MercenaryPostPortraits`,
  `UnusedSetName_ButtonsUnk` and `MapEditorLandscaping_QueueCommandCallback` all turned out to be. A
  flag used in arithmetic may also already match: `MenuItemRenderFunction_GameplayOptions_Buttons` has
  `0xe - (uint)(field != 0)` and the original does `neg al; sbb eax, eax; add eax, 0xe`, which is that
  same expression. Of twelve candidates only two were real, and both were large:
  `MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection` **31.2% -> 61.2%** and its
  action handler 90.2% -> 97.5%. There the six weapon arms each do their own
  `cmp dword ptr [DAT_GameCore+N], 0` and jump to one shared tail (L1 at 0x465124, L6 at 0x465257),
  which is MSVC cross-jumping six identical `if (field == 0) { ...; return; }` bodies - and the `return`
  Ghidra dropped there made the store dead, so **a weapon that could not be produced was never greyed
  out in the workshop menu**.
  `MenuItemRenderFunction_MapEditorProperties_MainButtons` is the counter-example to keep in mind: its
  flag *is* used numerically (`iVar1 + (uint)bVar4`) and the original *does* use the branch form
  (`xor edi, edi` ... `jne L9; mov edi, ebp` at 0x42e9ab), yet writing that form measured
  0.5415 -> 0.4483 on `quick_diff.py`'s ratio, and 0.4428 with the stray `return`s left in to isolate
  the change. That function now has two separate rewrites that read correctly off the binary and both
  lose, the other being `undrop_fallthrough` (53.2% -> 17.6%); treat it as settled.
- A chain of `sub reg, K; je` with no loop around it is MSVC's **sparse switch**, not an if/else chain:
  `sub eax, 0xd; je; sub eax, 5; je; sub eax, 2; je` is `switch (x) { case 0xd: case 0x12: case 0x14: }`.
  The arm that is reached by falling through the chain is `default:`, and the physical order of the bodies
  is still the source order, so read it off the addresses. `MenuItemActionHandler_HistoricMissionSelect_General`
  and its twin `UnusedEconomicMissionSelect_General` went **24.7% -> 91.1%** from that alone.
  **The arm order of a sparse switch is the exact reverse of the test order**, with the arm reached by
  falling out of the chain written first. That held in every one of the eleven functions it was checked
  against, so the addresses never need reading: `sub eax, 0; je A; sub eax, 1; je B; sub eax, 1; jne D`
  is `switch (x) { case 2: ...; case 1: ...; case 0: ... }` (the `case 2` body being the one that falls
  out of the chain), and a chain testing 0xd then 0xe is `case 0xe:` before `case 0xd:`. Where the
  fall-through arm is `default:`, that is what goes first (`NewMapMapsize_Buttons`,
  `HistoricMissionSelect_General`). This was worth
  `MenuItemActionHandler_ChooseNetworkServiceProvider_ProviderTableRows` and
  `MenuItemActionHandler_UnusedSomeMissionStartUnk_General` to **100%**,
  `MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader` 81.6% -> 98.1%, its action handler
  18.8% -> 64.5%, `MenuItemActionHandler_EditScenario_EventAndInvasionList` 52.4% -> 70.8%,
  `MenuItemRenderFunction_LobbyMenu_MapSelectHeader` 61.7% -> 74.8% and its action handler
  21.2% -> 32.7%.
  When scanning for the chain, do **not** require the `je` to sit immediately after the `sub`: MSVC
  interleaves the prologue's register pushes between them (`sub eax, 0; push ebx; push ebp; push esi;
  push edi; je ...` at 0x449294), and an adjacency test misses most of the family - it found 1 candidate
  where a six-instruction window found 7, every one of them a real mismatch.
  The map-list sorts behind two of those functions carry a second shape worth knowing. Ghidra renders
  MSVC's zero-trip test as a `break` inside the outer loop -
  `do { moved = 0; i = 0; if (bound < 1) break; do { ... } while (i < bound); } while (moved != 0);` -
  but `test edi, edi; jle` (0x440ad4, 0x4492d4) is the *inner* loop's entry test, so the inner loop is a
  counted `for` and the outer loop has no early exit at all (`uncount_loop.py`). The sort functions also
  keep the sort mode in a register across the dispatch, so a local for it is what reproduces the
  `test ecx, ecx` the original compares against rather than a reload of the field.
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
- A run of `cmp byte ptr [base + K], 0; je <next>; mov ecx, 1` at consecutive offsets, ending in one
  `jne` out and a `test ecx, ecx; jne` out, is a **flag accumulated over several fields** and not the
  `&&` chain Ghidra renders. The source is `int flag = 0;` then one `if (field != 0) { flag = 1; }` per
  offset, with the last field tested together with the flag:
  `if (data[0x6b] == 0 && flag == 0) { X = 1; return; }`. Ghidra's single nested conjunction compiles to
  early-out jumps instead and is about twenty instructions short.
  `MenuItemRenderFunction_NewEventCondition_Main` (0x4c02af..0x4c0346) had ten such fields; it also shows
  the two other things Ghidra loses around this shape - the store the chain guards ends in `pop ebx; ret`
  (0x4c0351), so the guard carries a `return;` our source did not have, and an earlier
  `cmp edx, 0x1388; jg` guard had decompiled as a second, dead `X = 0;` rather than an early return.
- Ghidra will emit a test that **cannot be true** when it loses a three-way compare: `cmp edx, 0x7d0;
  jg L29; je L27` became `if (param_1 < 2000) { if (param_1 == 2000) {` in
  `MenuItemRenderFunction_NewEventCondition_Main`, with the real `== 2000` arm inside the `< 2000` branch.
  An inner `== N` inside an `if (x < N)` is the tell, and it means the surrounding dispatch is a sparse
  switch whose halves have been nested rather than flattened. Rebuilding that one function's dispatch as a
  single `switch` with its arms in the order the addresses give - 1001, 1000, 2000, `default`, 2002, 2001,
  which is the reverse of the test order in each half with the fall-out arm between them - was worth
  0.4276 -> 0.5309 on `quick_diff.py`'s ratio with the length gap closing from -19 to -3.
- A store repeated as the **first statement of the guard that follows it** is Ghidra duplicating one store
  across a branch whose shape it lost: `X = V;` then `if (cond) { X = V; return; }` is
  `X = V; if (cond) return;`, because the original stores once before the test
  (`cmp edi, ebx; mov dword ptr [DAT_ButtonUnknownZero], ebx; jl`, 0x427941 and 0x427c2b). Removing the
  inner copy is behaviour-preserving and restores the shape. Only three sites across `UI::MenuItems`, all
  real, so it is worth one scan rather than a tool.
- Where several arms each store *their own* field and then share a tail, the store addresses are **not**
  enough to justify rewriting. `MenuItemActionHandler_CrusadeMap_Main` has one `mov` per trail
  (0x4d90ea skirmish, 0x4d913b warchest, 0x4d918a extreme), each falling into the shared tail at
  0x4d9190, and our source wrote all three fields on every hit with preloads of the two it was not
  setting. Moving each store into its arm and dropping the preloads - which is what the binary appears
  to say - measured **33.5% -> 31.2%** and was reverted: MSVC sinks the store into the arms by itself,
  so Ghidra's merged form is the closer *source* match even though the binary stores once per arm.
  This is the counter-example to the `CrusadeMap_Main` advice given earlier in this file; prefer the
  measurement.
- A block reached from **two different jump tables** is not in either table's source order.
  `MenuItemActionHandler_General_ToolbarButtonPressed` has 0x444615 as the eighth arm of its 0x19..0xc2
  table *and* as the default of its 0x120..0x166 table; moving our `default:` arm to that eighth position
  measured 0.5763 -> 0.5481 and was reverted. Both of that function's switches are otherwise in their
  table's order, so its remaining loss is not arm ordering.
- The sparse-switch seam is **exhausted in `UI::MenuItems`**: a scan tolerating interleaved instructions
  (a `sub reg, K` with a `je`/`jne` within six instructions, at least three links) finds ten functions and
  every one of them already has a `switch` in the source. Re-run that scan after a batch of rewrites
  rather than reading addresses by hand.
- `quick_diff.py`'s ratio can be **mis-scaled**, not merely noisy, and
  `MenuItemRenderFunction_LobbyMenu_NonBoxedButtons` is the case to remember: its reccmp raw match was
  51.4% where the ratio read 0.3408, and a `reorder_switch.py --loose` pass that took the ratio to
  0.3862 measured **51.4% -> 24.2%** on reccmp. When the ratio and the reccmp percentage disagree by
  more than a few points in *absolute* terms, the ratio is not a usable gate for that function at all.
  The six scrollbar-style reorder regressions already noted are the same family.
- `unwrap_guard.py` paid nothing in `UI::MenuItems`. Of the nine functions with no `return;` at all and
  three or more epilogue jumps, only three had the single-guard shape, two of those
  (`MenuItemActionHandler_InGameMenu_ViewToKeeps` 0.4755, `BuildingAndStatusMenu_TunnelerPortrait`
  0.6667) compiled to code identical to four decimals, and `BuildingAndStatusMenu_TaxArrowButtons` has
  an `else` on its guard that the tool turns into a syntax error. The epilogue-jump deficit also
  over-reports badly on its own: 81 functions read as short, including
  `MenuItemActionHandler_UnusedSomeMissionStartUnk_General`, which is at 100%.
- Moving a switch's out-of-table arms behind the switch to match a far-forward `jg`/`je` is an exact
  tie: `MenuItemRenderFunction_BuildMenu_UnitActionButtons` dispatches
  `cmp eax, 0x22e; jg 0x439; je 0x40b; sub eax, 0xd3; cmp eax, 0xa5; ja; jmp [table]`, and writing the
  two special arms after the switch (with `goto`s into them) compiled to the same instructions as
  Ghidra's inline-ahead-of-the-switch form. MSVC places those blocks where it likes; the arm *order*
  inside the table is the only placement the source controls.
- A dispatch bound one value short of the original's means the original gave that value an arm of its
  own, and **adding it to the `default:` arm does not recover it**: MSVC1400 folds a `case` that shares
  the default's body, so the table does not widen.
  `MenuItemRenderFunction_SingleplayerMapChoice_ButtonsAndHands` has `lea eax, [esi + 0x65]` then
  `cmp eax, 0xb3` against our `cmp eax, 0xb2`, so value 0x4e had its own body in the original - one
  that was then cross-jumped onto the default block at 0x42d544, which is why the table lists it there.
- `MenuItemRenderFunction_EditScenario_BaseMenuButtons`'s Gold (0x3d) and Rations (0xa6) arms each have
  one `cmp interacting, 0; jne` whose fall-through renders in 0xc2f0eb and **returns** (0x4bf067,
  0x4bf131), with the 0xccfaff copy out of line at L15/L17 returning too. Ghidra kept the hover render
  as a plain guard and left the normal render unconditional, so a hovered Gold or Rations button drew
  twice and the second draw overwrote the highlight. Writing the original's two mutually exclusive arms
  costs **51.7% -> 50.3%** of match and is kept anyway, per the priority order at the top of this file.
- **Signedness, as opposed to strictness, had no scanner and is the most productive seam left.**
  `diff_jcc.py` reports a comparison one strictness step off the original (`jl` against `jle`);
  `diff_signedness.py` reports the original's signed jump against our *unsigned* jump of the same
  direction (`jl` against `jb`, `jge` against `jae`), which is an `undefined4`/`uint` resolver field or
  local compared without an `(int)` cast. 44 sites across 19 functions were still open after every
  earlier sweep; casting them was **four new 100%s and no regressions at all**
  (`MenuItemActionHandler_EditScenario_Scrollbar` and `General_MessageScrollbar` 96.4% -> 100%,
  `InGameMenu_MapEventIconUnk` and `UnusedChooseMessageBox_Unknown` 91.7% -> 100%,
  `SaveLoadMap_Scrollbar` 96.3% -> 98.1%, `SaveLoadMap_TableHeader` 47.8% -> 49.4%,
  `LobbyMenu_MapSelectScrollbar` 91.0% -> 93.6%), and a second pass over the remaining 25 sites added
  `OnlineVoteQuitAndQuitGame_Main` 66.7% -> **80.9%**. `signcast.py FILE FIELD...` does the rewrite for
  named fields only, and only inside a relational comparison, so it cannot change a condition by
  accident. Re-run the scan after every batch: it finds sites that the previous build's code did not
  have. Roughly half the sites measure as exact ties and are kept, because the cast is what the
  original's signed jump says.
  The seam was driven to exhaustion over three builds - 44 sites to 4, and those 4 are false
  positives whose comparisons are already `int`, because the scan's pairing is deliberately loose.
  Seven functions reached 100% in total (`EditScenario_Scrollbar`, `General_MessageScrollbar`,
  `InGameMenu_MapEventIconUnk`, `UnusedChooseMessageBox_Unknown`, `LoadMap_TableContent`,
  `LobbyMenu_MapSelectTable`, `SaveMap_TableContent`) with no regression in any of the 34 files
  touched, which makes this the only pass in the whole file that can be run on every function and
  kept wholesale.
  Three shapes hide the same bug, which is why it survived every earlier sweep:
  - **a mixed-type sum**: `undefined4_field + param_1 < (int)other` makes the whole comparison
    unsigned, so the cast belongs on the *field inside the sum*
    (`MenuItemActionHandler_RankingGames_Main`).
  - **a `byte` local used as a counter**: `byte bVar1 = (x != -1); ... bVar1 = bVar1 + 1; if (1 < bVar1)`
    compares unsigned where the original has `jle`. Widening it to `int` was
    `MenuItemActionHandler_OnlineVoteQuitAndQuitGame_Main` 66.7% -> 80.9% from that one declaration.
    This is a third case for the byte-local rule above, distinct from the flag-set-from-constants one:
    here the local is *incremented*, so widening is unambiguous. Note the `BYTE` column flags only one
    function in the whole namespace, and widening *that* one's `bool` (set only from constants, 9 byte
    slots to the original's 0) measured 0.3808 -> 0.3791 on `quick_diff.py` and was reverted - so the
    column is not the way to find this shape; the signed/unsigned jump pairing is.
- **The `ret` count is the soundest check for missing exits, and it only works in one direction.**
  `diff_ret_count.py` counts the original's `ret` instructions against our `return;` statements plus
  the implicit one. Where the original has *more*, that many exits are missing from our source, and the
  epilogue-jump deficit does not tell you this: a conditional jump to a shared epilogue is one `ret`
  but many jumps, which is why `epilogue_jumps.py` called 81 functions short including one already at
  100%, while the `ret` count names 25. Feeding that list to `try_returns.py` was the single most
  productive pass of the night after the signedness sweep: of 19 functions tried, 9 improved and the
  two that regressed were caught by the reccmp gate
  (`MenuItemActionHandler_MissionEndscreen_Main` **74.3% -> 87.6% from one `return;`**,
  `MenuItemRenderFunction_EditScenario_BaseMenuButtons` 50.3% -> 62.4% from three,
  `MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick` 65.7% -> 69.0%,
  `ScenarioDescription_Main` 56.9% -> 59.6%, `SoundOptions_Buttons` 61.4% -> 63.9%,
  `Chat_MostButtons` 57.6% -> 59.6%, `LobbyMenu_ChatBox` 53.6% -> 54.5%).
  The **reverse direction is worthless**: our `return;` statements collapse onto a shared epilogue, so
  "ours > theirs" measures how much MSVC cross-jumped, not that we have extra exits. The scan's own top
  entries prove it - `BuildingAndStatusMenu_WorkshopWeaponSelection` reads "6 extra" (1 `ret` against
  our 7) and is at 97.5%, its six weapon arms funnelling through one `je L8` to the single `ret` at
  0x442aff. Do not use it to look for dropped fall-throughs.
- A far-forward `jg`/`je` to a block placed physically last does **not** always mean that block was
  written last in the source, which is the one place the forward-jump rule above has been seen to fail.
  `MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick` dispatches
  `cmp eax, 0x69; jg L21; je L20` with both bodies at the very end of the function (0x442ad8, 0x442b00),
  after every switch arm; moving them there cost 42 instructions of our own output (328 -> 286) and
  0.026 of ratio, with and without the `return;` fix that arm needed. The `return;` alone was worth
  +0.047. Read the length as well as the ratio: a rewrite that *shrinks* our function well below the
  original's is eliminating something, not re-laying it out.
- Where the original reads a field **once into a register** and uses it for a guard, a subscript and a
  store, Ghidra hoists that read and then leaves a stale local behind in one of the places that used it.
  `MenuItemActionHandler_TextEditor_TextInputRelatedUnk`'s arm 0xf2 (0x461798) had three different
  expressions for one register: two re-reads of `activeHelpHotspotIndex` and one use of an `iVar3` set
  before the switch. The arm also reads the character once into `eax` and pushes that same register as
  the call's argument, and puts the `>= 0x20` case in the fall-through with the token case out of line
  at L13 - Ghidra had the two arms the other way round. Rebuilding the two arms that way was worth
  0.4604 -> 0.5028, on top of 0.4383 -> 0.4604 for writing `(x <= 0)` where the original has
  `cmp eax, ebp; setle` (nine sites). That is the `setcc` form of the `x < 1` rule above, which had only
  ever been applied to the `jcc` form.
- MSVC's inline `strcpy` of a short literal **loads it out of .rdata**:
  `mov ecx, dword ptr [lit]; mov dl, byte ptr [lit + 4]; mov [eax], ecx; mov [eax + 4], dl` is
  `strcpy(p, ".map")`, repeated per path. Ghidra renders it as
  `*(undefined4*)p = 0x70616d2e; p[4] = 0;` and will hoist it behind a `goto` so that several paths
  share one copy, which writes immediates instead of loading the literal
  (`MenuItemActionHandler_SaveLoadMap_Buttons`, three sites). Writing `strcpy` back per path was worth
  0.5930 -> 0.6077 on the ratio and measured an exact tie on reccmp, so keep it for being the binary's
  form rather than for the number.
- **A single-use Ghidra local inside an argument list that contains a nested call costs a stack slot
  the original does not have.** This is the one actionable form of `diff_triage.py`'s `FRAME` flag, and
  `diff_slots.py` names it exactly: an extra slot of ours with one or two uses. The shape is
  `x = DAT_ButtonX::instance; y = DAT_ButtonY::instance; r = inner(); outer(..., r, x, y);` - the two
  coordinates have to survive `inner()`, so they get spilled, while the original pushes them straight
  into the argument list before calling `inner` (`mov eax, dword ptr [DAT_ButtonY]; push eax` at
  0x464746). Inlining them removes the slot: `MenuItemRenderFunction_InGameMenu_MainButtons`
  **42.6% -> 48.7%** (norm 31.6% -> 43.8%), `BuildingAndStatusMenu_OutpostUnitSelection` 69.6% -> 76.8%,
  `LobbyMenu_SkirmishTypeAndBalance` 57.3% -> 63.1%, `General_TextInputDisplay` 70.4% -> 73.6%,
  `BuildingAndStatusMenu_AvailablePeasantsTextUpperRight` 80.6% -> 83.3% (36 = 36 instructions),
  `DisableWeapon_Main` 57.8% -> 58.8% - six functions, no regressions.
  `inline_once.py` finds and rewrites the sites, but **the nested call is the whole predicate and the
  source shape alone is not enough**: of 36 files with a single-use coordinate local, 4 improved, 29
  were exact ties and 3 were worse (`SaveMap_InputTextDisplay` 0.8846 -> 0.7647). The ties are the
  evidence - MSVC eliminates such a local by itself whenever nothing is live across it - so gate per
  file and reach for `diff_slots.py` first rather than grepping the source.
  The related register evidence does **not** generalise: `MainButtons` loads `[DAT_GameCore+0x68]` once
  at 0x464431 and compares `ecx` against constants sixteen times afterwards, which looks exactly like a
  source local, but introducing one is an exact tie because MSVC enregisters it from the repeated field
  form anyway. That is consistent with the note above about values feeding comparisons against
  constants; a register reused across a *call* is the case that needs a source change, not a register
  reused across comparisons.
- The dead-store shape has a **third form** that none of the existing checks can see: an arm that
  stores `X = A` and then **`break`s**, where the statement after the switch's closing brace is
  `X = B`. MSVC deletes the arm's store, so the flag ends up `B` where the original leaves it `A`.
  `find_dead_store.py` cannot see it because the two stores are not adjacent; `diff_ret_count.py`
  cannot, because `break` and `return` both count as exits; and `quick_diff.py`'s ratio does not move
  at all (0.5751 either way on the function below). Only the arm's last instruction in the binary
  settles it. In `MenuItemRenderFunction_BuildMenu_UnitActionButtons` the catapult/trebuchet path
  (0x438cb8) and the engineer-carrying-a-resource path (0x438e19) both end
  `mov dword ptr [DAT_ButtonUnknownZero], edi; pop edi; pop esi; ret` with `edi` zero, while the
  `= 1` tail is `L11` at 0x439048 (`mov dword ptr [DAT_ButtonUnknownZero], esi` with `esi` one) - which
  is exactly what `break` compiles to. Two build-menu buttons were greyed out as a result. The fix
  costs 0.6 points (39.7% -> 39.1%) and is kept under the priority order at the top of this file.
  `find_break_dead_store.py` finds the sites; it must ignore a store followed by `return;` or `goto`,
  since an arm that jumps past the tail is correct as written
  (`MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops`'s `default:` arm is that case). With that
  filter the namespace is clean apart from the two fixed here.
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
