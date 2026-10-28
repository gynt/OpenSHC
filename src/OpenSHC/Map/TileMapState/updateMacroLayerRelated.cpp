#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

// masks for the handwritten neighbour-flag macro; MASM has no "|", so these must be literals
#define NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH 0x8000 // L_DEFAULT_EARTH_OR_TEXTURE
#define NEIGHBOUR_FLAGS_MASK_MARSH 0x20000000 // L_MARSH
#define NEIGHBOUR_FLAGS_MASK_SEA 0x1 // L_SEA
#define NEIGHBOUR_FLAGS_MASK_L2_SCRUB 0x1 // L2_SCRUB
#define NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES 0x2 // L2_EARTH_AND_STONES
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM 0x4 // L2_PLATEAU_MEDIUM
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH 0x8 // L2_PLATEAU_HIGH
#define NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS 0x10 // L2_OASIS_GRASS
#define NEIGHBOUR_FLAGS_MASK_L2_BEACH 0x20 // L2_BEACH
#define NEIGHBOUR_FLAGS_MASK_L2_STONES 0x40 // L2_STONES_OR_DRIVEN_SANDUnk
#define NEIGHBOUR_FLAGS_MASK_L2_THICK_SCRUB 0x80 // L2_THICK_SCRUB

#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_OIL;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FDB00
    void TileMapState::updateMacroLayerRelated(uint logic1, uint logic2, int clearMacroFirst)
    {
        /*
          Five copies of the same block/sub-tile loop skeleton, and eleven expansions of the
          handwritten neighbour-flag macro (see NeighbourFlagsAsm.hpp). The original was built
          without optimisation, so the pragma above is needed to reproduce its frame-pointer,
          reload-per-access code shape. At /Od MSVC 2005 orders the stack slots by a fixed per-name
          key, not by declaration order; these names give the original's slot layout
          (previous macro at ebp-4 down to the saved beach mask at ebp-0x34).
        */
        int previousMacroValue;
        int firstRow;
        int blockColIndex;
        int index;
        int chunkRow;
        int targetTile;
        int tileYIndex;
        int innerColumn;
        int cellYOffset;
        int randomVariation;
        int cellOffsetX;
        int tileX;
        int savedNeighbourMask;

        firstRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (chunkRow = this->dirtySectionRowMin; chunkRow <= this->dirtySectionRowMax; chunkRow++) {
            for (blockColIndex = this->dirtySectionColMin; blockColIndex <= this->dirtySectionColMax; blockColIndex++) {
                if (DAT_TileMapState::instance.mapping40x40[chunkRow][blockColIndex] != 0) {
                    tileYIndex = firstRow;
                    firstRow = 0;
                    for (; tileYIndex < 10; tileYIndex++) {
                        for (innerColumn = 0, this->curTileY = chunkRow * 10 + tileYIndex,
                            this->curTileX = blockColIndex * 10;
                             innerColumn < 10; innerColumn++, this->curTileX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY)
                                == FALSE) {
                                continue;
                            }
                            this->curTileIndex
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY);
                            if ((char)this->ChangedLayer[this->curTileIndex] == 0) {
                                continue;
                            }
                            previousMacroValue = (short)this->MacroLayer[this->curTileIndex];
                            if (clearMacroFirst != 0) {
                                this->MacroLayer[this->curTileIndex] = 0;
                            }
                            if ((this->LogicLayer[this->curTileIndex] & logic1) != 0) {
                                /* the tile carries the requested logic flag */
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & logic2) != 0) {
                                /* the tile carries the requested terrain flag */
                            } else {
                                continue;
                            }
                            if ((this->LogicLayer[this->curTileIndex] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                                this->neighbourMask = 0;
                            } else if (logic1 == 0x8000) {
                                MACRO_NEIGHBOUR_FLAGS_LOGIC_8(1, NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH)
                            } else if (logic1 == 0x20000000) {
                                if ((this->LogicLayer[this->curTileIndex] & L_OIL) != 0) {
                                    continue; // 0x4FDE01: jmp 0x4FDBD3 (next sub-column, tile untouched)
                                }
                                // 0x4FDED6: jmp 0x4FE5B0 (common MacroLayer store / updateWalkAndPathLayer tail)
                                MACRO_NEIGHBOUR_FLAGS_LOGIC_8(2, NEIGHBOUR_FLAGS_MASK_MARSH)
                            } else if (logic2 == 0x2) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(3, NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES)
                            } else if (logic2 == 0x10) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(4, NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS)
                            } else if (logic2 == 0x1) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(5, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                            } else if (logic2 == 0x80) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(6, NEIGHBOUR_FLAGS_MASK_L2_THICK_SCRUB)
                            } else if (logic2 == 0x40) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(7, NEIGHBOUR_FLAGS_MASK_L2_STONES)
                            } else if (logic2 == 0x20) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(8, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                                savedNeighbourMask = this->neighbourMask;
                                MACRO_NEIGHBOUR_FLAGS_LOGIC_8(9, NEIGHBOUR_FLAGS_MASK_SEA)
                                this->neighbourMask = this->neighbourMask | savedNeighbourMask;
                            } else if (logic2 == 0x4) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(10, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM)
                            } else if (logic2 == 0x8) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_8(11, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH)
                            } else {
                                this->neighbourMask = 0;
                            }
                            if (this->neighbourMask != 0xff) {
                                this->MacroLayer[this->curTileIndex] = 1;
                            } else if (((short)this->RandomLayer[this->curTileIndex] & 0xf) == 0) {
                                this->MacroLayer[this->curTileIndex] = 2;
                            } else {
                                this->MacroLayer[this->curTileIndex] = 0x800;
                            }
                            if (previousMacroValue != (short)this->MacroLayer[this->curTileIndex]) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                                    &DAT_PathFindingState::instance)(1, this->curTileX, this->curTileY);
                            }
                        }
                    }
                }
            }
        }
        firstRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (chunkRow = this->dirtySectionRowMin; chunkRow <= this->dirtySectionRowMax; chunkRow++) {
            for (blockColIndex = this->dirtySectionColMin; blockColIndex <= this->dirtySectionColMax; blockColIndex++) {
                if (DAT_TileMapState::instance.mapping40x40[chunkRow][blockColIndex] != 0) {
                    tileYIndex = firstRow;
                    firstRow = 0;
                    for (; tileYIndex < 10; tileYIndex++) {
                        for (innerColumn = 0, this->curTileY = chunkRow * 10 + tileYIndex,
                            this->curTileX = blockColIndex * 10;
                             innerColumn < 10; innerColumn++, this->curTileX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY)
                                == FALSE) {
                                continue;
                            }
                            this->curTileIndex
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY);
                            if ((short)this->MacroLayer[this->curTileIndex] != 0x800) {
                                continue;
                            }
                            tileX = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                &DAT_ViewportRenderState::instance)(this->curTileIndex, this->curTileY);
                            randomVariation = (short)this->RandomLayer[this->curTileIndex] & 0xf;
                            for (index = 0; index < 0x10; index++) {
                                cellOffsetX = DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[index].x;
                                cellYOffset = DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[index].y;
                                targetTile = MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(tileX + cellOffsetX, this->curTileY + cellYOffset);
                                if ((short)this->MacroLayer[targetTile] != 0x800) {
                                    break;
                                }
                            }
                            if (index < 0x10) {
                                continue;
                            }
                            for (index = 0; index < 0x10; index++) {
                                cellOffsetX = DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[index].x;
                                cellYOffset = DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[index].y;
                                targetTile = MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(tileX + cellOffsetX, this->curTileY + cellYOffset);
                                this->MacroLayer[targetTile] = 0x10;
                                (short&)this->MacroLayer[targetTile] += index << 6;
                                (short&)this->MacroLayer[targetTile] += randomVariation << 12;
                            }
                        }
                    }
                }
            }
        }
        firstRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (chunkRow = this->dirtySectionRowMin; chunkRow <= this->dirtySectionRowMax; chunkRow++) {
            for (blockColIndex = this->dirtySectionColMin; blockColIndex <= this->dirtySectionColMax; blockColIndex++) {
                if (DAT_TileMapState::instance.mapping40x40[chunkRow][blockColIndex] != 0) {
                    tileYIndex = firstRow;
                    firstRow = 0;
                    for (; tileYIndex < 10; tileYIndex++) {
                        for (innerColumn = 0, this->curTileY = chunkRow * 10 + tileYIndex,
                            this->curTileX = blockColIndex * 10;
                             innerColumn < 10; innerColumn++, this->curTileX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY)
                                == FALSE) {
                                continue;
                            }
                            this->curTileIndex
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY);
                            if ((short)this->MacroLayer[this->curTileIndex] != 0x800) {
                                continue;
                            }
                            tileX = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                &DAT_ViewportRenderState::instance)(this->curTileIndex, this->curTileY);
                            randomVariation = (short)this->RandomLayer[this->curTileIndex] & 0xf;
                            for (index = 0; index < 9; index++) {
                                cellOffsetX = DAT_TerrainDefinedData::instance.macroBlock3x3Offsets[index].x;
                                cellYOffset = DAT_TerrainDefinedData::instance.macroBlock3x3Offsets[index].y;
                                targetTile = MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(tileX + cellOffsetX, this->curTileY + cellYOffset);
                                if ((short)this->MacroLayer[targetTile] != 0x800) {
                                    break;
                                }
                            }
                            if (index < 9) {
                                continue;
                            }
                            for (index = 0; index < 9; index++) {
                                cellOffsetX = DAT_TerrainDefinedData::instance.macroBlock3x3Offsets[index].x;
                                cellYOffset = DAT_TerrainDefinedData::instance.macroBlock3x3Offsets[index].y;
                                targetTile = MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(tileX + cellOffsetX, this->curTileY + cellYOffset);
                                this->MacroLayer[targetTile] = 8;
                                (short&)this->MacroLayer[targetTile] += index << 6;
                                (short&)this->MacroLayer[targetTile] += randomVariation << 12;
                            }
                        }
                    }
                }
            }
        }
        firstRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (chunkRow = this->dirtySectionRowMin; chunkRow <= this->dirtySectionRowMax; chunkRow++) {
            for (blockColIndex = this->dirtySectionColMin; blockColIndex <= this->dirtySectionColMax; blockColIndex++) {
                if (DAT_TileMapState::instance.mapping40x40[chunkRow][blockColIndex] != 0) {
                    tileYIndex = firstRow;
                    firstRow = 0;
                    for (; tileYIndex < 10; tileYIndex++) {
                        for (innerColumn = 0, this->curTileY = chunkRow * 10 + tileYIndex,
                            this->curTileX = blockColIndex * 10;
                             innerColumn < 10; innerColumn++, this->curTileX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY)
                                == FALSE) {
                                continue;
                            }
                            this->curTileIndex
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY);
                            if ((short)this->MacroLayer[this->curTileIndex] != 0x800) {
                                continue;
                            }
                            tileX = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::computeTileXOffset,
                                &DAT_ViewportRenderState::instance)(this->curTileIndex, this->curTileY);
                            randomVariation = (short)this->RandomLayer[this->curTileIndex] & 0xf;
                            for (index = 0; index < 4; index++) {
                                cellOffsetX = DAT_TerrainDefinedData::instance.macroBlock2x2Offsets[index].x;
                                cellYOffset = DAT_TerrainDefinedData::instance.macroBlock2x2Offsets[index].y;
                                targetTile = MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(tileX + cellOffsetX, this->curTileY + cellYOffset);
                                if ((short)this->MacroLayer[targetTile] != 0x800) {
                                    break;
                                }
                            }
                            if (index < 4) {
                                continue;
                            }
                            for (index = 0; index < 4; index++) {
                                cellOffsetX = DAT_TerrainDefinedData::instance.macroBlock2x2Offsets[index].x;
                                cellYOffset = DAT_TerrainDefinedData::instance.macroBlock2x2Offsets[index].y;
                                targetTile = MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(tileX + cellOffsetX, this->curTileY + cellYOffset);
                                this->MacroLayer[targetTile] = 4;
                                (short&)this->MacroLayer[targetTile] += index << 6;
                                (short&)this->MacroLayer[targetTile] += randomVariation << 12;
                            }
                        }
                    }
                }
            }
        }
        firstRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (chunkRow = this->dirtySectionRowMin; chunkRow <= this->dirtySectionRowMax; chunkRow++) {
            for (blockColIndex = this->dirtySectionColMin; blockColIndex <= this->dirtySectionColMax; blockColIndex++) {
                if (DAT_TileMapState::instance.mapping40x40[chunkRow][blockColIndex] != 0) {
                    tileYIndex = firstRow;
                    firstRow = 0;
                    for (; tileYIndex < 10; tileYIndex++) {
                        for (innerColumn = 0, this->curTileY = chunkRow * 10 + tileYIndex,
                            this->curTileX = blockColIndex * 10;
                             innerColumn < 10; innerColumn++, this->curTileX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY)
                                == FALSE) {
                                continue;
                            }
                            this->curTileIndex
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    &DAT_ViewportRenderState::instance)(this->curTileX, this->curTileY);
                            if ((short)this->MacroLayer[this->curTileIndex] == 0x800) {
                                this->MacroLayer[this->curTileIndex] = 2;
                            }
                        }
                    }
                }
            }
        }
    }

}
}

#pragma optimize("", on)
