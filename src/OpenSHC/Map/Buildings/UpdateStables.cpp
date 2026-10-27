#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // numberOfAnimals / horsesInUseOrOutpostArcherCap are compared as signed bytes; the breeding timer as a
    // signed short (> 550). The horse layers are only refreshed when tickDivider wraps to 0 (every 6th tick).
    // FUNCTION: STRONGHOLDCRUSADER 0x004174E0
    void Buildings::UpdateStables()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits,
            DAT_BuildingsState::ptr)(buildingID);
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < 4) {
            DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer += 1;
            if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 0x226) {
                DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals += 1;
                DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recountStablesAndHorses,
                    DAT_GameState::ptr)();
                buildingID = DAT_CurrentBuildingID::instance;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 5) {
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider >= 1) {
            return;
        }
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals > 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap > 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x2a;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
                if ((char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0] <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                    = (char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        }
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals > 1) {
            if (DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap > 1) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0x29;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
                if ((char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1] <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                    = (char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        }
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals > 2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap > 2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0x28;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
                if ((char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2] <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2
                    = (char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
        }
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals > 3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].horsesInUseOrOutpostArcherCap > 3) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0x27;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
                if ((char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3] <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3
                    = (char)DAT_BuildingDefinedData::instance.stablesHorseIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
            }
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
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
