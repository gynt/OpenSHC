#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

// masks for the handwritten neighbour-flag macro; MASM has no "|", so these must be literals
#define NEIGHBOUR_FLAGS_MASK_MARSH 0x20000000 // L_MARSH
#define NEIGHBOUR_FLAGS_MASK_SEA 0x1 // L_SEA
#define NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH 0x8000 // L_DEFAULT_EARTH_OR_TEXTURE
#define NEIGHBOUR_FLAGS_MASK_L2_SCRUB 0x1 // L2_SCRUB
#define NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES 0x2 // L2_EARTH_AND_STONES
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM 0x4 // L2_PLATEAU_MEDIUM
#define NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH 0x8 // L2_PLATEAU_HIGH
#define NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS 0x10 // L2_OASIS_GRASS
#define NEIGHBOUR_FLAGS_MASK_L2_BEACH 0x20 // L2_BEACH
#define NEIGHBOUR_FLAGS_MASK_L2_STONES 0x40 // L2_STONES_OR_DRIVEN_SANDUnk

#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_MEDIUM;
    using OpenSHC::Map::LogicHelpers::L2_SCRUB;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC9E0
    void TileMapState::updateGFXLayers()
    {
        /*
          Contains the handwritten neighbour-flag macro nine times (see NeighbourFlagsAsm.hpp), which
          is why the surrounding code is unoptimised: MSVC disables optimisation in a function holding
          inline asm, so every field access reloads this from the frame.

          "tmpHeight" is stored below but never read (dead, present in the original). The original does
          NOT store the raw MacroLayer into "rotationTmp" here (0x4FCBCC-0x4FCC33): it is the start
          sub-row of the next 40x40 block, so such a store would skip rows of later blocks.
        */
        /*
          The locals are declared here, with these names and in this order, because the original was
          built without optimisation, so its stack slots are observable. MSVC 2005 /Od groups the slots
          by a hash of the variable name, and within a group a later declaration gets a higher address.
          These names and this order reproduce the original frame: rotationTmp -4, blockColumnVar -8,
          curGfxMode -0xc, index -0x10 ... savedBitFlag -0x4c.
        */
        int blockColumnVar;
        int rotationTmp;
        int curGfxMode;
        int index;
        int gfxBaseD;
        int localBlockRowValue;
        int macroHigh;
        int luminescence;
        int savedBitFlag;
        int curMacroMidValue;
        int gfxBaseC;
        int localBaseBTmp;
        int tmpHeight;
        int curGfxBaseEValue;
        int curMacroLowValue;
        int localGfxBaseATmp;
        int localColumnVar;
        int subRow;
        int gfxStrideCur;

        if (this->forceUpdateGFXLayers <= 0) {
            return;
        }
        this->forceUpdateGFXLayers = this->forceUpdateGFXLayers - 1;

        if (MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::getYSmallerThanYLimit, (&DAT_PathFindingState::instance))()
            == FALSE) {
            return;
        }

        rotationTmp = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (localBlockRowValue = this->dirtySectionRowMin; localBlockRowValue <= this->dirtySectionRowMax;
             localBlockRowValue++) {
            for (blockColumnVar = this->dirtySectionColMin; blockColumnVar <= this->dirtySectionColMax;
                 blockColumnVar++) {
                if (DAT_TileMapState::instance.mapping40x40[localBlockRowValue][blockColumnVar] != 0) {
                    subRow = rotationTmp;
                    rotationTmp = 0;
                    for (; subRow < 10; subRow++) {
                        for (localColumnVar = 0, this->curTileY = localBlockRowValue * 10 + subRow,
                            this->curTileX = blockColumnVar * 10;
                             localColumnVar < 10; localColumnVar++, this->curTileX++) {
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    (&DAT_ViewportRenderState::instance))(this->curTileX, this->curTileY)
                                == FALSE) {
                                continue;
                            }
                            this->curTileIndex
                                = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile,
                                    (&DAT_ViewportRenderState::instance))(this->curTileX, this->curTileY);
                            if ((this->LogicLayer[this->curTileIndex] & L_DEFAULT_EARTH_OR_TEXTURE) == 0) {
                                continue;
                            }
                            if (this->GfxLayer[this->curTileIndex] != 0) {
                                continue;
                            }
                            luminescence = this->LuminesenceLayer[this->curTileIndex];
                            if (luminescence < 2) {
                                luminescence = 2;
                            }
                            curMacroLowValue = (short)this->MacroLayer[this->curTileIndex] & 0x3f;
                            curMacroMidValue = ((short)this->MacroLayer[this->curTileIndex] & 0x7c0) >> 6;
                            macroHigh = ((short)this->MacroLayer[this->curTileIndex] & 0xf000) >> 12;
                            macroHigh = macroHigh & 3;
                            this->PillarGFXLayer[this->curTileIndex] = GMFirstPictureIndex::instance[9];

                            if ((this->LogicLayer[this->curTileIndex] & L_MARSH) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_LOGIC_4(1, NEIGHBOUR_FLAGS_MASK_MARSH)
                                localGfxBaseATmp = 1;
                                localBaseBTmp = 3;
                                gfxBaseC = 0x15;
                                gfxBaseD = 0x21;
                                curGfxBaseEValue = 0x25;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_EARTH_AND_STONES) != 0) {
                                tmpHeight = this->HeightLayer[this->curTileIndex];
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(2, NEIGHBOUR_FLAGS_MASK_L2_EARTH_AND_STONES)
                                localGfxBaseATmp = 0x99;
                                localBaseBTmp = 0x9b;
                                gfxBaseC = 0xad;
                                gfxBaseD = 0xb9;
                                curGfxBaseEValue = 0xbd;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_OASIS_GRASS) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(3, NEIGHBOUR_FLAGS_MASK_L2_OASIS_GRASS)
                                localGfxBaseATmp = 0x1c9;
                                localBaseBTmp = 0x1cb;
                                gfxBaseC = 0x1dd;
                                gfxBaseD = 0x1e9;
                                curGfxBaseEValue = 0x1ed;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_STONES_OR_DRIVEN_SANDUnk)
                                != 0) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(4, NEIGHBOUR_FLAGS_MASK_L2_STONES)
                                localGfxBaseATmp = 0x261;
                                localBaseBTmp = 0x263;
                                gfxBaseC = 0x275;
                                gfxBaseD = 0x281;
                                curGfxBaseEValue = 0x285;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_SCRUB) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(5, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                localGfxBaseATmp = 0x2f9;
                                localBaseBTmp = 0x2fb;
                                gfxBaseC = 0x30d;
                                gfxBaseD = 0x319;
                                curGfxBaseEValue = 0x31d;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_THICK_SCRUB) != 0) {
                                /* the original gathers L2_SCRUB here, not L2_THICK_SCRUB; kept as-is */
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(6, NEIGHBOUR_FLAGS_MASK_L2_SCRUB)
                                localGfxBaseATmp = 0x4a9;
                                localBaseBTmp = 0x4ab;
                                gfxBaseC = 0x4bd;
                                gfxBaseD = 0x4c9;
                                curGfxBaseEValue = 0x4cd;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_PLATEAU_MEDIUM) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(7, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_MEDIUM)
                                localGfxBaseATmp = 0x131;
                                localBaseBTmp = 0x133;
                                gfxBaseC = 0x145;
                                gfxBaseD = 0x151;
                                curGfxBaseEValue = 0x155;
                                gfxStrideCur = 4;
                                curGfxMode = 2;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_PLATEAU_HIGH) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(8, NEIGHBOUR_FLAGS_MASK_L2_PLATEAU_HIGH)
                                localGfxBaseATmp = 0x131;
                                localBaseBTmp = 0x133;
                                gfxBaseC = 0x145;
                                gfxBaseD = 0x151;
                                curGfxBaseEValue = 0x155;
                                gfxStrideCur = 4;
                                curGfxMode = 2;
                            } else if (((char)this->Logic2Layer[this->curTileIndex] & L2_BEACH) != 0) {
                                MACRO_NEIGHBOUR_FLAGS_TERRAIN_4(9, NEIGHBOUR_FLAGS_MASK_L2_BEACH)
                                savedBitFlag = this->neighbourMask;
                                MACRO_NEIGHBOUR_FLAGS_LOGIC_4(10, NEIGHBOUR_FLAGS_MASK_SEA)
                                this->neighbourMask = this->neighbourMask | savedBitFlag;
                                localGfxBaseATmp = 0x391;
                                localBaseBTmp = 0x393;
                                gfxBaseC = 0x3a5;
                                gfxBaseD = 0x3b1;
                                curGfxBaseEValue = 0x3b5;
                                gfxStrideCur = 4;
                                curGfxMode = 0;
                            } else {
                                MACRO_NEIGHBOUR_FLAGS_LOGIC_4(11, NEIGHBOUR_FLAGS_MASK_DEFAULT_EARTH)
                                localGfxBaseATmp = 0x131;
                                localBaseBTmp = 0x133;
                                gfxBaseC = 0x145;
                                gfxBaseD = 0x151;
                                curGfxBaseEValue = 0x155;
                                gfxStrideCur = 4;
                                curGfxMode = 2;
                            }

                            if (curMacroLowValue == 1) {
                                this->neighbourMask = ~this->neighbourMask;
                                this->neighbourMask = this->neighbourMask & 0xaa;
                                if (this->mapOrientation == 0) {
                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                            rotateByteLeft,
                                        (&DAT_DirectionAlgorithmState::instance))(this->neighbourMask, 0);
                                } else if (this->mapOrientation == 2) {
                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                            rotateByteLeft,
                                        (&DAT_DirectionAlgorithmState::instance))(this->neighbourMask, 2);
                                } else if (this->mapOrientation == 4) {
                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                            rotateByteLeft,
                                        (&DAT_DirectionAlgorithmState::instance))(this->neighbourMask, 4);
                                } else if (this->mapOrientation == 6) {
                                    this->neighbourMask = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                            rotateByteLeft,
                                        (&DAT_DirectionAlgorithmState::instance))(this->neighbourMask, 6);
                                }

                                if (curGfxMode == 1) {
                                    this->GfxLayer[this->curTileIndex] = 0;
                                    for (index = 0; index < 4; index++) {
                                        if (DAT_TerrainDefinedData::instance.edgeMaskGfxOffsetsA[index].unk1
                                            == this->neighbourMask) {
                                            this->GfxLayer[this->curTileIndex]
                                                = GMFirstPictureIndex::instance[55] + localGfxBaseATmp
                                                + (luminescence - 2) * gfxStrideCur - 1
                                                + (this->RandomLayer[this->curTileIndex] & 1)
                                                + DAT_TerrainDefinedData::instance
                                                      .edgeMaskGfxOffsetsA[index].unk2;
                                        }
                                    }
                                    for (index = 4; index < 8; index++) {
                                        if (DAT_TerrainDefinedData::instance.edgeMaskGfxOffsetsA[index].unk1
                                            == this->neighbourMask) {
                                            this->GfxLayer[this->curTileIndex]
                                                = GMFirstPictureIndex::instance[55] + localBaseBTmp
                                                + (luminescence - 2) * gfxStrideCur - 1
                                                + DAT_TerrainDefinedData::instance
                                                      .edgeMaskGfxOffsetsA[index].unk2;
                                        }
                                    }
                                    if (this->GfxLayer[this->curTileIndex] == 0) {
                                        this->GfxLayer[this->curTileIndex]
                                            = GMFirstPictureIndex::instance[55] + gfxBaseC
                                            + (luminescence - 2) * gfxStrideCur - 1
                                            + (this->RandomLayer[this->curTileIndex] & 3);
                                    }
                                } else if (luminescence == 2) {
                                    if (this->neighbourMask != 0) {
                                        this->GfxLayer[this->curTileIndex]
                                            = GMFirstPictureIndex::instance[55] + gfxBaseC
                                            + (this->RandomLayer[this->curTileIndex] & 7) - 1;
                                    } else {
                                        this->GfxLayer[this->curTileIndex]
                                            = GMFirstPictureIndex::instance[55] + gfxBaseD
                                            + (this->RandomLayer[this->curTileIndex] & 7) - 1;
                                    }
                                } else if (curGfxMode == 2) {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + localGfxBaseATmp
                                        + (luminescence - 3) * gfxStrideCur - 1
                                        + (this->RandomLayer[this->curTileIndex] & 3);
                                } else if (this->neighbourMask != 0) {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + localGfxBaseATmp
                                        + (luminescence - 3) * gfxStrideCur - 1
                                        + (this->RandomLayer[this->curTileIndex] & 1);
                                } else {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + localBaseBTmp
                                        + (luminescence - 3) * gfxStrideCur - 1
                                        + (this->RandomLayer[this->curTileIndex] & 1);
                                }
                            } else if (luminescence > 2) {
                                if (curGfxMode == 0) {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + localBaseBTmp
                                        + (luminescence - 3) * gfxStrideCur - 1
                                        + (this->RandomLayer[this->curTileIndex] & 1);
                                } else if (curGfxMode == 2) {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + localGfxBaseATmp
                                        + (luminescence - 3) * gfxStrideCur - 1
                                        + (this->RandomLayer[this->curTileIndex] & 3);
                                } else {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + gfxBaseD
                                        + (luminescence - 2) * gfxStrideCur - 1
                                        + (this->RandomLayer[this->curTileIndex] & 3);
                                }
                            } else if (curMacroLowValue == 2) {
                                if (curGfxMode == 0) {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + gfxBaseD
                                        + (this->RandomLayer[this->curTileIndex] & 7) - 1;
                                } else {
                                    this->GfxLayer[this->curTileIndex]
                                        = GMFirstPictureIndex::instance[55] + gfxBaseD
                                        + (this->RandomLayer[this->curTileIndex] & 3) - 1;
                                }
                            } else if (curMacroLowValue == 4) {
                                curMacroMidValue = DAT_TerrainDefinedData::instance
                                               .field2293_0x1a54[this->mapOrientation / 2][curMacroMidValue];
                                this->GfxLayer[this->curTileIndex] = GMFirstPictureIndex::instance[55]
                                    + curGfxBaseEValue + curMacroMidValue + macroHigh * 4 - 1;
                            } else if (curMacroLowValue == 8) {
                                curMacroMidValue = DAT_TerrainDefinedData::instance
                                               .field2294_0x1b54[this->mapOrientation / 2][curMacroMidValue];
                                this->GfxLayer[this->curTileIndex] = macroHigh * 9
                                    + (GMFirstPictureIndex::instance[55] + curGfxBaseEValue + curMacroMidValue) + 0xf;
                            } else if (curMacroLowValue == 0x10) {
                                curMacroMidValue = DAT_TerrainDefinedData::instance
                                               .field2295_0x1c54[this->mapOrientation / 2][curMacroMidValue];
                                this->GfxLayer[this->curTileIndex] = macroHigh * 16
                                    + (GMFirstPictureIndex::instance[55] + curGfxBaseEValue + curMacroMidValue) + 0x33;
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
