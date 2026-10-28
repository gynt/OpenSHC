#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // Only every other tick (tickDivider) does the logic run. The grind timer typeSpecificTimer slows the sail
    // and inactive-layer frame steps (every tick above 50, then every 2/4/8 ticks at <= 50/30/20; signed short
    // compares). overlayFrame1 is written twice, the second (sail-table) write wins.
    // FUNCTION: STRONGHOLDCRUSADER 0x00416F80
    void Buildings::UpdateMill()
    {
        int workerCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 1) {
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider == 1) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0) {
            workerCount = 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[1] != 0) {
            workerCount += 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[2] != 0) {
            workerCount += 1;
        }
        int millerID = DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId;
        if (millerID != 0) {
            if (DAT_UnitsState::instance.units[millerID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId = 0;
            }
            if (DAT_UnitsState::instance.units[millerID].unitType != OpenSHC::Map::Units::UT_MILLER) {
                DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId = 0;
            }
            if (DAT_UnitsState::instance.units[millerID].state.generic
                != OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId = 0;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 0;
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        }
        BOOLEnum savedFirstTick = DAT_BuildingsState::instance.isFirstTickInLoop;
        DAT_BuildingsState::instance.isFirstTickInLoop = (BOOLEnum)1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(buildingID);
        int visuallyActive = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        DAT_BuildingsState::instance.isFirstTickInLoop = savedFirstTick;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        if (workerCount > 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 0) {
                DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer -= 1;
                if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer <= 50) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 30) {
                        if ((DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer & 1) != 0) {
                            goto sailNoStep;
                        }
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 20) {
                        if ((DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer & 3) != 0) {
                            goto sailNoStep;
                        }
                    } else if ((DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer & 7) != 0) {
                        goto sailNoStep;
                    }
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
                sailNoStep:
                if ((char)DAT_BuildingDefinedData::instance
                        .millSailFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3
                    = (char)DAT_BuildingDefinedData::instance
                          .millSailFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 1;
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 1;
        }
        int inactiveWrapped = 0;
        if (workerCount > 0 && visuallyActive == 0
            && DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer != 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer <= 50) {
                if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 30) {
                    if ((DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer & 1) != 0) {
                        goto inactiveNoStep;
                    }
                } else if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 20) {
                    if ((DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer & 3) != 0) {
                        goto inactiveNoStep;
                    }
                } else if ((DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer & 7) != 0) {
                    goto inactiveNoStep;
                }
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            inactiveNoStep:
            if ((char)DAT_BuildingDefinedData::instance
                    .millInactiveLayerFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                inactiveWrapped = 1;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                = (char)DAT_BuildingDefinedData::instance
                      .millInactiveLayerFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                + 0xf;
            if (inactiveWrapped != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        }
        if (workerCount > 0 && visuallyActive != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .millActiveLayerFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                = (char)DAT_BuildingDefinedData::instance
                      .millActiveLayerFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                + 0x1e;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                = (char)DAT_BuildingDefinedData::instance
                      .millSailFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3]
                + 0x1e;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        }
        int millerWrapped = 0;
        if (workerCount > 0 && DAT_BuildingsState::instance.buildings[buildingID].occupyingWorkerId != 0) {
            short millerState = DAT_BuildingsState::instance.buildings[buildingID].subAnimState2;
            if (millerState == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0x2e;
                millerWrapped = 1;
            } else if (millerState == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .millerPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                    millerWrapped = 1;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2
                    = (char)DAT_BuildingDefinedData::instance
                          .millerPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2]
                    + 0x2d;
            } else if (millerState == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
                if ((char)DAT_BuildingDefinedData::instance
                        .millerPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                    millerWrapped = 1;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2
                    = (char)DAT_BuildingDefinedData::instance
                          .millerPhase2Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2]
                    + 0x3d;
            } else if (millerState == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0x2e;
                millerWrapped = 1;
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 0;
            }
        }
        if (millerWrapped != 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 1;
            } else if (DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 1
                || DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 2
                || DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].subAnimState2 = 3;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].showOverlays;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
    }

}
}
