#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0056F9B0
    void Units::UpdateCageDog()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int tribe = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].tribeID;
        int kennel = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateBasedSpeed = 0;
        DAT_GameState::instance.mapAndTime.cageDogCount += 1;
        if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 0
            && DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel -= 1;
        }
        if (DAT_UnitsState::instance.units[unitID].cooldownTicks != 0) {
            DAT_UnitsState::instance.units[unitID].cooldownTicks -= 1;
        }
        // the dogs vanish together with their kennel
        if (DAT_UnitsState::instance.units[unitID].dying == 0
            && DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID].uid
                != DAT_UnitsState::instance.units[unitID].workplaceBuildingOrTraderUID) {
            DAT_UnitsState::instance.units[unitID].dying = 1;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance, DAT_TribesState::instance.tribes[tribe].leaderUnitID);
            int enemy = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::findClosestEnemyByAreaAndRange, DAT_UnitsState::ptr)(15,
                DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID]
                    .buildingEntryX,
                DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID]
                    .buildingEntryY,
                DAT_BuildingsState::instance.buildings[kennel].owner);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::tryAttackUnitID, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, enemy)
                == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)0xd3;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == (UnitState)0xd2) {
            // waiting in the kennel until enough enemies are close
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker
                <= DAT_UnitsState::instance.units[unitID].cagedogReleaseCheckMoment * 8 + 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker
                = DAT_UnitsState::instance.units[unitID].cagedogReleaseCheckMoment * 8;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[kennel].owner, 0, 1,
                DAT_UnitsState::instance.units[unitID].tile, 16);
            if (DAT_PathFindingState::instance.ALGO_TotalTroopValue >= 25
                || DAT_PathFindingState::instance.ALGO_TotalTroopCount > 5) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 31;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeAlphaStep
                    = 0xfe;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)0xd3) {
            // returning to the kennel
            DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                    != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                       DAT_BuildingsState::ptr)(kennel, 1)
                    != 0
                && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                       DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[kennel].buildingEntryX,
                       DAT_BuildingsState::instance.buildings[kennel].buildingEntryY, 0)
                    != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeAlphaStep
                    = 2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade = 0xd2;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == (UnitState)0xd0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
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
                int frame;
                if (DAT_UnitsState::instance.units[unitID].restingPoseFlag != 0) {
                    frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                                .animCageDogGetUpFromRest[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                } else {
                    frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                                .animCageDogGetUp[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
                }
                DAT_UnitsState::instance.units[unitID].animationFrame = frame;
                if (frame <= 0) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].seated = 0;
                    DAT_UnitsState::instance.units[unitID].substate = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                    DAT_UnitsState::instance.units[unitID].gfxNumber += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected;
                    return;
                }
                if (DAT_UnitsState::instance.units[unitID].restingPoseFlag != 0) {
                    DAT_UnitsState::instance.units[unitID].gfxNumber
                        = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x270 + frame * 8;
                    return;
                }
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x2b0 + frame * 8;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_TribesState::instance.tribes[tribe].wildlifeAlarmTimer != 0) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 2;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            } else {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 3;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].substate = DAT_UnitsState::instance.units[unitID].fixedRng & 1;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)0xcf) {
            // chasing an enemy
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                short enemy = DAT_UnitsState::instance.units[unitID].targetUnitId;
                if (enemy != 0) {
                    if (DAT_UnitsState::instance.units[unitID]
                                .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                            == DAT_UnitsState::instance.units[enemy].uid
                        && DAT_UnitsState::instance.units[enemy].dying == 0
                        && DAT_UnitsState::instance.units[enemy].isHiddenInBuilding == 0) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                                DAT_UnitsState::instance.units[enemy].x, DAT_UnitsState::instance.units[enemy].y, 0)
                            == FALSE) {
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .targetUnitId = 0;
                        }
                    } else {
                        DAT_UnitsState::instance.units[unitID].targetUnitId = 0;
                    }
                }
                unitID = DAT_CurrentUnitSlotID::instance;
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
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            } else {
                DAT_UnitsState::instance.units[unitID].moveInstructionSpeedDelayTracker = 0;
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
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
            int frame;
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogMelee0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogMelee1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 2) {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogMelee2[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 3) {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogMelee3[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogMelee4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            DAT_UnitsState::instance.units[unitID].animationFrame = frame;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_WOLF_ATTACK);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x179 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 4) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 1;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
            DAT_TribesState::instance.tribes[tribe].elapsedTicks = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FADE_TRANSITION) {
            DAT_UnitsState::instance.units[unitID].fadeLevel
                += DAT_UnitsState::instance.units[unitID].fadeAlphaStep;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel < 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            } else if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel >= 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 31;
            }
            if (DAT_UnitsState::instance.units[unitID].fadeLevel == 0
                && (char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep < 0) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].stateAfterFade;
            }
            if (DAT_UnitsState::instance.units[unitID].fadeLevel == 31
                && (char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep > 0) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = DAT_UnitsState::instance.units[unitID].stateAfterFade;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
            }
            return;
        }
        if (state == (UnitState)0xce) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x278;
            DAT_UnitsState::instance.units[unitID].restingPoseFlag = 1;
            int frame;
            if (DAT_UnitsState::instance.units[unitID].seated == 0) {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogLieDown[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                frame = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                            .animCageDogResting[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            DAT_UnitsState::instance.units[unitID].animationFrame = frame;
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x18;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    += DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected - 8
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
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
        if (state == OpenSHC::Map::Units::States::US_DEATH_01) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .ANIM_UnitDeath1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x338;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 800;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_WOLF_DIE);
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].facingDirection = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animCageDogDeathOther[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x340;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)117;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x338;
            }
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber == 1
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_WOLF_DIE);
            }
            return;
        }
        if (DAT_UnitsState::instance.units[unitID].state.generic == (UnitState)117) {
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 50) {
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        if (DAT_UnitsState::instance.units[unitID].state.generic == OpenSHC::Map::Units::States::US_DISAPPEAR) {
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
            DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
    }

}
}
