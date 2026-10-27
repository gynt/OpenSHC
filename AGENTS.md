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
  asm operand, so a resolver global cannot be named there. Where the handwritten block reaches a *global* layer rather
  than a `this` field, give it a C++ pointer local and name that local in the asm; the original caches the same bases in
  stack slots anyway, so the inner loop still matches. `mov eax, 0` followed by `mov ax, word ptr [..]` is the giveaway
  in its own right - that is a hand-rolled `movzx`, which the compiler always emits as one instruction.
  Such a block is usually a **macro**: the same instruction stream appears verbatim in several functions and never as a
  call, so it belongs in a hand-written `*Asm.hpp` beside them (`NeighbourFlagsAsm.hpp`, `LinkageNeighbourAsm.hpp`).
  This has been worth ~45 points per function, three times over.
- a frame pointer plus a `this` spill - the original was built without optimisation, **unless the same function also
  reports `mov reg, 0`**. MSVC keeps `ebp` in any function containing an `__asm` block, so for a function with
  handwritten assembly the frame pointer says nothing about the optimisation level: reimplement the handwritten part as
  inline asm.
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

**The function resolvers are a second, separate switch, and they matter just as much.** Every
`MACRO_FUNCTION_RESOLVER(..., false, Address::...)` in a `*.func.hpp` routes `MACRO_CALL`/`MACRO_CALL_MEMBER` to the
*original binary*, so with it off the compiler never sees our callee. It cannot then know the callee leaves `ecx`
alone, and the caller spills `this` into a callee-saved register, which renames every register downstream of the
call. `processSyncPacket` read 26.2% for that reason alone; enabling its (already 100%) callee took it to 79.2%,
and enabling all 23 finished functions of `GameSynchronyState` moved the namespace average 84.6% -> 85.7% with
nothing getting worse. It is also the missing precondition for `cmake/compiler-flags-gl.txt`: `/GL` on both sides
does nothing while the callee is still proxied. `tools/reimplementation-control/Enable-Reimplemented-Functions.ps1`
flips them; like the struct resolvers they are never committed. Only enable a callee that is itself finished.

## Working on Many Functions

When restyling or improving a large set of functions, work in batches (e.g. per folder) and verify each batch:

0. Switch **both** sets of reimplementations on before measuring anything, and never commit those files: the
   global data (the `MACRO_STRUCT_RESOLVER` flag in `src/OpenSHC/Globals/*.hpp`) and the finished functions
   (the `MACRO_FUNCTION_RESOLVER` flag in the `*.func.hpp` files). With the resolvers inactive, reccmp collapses every
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
- Prefer `const` on a local that is assigned once, spelled with `const` *after* the type (`int const tribeID = ...`).
  This is not free: a `const` local whose initialiser is a **compile-time literal** lets MSVC fold the value into its
  use sites and drop instructions the original still has, so leave those non-const. A `const` local initialised from a
  memory read or a call is code-generation neutral. Over `AI::AICState` 165 of 172 candidates were neutral and 7 were
  not - every one of them an `int tribeIndex = <literal>` feeding an array index, each costing 4 instructions and
  0.18-0.50 of match (`setTribe0x11ToAggressiveAndAttackIfConditionMet` went 1.0000 -> 0.5000). Isolate before
  blaming the qualifier: in `aiCommandTribe13DefensiveWave`, keeping `int const tribeID = <array read>` while
  reverting `int tribeIndex = 13` alone restored 1.0000.
- Never change the `// FUNCTION:` address line; keep generated headers untouched unless asked.
- Write sources as UTF-8 with LF line endings.

When removing the decompiler's `goto`s, check how many predecessors the target block has. A `LAB_*` reached from
several places has to be **duplicated** into each path; dropping it instead still compiles and is silent. Three such
bugs sat in one function (`processEntityDamageToUnit`): a damage value never assigned so the variable still held an
unrelated height, a `break` left outside its `if` that made six `switch` arms unreachable, and a `case` that fell out
of the switch leaving the value it should have set uninitialised. Fixing them was also worth 7.7% of match, so a
suspicious dead store is worth decompiling for rather than deleting. Note this is the opposite of the duplicate-tail
pattern below, where our shared block should have been two separate branches - check the predecessor count either way.

