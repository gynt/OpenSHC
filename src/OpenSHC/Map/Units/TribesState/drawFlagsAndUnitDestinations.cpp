#include "../TribesState.func.hpp"

#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // cursorAnimTick / floatAnimFrame are declared undefined4 but used signed (cdq; idiv at 0x523AB5, jl at
        // 0x523BCF / 0x523C50). The instruction-type dispatch is an if-chain in the order 5, 0x16, 7, 6, 4, 9, 0x22
        // (0x523C78..0x523D62).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523A30
        void TribesState::drawFlagsAndUnitDestinations(int tribeID)
        {
            short const rallyMode = this->tribes[tribeID].rallyMode;
            if (rallyMode != 0 && this->tribes[tribeID].owner == (int)DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                int rallyIndex = 0;
                if (rallyMode < 0) {
                    rallyIndex = 1;
                }
                if (rallyIndex < this->tribes[tribeID].rallyPointCount) {
                    short* rallyPoint = this->tribes[tribeID].rallyPointArray[rallyIndex];
                    do {
                        int const y = rallyPoint[1];
                        int const x = rallyPoint[0];
                        int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            (x + (int)DAT_TileMapState::instance.cursorAnimTick + rallyIndex + y) % 10 + 0x61, 0x12, -1,
                            tile, 0xa0022);
                        ++rallyIndex;
                        rallyPoint += 2;
                    } while (rallyIndex < this->tribes[tribeID].rallyPointCount);
                }
            }
            for (int iterationStep = 0; iterationStep < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getSpecificUnitFromTribe, this)(tribeID, iterationStep);
                ++iterationStep;
                if (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                    || DAT_UnitsState::instance.units[unitID].dying != 0
                    || DAT_UnitsState::instance.units[unitID].isHiddenInBuilding != 0
                    || DAT_UnitsState::instance.units[unitID].owner
                        != (int)DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    continue;
                }
                short const markerTimer = DAT_UnitsState::instance.units[unitID].destinationMarkerTimer;
                if (markerTimer != 0) {
                    int alpha;
                    if (markerTimer >= 8) {
                        alpha = 0;
                    } else {
                        alpha = (8 - markerTimer) * 4;
                    }
                    int const tile = DAT_UnitsState::instance.units[unitID].plannedDestinationX
                        + DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_UnitsState::instance.units[unitID].plannedDestinationY]
                              .addXgetTile;
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(
                        OpenSHC::IO::Graphics::GID_CURSORS, 0x6a - markerTimer, 10, 6, tile, alpha << 16 | 2);
                    int frame = (int)DAT_TileMapState::instance.floatAnimFrame - 1;
                    if (frame >= 8) {
                        frame = 15 - frame;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_CURSORS, frame + 0x52, 0xc, 6, tile,
                        DAT_UnitsState::instance.units[unitID].destinationMarkerTimer << 17 | 2);
                } else if (DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan
                        < DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan
                    && DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep != UIT_UNIT_ATTACK_UNIT
                    && DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep != UIT_ATTACK_LAND
                    && DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep != UIT_MAN_SIEGE_EQUIPMENT) {
                    int const tile = DAT_UnitsState::instance.units[unitID].plannedDestinationX
                        + DAT_ViewportRenderState::instance
                              .translationMatrix[DAT_UnitsState::instance.units[unitID].plannedDestinationY]
                              .addXgetTile;
                    int frame = (int)DAT_TileMapState::instance.floatAnimFrame - 1;
                    if (frame >= 8) {
                        frame = 15 - frame;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(OpenSHC::IO::Graphics::GID_CURSORS, frame + 0x52, 0xc, 6, tile, 2);
                }
                UnitInstructionTypeShort const targetingType
                    = DAT_UnitsState::instance.units[unitID].targetingType_OR_performanceStep;
                if (targetingType == UIT_ATTACK_LAND || targetingType == UIT_THROW_COW) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::spawnFloatingNumberAroundTile,
                        DAT_TileMapState::ptr)(DAT_UnitsState::instance.units[unitID].attackAtTileX,
                        DAT_UnitsState::instance.units[unitID].attackAtTileY,
                        DAT_UnitsState::instance.units[unitID].unkAttackRelated);
                } else if (targetingType == UIT_FILL_MOAT) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingTextElement,
                        DAT_ViewportRenderState::ptr)(0x4e, 6, -0x20,
                        DAT_UnitsState::instance.units[unitID].targetX
                            + DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_UnitsState::instance.units[unitID].targetY]
                                  .addXgetTile,
                        2);
                } else if (targetingType == UIT_DIG_MOAT) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::createFloatingTextElement,
                        DAT_ViewportRenderState::ptr)(0x4e, 6, -0x20,
                        DAT_UnitsState::instance.units[unitID].targetX
                            + DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_UnitsState::instance.units[unitID].targetY]
                                  .addXgetTile,
                        2);
                } else if (targetingType == UIT_UNIT_ATTACK_UNIT) {
                    int const targetUnitID = DAT_UnitsState::instance.units[unitID].targetUnitId;
                    if (DAT_UnitsState::instance.units[targetUnitID].uid
                            == DAT_UnitsState::instance.units[unitID]
                                   .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                        && DAT_UnitsState::instance.units[targetUnitID].logicalState == ULS_NORMAL) {
                        DAT_UnitsState::instance.units[targetUnitID].overheadMarkerType = 1;
                    }
                } else if (targetingType == UIT_ATTACK_BUILDING) {
                    short const buildingID = DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID;
                    if (buildingID != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].uid
                            == DAT_UnitsState::instance.units[unitID]
                                   .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                        DAT_BuildingsState::instance.buildings[buildingID].floatMarkerMode = 1;
                    }
                } else if (targetingType == UIT_LIGHT_PITCH) {
                    short const pitchDitchID = DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID;
                    if (pitchDitchID != 0
                        && DAT_TileMapState::instance.pitchDitches[pitchDitchID].uid
                            == DAT_UnitsState::instance.units[unitID]
                                   .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                        DAT_TileMapState::instance.MiscDisplayLayer[DAT_TileMapState::instance.pitchDitches[pitchDitchID].tile]
                            |= 0x4000;
                    }
                } else {
                    uint const tile = DAT_UnitsState::instance.units[unitID].targetedBuildingTile;
                    if (tile != 0 && DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                        DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.BuildingLayer[tile]]
                            .floatMarkerMode
                            = 1;
                    }
                }
            }
        }

    }
}
}
