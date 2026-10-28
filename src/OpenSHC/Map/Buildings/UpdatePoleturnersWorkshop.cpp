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

    // Spear: states 0..1 (end of state 1 completes a product), frames +0x5e. Pike: states 0..3 (end of state 3
    // completes a product), frames +0 / +0x3d. Other item types and states skip straight to the fade clamp
    // (jne 0x413cb2). Frame tables are signed bytes (cmp al, bl; jg). Visually active while the worker is in unit
    // state 6 or 5 (0x413CEB / 0x413CFA). showOverlays is written 1 before the GM_SOLITARY test and again after
    // it (0x413D61 / 0x413D69).
    // FUNCTION: STRONGHOLDCRUSADER 0x004138D0
    void Buildings::UpdatePoleturnersWorkshop()
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
            short itemType = DAT_BuildingsState::instance.buildings[buildingID].currentProducedItemType;
            if (itemType == OpenSHC::Game::Resources::RT_SPEAR) {
                short state = DAT_BuildingsState::instance.buildings[buildingID].state;
                if (state == 0) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                        short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                        if (animationIndex == 7 || animationIndex == 0x27 || animationIndex == 0x4a
                            || animationIndex == 0x6a || animationIndex == 0x8c || animationIndex == 0xaf) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                DAT_BuildingsState::instance.buildings[buildingID].x,
                                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_POLE_TURN);
                            buildingID = DAT_CurrentBuildingID::instance;
                        }
                    }
                    char frame;
                    int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        frame = DAT_BuildingDefinedData::instance.poleturnerSpearFramesSolitary[frameIndex];
                    } else {
                        frame = DAT_BuildingDefinedData::instance.poleturnerSpearFrames[frameIndex];
                    }
                    if (frame <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x5e;
                    }
                    short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                    } else if (animationIndex < 0x1e) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha -= 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    }
                } else if (state == 1) {
                    char frame = DAT_BuildingDefinedData::instance
                                     .poleturnerSpearPhase1Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x5e;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha
                        = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
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
            } else if (itemType == OpenSHC::Game::Resources::RT_PIKE) {
                short state = DAT_BuildingsState::instance.buildings[buildingID].state;
                if (state == 0) {
                    char frame = DAT_BuildingDefinedData::instance
                                     .poleturnerPikePhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                    }
                    short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                    } else if (animationIndex < 0x1e) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha -= 1;
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame == 0x3d) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha += 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    }
                } else if (state == 1 || state == 2) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                        short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                        if (animationIndex == 2 || animationIndex == 0x30) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                DAT_BuildingsState::instance.buildings[buildingID].x,
                                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_POLE_GRIND);
                            buildingID = DAT_CurrentBuildingID::instance;
                        }
                    }
                    char frame;
                    int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        frame = DAT_BuildingDefinedData::instance.poleturnerPikeGrindFramesSolitary[frameIndex];
                    } else {
                        frame = DAT_BuildingDefinedData::instance.poleturnerPikeGrindFrames[frameIndex];
                    }
                    if (frame <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x3d;
                    }
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex < 0x20) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha -= 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    }
                } else if (state == 3) {
                    char frame = DAT_BuildingDefinedData::instance
                                     .poleturnerPikePhase3Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha
                            = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x3d;
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha
                            = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    }
                } else {
                    goto clampFade;
                }
                if (cycleEnded != 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                    short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
                    if (phase == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 1;
                    } else if (phase == 1) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 2;
                    } else if (phase == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 3;
                    } else if (phase == 3) {
                        DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                        DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                        DAT_BuildingsState::instance.buildings[buildingID].state = 0;
                    }
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
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
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