Duplicating a `LAB_*` is correct C++ but not automatically a better match, so **measure every `goto` removal**. A
`goto` in the decompiler output usually marks a block the original compiler emitted once and jumped to, and writing
the block out twice makes MSVC emit it twice: duplicating the single shared tail in
`setClimbBasedOnClosestClimbData` - two `if` arms that set a coordinate pair and then share the distance test - was
semantically identical and cost **35 points**. Keep the `goto` where the measurement says the original shared the
block, and record that in the commit remark rather than trading match for style.

Diff patterns that were reliable (more in the cheat sheet):

- Absolute `DAT_*` addresses in the original asm where the source uses `this->` mean the original accessed the global instance.
- Signed `jl/jge` vs our unsigned `jb/jae` on `undefined4`/`uint` fields: compare through `(int)`.
- `cmp x, N; ja` means `<= N`; write the literal the asm shows.
- `mov r, [x]; sub r, 1; je` inside a loop is a `switch` on `x`.
- A tail call to the same callee from our code but a jump back to a shared block in the original means separate
  `if` branches with identical bodies, not a combined condition.
- Callee-saved registers reused after a call without reload (`ecx`/`edx`) indicate LTCG (`cmake/compiler-flags-gl.txt`),
  not a source difference. Investigate by adding the caller and callee to the txt and enabling their reimplementation in the .func.hpp files.
  Only makes sense if the callee is 100% matching (e.g. ECX not touched).
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
- `jmp dword ptr [reg*4 + table]` on one side only is a dispatch-form mismatch: a `switch` over contiguous values
  becomes a jump table, an if/else-if chain becomes compares. Both directions have been worth several percent
  (`scan_dispatch.py` finds them). Handing some of a switch's values to `default:` and re-testing them with an `if`
  drops them out of the table, so give every value its own `case` and lift a shared tail out behind a flag instead.
- `x < 1` compiles to `cmp x, 1; jl` but the original usually shows `test x, x; jle`, i.e. `x <= 0`. The two are
  identical for signed and unsigned alike; write the form the asm shows.
  This one is worth sweeping rather than waiting for a diff to point at it: over `UI/MenuItems` 6 of the 10 files
  holding a `< 1)` gained, `MenuItemRenderFunction_LobbyMenu_MapSelectTable` by 7.3 points, while the reverse
  rewrite (`<= 0` to `< 1`) paid on 1 of 13 - so the asm's form really is `<= 0` and not merely a tie.
- **A comparison's operand order is a free lever and pays more often than anything else mechanical.** Ghidra puts
  whichever operand it likes on the left, usually the constant; the original source had the other one there, and
  `cmp a, b` reads `a` into the register the condition destroys, so the two orders allocate differently
  (`diff_jcc.py` reports the pair as `ORDER`). Flipping inverts the operator too, so behaviour cannot change -
  which makes it safe to try everywhere and keep per site. `flipcmp.py` does that: 25 of 314 sites paid over
  `UI/MenuItems`, taking `MenuItemActionHandler_LobbyMenu_LobbyscreenStartButtonClick` 67.7% -> 80.5% on one
  `7 < iVar3`, `MenuItemRenderFunction_InGameMenu_MainButtons` 47.6% -> 57.7% on one `10 < param_1`, and
  `MenuItemActionHandler_OverlaySlider_Deselect` and `MenuItemActionHandler_UnusedWinCondition_DeselectUnk` both
  to 100% once the mouse coordinate went first in their four bounds tests. Mind that it is per site and not per
  function: `MenuItemRenderFunction_LobbyMenu_PlayerListAndNpcButtons` has the same bounds test and *loses* 0.1 by
  flipping it.
- **The arm order of an `if`/`else` is a second free lever, and it has paid better than any other.** Ghidra
  picks the arm order from the jump it decompiled and picks it the wrong way round often: where the original
  takes `je` over a `cmp` and we take `jne`, our source has put the original's fall-through arm in the `else`.
  Inverting the operator and swapping the arms cannot change behaviour, so, like the operand-order flip, it is
  safe to try at every site and keep per site - `swaparms.py` does that. Over `UI/MenuItems` 39 of 210 sites
  paid on `quick_diff` and 25 confirmed on reccmp, worth about a point of namespace average on its own:
  `MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay` 68.4% -> 97.5%,
  `MenuItemRenderFunction_General_MenuMiniMap` 56.7% -> 83.9%,
  `MenuItemRenderFunction_EditScenario_EventAndInvasionList` 57.5% -> 79.2%,
  `MenuItemRenderFunction_MainMenu_Main` 66.9% -> 81.4%, `MenuItemRenderFunction_VideoOptions_Main` 68.7% -> 75.7%.
  Ten of the hits were one shape: a `DAT_ButtonCurrentlyInteracting::instance == FALSE` guard over two render
  calls differing only in the colour literal, where the original always falls through into the *interacting*
  arm - so the decompiler inverted that guard systematically across the menu render functions rather than by
  chance in one or two. Measure anyway: two sites that gained on `quick_diff` lost on reccmp
  (`MenuItemRenderFunction_Allies_Main` 49.7% -> 46.9%).
  The De Morgan extension of the same lever - `if (A && B) {X} else {Y}` becoming
  `if (!A || !B) {Y} else {X}` - is not worth a tool: `UI/MenuItems` holds only 4 compound
  `if`/`else` sites and none of them paid, because the decompiler writes a compound guard as an
  early return without an `else`.
