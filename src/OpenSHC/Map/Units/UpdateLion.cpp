#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00ee1058.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0056B0E0
    void Units::UpdateLion()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int tribe = DAT_UnitsState::instance.units[unitID].tribeID;
        DAT_GameState::instance.mapAndTime.lionCount += 1;
        DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
        if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 0
            && DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel -= 1;
        }
        if (DAT_UnitsState::instance.units[unitID].cooldownTicks != 0) {
            DAT_UnitsState::instance.units[unitID].cooldownTicks -= 1;
        }
        if (DAT_TribesState::instance.tribes[tribe].isProvoked != 0) {
            DAT_UnitsState::instance.units[unitID].cooldownTicks = 0;
            DAT_TribesState::instance.tribes[tribe].pendingEventFlag = 0;
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(unitID, DAT_TribesState::instance.tribes[tribe].leaderUnitID);
            unitID = DAT_CurrentUnitSlotID::instance;
            // hungry lions search for prey in a growing radius
            int prey = 0;
            if (DAT_UnitsState::instance.units[unitID].cooldownTicks == 0
                && DAT_TribesState::instance.tribes[tribe].pendingEventFlag == 0) {
                if (DAT_TribesState::instance.tribes[tribe].isProvoked != 0) {
                    prey = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::findClosestPreyInArea, DAT_UnitsState::ptr)(200,
                        TRUE, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                    unitID = DAT_CurrentUnitSlotID::instance;
                } else {
                    DAT_TribesState::instance.tribes[tribe].elapsedTicks += 1;
                    if (DAT_TribesState::instance.tribes[tribe].elapsedTicks >= 3000) {
                        prey = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::findClosestPreyInArea, DAT_UnitsState::ptr)(50,
                            TRUE, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y);
                        unitID = DAT_CurrentUnitSlotID::instance;
                    } else if (DAT_TribesState::instance.tribes[tribe].elapsedTicks >= 10) {
                        prey = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findClosestPreyInArea,
                            DAT_UnitsState::ptr)(25, FALSE, DAT_UnitsState::instance.units[unitID].x,
                            DAT_UnitsState::instance.units[unitID].y);
                        unitID = DAT_CurrentUnitSlotID::instance;
                    }
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::tryAttackUnitID, DAT_UnitsState::ptr)(
                    unitID, prey)
                == 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)0xcd;
            }
            return;
        }
        if (state == (UnitState)0xd0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(unitID);
            if (DAT_UnitsState::instance.units[unitID].subTileStepProgress >= 8) {
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION || state == (UnitState)120) {
            if (DAT_UnitsState::instance.units[unitID].substate == 100) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 20;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
                DAT_UnitsState::instance.units[unitID].animationSpeed
                    = (DAT_UnitsState::instance.units[unitID].fixedRng & 7) + 1;
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animLionGetUp[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].seated = 0;
                    DAT_UnitsState::instance.units[unitID].substate
                        = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x170;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_TribesState::instance.tribes[tribe].wildlifeAlarmTimer == 0) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 2;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].substate = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == (UnitState)0xcf) {
            // chasing prey
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                short prey = DAT_UnitsState::instance.units[unitID].targetUnitId;
                if (prey != 0) {
                    if (DAT_UnitsState::instance.units[unitID]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            == DAT_UnitsState::instance.units[prey].uid
                        && DAT_UnitsState::instance.units[prey].dying == 0
                        && DAT_UnitsState::instance.units[prey].isHiddenInBuilding == 0) {
                        BOOL ok = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(unitID, DAT_UnitsState::instance.units[prey].x,
                            DAT_UnitsState::instance.units[prey].y, 0);
                        unitID = DAT_CurrentUnitSlotID::instance;
                        if (ok == FALSE) {
                            DAT_UnitsState::instance.units[unitID].targetUnitId = 0;
                        }
                    } else {
                        DAT_UnitsState::instance.units[unitID].targetUnitId = 0;
                    }
                }
                if (DAT_UnitsState::instance.units[unitID].targetUnitId == 0) {
                    DAT_UnitsState::instance.units[unitID].chaseTargetUnitID = 0;
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].substate
                        = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            if (DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan <= 4
                && DAT_UnitsState::instance.units[unitID].totalSizeOfPathPlan > 8) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
            } else {
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber > 50) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animLionMelee[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_LION_ATTACK);
                unitID = DAT_CurrentUnitSlotID::instance;
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate += 1;
            if (DAT_UnitsState::instance.units[unitID].substate > 4) {
                DAT_UnitsState::instance.units[unitID].substate = 1;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(unitID);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].cooldownTicks = 1000;
            DAT_TribesState::instance.tribes[tribe].elapsedTicks = 0;
            // "Lions are attacking" at most every 90 seconds
            if (timeGetTime() - DWORD_00ee1058::instance <= 90000) {
                return;
            }
            int victim = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].meleeOpponentUnitID;
            if (victim == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[victim].owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_General_Warning17_wav_005abe40);
            DWORD_00ee1058::instance = timeGetTime();
            return;
        }
        if (state == (UnitState)0xcc) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x2b8;
            DAT_UnitsState::instance.units[unitID].restingPoseFlag = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animLionStandingIdle[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x20;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitAnimationFinished::instance = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)0xcd) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x170;
            DAT_UnitsState::instance.units[unitID].restingPoseFlag = 0;
            if (DAT_UnitsState::instance.units[unitID].seated == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animLionLieDown[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animLionResting[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber += 0x18;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].animationFrame;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate += 1;
            if (DAT_UnitsState::instance.units[unitID].substate > 1) {
                DAT_UnitsState::instance.units[unitID].substate = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].seated = 1;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == (UnitState)0xce) {
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1b8;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x1a0;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_LION_DIE);
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1a0;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x188;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_LION_DIE);
            }
            return;
        }
        state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == (UnitState)117) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 50) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
