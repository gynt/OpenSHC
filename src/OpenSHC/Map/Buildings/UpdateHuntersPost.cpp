#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // dogRespawnCooldown > 0 is a signed word compare (jle 0x423416). The dog spawns only when numberOfAnimals == 0,
    // the hunter in slot 0 is valid and the cooldown is 0 (0x423444..0x423460); entry X/Y must be nonzero.
    // Animation: state 0 fades from (0x10 - animationIndex) * 2 and advances when that is <= 0 (signed word, jg
    // 0x4235F7) or the frame table ends; states 1..6 (signed jl/jg 0x42360D/0x423617) butcher and add 1 meat when the
    // table ends; state 7 fades in animationIndex * 2 and advances at >= 0x20 (jl 0x423719) or table end. All frame
    // tables are signed bytes. The final fade clamp is 0..0x1F (0x4237AF..0x4237C3). ownerFlagFrames index is a signed
    // /2 (cdq; sub; sar at 0x42386F). The original keeps the no-op `if (workerID[1] == 0) workerID[1] = 0`
    // (0x423845..0x42384E).
    // FUNCTION: STRONGHOLDCRUSADER 0x00423370
    void Buildings::UpdateHuntersPost()
    {
        int finished = 0;
        int hunterPresent = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        int unitID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
        if (unitID != 0
            && DAT_UnitsState::instance.units[unitID].uid == DAT_BuildingsState::instance.buildings[buildingID].workerUID[0]) {
            hunterPresent = 1;
        }
        unitID = DAT_BuildingsState::instance.buildings[buildingID].workerID[1];
        if (unitID != 0
            && DAT_UnitsState::instance.units[unitID].uid == DAT_BuildingsState::instance.buildings[buildingID].workerUID[1]) {
            short unitType = DAT_UnitsState::instance.units[unitID].unitType;
            if (unitType == OpenSHC::Map::Units::UT_BURNINGMAN || unitType == OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG
                || unitType == OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL) {
                DAT_BuildingsState::instance.buildings[buildingID].dogRespawnCooldown = 400;
            }
        }
        short cooldown = DAT_BuildingsState::instance.buildings[buildingID].dogRespawnCooldown;
        if (cooldown > 0) {
            DAT_BuildingsState::instance.buildings[buildingID].dogRespawnCooldown = cooldown - 1;
        }
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals == 0 && hunterPresent != 0
            && DAT_BuildingsState::instance.buildings[buildingID].dogRespawnCooldown == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                DAT_BuildingsState::ptr)(buildingID, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCampgroundArea,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 2, FALSE);
            buildingID = DAT_CurrentBuildingID::instance;
            short entryX = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
            if (entryX != 0) {
                short entryY = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                if (entryY != 0) {
                    int dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].owner, 0, entryX * 8, entryY * 8,
                        DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
                        OpenSHC::Map::Units::UT_HUNTERDOG);
                    buildingID = DAT_CurrentBuildingID::instance;
                    if (dogID != 0) {
                        DAT_UnitsState::instance.units[dogID].targetX_2
                            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                        DAT_UnitsState::instance.units[dogID].targetY_2
                            = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCampgroundArea,
                            DAT_BuildingsState::ptr)(buildingID, 1, FALSE);
                        buildingID = DAT_CurrentBuildingID::instance;
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingOrTraderUID
                            = DAT_BuildingsState::instance.buildings[buildingID].uid;
                        int dogUID = DAT_UnitsState::instance.units[dogID].uid;
                        DAT_BuildingsState::instance.buildings[buildingID].workerID[1] = (short)dogID;
                        DAT_UnitsState::instance.units[dogID].workplaceOrHomeBuildingID = (short)buildingID;
                        DAT_UnitsState::instance.units[dogID].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[dogID].substate = -1;
                        DAT_UnitsState::instance.units[dogID].facingDirection = 4;
                        DAT_UnitsState::instance.units[dogID].fadeLevel = 0x20;
                        DAT_BuildingsState::instance.buildings[buildingID].workerUID[1] = dogUID;
                        DAT_UnitsState::instance.units[dogID].workerIndex = 1;
                        DAT_UnitsState::instance.units[dogID].buildingID = (short)buildingID;
                    }
                }
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].renderAnimation != 0) {
            short state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                char frame = DAT_BuildingDefinedData::instance
                                 .hunterPostPhase0Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame <= 0) {
                    finished = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                }
                short alpha = (short)((0x10 - DAT_BuildingsState::instance.buildings[buildingID].animationIndex) * 2);
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = alpha;
                if (alpha <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    finished = 1;
                }
            } else if (state >= 1 && state <= 6) {
                short index = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if ((char)DAT_BuildingDefinedData::instance.hunterPostButcherFrames[index] <= 0) {
                    finished = 1;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid,
                        OpenSHC::Game::Resources::RT_MEAT, 1, 6, 1);
                    buildingID = DAT_CurrentBuildingID::instance;
                } else {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0 && index == 4) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_HUNTER_CUT);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .hunterPostButcherFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                }
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            } else if (state == 7) {
                char frame = DAT_BuildingDefinedData::instance
                                 .hunterPostPhase7Frames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame <= 0) {
                    finished = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                }
                short alpha = (short)(DAT_BuildingsState::instance.buildings[buildingID].animationIndex * 2);
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = alpha;
                if (alpha >= 0x20) {
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x20;
                    finished = 1;
                }
            }
            if (finished != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                state = DAT_BuildingsState::instance.buildings[buildingID].state;
                if (state == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 1;
                } else if (state == 1) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 2;
                } else if (state == 2) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 3;
                } else if (state == 3) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 4;
                } else if (state == 4) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 5;
                } else if (state == 5) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 6;
                } else if (state == 6) {
                    DAT_BuildingsState::instance.buildings[buildingID].state = 7;
                } else if (state == 7) {
                    DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                    DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].state = 0;
                }
            }
        }
        short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
        if (fade > 0x1f) {
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
        } else if (fade < 0) {
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
        }
        int meat = DAT_BuildingsState::instance.buildings[buildingID].resources[OpenSHC::Game::Resources::RT_MEAT];
        if (meat == 1) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x14;
        } else if (meat == 2) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x15;
        } else if (meat == 3) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x16;
        } else if (meat == 4) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x17;
        } else if (meat == 5) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x18;
        } else if (meat == 6) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0x19;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals = 0;
        if (DAT_BuildingsState::instance.buildings[buildingID].workerID[1] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].workerID[1] = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
        if ((char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
            <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
            .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
    }

}
}