- Ghidra collapses a **negated flag** into its opposite: where the original builds
  `int flag = 0; if (call() == FALSE) flag = 1;` (`xor edi,edi` / `test eax,eax` / `jne` /
  `lea edi,[eax+1]`) and later tests `flag == 0`, the decompiler stores the call's result straight
  into the local and inverts the later test instead. Writing the explicit negated flag back took
  `MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton` 62.1% -> 68.6%; writing it as
  `BOOLEnum x = (call() == FALSE)` did **not** (the cast adds the test that normalises the result to
  0/1). The `lea reg,[reg+1]` signature appears nowhere else in the namespace, so look for it per
  function rather than sweeping.
- **Correcting an off-by-one can cost a lot of match, and the correction still wins.** In
  `MenuItemRenderFunction_InGameMenu_MainButtons` the decompiler rendered one bound `-param_1 > 10`
  (that is `param_1 <= -11`) where the binary has `cmp esi, -0xa; jg`, so the original runs the
  guarded block at `param_1 == -10` and we did not; the same bound 80 lines later came out
  `param_1 < -9`, which *is* `<= -10`, and the two spellings disagreeing for one `cmp` is what
  identified the wrong one. Fixing it dropped the function 57.7% -> 47.6%, because `param_1 <= -10`
  makes MSVC hold the parameter in `edi` and the tab-type global in `esi` - the opposite of the
  original - and every downstream register follows. Neither the operand-order flip nor a snapshot
  local for the global recovers it. Keep the correct bound and say so in the commit remark.
- **Inlining a decompiler `goto` is now mechanical, and it mostly loses.** `inline_goto.py` replaces a
  forward `goto LAB;` with a copy of the label's block plus `return;`, for the one safe shape where the
  label's enclosing block runs to the end of the function; it skips a body holding a `case`, a `default:`
  or another label, because copying one redefines it (that is what three compile failures over
  `UI/MenuItems` were). The numbers put a figure on the "measure every `goto` removal" rule above: 4 of
  46 sites confirmed on reccmp - `MenuItemRenderFunction_GameplayOptions_Buttons` 68.5% -> 76.5%,
  `MenuItemRenderFunction_VideoOptions_Main` 75.7% -> 80.0%,
  `MenuItemActionHandler_General_ToolbarButtonPressed` 65.0% -> 67.6%,
  `MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons` 53.8% -> 54.4% - and a second pass that
  applied one site per file blind paid at 1 of 21 (`BuildingAndStatusMenu_BarrackMenuClick` 46.4% ->
  47.3%) while wrecking the rest: `MenuItemRenderFunction_RankingGames_Main` 97.6% -> 7.6%,
  `MenuItemRenderFunction_SingleplayerMapChoice_MapTable` 96.8% -> 51.0%,
  `MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons` 67.3% -> 32.4%. So the `goto` really is
  the original's own shared block nearly every time, and the gains are worth a sweep only because the
  tool makes each trial cheap.
- **`quick_diff.py` underrates block duplication.** `VideoOptions_Main` gained 0.0002 there and 4.3
  points on reccmp, and five sites that gained on `quick_diff` lost on reccmp. Duplicating a block moves
  every later instruction, which `quick_diff`'s line-level ratio punishes while reccmp's own alignment
  does not; use the gate as a filter against disasters rather than as a predictor, and measure anything
  that changes a function's length on reccmp.
