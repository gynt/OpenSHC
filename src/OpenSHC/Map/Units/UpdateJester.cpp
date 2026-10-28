#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0056E190
    void Units::UpdateJester()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[unitID].owner;
        DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
        DAT_UnitsState::instance.units[unitID].hopGaitMode = 0;
        if (DAT_UnitsState::instance.units[unitID].blockedWaitCounter > 1) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel < 0) {
                    DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                    DAT_UnitsState::instance.units[unitID].isFadeActive = 0;
                }
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // walking back to the keep
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                    DAT_UnitsState::instance.units[unitID].targetY_2, 0);
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 2;
            DAT_UnitsState::instance.units[unitID].stateAfterFade = 2;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            return;
        }
        if (state == (UnitState)2) {
            // inside the keep, choosing the next outing
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 400) {
                return;
            }
            int nearbyUnit = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::findEligibleUnitByTimeAndLocation, DAT_UnitsState::ptr)(unitID,
                owner, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 0, 0);
            int inn
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(owner, OpenSHC::Map::Buildings::BT_INN);
            int random = (byte)SEC_RNG::instance.currentNumber2 & 7;
            if (random <= 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade
                    = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
            } else if (random <= 4 && inn != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade
                    = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
            } else if (nearbyUnit != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade = 3;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .targetUnitId = (short)nearbyUnit;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    = DAT_UnitsState::instance.units[nearbyUnit].uid;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].stateAfterFade
                    = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeLevel = 32;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].fadeAlphaStep
                = 0xfe;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // wandering around
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].animCycle16 <= 3
                || DAT_UnitsState::instance.units[unitID].animCycle16 >= 12) {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 6;
            } else {
                DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 2;
                DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            DAT_UnitsState::instance.units[unitID].hopGaitMode = 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeRandomWanderPath,
                        DAT_UnitsState::ptr)(unitID, 0, 0, 1)
                    == 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitMovementIdle, DAT_UnitsState::ptr)(unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // juggling
            DAT_UnitsState::instance.units[unitID].animationSpeed = 4;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJesterArrival[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x81;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x79
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate += 1;
            if (DAT_UnitsState::instance.units[unitID].substate > 10) {
                DAT_UnitsState::instance.units[unitID].substate = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == (UnitState)3) {
            // walking up to someone to entertain them
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                BOOL ok = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                    DAT_UnitsState::ptr)(unitID,
                    DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].targetUnitId].x,
                    DAT_UnitsState::instance.units[DAT_UnitsState::instance.units[unitID].targetUnitId].y, 0);
                unitID = DAT_CurrentUnitSlotID::instance;
                if (ok != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount,
                        DAT_UnitsState::ptr)(unitID, 1);
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                } else {
                    DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].movementSpeed
                = 4 - DAT_UnitsState::instance.units[unitID].currentIndexInPathPlan;
            if (DAT_UnitsState::instance.units[unitID].movementSpeed <= 0) {
                DAT_UnitsState::instance.units[unitID].movementSpeed = 1;
            }
            int target = DAT_UnitsState::instance.units[unitID].targetUnitId;
            if (target == 0
                || DAT_UnitsState::instance.units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                    != DAT_UnitsState::instance.units[target].uid) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                    DAT_UnitsState::ptr)(unitID);
                if (DAT_UnitsState::instance.units[unitID].subTileStepProgress < 8) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y, DAT_UnitsState::instance.units[target].x,
                DAT_UnitsState::instance.units[target].y);
            if (DAT_DirectionAlgorithmState::instance.distanceHigh < 5) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                    DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance)
                != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // performing for someone
            if (DAT_UnitsState::instance.units[unitID].subTileStepProgress < 8) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
                DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                unitID, DAT_UnitsState::instance.units[unitID].targetUnitId);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSpeed = 3;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].field_0x30_animRelated = 0;
            int gfxBase = 0;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animJesterPerform0
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                gfxBase = 0x1b1;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animJesterPerform1
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                gfxBase = 0x1b1;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 2) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animJesterArrival
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                gfxBase = 0x81;
            } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate == 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animJesterPerform3
                          [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
                gfxBase = 0x1b1;
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + gfxBase;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + gfxBase - 8 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate > 3) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].substate = 0;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit < 5) {
                int nearbyUnit
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findEligibleUnitByTimeAndLocation,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, owner,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, 1, 0);
                if (nearbyUnit != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetUnitId = (short)nearbyUnit;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                        = DAT_UnitsState::instance.units[nearbyUnit].uid;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    return;
                }
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // walking to the inn
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int inn = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    DAT_BuildingsState::ptr)(owner, OpenSHC::Map::Buildings::BT_INN);
                if (inn != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[inn].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[inn].buildingEntryY, 0);
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                } else {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 2;
            DAT_UnitsState::instance.units[unitID].stateAfterFade = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // drinking in the inn
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 500) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 0xfe;
            DAT_UnitsState::instance.units[unitID].stateAfterFade = OpenSHC::Map::Units::States::US_IDLEUnk;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                unitID);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            }
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
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
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 16) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = DAT_UnitsState::instance.units[unitID].stateAfterFade;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    unitID);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID, 2);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animJesterPerform0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x1b1;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x1a9
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget, DAT_UnitsState::ptr)(unitID);
            }
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
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x1b0;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x198;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
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
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x198;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x180;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
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
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
        DAT_UnitsState::instance.units[unitID].destinationNeeded
            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
