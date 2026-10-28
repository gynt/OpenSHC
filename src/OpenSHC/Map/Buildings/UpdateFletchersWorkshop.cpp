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

    // The "cycle ended" flag starts at 0 (xor ebp, ebp at 0x412D70); states other than 0/1 skip the end-of-cycle
    // handling (jne 0x412fc8). Frame tables are signed bytes (cmp al, bl; jg). Non-GM_SOLITARY bow/crossbow
    // state 1 has no table and ends the cycle immediately (0x412EBE / 0x412F5C). Visually active while the
    // worker is in unit state 5 or 4 (0x413001 / 0x413010).
    // FUNCTION: STRONGHOLDCRUSADER 0x00412D50
    void Buildings::UpdateFletchersWorkshop()
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
        DAT_GameState::instance.playerDataArray[owner].countFletchersPoleturners += 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = firstWorker != 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
        if (((DAT_BuildingsState::instance.buildings[buildingID].uid + DAT_GameCore::instance.mapTimeInTicks) & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeWallFacingRotationAt, DAT_TileMapState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        short state = DAT_BuildingsState::instance.buildings[buildingID].state;
        if (DAT_BuildingsState::instance.buildings[buildingID].currentProducedItemType
            == OpenSHC::Game::Resources::RT_BOW) {
            if (state == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                    short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 8 || animationIndex == 0x3a) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_FLETCH_LONG);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                }
                char frame;
                int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    frame = DAT_BuildingDefinedData::instance.FletcherWorkshopAnimationCycle[frameIndex];
                } else {
                    frame = DAT_BuildingDefinedData::instance.fletcherBowFramesSolitary[frameIndex];
                }
                if (frame <= 0) {
                    cycleEnded = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                }
            } else if (state == 1) {
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    cycleEnded = 1;
                } else {
                    char frame = DAT_BuildingDefinedData::instance.fletcherBowPhase1FramesSolitary
                                     [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                    }
                }
                goto phase1Fade;
            } else {
                goto clampFade;
            }
        } else {
            if (state == 0) {
                char frame;
                int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    frame = DAT_BuildingDefinedData::instance.fletcherCrossbowFrames[frameIndex];
                } else {
                    frame = DAT_BuildingDefinedData::instance.fletcherCrossbowFramesSolitary[frameIndex];
                }
                if (frame <= 0) {
                    cycleEnded = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x24;
                }
            } else if (state == 1) {
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    cycleEnded = 1;
                } else {
                    char frame = DAT_BuildingDefinedData::instance.fletcherCrossbowPhase1FramesSolitary
                                     [DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x24;
                    }
                }
                goto phase1Fade;
            } else {
                goto clampFade;
            }
        }
        {
            short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
            if (animationIndex == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
            } else if (animationIndex < 0x1e) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha -= 1;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            }
            goto checkEnded;
        }
    phase1Fade:
        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha
            = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
    checkEnded:
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
        {
            int workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
            if (workerID != 0) {
                OpenSHC::Map::Units::States::UnitStateShort workerState = DAT_UnitsState::instance.units[workerID].state.generic;
                if (workerState == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    goto visualDone;
                }
                if (workerState == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
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
                DAT_CurrentBuildingID::instance);
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