- **Statement reordering is the best-paying lever found so far, once the trials are cheap.**
  `reorder_search.py --quick` scores with `quick_diff.py` instead of a full build and a reccmp run,
  which drops a trial from minutes to about a second and makes the whole selection reachable; it also
  means the tool's own "about one move in ten pays" was measured under a budget that only allowed a
  handful of moves. Over `UI/MenuItems` the sweep (`--pairs`, then the default run permutations) kept
  47 moves on `quick_diff` across 29 of 171 functions, and **21 of 24 changed functions confirmed
  better on reccmp**: `MenuItemActionHandler_EditScenario_EventAndInvasionList` 70.8% -> 96.4%,
  `MenuItemRenderFunction_General_MenuMiniMap` 83.9% -> 94.0%,
  `MenuItemRenderFunction_General_CreateEventCallbackFunction` 90.2% -> 95.3%,
  `MenuItemActionHandler_General_EventSlider` 69.2% -> 83.3%,
  `MenuItemActionHandler_AlliesOrder_Main` 72.0% -> 80.0%,
  `MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton` 68.6% -> 77.4%,
  `MenuItemActionHandler_TextEditor_Buttons` 69.7% -> 75.8%, `MenuItemRenderFunction_Allies_Main`
  49.7% -> 52.3% - the last after arm swaps, locals and operand flips had all been tried on it and
  reverted. Nearly every paying move is an adjacent swap of two independent stores, which is why it
  is safe: the tool's independence test is conservative, but read the diff anyway.
  Two caveats. It only looks like a contradiction of the *Statement Order* note above - the compiler
  does schedule freely, so reordering to follow the asm is still pointless; what pays is that the
  order decides which value becomes live first and so which register it lands in, which is not
  readable off the diff and has to be searched. And a second pass finds nothing: after the first
  sweep the only moves left were the four that had already measured as exact ties, so the search
  reaches a local optimum in one pass and re-running it is wasted time.
- **Triage before picking a target: `structural_diff.py --all`, and read
  `tools/compiler-internals/finding-mismatches.md` first.** That walkthrough and the tools it
  describes came from `upstream/docs/msvc-stack-slot-order`, which is a *branch*, not a path.
  The order of work is frame (`slot_map.py`), then instruction mix (`structural_diff.py`), then
  nothing - registers follow from the first two, and chasing them directly does not pay. Over the
  201 `UI/MenuItems` functions `--all` classifies 157 `mix`, 16 `order` and **22 `allocation`**,
  and that last group is the useful part: same instructions in the same order, so no source change
  can move them and they should be left alone (`RankingGames_Main` 97.6%,
  `SaveMap_InputTextDisplay` 98.1%, `EditScenario_EventAndInvasionList` 96.4%,
  `OptionsMenu_SubOptionsButtons` 97.8% and 18 more). `delta 0` with a percentage below 100 means
  the cause is outside the function - the build, a header, a resolver - and a *tie* across
  unrelated functions says how far outside.
- **`structural_diff.py`'s POLARITY block locates the arm-order lever instead of searching for
  it.** It names every branch where the original takes `je` and we take `jne` over the same
  compare - 94 sites over 51 `UI/MenuItems` functions - including the ones the decompiler wrote as
  an early return with no `else`, which `swaparms.py`'s pattern cannot match. A located site is a
  candidate and nothing more: gating the sweep on the structural score instead of `quick_diff`
  kept 22 swaps and reccmp then made **12 functions worse and one better by 0.1**
  (`InGameMenu_MainButtons` 86.3% -> 72.9%). `delta` is a mnemonic histogram and an arm swap
  barely changes which mnemonics are emitted, so it rewards noise while the allocation scrambles.
  Keep the `quick_diff` gate for swaps; reccmp is the only arbiter.
- **Both original-stream extractors used to stop at the first `ret` after a switch dispatch.** A
  `jmp dword ptr [reg*4 + TABLE]` names no target in its operands, so every case arm was invisible
  and the original read as a fragment: `MenuItemActionHandler_General_CreateEventCallbackFunction`
  came out 20 instructions of 663, which is why `quick_diff.py` could never triage it and why its
  ratio was worthless as a gate on *any* jump-table function - it was comparing our whole function
  against the dispatch prologue. `orig_body.find_end` and `quick_diff.orig` now read the table.
  Six functions were affected; `structural_diff --all`'s verdicts were otherwise unchanged. The
  heuristic still fails where a function's arms end before a *later* function's table (it then
  walks on and returns nothing, as on `QueueCommandCallback` at `0x443a30`), which is what
  `--end 0xADDR` is for.
