#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // The building is always addressed through DAT_CurrentBuildingID (re-read after every call, e.g. 0x416143,
    // 0x416180, 0x4162C6). Frame tables are signed (movsx; cmp eax, 0; jg). State 8 stores its frame without +0x20
    // and then shares the fade-in step of state 5 (jg 0x416072 / jmp 0x416078). Overlay 0 picks the full or empty
    // fire table by resources[7] >= 1 (jl 0x416275); the pot overlay is chosen by the pot count (signed jg chain).
    // FUNCTION: STRONGHOLDCRUSADER 0x00415E80
    void Buildings::UpdateOilSmelter()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int frame;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleJustEnded = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentEmployeeCount = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tickDivider > 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tickDivider = 0;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
        short state = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state;
        if (state == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
        } else if (state == 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
        } else if (state == 2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x5c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha = 0x1f;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
        } else if (state == 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x5c;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPhase3Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 0x20;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha - 1;
            }
        } else if (state == 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x5c;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPhase4Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 0x20;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0x1c && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].subAnimState1 = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] += 1;
            }
        } else if (state == 5) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x10;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x5c;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPhase5Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame + 0x20;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha < 0x1f) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha + 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            }
        } else if (state == 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x48;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x54;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPhase6Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 7;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha - 1;
            }
        } else if (state == 7) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0 && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 10) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, OpenSHC::DE::SHCDE::FX_POT_OPEN);
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0 && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 0xd) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, OpenSHC::DE::SHCDE::FX_OIL_REFILL);
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x48;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x54;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPhase7Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 8;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] -= 1;
                int engineerID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oilWaitingEngineerID;
                if (engineerID != 0 && DAT_UnitsState::instance.units[engineerID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[engineerID].state.generic == OpenSHC::Map::Units::States::US_STATE_9Unk) {
                    DAT_UnitsState::instance.units[engineerID].resourceToDeposit = 1;
                }
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
        } else if (state == 8) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -0x48;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -0x54;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPhase8Frames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha < 0x1f) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animFadeAlpha + 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
            }
        }
        {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] >= 1) {
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterFireFullFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0];
            } else {
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterFireEmptyFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0];
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 += 1;
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex0 = 0;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame0 = frame + 0x3d;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].subAnimState1 == 1) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, OpenSHC::DE::SHCDE::FX_POT_FLARE_UP);
            }
            int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
            frame = (char)DAT_BuildingDefinedData::instance.oilSmelterFlareUpFrames[index];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].subAnimState1 = 0;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x7a;
            }
        } else {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 1) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x4d;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 2) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x52;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 3) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x57;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 4) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x5c;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 5) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x61;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 6) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x66;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 7) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x6b;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].resources[7] <= 8) {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x70;
                }
            } else {
                int index = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1;
                frame = (char)DAT_BuildingDefinedData::instance.oilSmelterPotFrames[index];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = index + 1;
                if (frame <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayAnimIndex1 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame1 = frame + 0x75;
                }
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState == -1) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].showOverlays;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance.ownerFlagFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame13 / 2] <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame14 = (char)DAT_BuildingDefinedData::instance.ownerFlagFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame13 / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayFrame14 = 0;
    }

}
}