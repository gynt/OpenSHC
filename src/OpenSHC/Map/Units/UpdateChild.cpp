#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005477C0
    void Units::UpdateChild()
    {
        int slot = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[slot].owner;
        DAT_GameState::instance.playerDataArray[owner].childCountThisTick += 1;
        DAT_GameState::instance.playerDataArray[owner].nonInteractiveUnitCountThisTick += 1;
        if (DAT_UnitsState::instance.units[slot].blockedWaitCounter > 1) {
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        // too many children
        if (DAT_GameState::instance.playerDataArray[owner].motherCountThisTick
                + DAT_GameState::instance.playerDataArray[owner].childCountThisTick
            > 75) {
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        DAT_UnitsState::instance.units[slot].stateBasedSpeed = 0;
        DAT_UnitsState::instance.units[slot].ownerColorIndex
            = (int)DAT_UnitsState::instance.units[slot].fixedRng % 9;
        if (DAT_UnitsState::instance.units[slot].spriteID == 0x81
            && DAT_UnitsState::instance.units[slot].ownerColorIndex == 3) {
            DAT_UnitsState::instance.units[slot].ownerColorIndex = 4;
        }
        DAT_UnitsState::instance.units[slot].health = 60000;
        UnitStateShort state = DAT_UnitsState::instance.units[slot].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            if (DAT_UnitsState::instance.units[slot].isFadeActive != 0) {
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[slot].fadeLevel = 32;
                DAT_UnitsState::instance.units[slot].fadeAlphaStep
                    = 0xff;
                DAT_UnitsState::instance.units[slot].stateAfterFade
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[slot].gfxNumber = 1;
                return;
            }
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            if (DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[slot]
                                .workplaceOrHomeBuildingID]
                        .uid
                    != DAT_UnitsState::instance.units[slot].workplaceBuildingOrTraderUID
                || DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[slot]
                                .workplaceOrHomeBuildingID]
                        .logicalState
                    == (BuildingLogicalState)0) {
                // the home is gone
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_DISAPPEAR;
                return;
            }
            if (DAT_GameState::instance.playerDataArray[owner].popularity / 100 < 50) {
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                return;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                return;
            }
            int choice = SEC_RNG::instance.currentNumber2;
            switch (choice % 25) {
            case 3:
            case 4:
            case 5:
            case 6:
                DAT_UnitsState::instance.units[slot].targetID_OR_targetBuildingID
                    = DAT_UnitsState::instance.units[slot].workplaceOrHomeBuildingID;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            case 7:
            case 8:
            case 9:
            case 18:
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeRandomWanderPath,
                        DAT_UnitsState::ptr)(slot, 1, 0, 0)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)120;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                    return;
                }
                break;
            case 10:
            case 11:
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            case 12:
            case 13:
            case 14:
                DAT_UnitsState::instance.units[slot].state.generic
                    = DAT_UnitsState::instance.units[slot].spriteID == 0x80
                    ? OpenSHC::Map::Units::States::US_STAND_UPUnk
                    : (UnitState)12;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            case 15:
            case 16:
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)12;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            case 17:
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)16;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            case 19:
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)17;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            case 20:
            case 21:
            case 22:
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)18;
                DAT_UnitsState::instance.units[slot].updateTickTracker
                    = (short)((choice >> 8) % 20);
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            return;
        }
        if (state == (UnitState)120) {
            // climbing around
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitMovementIdle,
                    DAT_UnitsState::ptr)(slot)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION) {
            // playing near the home
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    slot,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[slot]
                                .targetID_OR_targetBuildingID]
                        .buildingEntryX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[slot]
                                .targetID_OR_targetBuildingID]
                        .buildingEntryY,
                    0);
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // running home
            DAT_UnitsState::instance.units[slot].movementSpeed = 1;
            DAT_UnitsState::instance.units[slot].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int home = DAT_UnitsState::instance.units[slot].workplaceOrHomeBuildingID;
                if (home == 0
                    || DAT_BuildingsState::instance.buildings[home].uid
                        != DAT_UnitsState::instance.units[slot].workplaceBuildingOrTraderUID) {
                    DAT_UnitsState::instance.units[slot].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                               DAT_UnitsState::ptr)(slot,
                               DAT_BuildingsState::instance.buildings[home].buildingEntryX,
                               DAT_BuildingsState::instance.buildings[home].buildingEntryY, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    return;
                }
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // walking home
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int home = DAT_UnitsState::instance.units[slot].workplaceOrHomeBuildingID;
                if (home == 0
                    || DAT_BuildingsState::instance.buildings[home].uid
                        != DAT_UnitsState::instance.units[slot].workplaceBuildingOrTraderUID) {
                    DAT_UnitsState::instance.units[slot].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                               DAT_UnitsState::ptr)(slot,
                               DAT_BuildingsState::instance.buildings[home].buildingEntryX,
                               DAT_BuildingsState::instance.buildings[home].buildingEntryY, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    return;
                }
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // looking for a child to play with
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            DAT_UnitsState::instance.units[slot].gfxNumber
                = DAT_UnitsState::instance.units[slot].facingDirectionMapOrientationCorrected
                + 1;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId = 0;
                for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; i++) {
                    if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                        && DAT_UnitsState::instance.units[i].unitType == OpenSHC::Map::Units::UT_CHILD
                        && DAT_UnitsState::instance.units[i].owner == owner
                        && (DAT_UnitsState::instance.units[i].state.generic
                                == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                            || DAT_UnitsState::instance.units[i].state.generic
                                == OpenSHC::Map::Units::States::US_IDLEUnk)) {
                        DAT_UnitsState::instance.units[i].state.generic
                            = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                        DAT_UnitsState::instance.units[i].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                        DAT_UnitsState::instance.units[slot]
                            .targetUnitId = (short)i;
                        DAT_UnitsState::instance.units[i].targetUnitId
                            = (short)slot;
                        short rounds = SEC_RNG::instance.currentNumber2 % 5 + 1;
                        DAT_UnitsState::instance.units[slot].updateTickTracker = rounds;
                        DAT_UnitsState::instance.units[i].updateTickTracker = rounds;
                        break;
                    }
                }
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                if (DAT_UnitsState::instance.units[slot]
                        .targetUnitId
                    == 0) {
                    DAT_UnitsState::instance.units[slot].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(slot,
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId);
            slot = DAT_CurrentUnitSlotID::instance;
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            int other = DAT_UnitsState::instance.units[slot]
                            .targetUnitId;
            if (DAT_UnitsState::instance.units[other].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    other)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // walking to the child that wants to play
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            DAT_UnitsState::instance.units[slot].gfxNumber
                = DAT_UnitsState::instance.units[slot].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int other = DAT_UnitsState::instance.units[slot]
                                .targetUnitId;
                for (int i = 0; i < 4; i++) {
                    int offset = (DAT_UnitsState::instance.units[slot].fixedRng & 3) + i;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(slot,
                            DAT_UnitsState::instance.units[other].x
                                + DAT_UnitPropertiesDefinedData::instance.childPlayOffsets[offset].x,
                            DAT_UnitsState::instance.units[other].y
                                + DAT_UnitPropertiesDefinedData::instance.childPlayOffsets[offset].y,
                            0)
                        != FALSE) {
                        break;
                    }
                    slot = DAT_CurrentUnitSlotID::instance;
                    if (i == 3) {
                        DAT_UnitsState::instance.units[slot].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[other].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    }
                }
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            int other = DAT_UnitsState::instance.units[slot]
                            .targetUnitId;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[slot].x,
                DAT_UnitsState::instance.units[slot].y,
                DAT_UnitsState::instance.units[other].x, DAT_UnitsState::instance.units[other].y);
            slot = DAT_CurrentUnitSlotID::instance;
            if (DAT_DirectionAlgorithmState::instance.distanceHigh == 1
                && abs(DAT_UnitsState::instance.units[slot].terrainOrClimbHeight
                       - DAT_UnitsState::instance.units[other].terrainOrClimbHeight)
                    < 6) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)9;
                return;
            }
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[other].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // playing together
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(slot,
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId);
            slot = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[slot].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildPairGameA1
                      [DAT_UnitsState::instance.units[slot].animationCycleNumber];
            if (DAT_UnitsState::instance.units[slot].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[slot].gfxNumber
                    = DAT_UnitsState::instance.units[slot]
                          .facingDirectionMapOrientationCorrected
                    + 0xf9 + DAT_UnitsState::instance.units[slot].animationFrame * 8;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            DAT_UnitsState::instance.units[slot].state.generic
                = DAT_UnitsState::instance.units[slot].updateTickTracker < 0
                ? OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                : (UnitState)9;
            return;
        }
        if (state == (UnitState)9) {
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(slot,
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId);
            slot = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[slot].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildPairGameA2
                      [DAT_UnitsState::instance.units[slot].animationCycleNumber];
            if (DAT_UnitsState::instance.units[slot].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[slot].gfxNumber
                    = DAT_UnitsState::instance.units[slot]
                          .facingDirectionMapOrientationCorrected
                    + 0x179 + DAT_UnitsState::instance.units[slot].animationFrame * 8;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            DAT_UnitsState::instance.units[slot].state.generic
                = DAT_UnitsState::instance.units[slot].updateTickTracker < 0
                ? OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                : OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            return;
        }
        if (state == (UnitState)12) {
            // looking for a child to play with (second game)
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            DAT_UnitsState::instance.units[slot].gfxNumber
                = DAT_UnitsState::instance.units[slot].facingDirectionMapOrientationCorrected
                + 1;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId = 0;
                for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; i++) {
                    if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                        && DAT_UnitsState::instance.units[i].unitType == OpenSHC::Map::Units::UT_CHILD
                        && DAT_UnitsState::instance.units[i].owner == owner
                        && (DAT_UnitsState::instance.units[i].state.generic
                                == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                            || DAT_UnitsState::instance.units[i].state.generic
                                == OpenSHC::Map::Units::States::US_IDLEUnk)
                        && (DAT_UnitsState::instance.units[i].spriteID == 0x81
                            || (DAT_UnitsState::instance.units[i].fixedRng & 3) == 1)) {
                        DAT_UnitsState::instance.units[i].state.generic = OpenSHC::Map::Units::States::US_SIT_DOWNUnk;
                        DAT_UnitsState::instance.units[i].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                        DAT_UnitsState::instance.units[slot]
                            .targetUnitId = (short)i;
                        DAT_UnitsState::instance.units[i].targetUnitId
                            = (short)slot;
                        short rounds = SEC_RNG::instance.currentNumber2 % 5 + 1;
                        DAT_UnitsState::instance.units[slot].updateTickTracker = rounds;
                        DAT_UnitsState::instance.units[i].updateTickTracker = rounds;
                        break;
                    }
                }
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                if (DAT_UnitsState::instance.units[slot]
                        .targetUnitId
                    == 0) {
                    DAT_UnitsState::instance.units[slot].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(slot,
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId);
            slot = DAT_CurrentUnitSlotID::instance;
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            int other = DAT_UnitsState::instance.units[slot]
                            .targetUnitId;
            if (DAT_UnitsState::instance.units[other].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    other)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic = (UnitState)10;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_SIT_DOWNUnk) {
            // walking to the child that wants to play (second game)
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            DAT_UnitsState::instance.units[slot].gfxNumber
                = DAT_UnitsState::instance.units[slot].facingDirectionMapOrientationCorrected
                + 1;
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int other = DAT_UnitsState::instance.units[slot]
                                .targetUnitId;
                for (int i = 0; i < 4; i++) {
                    int offset = (DAT_UnitsState::instance.units[slot].fixedRng & 3) + i;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                            DAT_UnitsState::ptr)(slot,
                            DAT_UnitsState::instance.units[other].x
                                + DAT_UnitPropertiesDefinedData::instance.childPlayOffsets[offset + 4].x,
                            DAT_UnitsState::instance.units[other].y
                                + DAT_UnitPropertiesDefinedData::instance.childPlayOffsets[offset + 4].y,
                            0)
                        != FALSE) {
                        break;
                    }
                    slot = DAT_CurrentUnitSlotID::instance;
                    if (i == 3) {
                        DAT_UnitsState::instance.units[slot].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        DAT_UnitsState::instance.units[other].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    }
                }
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            int other = DAT_UnitsState::instance.units[slot]
                            .targetUnitId;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[slot].x,
                DAT_UnitsState::instance.units[slot].y,
                DAT_UnitsState::instance.units[other].x, DAT_UnitsState::instance.units[other].y);
            slot = DAT_CurrentUnitSlotID::instance;
            if (DAT_DirectionAlgorithmState::instance.distanceHigh == 1
                && abs(DAT_UnitsState::instance.units[slot].terrainOrClimbHeight
                       - DAT_UnitsState::instance.units[other].terrainOrClimbHeight)
                    < 6) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)13;
                return;
            }
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[other].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == (UnitState)10) {
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 5;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(slot,
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId);
            slot = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[slot].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildPairGameB1
                      [DAT_UnitsState::instance.units[slot].animationCycleNumber];
            if (DAT_UnitsState::instance.units[slot].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[slot].gfxNumber
                    = DAT_UnitsState::instance.units[slot]
                          .facingDirectionMapOrientationCorrected
                    + 0x1f9 + DAT_UnitsState::instance.units[slot].animationFrame * 8;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            DAT_UnitsState::instance.units[slot].state.generic
                = DAT_UnitsState::instance.units[slot].updateTickTracker < 0
                ? OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                : (UnitState)13;
            return;
        }
        if (state == (UnitState)13) {
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 5;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget,
                DAT_UnitsState::ptr)(slot,
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId);
            slot = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[slot].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildPairGameB2
                      [DAT_UnitsState::instance.units[slot].animationCycleNumber];
            if (DAT_UnitsState::instance.units[slot].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[slot].gfxNumber
                    = DAT_UnitsState::instance.units[slot]
                          .facingDirectionMapOrientationCorrected
                    + 0x1f9 + DAT_UnitsState::instance.units[slot].animationFrame * 8;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            DAT_UnitsState::instance.units[slot].state.generic
                = DAT_UnitsState::instance.units[slot].updateTickTracker < 0
                ? OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                : (UnitState)10;
            return;
        }
        if (state == (UnitState)16) {
            // gathering a group of children to lead
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildIdle
                      [DAT_UnitsState::instance.units[slot].animationCycleNumber];
            if (DAT_UnitsState::instance.units[slot].animationFrame <= 0) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildIdle[0];
            }
            DAT_UnitsState::instance.units[slot].gfxNumber
                = DAT_UnitsState::instance.units[slot].animationFrame + 0x280;
            int random = SEC_RNG::instance.currentNumber2;
            int followers = random % 8 + 4;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int leader = DAT_GameState::instance.playerDataArray[owner].childLeaderUnitId;
                if (leader != 0
                    && DAT_UnitsState::instance.units[leader].uid
                        == DAT_GameState::instance.playerDataArray[owner].childLeaderUid) {
                    // there is a leader already: follow it
                    DAT_UnitsState::instance.units[slot].state.generic = (UnitState)15;
                    DAT_UnitsState::instance.units[slot]
                        .targetUnitId = (short)leader;
                    state = (UnitState)15;
                } else {
                    if (leader != 0) {
                        DAT_GameState::instance.playerDataArray[owner].childLeaderUnitId = 0;
                        DAT_GameState::instance.playerDataArray[owner].childLeaderUid = 0;
                    }
                    DAT_UnitsState::instance.units[slot]
                        .targetUnitId = 0;
                    bool found = false;
                    for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; i++) {
                        if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                            && DAT_UnitsState::instance.units[i].unitType == OpenSHC::Map::Units::UT_CHILD
                            && DAT_UnitsState::instance.units[i].owner == owner
                            && (DAT_UnitsState::instance.units[i].state.generic
                                    == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                                || DAT_UnitsState::instance.units[i].state.generic
                                    == OpenSHC::Map::Units::States::US_IDLEUnk)) {
                            followers -= 1;
                            DAT_UnitsState::instance.units[i].state.generic = (UnitState)15;
                            DAT_UnitsState::instance.units[i].destinationNeeded
                                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                            DAT_UnitsState::instance.units[i].targetUnitId
                                = (short)slot;
                            found = true;
                            if (followers <= 0) {
                                break;
                            }
                        }
                    }
                    if (!found) {
                        DAT_UnitsState::instance.units[slot].state.generic
                            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        return;
                    }
                    DAT_UnitsState::instance.units[slot].updateTickTracker = 300;
                    DAT_UnitsState::instance.units[slot].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                    DAT_GameState::instance.playerDataArray[owner].childLeaderUnitId = slot;
                    DAT_GameState::instance.playerDataArray[owner].childLeaderUid
                        = DAT_UnitsState::instance.units[slot].uid;
                }
            }
            if (state == (UnitState)16) {
                if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                    || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                    DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[slot].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    DAT_UnitsState::instance.units[slot].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    DAT_GameState::instance.playerDataArray[owner].childLeaderUnitId = 0;
                    DAT_GameState::instance.playerDataArray[owner].childLeaderUid = 0;
                    return;
                }
                DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
                if (DAT_UnitsState::instance.units[slot].updateTickTracker > 0) {
                    return;
                }
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic = (UnitState)14;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[slot].updateTickTracker
                    = (short)((random >> 5) % 5) + 3;
                return;
            }
        }
        if (state == (UnitState)14) {
            // leading the group around
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[slot].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeRandomWanderPath, DAT_UnitsState::ptr)(
                    slot, 2, 0, 1);
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_GameState::instance.playerDataArray[owner].childLeaderUnitId = 0;
                DAT_GameState::instance.playerDataArray[owner].childLeaderUid = 0;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitMovementIdle,
                    DAT_UnitsState::ptr)(slot)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            if (DAT_UnitsState::instance.units[slot].updateTickTracker <= 0
                || DAT_UnitsState::instance.units[slot].updateTickTracker > 20) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_GameState::instance.playerDataArray[owner].childLeaderUnitId = 0;
                DAT_GameState::instance.playerDataArray[owner].childLeaderUid = 0;
                return;
            }
            DAT_UnitsState::instance.units[slot].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == (UnitState)15) {
            // following the leading child
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[slot].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            int leader = DAT_UnitsState::instance.units[slot]
                             .targetUnitId;
            if (DAT_UnitsState::instance.units[leader].state.generic == (UnitState)16) {
                DAT_UnitsState::instance.units[slot].stateBasedSpeed = 0;
            }
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int random = SEC_RNG::instance.currentNumber2;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    slot, DAT_UnitsState::instance.units[leader].x - 3 + random % 7,
                    DAT_UnitsState::instance.units[leader].y - 3 + (random >> 5) % 7, 0);
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            if (DAT_UnitsState::instance.units[leader].state.generic != (UnitState)14
                && DAT_UnitsState::instance.units[leader].state.generic != (UnitState)16) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            DAT_UnitsState::instance.units[slot].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == (UnitState)17) {
            // running after a selectable unit
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                DAT_UnitsState::instance.units[slot]
                    .targetUnitId = 0;
                int i;
                for (i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; i++) {
                    if (DAT_UnitsState::instance.units[i].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE
                        || DAT_UnitsState::instance.units[i].isSelectable_OR_matchTime == 0
                        || DAT_UnitsState::instance.units[i].owner != owner) {
                        continue;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(
                        DAT_UnitsState::instance.units[slot].x,
                        DAT_UnitsState::instance.units[slot].y,
                        DAT_UnitsState::instance.units[i].x, DAT_UnitsState::instance.units[i].y);
                    slot = DAT_CurrentUnitSlotID::instance;
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 20) {
                        DAT_UnitsState::instance.units[slot]
                            .targetUnitId = (short)i;
                        DAT_UnitsState::instance.units[slot].updateTickTracker
                            = SEC_RNG::instance.currentNumber2 % 50 + 25;
                        break;
                    }
                }
                if (DAT_UnitsState::instance.units[slot]
                        .targetUnitId
                    == 0) {
                    DAT_UnitsState::instance.units[slot].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    slot, DAT_UnitsState::instance.units[i].x,
                    DAT_UnitsState::instance.units[i].y, 0);
                slot = DAT_CurrentUnitSlotID::instance;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
                    slot, 1);
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            if (DAT_UnitsState::instance.units[slot].updateTickTracker > 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        }
        if (state == (UnitState)18) {
            // following the lord
            int lord = DAT_GameState::instance.playerDataArray[owner].lordID;
            DAT_UnitsState::instance.units[slot].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[slot].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0x10;
            if (lord == 0
                || DAT_UnitsState::instance.units[lord].uid != DAT_GameState::instance.playerDataArray[owner].lordUID) {
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            if (DAT_UnitsState::instance.units[slot].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    slot,
                    DAT_UnitsState::instance.units[lord].x - 3 + SEC_RNG::instance.currentNumber2 % 7,
                    DAT_UnitsState::instance.units[lord].y - 3 + (SEC_RNG::instance.currentNumber2 >> 5) % 7, 0);
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                slot = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    slot)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[slot].updateTickTracker -= 1;
            if (DAT_UnitsState::instance.units[slot].updateTickTracker <= 0) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                return;
            }
            DAT_UnitsState::instance.units[slot].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            DAT_UnitsState::instance.units[slot].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[slot].animationSpeed = 3;
            DAT_UnitsState::instance.units[slot].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animChildIdle
                      [DAT_UnitsState::instance.units[slot].animationCycleNumber];
            if (DAT_UnitsState::instance.units[slot].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[slot].gfxNumber
                    = DAT_UnitsState::instance.units[slot].animationFrame + 0x280;
            }
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0)
                || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    && DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0)) {
                DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[slot].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[slot].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].animationCycleNumber = 0;
            if ((SEC_RNG::instance.currentNumber2 & 1) == 0) {
                return;
            }
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FADE_TRANSITION) {
            DAT_UnitsState::instance.units[slot].fadeLevel
                += DAT_UnitsState::instance.units[slot]
                       .fadeAlphaStep;
            if ((char)DAT_UnitsState::instance.units[slot].fadeLevel < 0) {
                DAT_UnitsState::instance.units[slot].fadeLevel = 0;
            } else if ((char)DAT_UnitsState::instance.units[slot].fadeLevel
                >= 32) {
                DAT_UnitsState::instance.units[slot].fadeLevel = 31;
            }
            DAT_UnitsState::instance.units[slot].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[slot].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[slot].updateTickTracker = 0;
            DAT_UnitsState::instance.units[slot].fadeLevel = 0;
            DAT_UnitsState::instance.units[slot].state.generic
                = DAT_UnitsState::instance.units[slot].stateAfterFade;
            if ((char)DAT_UnitsState::instance.units[slot]
                        .fadeAlphaStep
                    < 0
                || (char)DAT_UnitsState::instance.units[slot]
                        .fadeAlphaStep
                    > 0) {
                if (DAT_UnitsState::instance.units[slot].isFadeActive != 0) {
                    DAT_UnitsState::instance.units[slot].isFadeActive = 0;
                }
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                DAT_UnitsState::ptr)(slot)
            != FALSE) {
            DAT_UnitsState::instance.units[slot].state.generic
                = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[slot].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[slot].fadeLevel
                > 32) {
                DAT_UnitsState::instance.units[slot].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[slot].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[slot].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[slot].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            int home = DAT_UnitsState::instance.units[slot].workplaceOrHomeBuildingID;
            if (home == 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[home].uid
                != DAT_UnitsState::instance.units[slot].workplaceBuildingOrTraderUID) {
                return;
            }
            // leave the home
            for (int i = 0; i < 4; i++) {
                if (DAT_BuildingsState::instance.buildings[home].workerID[i] == slot) {
                    for (int j = i; j < 3; j++) {
                        DAT_BuildingsState::instance.buildings[home].workerID[j]
                            = DAT_BuildingsState::instance.buildings[home].workerID[j + 1];
                        DAT_BuildingsState::instance.buildings[home].workerUID[j]
                            = DAT_BuildingsState::instance.buildings[home].workerUID[j + 1];
                    }
                    DAT_BuildingsState::instance.buildings[home].currentEmployeeCount -= 1;
                    DAT_BuildingsState::instance.buildings[home].workerID[3] = 0;
                    DAT_BuildingsState::instance.buildings[home].workerUID[3] = 0;
                    return;
                }
            }
            return;
        }
        DAT_UnitsState::instance.units[slot].state.generic
            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(slot);
    }

}
}