- **`git checkout -- src/OpenSHC/<anything>` reverts the resolver flags with the sources**, because
  the uncommitted `*.func.hpp` flags live in those same directories - so reverting a rejected
  experiment that way silently disables the function resolvers and every number measured afterwards
  is against a different build than the baseline. Revert with a `'*.cpp'` pathspec instead. The
  tell is in the comparison itself: raw falls while **`norm` stays identical** (`93.5 -> 93.5`,
  `100.0 -> 100.0`), and functions the experiment never touched appear in the WORSE list. That
  mistake turned a real 12-function regression into an apparent 24-function one here, and
  `enable_local_functions.py` is what puts the flags back (not the project-wide PowerShell script,
  which enables every resolver with a `.cpp` anywhere in the tree and will not link while the build
  list is a subset - that is the `LNK2001` wall).
- **The most productive hand work is reading the original's `ret`s and tail jumps, not its
  registers.** Where the original ends a block with `pop .. / ret` or `mov [esp+4], eax / jmp F`
  and our source falls on into the function's tail, our control flow is wrong - and it is usually
  wrong in a way that is also a *bug*, which is why this pays more than any style lever. Two
  functions, done by hand off `orig_asm.py` plus `quick_diff.py`'s aligned stream:
  `MenuItemRenderFunction_LobbyMenu_NonBoxedButtons` 59.3% -> 76.5% and
  `MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus` 61.5% -> 69.0%. The shapes
  that keep recurring:
  - **A loop-exit body the decompiler put inside the loop.** It writes the exit block under the
    bound check and jumps into it with a `goto`, so after the block runs control falls back to
    the loop test. Hoist the block out after the loop. Two sites in one function, and the
    `goto` removal then leaves a `switch` arm falling into the next `case` - add the `return`
    the original's epilogue shows.
  - **A flag the original never materialised.** `bVar5 = param_1 == -2; goto LAB; if (!bVar5)`
    compiles to `xor eax,eax / sete al / cmp eax, ebp / jne`, four instructions where the
    original just lands on `je`. Both chains testing their own last value and falling into one
    shared `{ store; return; }` is the same thing without the flag.
  - **Arms we run in sequence that the original runs either/or.** Count the tail jumps: if every
    epilogue in a region is a `jmp F`, each path makes exactly *one* call, so an `if (c) { A(); }
    B();` that should be `if (c) { A(); return; } B();` shows up as one non-tail `call` among
    them. Conversely a region where the original holds *two* copies of a call plus epilogue is
    one we over-shared: in `BuildingWorkStatus` the "No labour" call belongs in both arms with
    its own `return`, and the shared version was 10 instructions short of the original.
  - **A `case` that only prepares a value and falls through into `default:`.** That is what a
    DUPLICATION run of a whole call tail means. Move the arm to just before `default:` so
    `default:` stays last and the two-level jump table survives.
- **`quick_diff.py` cannot price a switch-arm reorder, and will talk you into one.** The original's
  jump-table arms in `NonBoxedButtons` run (arg 0, no guard), (guard, arg 0), (guard, arg 1),
  (arg 1, no guard) where ours ran `case 1`..`case 4` first, so reordering to match looked like
  the obvious next move and the gate agreed - that edit gave the best ratio of the whole session,
  0.7458 against 0.4567 at the start, with the instruction count landing on 384 against the
  original's 383. reccmp then read **47.9%, eleven points below where the function started**,
  while the identical tree with the reorder dropped read 76.5%. Reordering arms moves every
  later instruction and renumbers the table, which the line-level ratio scores as alignment it
  likes and reccmp scores as a different function. Bisect with reccmp before believing the gate
  on anything that moves a block.
- The same is **not** true of addition, although `diff_lea.py`'s `add`/`lea` pairs suggest it: swapping the operands
  of every `A + B` over `UI/MenuItems` paid at 1 of 220 sites, and that one by 0.3%. The exception is the button
  rectangle the menu render functions pass to `drawColorBox`/`drawBoxWithRoundedEdges`, where the fourth argument is
  `(int)(DAT_ButtonY::instance + DAT_ButtonH::instance)` - Y first, the opposite of what the decompiler emits - while
  the third really is `DAT_ButtonW::instance + DAT_ButtonX::instance`, W first. Six of the twelve files holding the
  `H + Y` form gained, three of them reaching 100% or near it, and the 15 sites in
  `MenuItemRenderFunction_TextEditor_Buttons` all lost, so measure per file here too.
