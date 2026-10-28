/**
  HAND WRITTEN - not generated.

  path: 'OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp'

  The original gathers the neighbours of DAT_SomeTile into bitFlag with handwritten assembly, and that
  assembly is a MACRO: the identical instruction stream appears verbatim inside
  setBitFlagBasedOnWallTowerGatehouseOrKeep (0x004FF870, once), updateGFXLayers (0x004FC9E0, eleven
  times), updateMacroLayerRelated (0x004FDB00, eleven times) and updateGfxLayer (0x00509180, nineteen
  times) - never as a call. It is recognisable by "mov edx, 0" (no compiler materialises zero that
  way), by advancing the row pointer with repeated "add esi, ecx" instead of one scaled lea, and, in
  the TERRAIN variants, by loading a dword at a one-byte offset and masking it down to the low byte.

  Five shapes occur, selected by which layer pointer is read and how many neighbours are gathered:

    LOGIC   - ptr_LogicLayer,         4-byte elements: "shl eax, 2", "add esi, ecx" x4, [esi +/- 4]
    MISC    - ptr_MiscDisplayLayer,   2-byte elements: "shl eax, 1", "add esi, ecx" x2, [esi +/- 2]
    TERRAIN - ptr_TerrainTypeTileMap, 1-byte elements: no shift,     "add esi, ecx" x1, [esi +/- 1]
    _4      - east, west, north and south only
    _8      - also north-west, north-east, south-west and south-east

  bitFlag bits: 0x02 west, 0x20 east, 0x80 north, 0x08 south,
                0x01 north-west, 0x40 north-east, 0x04 south-west, 0x10 south-east.

  Every expansion clobbers eax, ebx, ecx, edx, esi and edi and leaves the result in this->neighbourMask.

  ID must be unique within the enclosing function; it exists only to keep the asm labels of two
  expansions apart. MASK must be a numeric literal or a preprocessor constant: MASM has no "|"
  operator, so an enum OR expression cannot be used as an asm operand.

  The original reaches the fields through the global instance's absolute address (0x004FF8A1
  "mov edi, [0x1FE7C70]", 0x004FF96B "mov byte ptr [0x1FE7C48], dl" - never "this"). MSVC inline asm
  cannot name DAT_TileMapState::instance ("::" is not parseable in an asm operand), so the address is
  the constant below, checked against the resolver's address at compile time. Residue: "ds:" is needed
  (without it MSVC takes "[constant]" as an immediate, error C2415), so each such read carries a redundant
  0x3E prefix the original lacks - a no-op in flat 32-bit mode.
*/

#pragma once

#include "OpenSHC/Map/TileMapState.hpp"

// DAT_TileMapState::instance (OpenSHC/Globals/DAT_TileMapState.hpp)
#define NEIGHBOUR_FLAGS_TILEMAPSTATE 0x01A93208
static_assert_cpp98_obj(NEIGHBOUR_FLAGS_TILEMAPSTATE == Address::SHC_3BB0A8C1_0x01A93208, NeighbourFlagsTileMapState)

// clang-format off

#define MACRO_NEIGHBOUR_FLAGS_LOGIC_4(ID, MASK)                                       \
    __asm mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_LogicLayer                         \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileIndex                           \
    __asm shl eax, 0x2                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x4]                                              \
    __asm mov ebx, dword ptr [esi - 0x4]                                              \
    __asm and eax, MASK                                                               \
    __asm jz east_done_##ID                                                           \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    __asm jz west_done_##ID                                                           \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz north_done_##ID                                                          \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz south_done_##ID                                                          \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov byte ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.neighbourMask, dl

#define MACRO_NEIGHBOUR_FLAGS_LOGIC_8(ID, MASK)                                       \
    __asm mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_LogicLayer                         \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileIndex                           \
    __asm shl eax, 0x2                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x4]                                              \
    __asm mov ebx, dword ptr [esi - 0x4]                                              \
    __asm and eax, MASK                                                               \
    __asm jz east_done_##ID                                                           \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    __asm jz west_done_##ID                                                           \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x4]                                              \
    __asm mov ebx, dword ptr [esi + 0x4]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz north_west_done_##ID                                                     \
    __asm or edx, 0x1                                                                 \
    __asm north_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    __asm jz north_east_done_##ID                                                     \
    __asm or edx, 0x40                                                                \
    __asm north_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    __asm jz north_done_##ID                                                          \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x4]                                              \
    __asm mov ebx, dword ptr [esi + 0x4]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz south_west_done_##ID                                                     \
    __asm or edx, 0x4                                                                 \
    __asm south_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    __asm jz south_east_done_##ID                                                     \
    __asm or edx, 0x10                                                                \
    __asm south_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    __asm jz south_done_##ID                                                          \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov byte ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.neighbourMask, dl

