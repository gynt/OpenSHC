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

    // Brewery: 8 phases in state (0..7); a non-positive (signed, test al, al; jle) table entry advances the phase,
    // the end of phase 7 counts a work cycle and restarts at phase 4 outside GM_SOLITARY, at 0 in it (neg/sbb/and 4
    // at 0x414FEF). Visually active while the worker is in unit state 6 or 5 (0x414BC9 / 0x414BDA); the value before
    // updateVisuallyActiveState is kept in a stack local (0x414C2C) and drives renderAnimation and overlay 0.
    // FUNCTION: STRONGHOLDCRUSADER 0x00414B60
    void Buildings::UpdateBrewery()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        short* productionPtr = &DAT_BuildingsState::instance.buildings[buildingID].isProductionWorkshop;
        *productionPtr = 1;
        {
            int workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
            if (workerID != 0) {
                OpenSHC::Map::Units::States::UnitStateShort workerState
                    = DAT_UnitsState::instance.units[workerID].state.generic;
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
        if (DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount == 0) {
            DAT_GameState::instance.playerDataArray[owner].someCount12 += 1;
        }
        int activeThisTick = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        DAT_GameState::instance.playerDataArray[owner].countBrewers += 1;
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
        if (activeThisTick == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 0;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
                = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
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
            char frame;
            short state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                    short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 5 || animationIndex == 0x34 || animationIndex == 100 || animationIndex == 0x96
                        || animationIndex == 200 || animationIndex == 0xfa || animationIndex == 300
                        || animationIndex == 0x15e || animationIndex == 400) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_STIR);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                }
                frame = DAT_BuildingDefinedData::instance
                            .breweryStirPhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                    goto overlays;
                }
            } else if (state == 1) {
                frame = DAT_BuildingDefinedData::instance
                            .breweryPhase135Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x10;
                    goto overlays;
                }
            } else if (state == 2) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_STIR);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                frame = DAT_BuildingDefinedData::instance
                            .breweryStirPhase24Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                    goto overlays;
                }
            } else if (state == 3) {
                frame = DAT_BuildingDefinedData::instance
                            .breweryPhase135Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x10;
                    goto overlays;
                }
            } else if (state == 4) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_STIR);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                frame = DAT_BuildingDefinedData::instance
                            .breweryStirPhase24Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                    goto overlays;
                }
            } else if (state == 5) {
                frame = DAT_BuildingDefinedData::instance
                            .breweryPhase135Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x10;
                    goto overlays;
                }
            } else if (state == 6) {
                frame = DAT_BuildingDefinedData::instance
                            .breweryPhase6Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x20;
                    goto overlays;
                }
            } else if (state == 7) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_STIR);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                frame = DAT_BuildingDefinedData::instance
                            .breweryStirPhase7Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame > 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                    goto overlays;
                }
            } else {
                goto overlays;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
        {
            short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (phase == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 1;
            } else if (phase == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 2;
            } else if (phase == 2) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 3;
            } else if (phase == 3) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 4;
            } else if (phase == 4) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 5;
            } else if (phase == 5) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 6;
            } else if (phase == 6) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 7;
            } else if (phase == 7) {
                DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[buildingID].state
                    = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY ? 4 : 0;
            }
        }
    overlays:
        if (activeThisTick == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        } else {
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            }
            if ((char)DAT_BuildingDefinedData::instance
                    .breweryOverlayFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0
                = (char)DAT_BuildingDefinedData::instance
                      .breweryOverlayFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                + 0x30;
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
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
    }

}
}