- `x == TRUE` on a field that really is a boolean is often the decompiler's rendering of a truth test: `cmp x, 1`
  against the original's `test x, x`. Rewriting it to `x != FALSE` took `MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance`
  from 62.4% to 75.2%. Only do it where the asm agrees and the field is a flag - the note above about `== TRUE`
  being a genuine `== 1` test still holds for int-typed fields, and 5 of the 7 files tried did not gain.
- A `default:` arm in the middle of a `switch` is worth moving to the end even though the move is rarely worth
  anything on its own (2 of 8 files over `UI/MenuItems`, both marginal). Where it does pay it pays with something
  else: in `MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus` moving `default:` last restored the
  original's two-level jump table over `buildingType` 5..34 (a byte table at `0x447a0c` indexing five arms at
  `0x4479f8`), and together with inlining the mill arm in place of its `goto` and inverting the `sleeping` guard so
  the cold "Turned off" arm comes first - the original jumps away on `== 0`, we jumped away on `!= 0` - it went
  39.7% -> 58.5%.
- **`undiv.py` can raise the normalized match and drop the raw match at the same time.** On
  `MenuItemRenderFunction_General_AdvancedGameOptions` its 23 restored divisions took normalized 40.8% -> 48.1% and
  brought the instruction count to 960 against the original's 961, while raw fell 39.6% -> 24.6%: the shorter body
  flips one register choice (`edi` to `ebx`) across a 50-instruction dispatch chain, and every jump offset with it.
  `perm_decls.py` over the three locals did not recover it. Decide which number the branch is reporting before
  keeping such a change; the status file records raw.
- A range's upper bound is half-open when the original ends it with `jge` and inclusive when it ends with `jg`.
  Writing `<= N-1` where the original has `< N` is a real off-by-one whenever the bound is a player or slot count -
  `processSingleTimeTick` had five, each calling a per-player routine one index out of range.
- Trust the asm over the decompilation for constants and their sign. Ghidra rendered `2400 / n + 40` where the binary
  has `sub eax, 0x28`, so the formula is `- 40`; the function reached 100% once corrected (`diff_types.py` finds these).
  A `(longlong)` in a Ghidra division is usually spurious too - it emits `_alldiv` where the original has a plain `idiv`.
- MSVC1400 at `/O2` does unroll small constant-trip loops (`applyAIV`'s 10-iteration unit loop comes out five copies
  wide from a plain `for`), and `!=` as the bound suppresses it - see the cheat sheet. A body repeated N times in the
  asm is therefore not proof that the source wrote it out N times; compile the plain loop first and compare.
  What the asm pins down is the unroll *factor*, and the way to hit a factor the compiler will not pick on its own is
  an outer loop stepping by N with the inner N left to it: that compiles identically to writing the N copies out by
  hand, down to everything but MSVC's label numbering. Read the factor off how the index is held. Once the whole trip
  count is visible the compiler constant-folds every index, so each body carries absolute addresses and an immediate;
  an original that instead keeps the index in a register and computes stored values with `lea` still had an induction
  variable, so its source had a loop. `someChatMessageSelection` is the worked case: a plain 1..8 loop and 8
  hand-written copies both give 154 instructions at 0.6745, while outer-step-4 plus an inner 0..3 gives 132 at 0.9198
  against the original's 119. Do not bother varying the loop variable - a fresh `int i`, the function's already
  declared `i`, a fresh name and a pre-declared one all produced byte-identical code.
- A flag stored with `mov dword ptr [..], 0/1` is four bytes wide, so it is not a `bool`, which stores a byte. It
  does not follow that it is a plain `int`: `BOOLEnum` is a typedef of `BOOL` and so of `int`, which means a dword
  store is exactly what a `BOOLEnum` field looks like and is no evidence against one. Decide from the writes, not
  the width - xref the field's address and read every store. `PlayerData::isNotNervousByEnemyTroopValue` is written
  7 times across the image and every store is 0 or 1 (three through a register: two `xor eax, eax` and an `ebx` the
  decompiler renders as `= 1`), and its 6 reads are all boolean tests - five `cmp .., 0x0` plus one against a zeroed
  register that Ghidra prints as `== FALSE` - so the field is a `BOOLEnum`. Grepping our own sources would have
  missed this, because 3 of its 4 writing functions are not reimplemented yet. Check Ghidra's own type for the
  field too; it already had this one as `BOOLEnum`. Correcting such a field is free: the underlying type is the
  same, so the match does not move.
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
