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

**A `BUILD_OK` is not by itself evidence that a measurement is valid - read the coverage line.** A link can fail with
`LNK1318: Unexpected PDB error; RPC (23)` when `mspdbsrv.exe` drops its connection; that is toolchain flakiness, not a
source error, and it happens at link time after every object has compiled. Killing the stale `mspdbsrv.exe` processes
and rebuilding then reports `BUILD_OK` and writes a DLL and PDB, but the PDB can come out with no symbols reccmp can
read. `diff.json` is then `function_count: 0` with empty `data`, and `reccmp_report.py` prints

    warning: the last reccmp run covers only 0 of the 805 functions in the build list.

while still reporting `0 WORSE` - which is indistinguishable from a genuine clean result if the warning is skipped.
Deleting the DLL and the PDB to force a clean relink fixes it. So after any build that did not succeed first time,
confirm the report covers the whole list before believing a number.

`try_styles.py` reports four decimals, and its tie test is exact. It used to parse the one-decimal percentage
`reccmp_report.py` prints, so anything sharing a first decimal compared as a tie - which is how a variant 0.02
points *below* its baseline got kept as "identical, so pick the readable one". Treat a tie from an older run as
unverified.

`orig_asm.py NAME` prints the **original** instruction stream of one function from the last reccmp run, rather than the
interleaved diff `reccmp_report.py diff` gives you. Use it when the diff comes back truncated, or when you need the
original's own jump targets and fall-through order to reconstruct control flow. It reads `reccmp/dll/diff.json`, so it
works with no Ghidra connection.

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
  The "no pointer variables" preference does **not** extend to the read-modify-write idiom
  `piVar1 = &x.field; *piVar1 = *piVar1 + 1;`: there the original often did compute the address once, and removing the
  pointer measurably loses. See the `unptr.py` note among the diff patterns below - decide that one per function.
  The early-return preference has one known exception, still tentative - see the note on arms sharing a tail among the
  diff patterns below.
  The `for` preference applies to loops that are already counted; **do not sweep the tree converting `while`**. All
  217 standalone `while` loops were classified and none converts safely: 108 are `while (true)` with no induction
  variable, 64 have a sentinel, flag or comma-expression condition, 11 never modify the condition variable in the
  body, 6 contain `continue`/`goto`, and 1 increments before the end. The relational-looking ones each fail for a
  concrete reason - `loadWavSounds` consumes the variable *after* incrementing it (`loadingBar = i * 80`), so
  hoisting the increment changes the result; `MenuItemActionHandler_CrusadeMap_Main` has a trailing `if (20 < i) {}`
  bound check that must stay after the increment; the `FilePackager` inner scans never touch their condition
  variable; and `copyData`/`fillMemory`/`compressRLE`/`computeHash` are block-stride routines. Note that a `while`
  with a trailing increment and a `continue` is **not** equivalent to the `for`: the `for` header always runs the
  increment.
- Never change the `// FUNCTION:` address line; keep generated headers untouched unless asked.
- Write sources as UTF-8 with LF line endings.

When removing the decompiler's `goto`s, check how many predecessors the target block has. A `LAB_*` reached from
several places has to be **duplicated** into each path; dropping it instead still compiles and is silent. Three such
bugs sat in one function (`processEntityDamageToUnit`): a damage value never assigned so the variable still held an
unrelated height, a `break` left outside its `if` that made six `switch` arms unreachable, and a `case` that fell out
of the switch leaving the value it should have set uninitialised. Fixing them was also worth 7.7% of match, so a
suspicious dead store is worth decompiling for rather than deleting. Note this is the opposite of the duplicate-tail
pattern below, where our shared block should have been two separate branches - check the predecessor count either way.

Diff patterns that were reliable (more in the cheat sheet):

- Absolute `DAT_*` addresses in the original asm where the source uses `this->` mean the original accessed the global instance.
- Signed `jl/jge` vs our unsigned `jb/jae` on `undefined4`/`uint` fields: compare through `(int)`.
- `cmp x, N; ja` means `<= N`; write the literal the asm shows.
- `mov r, [x]; sub r, 1; je` inside a loop is a `switch` on `x`.
- A tail call to the same callee from our code but a jump back to a shared block in the original means separate
  `if` branches with identical bodies, not a combined condition.
- Callee-saved registers reused after a call without reload (`ecx`/`edx`) indicate LTCG (`cmake/compiler-flags-gl.txt`),
  not a source difference.
