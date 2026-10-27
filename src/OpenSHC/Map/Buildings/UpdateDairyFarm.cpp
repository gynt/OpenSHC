#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
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
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // dairyState runs as an if-chain (cmp al, 0..6). In state 0 a missing or stale cow in the chosen milking slot
    // returns at once (je/jne 0x416F69, no graphics refresh, no flag update). The cow-slot scan reuses its index
    // after the loop: on a stale slot it clears workerID[slot] and takes slot - 1 (lea edi, [eax - 1] at 0x416BF4);
    // a completed scan keeps slot 0 (xor edi, edi at 0x416B9A). In state 4 the "bucket empty" branch jumps past the
    // milking sound to the FX_MILK_POUR check (jl 0x416E8E). Timers/fade compare signed (jle/jg/jl on ax).
    // FUNCTION: STRONGHOLDCRUSADER 0x004167E0
    void Buildings::UpdateDairyFarm()
    {
        int buildingID = DAT_CurrentBuildingID::instance;
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].countFarms += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_GameState::instance.playerDataArray[owner].farmsWithoutWorkers += 1;
        }
        if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals > 0) {
            DAT_GameState::instance.playerDataArray[owner].aiEconomyTickCounter = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        buildingID = DAT_CurrentBuildingID::instance;
        short* renderPtr = &DAT_BuildingsState::instance.buildings[buildingID].renderAnimation;
        *renderPtr = 0;
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        int* tickPtr = &DAT_BuildingsState::instance.buildings[buildingID].tickDivider;
        *tickPtr += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 1) {
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 += 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 += 1;
        }
        short cooldown = DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs;
        if (cooldown != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs = cooldown - 1;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = 0;
            DAT_BuildingsState::instance.buildings[buildingID].dairyState = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0;
        } else if (DAT_BuildingsState::instance.buildings[buildingID].dairyState == 0) {
            if ((char)DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals < 3 && DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer += 1;
                if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 400) {
                    DAT_BuildingsState::instance.buildings[buildingID].dairyState = 1;
                    DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x20;
                }
            } else if (DAT_BuildingsState::instance.buildings[buildingID].resources[11] == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer += 1;
                if (DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer > 400) {
                    DAT_BuildingsState::instance.buildings[buildingID].dairyMilkCowSlot += 1;
                    if ((char)DAT_BuildingsState::instance.buildings[buildingID].dairyMilkCowSlot > 3) {
                        DAT_BuildingsState::instance.buildings[buildingID].dairyMilkCowSlot = 1;
                    }
                    int milkSlot = (char)DAT_BuildingsState::instance.buildings[buildingID].dairyMilkCowSlot;
                    int cowID = DAT_BuildingsState::instance.buildings[buildingID].workerID[milkSlot];
                    if (cowID == 0) {
                        return;
                    }
                    if (DAT_UnitsState::instance.units[cowID].uid != DAT_BuildingsState::instance.buildings[buildingID].workerUID[milkSlot]) {
                        return;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].typeSpecificTimer = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].dairyState = 3;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x20;
                    DAT_UnitsState::instance.units[cowID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                    DAT_UnitsState::instance.units[cowID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[cowID].fadeAlphaStep = 1;
                }
            }
        } else {
            goto otherStates;
        }
    refreshArea:
        if (DAT_BuildingsState::instance.areaGfxRefreshTicks != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateBuildingAreaTileGraphics,
                DAT_BuildingsState::ptr)(buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
        }
        DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals = 0;
        {
            int cowID = DAT_BuildingsState::instance.buildings[buildingID].workerID[1];
            if (cowID == 0 || DAT_UnitsState::instance.units[cowID].uid != DAT_BuildingsState::instance.buildings[buildingID].workerUID[1]) {
                DAT_BuildingsState::instance.buildings[buildingID].workerID[1] = 0;
            }
            cowID = DAT_BuildingsState::instance.buildings[buildingID].workerID[2];
            if (cowID == 0 || DAT_UnitsState::instance.units[cowID].uid != DAT_BuildingsState::instance.buildings[buildingID].workerUID[2]) {
                DAT_BuildingsState::instance.buildings[buildingID].workerID[2] = 0;
            }
            cowID = DAT_BuildingsState::instance.buildings[buildingID].workerID[3];
            if (cowID == 0 || DAT_UnitsState::instance.units[cowID].uid != DAT_BuildingsState::instance.buildings[buildingID].workerUID[3]) {
                DAT_BuildingsState::instance.buildings[buildingID].workerID[3] = 0;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            goto solitary;
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
        if ((char)DAT_BuildingDefinedData::instance.ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2] <= 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance.ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
        return;
    otherStates:
        {
            byte state = DAT_BuildingsState::instance.buildings[buildingID].dairyState;
            if (state == 1) {
                int* frame0Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0;
                *frame0Ptr = 0x46;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha += -1;
                if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].dairyState = 2;
                }
            } else if (state == 2) {
                byte spawnFrame = DAT_BuildingDefinedData::instance.dairyCowSpawnFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
                if (spawnFrame == 0x18) {
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha += 1;
                    if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha < 0x20) {
                        goto refreshArea;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x20;
                    short* cowIDPtr = &DAT_BuildingsState::instance.buildings[buildingID].workerID[1];
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                    int cowSlot;
                    if (*cowIDPtr == 0) {
                        cowSlot = 0;
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].workerID[2] == 0) {
                        cowSlot = 1;
                    } else if (DAT_BuildingsState::instance.buildings[buildingID].workerID[3] == 0) {
                        cowSlot = 2;
                    } else {
                        cowSlot = 0;
                        int* cowUIDPtr = &DAT_BuildingsState::instance.buildings[buildingID].workerUID[1];
                        for (int slot = 1; slot < 4; slot++) {
                            if (*cowUIDPtr != DAT_UnitsState::instance.units[*cowIDPtr].uid
                                || DAT_UnitsState::instance.units[*cowIDPtr].logicalState
                                    == OpenSHC::Map::Units::ULS_REMOVE) {
                                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[slot] = 0;
                                cowSlot = slot - 1;
                                break;
                            }
                            cowIDPtr++;
                            cowUIDPtr++;
                        }
                    }
                    int tile = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tileRefs[cowSlot];
                    int cowID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        owner, 0,
                        (tile
                            - DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                                  .addXgetTile)
                            * 8,
                        DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile] * 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeight,
                        OpenSHC::Map::Units::UT_COW);
                    buildingID = DAT_CurrentBuildingID::instance;
                    if (cowID == 0) {
                        goto refreshArea;
                    }
                    DAT_GameState::instance.playerDataArray[owner].cowCount += 1;
                    DAT_UnitsState::instance.units[cowID].workplaceBuildingOrTraderUID = DAT_BuildingsState::instance.buildings[buildingID].uid;
                    DAT_UnitsState::instance.units[cowID].fadeAlphaStep = -1;
                    DAT_UnitsState::instance.units[cowID].substate = -1;
                    DAT_UnitsState::instance.units[cowID].workplaceOrHomeBuildingID = (short)buildingID;
                    DAT_UnitsState::instance.units[cowID].idInTribe = (short)cowSlot;
                    DAT_UnitsState::instance.units[cowID].state.generic
                        = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                    DAT_UnitsState::instance.units[cowID].fadeLevel = 0x20;
                    DAT_UnitsState::instance.units[cowID].facingDirection
                        = (byte)DAT_UnitsState::instance.units[cowID].fixedRng & 7;
                    DAT_UnitsState::instance.units[cowID].animationCycleNumber = 0;
                    if (cowSlot == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].workerID[1] = (short)cowID;
                        DAT_BuildingsState::instance.buildings[buildingID].workerUID[1] = DAT_UnitsState::instance.units[cowID].uid;
                        DAT_UnitsState::instance.units[cowID].workerIndex = 1;
                        DAT_UnitsState::instance.units[cowID].buildingID = (short)buildingID;
                    } else if (cowSlot == 1) {
                        DAT_BuildingsState::instance.buildings[buildingID].workerID[2] = (short)cowID;
                        DAT_BuildingsState::instance.buildings[buildingID].workerUID[2] = DAT_UnitsState::instance.units[cowID].uid;
                        DAT_UnitsState::instance.units[cowID].workerIndex = 2;
                        DAT_UnitsState::instance.units[cowID].buildingID = (short)buildingID;
                    } else if (cowSlot == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].workerID[3] = (short)cowID;
                        DAT_BuildingsState::instance.buildings[buildingID].workerUID[3] = DAT_UnitsState::instance.units[cowID].uid;
                        DAT_UnitsState::instance.units[cowID].workerIndex = 3;
                        DAT_UnitsState::instance.units[cowID].buildingID = (short)buildingID;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].dairyState = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = (char)spawnFrame + 0x37;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                }
            } else if (state == 3) {
                int* frame0Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0;
                *frame0Ptr = 0x10;
                int* frame1Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1;
                *frame1Ptr = 0x1c;
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha += -1;
                if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
                    DAT_BuildingsState::instance.buildings[buildingID].dairyState = 4;
                }
            } else if (state == 4) {
                if (DAT_BuildingDefinedData::instance.dairyMilkBucketFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1] == 0) {
                    int* frame2Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2;
                    *frame2Ptr = 0x30;
                    int* frame0Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0;
                    *frame0Ptr = 0x10;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha += 1;
                    if (DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha >= 0x20) {
                        DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x20;
                        DAT_BuildingsState::instance.buildings[buildingID].dairyState = 5;
                        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                    }
                } else {
                    int* frame0Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0;
                    *frame0Ptr = (char)DAT_BuildingDefinedData::instance.dairyMilkingFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
                    int* frame1Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1;
                    *frame1Ptr = (char)DAT_BuildingDefinedData::instance.dairyMilkBucketFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1] + 0x10;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                    int bucketIndex = DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1;
                    if (bucketIndex / 12 < 0x1e && bucketIndex % 12 == 10) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x, DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_COW_MILK);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 == 0x170) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x, DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_MILK_POUR);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
            } else if (state == 5) {
                byte phaseFrame = DAT_BuildingDefinedData::instance.dairyPhase5Frames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2];
                if (phaseFrame == 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0x36;
                    DAT_BuildingsState::instance.buildings[buildingID].dairyState = 6;
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = (char)phaseFrame + 0x2f;
                    DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
                }
            } else if (state == 6) {
                int* frame2Ptr = &DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2;
                *frame2Ptr = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame3 = 0x37;
                DAT_BuildingsState::instance.buildings[buildingID].resources[11] = 1;
                DAT_BuildingsState::instance.buildings[buildingID].dairyState = 0;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex2 = 0;
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame2 = 0;
            }
        }
        goto refreshArea;
    solitary:
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
    }

}
}