#define MACRO_NEIGHBOUR_FLAGS_MISC_8(ID, MASK)                                       \
    __asm mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MiscDisplayLayer                         \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileIndex                           \
    __asm shl eax, 0x1                                                                \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x2]                                              \
    __asm mov ebx, dword ptr [esi - 0x2]                                              \
    __asm and eax, MASK                                                               \
    __asm jz east_done_##ID                                                           \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    __asm jz west_done_##ID                                                           \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x2]                                              \
    __asm mov ebx, dword ptr [esi + 0x2]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz north_west_done_##ID                                                     \
    __asm or edx, 0x1                                                                 \
    __asm north_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    __asm jz north_east_done_##ID                                                     \
    __asm or edx, 0x40                                                                \
    __asm north_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    __asm jz north_done_##ID                                                          \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x2]                                              \
    __asm mov ebx, dword ptr [esi + 0x2]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz south_west_done_##ID                                                     \
    __asm or edx, 0x4                                                                 \
    __asm south_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    __asm jz south_east_done_##ID                                                     \
    __asm or edx, 0x10                                                                \
    __asm south_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    __asm jz south_done_##ID                                                          \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov byte ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.neighbourMask, dl

#define MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(ID, MASK)                                     \
    __asm mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_TerrainTypeTileMap                 \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileIndex                           \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x1]                                              \
    __asm mov ebx, dword ptr [esi - 0x1]                                              \
    __asm and eax, MASK                                                               \
    __asm jz east_done_##ID                                                           \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    __asm jz west_done_##ID                                                           \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz north_done_##ID                                                          \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz south_done_##ID                                                          \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov byte ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.neighbourMask, dl

#define MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(ID, MASK)                                     \
    __asm mov edi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_MovementDirectionTranslationMatrix \
    __asm mov esi, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.ptr_TerrainTypeTileMap                 \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileIndex                           \
    __asm add esi, eax                                                                \
    __asm push esi                                                                    \
    __asm mov eax, dword ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.curTileY                              \
    __asm shl eax, 0x5                                                                \
    __asm add edi, eax                                                                \
    __asm mov edx, 0x0                                                                \
    __asm mov eax, dword ptr [esi + 0x1]                                              \
    __asm mov ebx, dword ptr [esi - 0x1]                                              \
    __asm and eax, MASK                                                               \
    __asm jz east_done_##ID                                                           \
    __asm or edx, 0x20                                                                \
    __asm east_done_##ID:                                                             \
    __asm and ebx, MASK                                                               \
    __asm jz west_done_##ID                                                           \
    __asm or edx, 0x2                                                                 \
    __asm west_done_##ID:                                                             \
    __asm mov ecx, dword ptr [edi]                                                    \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x1]                                              \
    __asm mov ebx, dword ptr [esi + 0x1]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz north_west_done_##ID                                                     \
    __asm or edx, 0x1                                                                 \
    __asm north_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    __asm jz north_east_done_##ID                                                     \
    __asm or edx, 0x40                                                                \
    __asm north_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    __asm jz north_done_##ID                                                          \
    __asm or edx, 0x80                                                                \
    __asm north_done_##ID:                                                            \
    __asm mov ecx, dword ptr [edi + 0x10]                                             \
    __asm pop esi                                                                     \
    __asm add esi, ecx                                                                \
    __asm mov eax, dword ptr [esi - 0x1]                                              \
    __asm mov ebx, dword ptr [esi + 0x1]                                              \
    __asm mov ecx, dword ptr [esi]                                                    \
    __asm and eax, MASK                                                               \
    __asm jz south_west_done_##ID                                                     \
    __asm or edx, 0x4                                                                 \
    __asm south_west_done_##ID:                                                       \
    __asm and ebx, MASK                                                               \
    __asm jz south_east_done_##ID                                                     \
    __asm or edx, 0x10                                                                \
    __asm south_east_done_##ID:                                                       \
    __asm and ecx, MASK                                                               \
    __asm jz south_done_##ID                                                          \
    __asm or edx, 0x8                                                                 \
    __asm south_done_##ID:                                                            \
    __asm mov byte ptr ds:[NEIGHBOUR_FLAGS_TILEMAPSTATE]TileMapState.neighbourMask, dl

// clang-format on