- A mismatching argument count or `ret N` usually means the generated header is wrong; report it instead of working around it.
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
- `piVar1 = &x.field; *piVar1 = *piVar1 + 1;` is `x.field = x.field + 1` (`unptr.py`). Only rewrite it when the store
  immediately follows the pointer: a pointer freezes the address while the field form re-evaluates the index, so with a
  call or a write to the index in between the two forms differ. It was worth 1.2% over 60 sites in one function, but
  **do not run it as a blanket pass** - which of the two forms matches is decided per function and swings up to 8
  points either way. Measured over 20 functions with `try_styles.py`: 10 preferred the pointer, 5 preferred the field
  form, 5 tied exactly. Largest wins for the pointer `UpdateMill` +3.3 (42.4850% against 39.2000%) and `UpdateIronMine`
  +3.5; largest wins for the field form `processDeerMoving` +7.8 (36.4729% -> 44.3114%) and `UpdateWheatFarm` +3.2
  (56.0748% -> 59.2593%). So neither "remove the pointer walks" nor "keep them" is right on its own, and both
  directions are real rather than allocator noise - they reproduce exactly to four decimals.
  Five ways of predicting the winner from the source were tried and **all failed**; do not spend time re-deriving them:
  what the pointer targets (a variable-indexed global array element, a `this->` member or a global scalar), how many
  sites the function has, what fraction of its RMW sites already match the original, how many `[DAT_*::instance]`
  indices it contains, and whether the index variable is loaded from a global or is a local or parameter. The last
  looked strong in-sample (global-indexed preferred the pointer 7 of 10, mean +1.0) and was then falsified
  out-of-sample by `UpdateWheatFarm`, which is global-indexed and prefers the field form by 3.2.
  Two things are settled, and both save builds:
  - `x = x + 1`, `x += 1` and `x++` compile **identically** - exact ties on two functions (three ways at 39.2000% on
    `UpdateMill`, again at 24.9578% on `UpdatePoleturnersWorkshop`). There are only ever two candidates, so a
    `try_styles.py` run here needs exactly two variants, and compound assignment is not a lever.
  - Never hoist an **object pointer** to a global array element (`Building* b = &...buildings[id];` then `b->field`).
    On `UpdateMill` that scored 18.5263% against 42.4850% for the per-field pointer, **24 points worse**. The original
    folds the global's address into the instruction displacement and keeps only the scaled index in a register
    (`add dword ptr [esi + BuildingsState+108], ecx`); an explicit `T*` forces `[ptr + 108]` and loses the folding.
    That `esi` is the compiler's own CSE of the index computation, not a pointer the source held.
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
  There is one mechanically actionable case, and it is worth checking first because it is a real bug rather than a
  style difference: **our frame being far *smaller* than the original's** (8 bytes, or `-`, against 0x3f4). That
  means a local was declared and never referenced, so MSVC deleted it -- and the usual reason is that Ghidra split
  one stack object into two locals. Nine files had the same split of a 1008-byte filename buffer:

      char local_3f4[4];      // the filename is copied in here through a pointer walk
      char local_3f0[1004];   // never referenced anywhere, so MSVC drops it

  The code then copies a map or save name into what is left and appends an extension, i.e. it writes an arbitrary
  length string past the end of the frame. Merging the pieces into one `char local_3f4[1008]` fixed the corruption
  and moved every one of the nine closer to the original; four landed on the original's frame size exactly, and the
  match gains ran +1.2 to +16.0 (average +6.6 over the last six). `MenuView_LobbyMenu_DoEveryFrame` went from a
  16-byte frame to the original's 0x400 and is now `alloc-only`.
  To find them: Ghidra names a stack local after its frame offset (`local_3f4` is -0x3f4, `aGStack_3c` is -0x3c),
  so the pieces of one object are exactly contiguous - `offset(next) == offset(prev) - sizeof(prev)`. Look for two
  adjacent arrays of the same element type where the second is never referenced, and confirm the merge by watching
  `frmU` converge on `frmO` rather than by the percentage. Note the trailing `local_4`/`local_c` in such a run is
  the security cookie, not part of the object, and that a local which has already been given a meaningful name has
  lost its offset and so cannot be found this way - `undefined4 _dpSessionDesc2[6]` plus `GUID aGStack_3c[3]` was
  one 80-byte `DPSESSIONDESC2` (`guidApplication` is at +24), caught only by its `_memset(.., 0x50)` overrunning a
  24-byte array.
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
- MSVC1400 at `/O2` never unrolls a loop, so a body repeated N times in the asm means the source was written out N
  times. A plain loop where the original is unrolled has cost 80 points on its own.
- A flag stored with `mov dword ptr [..], 0/1` is an `int`, not a `bool`, which stores a byte.
- `BOOLEnum` is `typedef BOOL`, i.e. `int`, so `x == FALSE` is exactly `!x` but **`x == TRUE` is `x == 1`** and is
  not `x` for any other nonzero value. The decompiler writes `== TRUE` wherever the constant happens to be 1, which
  is how `currentPlayerSlotID == TRUE` (an `int` player slot 0..8) and `unitControlsRelated == TRUE` (an
  `undefined4` holding 4, 5, 0x14, 0x16, 0x20) both appear in the sources: those are genuine `== 1` tests and
  rewriting them to a truth test is a behaviour change. Check the operand's declared type before touching one.
  The two forms also differ in codegen - `cmp x, 1; je` against `test x, x; jne` - so the asm says which the
  original used. Note too that `bVar = x != FALSE;` is an assignment rather than a condition, and there the
  `!= FALSE` is load-bearing: it emits the 0/1 normalisation a raw store does not.
