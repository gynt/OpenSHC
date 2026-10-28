#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace Map {

    // All level/phase/counter compares are signed shorts (orig cmp cx, imm with jl/jle/jge); frame tables are
    // read as signed chars (movsx byte, e.g. 0x4057F4) and the frame must be > 0 (test; jg 0x4058CC). The spread
    // height check is abs(tileHeight - neighbourTotalHeight) < 0x19 (cdq; xor; sub; cmp 0x19; jge 0x405790).
    // FUNCTION: STRONGHOLDCRUSADER 0x00405680
    void Entities::UpdateFireEntity()
    {
        short fireLevel = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel;
        if (fireLevel == 5) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 8;
        }
        else if (fireLevel == 4) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 9;
        }
        else if (fireLevel == 3) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0xc;
        }
        else if (fireLevel == 2) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0xe;
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0x10;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 0x76;

        int frame = 0;
        short animState = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState;
        if (animState < 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0x20;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState++;
            frame = 1;
        }
        else if (animState == 0) {
            fireLevel = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel;
            if (fireLevel >= 3) {
                if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 0x80) != 0) {
                    frame = (char)DAT_EntityDefinedData::instance.fireLargeStartFramesA
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
                else {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 0x90;
                    frame = (char)DAT_EntityDefinedData::instance.fireLargeStartFramesB
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
            }
            else {
                if (fireLevel == 2) {
                    frame = (char)DAT_EntityDefinedData::instance.fireLevel2Frames
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
                else {
                    frame = (char)DAT_EntityDefinedData::instance.fireLevel1Frames
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
            }
        }
        else if (animState == 1) {
            fireLevel = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel;
            if (fireLevel >= 3) {
                if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 0x80) != 0) {
                    frame = (char)DAT_EntityDefinedData::instance.fireLargeLoopFramesA
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
                else {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 0x90;
                    frame = (char)DAT_EntityDefinedData::instance.fireLargeLoopFramesB
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
            }
            else {
                if (fireLevel == 2) {
                    frame = (char)DAT_EntityDefinedData::instance.fireLevel2Frames
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
                else {
                    frame = (char)DAT_EntityDefinedData::instance.fireLevel1Frames
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
            }
        }
        else if (animState == 2) {
            fireLevel = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel;
            if (fireLevel >= 3) {
                if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 0x80) != 0) {
                    frame = (char)DAT_EntityDefinedData::instance.fireLargeEndFramesA
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
                else {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].gmID = 0x90;
                    frame = (char)DAT_EntityDefinedData::instance.fireLargeEndFramesB
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
            }
            else {
                if (fireLevel == 2) {
                    frame = (char)DAT_EntityDefinedData::instance.fireLevel2Frames
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
                else {
                    frame = (char)DAT_EntityDefinedData::instance.fireLevel1Frames
                        [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter];
                }
            }
        }

        if (frame <= 0) {
            // end of the animation cycle
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
            animState = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState;
            if (animState == 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState = 1;
            }
            else if (animState == 1) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown++;
                if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown
                        == 6)
                    && (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel > 2)) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel = 2;
                }
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown++;
                if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown
                    > 8) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState = 2;
                }
                short buildingID = DAT_TileMapState::instance
                                       .BuildingLayer[DAT_EntityState::instance
                                               .entityArray[DAT_CurrentEntityID::instance]
                                               .tile];
                if ((buildingID != 0)
                    && (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor,
                            DAT_BuildingsState::ptr)(buildingID)
                        != 0)) {
                    if (DAT_BuildingsState::instance
                            .buildings[DAT_TileMapState::instance.BuildingLayer
                                    [DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile]]
                            .fireDuration
                        != 0) {
                        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel < 3) {
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel = 3;
                        }
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState = 1;
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance]
                            .burnCyclesOrImpactCountdown
                            = 0;
                    }
                    else {
                        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState = 2;
                    }
                }
            }
            else if (animState == 2) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            }
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = frame;
        }

        // spread to the next neighbour once per cycle, on frame 1 of the start phase
        if ((DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animState == 0)
            && (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter == 1)) {
            short direction = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireSpreadDirIndex;
            int tile = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile;
            int tileHeight = DAT_TileMapState::instance.HeightLayer[tile];
            if ((direction < 4)
                && (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel > 1)) {
                if (direction == 0) {
                    if (abs((int)(tileHeight
                            - MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                DAT_TileMapState::ptr)(tile - 1)))
                        < 0x19) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX - 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                }
                else if (direction == 1) {
                    if (abs((int)(tileHeight
                            - MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                DAT_TileMapState::ptr)(tile + 1)))
                        < 0x19) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX + 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                }
                else if (direction == 2) {
                    if (abs((int)(tileHeight
                            - MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                DAT_TileMapState::ptr)(
                                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition
                                + DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_EntityState::instance
                                              .entityArray[DAT_CurrentEntityID::instance]
                                              .yPosition
                                          + 1]
                                      .addXgetTile)))
                        < 0x19) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY + 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                }
                else if (direction == 3) {
                    if (abs((int)(tileHeight
                            - MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                DAT_TileMapState::ptr)(
                                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition
                                + DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_EntityState::instance
                                              .entityArray[DAT_CurrentEntityID::instance]
                                              .yPosition
                                          - 1]
                                      .addXgetTile)))
                        < 0x19) {
                        MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile)(
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY - 8,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireLevel - 1,
                            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
                    }
                }
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireSpreadDirIndex++;
            }
        }

        int tile = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].tile;
        if ((DAT_TileMapState::instance.LogicLayer[tile] & 0xba7001b1) == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::processFireDamageToUnitsAtTile,
                DAT_EntityState::ptr)(tile, DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner,
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fireIntensity);
        }
    }

}
}
