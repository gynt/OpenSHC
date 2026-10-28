#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // Armorer: state 0 then state 1 (end of state 1 completes a product). FX_ARMOUR_HIT tests the GM_SOLITARY table
    // in all modes (cmp byte [eax+0x5bc280], 5 at 0x413EA6). State 0 fade only steps down while > 0 (jle 0x413f63),
    // state 1 sets fade = 2 * animationIndex (add ax, ax). showOverlays is cleared after the clamp (0x413FB5);
    // visually active for worker unit states 6, 5 and 0x6D. updateBuildingGraphicsLayer gets the cached id (push ebx).
    // FUNCTION: STRONGHOLDCRUSADER 0x00413DC0
    void Buildings::UpdateArmorersWorkshop()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int cycleEnded = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].isProductionWorkshop = 1;
        short firstWorker = DAT_BuildingsState::instance.buildings[buildingID].workers[0];
        DAT_GameState::instance.playerDataArray[owner].countArmorersAndBlacksmiths += 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = firstWorker != 0;
        if (((DAT_BuildingsState::instance.buildings[buildingID].uid + DAT_GameCore::instance.mapTimeInTicks) & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeWallFacingRotationAt, DAT_TileMapState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        {
            short state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && DAT_BuildingDefinedData::instance
                            .armorerFramesSolitary[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        == 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_ARMOUR_HIT);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                char frame;
                int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    frame = DAT_BuildingDefinedData::instance.armorerFramesSolitary[frameIndex];
                } else {
                    frame = DAT_BuildingDefinedData::instance.armorerFrames[frameIndex];
                }
                if (frame <= 0) {
                    cycleEnded = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                } else {
                    short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
                    if (fade > 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = fade - 1;
                    }
                }
            } else if (state == 1) {
                char frame = DAT_BuildingDefinedData::instance
                                 .armorerPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame <= 0) {
                    cycleEnded = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha
                    = DAT_BuildingsState::instance.buildings[buildingID].animationIndex * 2;
            } else {
                goto clampFade;
            }
            if (cycleEnded != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                if (DAT_BuildingsState::instance.buildings[buildingID].state == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                    DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].state = 0;
                }
            }
        }
    clampFade:
        {
            short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
            if (fade > 0x1f) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
            } else if (fade < 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        {
            int workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
            if (workerID != 0) {
                OpenSHC::Map::Units::States::UnitStateShort workerState = DAT_UnitsState::instance.units[workerID].state.generic;
                if (workerState == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    goto visualDone;
                }
                if (workerState == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    goto visualDone;
                }
                if (workerState == OpenSHC::Map::Units::States::US_FADE_TRANSITION) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    goto visualDone;
                }
            }
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        }
    visualDone:
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
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
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