- **A generated `BOOLEnum` field that is assigned a non-boolean constant is mis-typed**, and the wrong type is worth
  fixing because it is what makes the `== TRUE` above look rewritable. Two cases so far, both found by noticing one
  odd assignment: `GameCore::scribeAnimationPhase` is compared against `2` as well as `TRUE`, so it is a three-state
  animation phase; `UnitsState::pendingUnitControlMode` is assigned `0x14` and two parameters, and its only consumer
  copies it into `unitControlsRelated`, an `undefined4` at the adjacent offset. Scan for an assignment or comparison
  that is neither `TRUE`, `FALSE`, `0` nor `1`; when the field is really an int, the `= TRUE` assignments can stay,
  since `TRUE` is `1` and `1` is usually a legitimate value.
- Tentative, one clear case so far: where two arms of a condition share a tail, the nested `if/else` shape the
  decompiler emits can beat the early returns the style list above asks for, because it decides *which* arm holds the
  physical copy of the shared block. In `calculateTaxIncomeForPlayer` the original keeps the shared `(tax * 150) / 100`
  in the second arm and jumps forward into it from the first; early returns put the copy in the first arm and made the
  second jump backwards, and switching to nested `if/else` was worth 17 points. Read the original's own jump direction
  with `orig_asm.py NAME` to see which arm should hold it. Treat this as a thing to try, not a rule: the same change
  measured *worse* on `updateCrowding` (all three nested variants lost 9-14 points) and made no difference at all on
  `showPopAndGoldPopup` and `createStatsPopUpEntities`, where every shape tied to the decimal because the gap there is
  the loop base-pointer anchor. `try_styles.py` settles it per function; prefer the early-return form on a tie.

## Naming Struct Fields

Naming a `field*_0x*` or `padding*` slot is an evidence problem, not a guessing one. Three traps have each
cost real work:

- **A Ghidra DATA xref to a field's address can be a loop terminator, not a use.** `ResetAiVariationArrayValue`
  and `SetAIPlayerNickNames` both reference `GameSynchronyState+0x75c`, which looks like strong evidence that
  the field is the AI variation array. It is not: the decompilation ends its loop with
  `while ((int)piVar1 < 0x191dec4)`, and `0x0191DEC4` *is* that field's address - it is the exclusive end bound
  of a walk over the preceding `aiVariationArray[9]` (`0x738-0x75B`). Read the decompilation before treating an
  xref as a use, and check whether the address is simply the end of the field before it.
- **Read the field's whole site list before naming it.** `Building+0x298` assigns `0` and `1` in its first three
  sites and reads as `if (!x)`, which reads exactly like a boolean; the full list also assigns `2` and `3`, so it
  is a stage machine. A name taken from a sample of the sites will be confidently wrong.
- **Write-only across the whole binary is common, and is the right reason to leave a field unnamed.** Verify it
  with Ghidra xrefs on the resolved address, not with the reimplemented subset: a field can look write-only to us
  simply because its reader is not reimplemented yet. Of `GameSynchronyState`'s 38 referenced unnamed fields, 19
  turned out to have no reader anywhere, including `0xba4`, which `SyncPacketSizeAnnouncement` serialises onto the
  wire and which neither side ever reads. Prefer leaving these alone over inventing semantics for them.

Two further notes:

- Compute the address as the resolver's base plus the field offset and confirm it against a field whose name is
  already known. Mis-attributing one slot shifts every conclusion: `[0x01fe7bc8]` in `renderMap` is
  `TileMapState+0x5549C0`, so it is `field161`, not the `field162` an off-by-one makes it look like.
- A struct's own header shows which convention a new name should follow - PascalCase beside
  `MissionSpeechFileNames` for a predefined table, camelCase beside `sortColumn` for mutable state - and the
  offsets chain exactly, so a `[50][4]` table at `0xFF4` following `SkirmishTrailIconOffsets[50]` at `0xF2C`
  (`0xF2C + 200 = 0xFF4`) is confirmation that it belongs to the same family.

Where a slot is shared between building types, name it after the type that uses it and expect the name to be
extended later, as `flagonsOfAleOrCheeseOrReleaseDogs` already was.

## Agent Skills

Task-specific guidance is available under `.agents/skills/`.

When a relevant skill exists, prefer it over this document, as it contains more detailed workflows and repository-specific guidance.

## Agent Maintenance

If you discover undocumented conventions, missing workflows, or repeated guidance, suggest updates to this guide or the relevant skill.
