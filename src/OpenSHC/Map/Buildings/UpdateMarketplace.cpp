#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // animFadeAlpha compares are signed 16-bit (jge 0x415D4E, jle 0x415DDC, jg 0x415DFC, jl 0x415E11). The market
    // frame table is signed (jg 0x415DAD); a wrap also forces animationFrame = 1 (0x415DC3).
    // FUNCTION: STRONGHOLDCRUSADER 0x00415C90
    void Buildings::UpdateMarketplace()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        bool isSkirmish = DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        if (isSkirmish) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
        } else {
            if (DAT_GameState::instance.mapAndTime.traderState == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
                if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive != 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                    DAT_BuildingsState::instance.buildings[buildingID].workCycleCount = 0;
                }
                goto updateVisual;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 1;
            }
            short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
            if (fade == 0 || fade >= 0x20) {
                goto updateVisual;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
    updateVisual:
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        int frame = (char)DAT_BuildingDefinedData::instance
                        .AnimMarketPlace[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
        if (frame <= 0) {
            short* indexPtr = &DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            *indexPtr = 0;
            DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
            DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 0;
        }
        short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
        if (fade > 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].workCycleCount == 0) {
                fade += -1;
            } else {
                fade += 1;
            }
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = fade;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha >= 0x20) {
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x20;
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
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
