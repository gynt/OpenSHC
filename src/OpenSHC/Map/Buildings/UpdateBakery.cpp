#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
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

    // Bakery: state 0 (baking, FX_BAKE2 / FX_BAKE on fixed animation indices) then state 1 (end of batch). Frame tables
    // are signed (test al, al; jg at 0x4148E5 / 0x41493C); states other than 0/1 skip to the fade clamp (jne
    // 0x414995). Visually active while the worker is in unit state 4 or 3 (0x4149D0 / 0x4149DF). The overlay frame
    // for the bread pile depends on the animation index (signed compares, setge at 0x414AA2). The owner flag frame is
    // stored once after the mode test (ecx = 0 default, 0x414B4E).
    // FUNCTION: STRONGHOLDCRUSADER 0x00414720
    void Buildings::UpdateBakery()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int cycleEnded = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        short* productionPtr = &DAT_BuildingsState::instance.buildings[buildingID].isProductionWorkshop;
        *productionPtr = 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        if (((DAT_BuildingsState::instance.buildings[buildingID].uid + DAT_GameCore::instance.mapTimeInTicks) & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeWallFacingRotationAt, DAT_TileMapState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount == 0) {
            DAT_GameState::instance.playerDataArray[owner].someCount13 += 1;
        }
        DAT_GameState::instance.playerDataArray[owner].countBakers += 1;
        short state = DAT_BuildingsState::instance.buildings[buildingID].state;
        if (state == 0) {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (animationIndex == 0x15 || animationIndex == 0x62 || animationIndex == 0x73 || animationIndex == 0xc0
                    || animationIndex == 0xd1 || animationIndex == 0x11e || animationIndex == 0x12f
                    || animationIndex == 0x17c) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BAKE2);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (animationIndex == 0x23 || animationIndex == 0x81 || animationIndex == 0xdf
                    || animationIndex == 0x13d) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BAKE);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
            }
            char frame = DAT_BuildingDefinedData::instance
                             .bakeryPhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (frame <= 0) {
                cycleEnded = 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
            }
            short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
            } else if (animationIndex < 0xf) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha -= 2;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            }
        } else if (state == 1) {
            char frame = DAT_BuildingDefinedData::instance
                             .bakeryPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
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
            short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (phase == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 1;
            } else if (phase == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[buildingID].state = 0;
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
        int workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
        if (workerID != 0) {
            OpenSHC::Map::Units::States::UnitStateShort workerState = DAT_UnitsState::instance.units[workerID].state.generic;
            if (workerState == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                goto visualDone;
            }
            if (workerState == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                goto visualDone;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
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
        int flagFrame = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        if (workerID == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].state == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x44;
        } else {
            short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (animationIndex < 100) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
            } else if (animationIndex < 0xc2) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x41;
            } else if (animationIndex < 0x120) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x42;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = (animationIndex >= 0x17e) + 0x43;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 3) {
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workerID[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        } else {
            if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            }
            if ((char)DAT_BuildingDefinedData::instance
                    .chimneySmokeFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1
                = (char)DAT_BuildingDefinedData::instance
                      .chimneySmokeFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                + 0x10;
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
            flagFrame = (char)DAT_BuildingDefinedData::instance
                            .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = flagFrame;
    }

}
}
