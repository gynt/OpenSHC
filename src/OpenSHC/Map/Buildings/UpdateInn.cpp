#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
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

    // The inn's ale-serving counter is the signed word at Building+0x2B2 (declared as undefined1 field_0x2b2[2]):
    // movsx + cmp with aleRate, jl at 0x41599C. flagonsOfAleOrCheeseOrReleaseDogs is compared signed (jle 0x415975 /
    // 0x4159B4). The overlay tables are 0-terminated (cmp eax, 0; jne) and restart at entry 0; overlay 1 restarts
    // from the idle table even while the drunkard timer runs (0x415845). updateBuildingGraphicsLayer gets a fresh
    // DAT_CurrentBuildingID (0x4159F5).
    // FUNCTION: STRONGHOLDCRUSADER 0x004156F0
    void Buildings::UpdateInn()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        int innkeeperID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
        if (innkeeperID == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs == 0
                   && DAT_BuildingsState::instance.buildings[buildingID].drunkardSpawnCountdown == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        }
        int activeThisTick = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (activeThisTick != 0) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].showOverlays;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
            int frame = (char)DAT_BuildingDefinedData::instance.innOverlay0Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = frame;
            if (frame == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = (char)DAT_BuildingDefinedData::instance.innOverlay0Frames[0];
            } else if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                int* index0Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0;
                *index0Ptr += 1;
            }
            int* frame0Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0;
            *frame0Ptr = 0;
            if (DAT_BuildingsState::instance.buildings[buildingID].drunkardSpawnCountdown != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = (char)DAT_BuildingDefinedData::instance.innBusyOverlayFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = (char)DAT_BuildingDefinedData::instance.innIdleOverlayFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1];
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = (char)DAT_BuildingDefinedData::instance.innIdleOverlayFrames[0];
            } else if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                int* index1Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1;
                *index1Ptr += 1;
            }
            if (DAT_UnitsState::instance.units[innkeeperID].state.generic
                == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                frame = (char)DAT_BuildingDefinedData::instance.innkeeperServeFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = frame;
                if (frame == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = (char)DAT_BuildingDefinedData::instance.innkeeperServeFrames[0];
                } else if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                    int* index2Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2;
                    *index2Ptr += 1;
                }
            }
            short countdown = DAT_BuildingsState::instance.buildings[buildingID].drunkardSpawnCountdown;
            if (countdown != 0) {
                countdown = countdown - 1;
                DAT_BuildingsState::instance.buildings[buildingID].drunkardSpawnCountdown = countdown;
                if (countdown == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnDrunkard, DAT_GameState::ptr)(
                        DAT_CurrentBuildingID::instance);
                }
                buildingID = DAT_CurrentBuildingID::instance;
                frame = (char)DAT_BuildingDefinedData::instance.innOverlay3Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3];
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = frame;
                if (frame == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = (char)DAT_BuildingDefinedData::instance.innOverlay3Frames[0];
                } else if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                    int* index3Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3;
                    *index3Ptr += 1;
                }
            }
        } else {
            int* hideOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].showOverlays;
            *hideOverlaysPtr = 0;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs > 0) {
            if (innkeeperID != 0) {
                short* serveCounterPtr = (short*)DAT_BuildingsState::instance.buildings[buildingID].field_0x2b2;
                *serveCounterPtr += 1;
                if (*serveCounterPtr >= DAT_GameState::instance.playerDataArray[owner].aleRate) {
                    *serveCounterPtr = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs -= 1;
                }
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs > 0
                && DAT_BuildingsState::instance.buildings[buildingID].workerID[0] != 0) {
                DAT_GameState::instance.playerDataArray[owner].workingInnsCount += 1;
            }
        }
        short visual = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        DAT_GameState::instance.playerDataArray[owner].countInns += 1;
        if (visual != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
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
