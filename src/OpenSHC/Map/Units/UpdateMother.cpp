#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
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
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00ee1048.hpp"
#include "OpenSHC/Globals/DWORD_00ee104c.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00546BC0
    void Units::UpdateMother()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int owner = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner;
        DAT_GameState::instance.playerDataArray[owner].motherCountThisTick += 1;
        DAT_GameState::instance.playerDataArray[owner].nonInteractiveUnitCountThisTick += 1;
        if (DAT_UnitsState::instance.units[unitID].blockedWaitCounter > 1) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        if (DAT_GameState::instance.playerDataArray[owner].childCountThisTick
                + DAT_GameState::instance.playerDataArray[owner].motherCountThisTick
            > 75) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
        }
        DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
        DAT_UnitsState::instance.units[unitID].ownerColorIndex
            = (int)DAT_UnitsState::instance.units[unitID].fixedRng % 9;
        DAT_UnitsState::instance.units[unitID].health = 60000;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FADE_TRANSITION;
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
                DAT_UnitsState::instance.units[unitID].fadeAlphaStep = 0xff;
                DAT_UnitsState::instance.units[unitID].stateAfterFade
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[unitID].gfxNumber = 1;
                return;
            }
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            int house = DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID;
            if (DAT_BuildingsState::instance.buildings[house].uid
                    != DAT_UnitsState::instance.units[unitID].workplaceBuildingOrTraderUID
                || DAT_BuildingsState::instance.buildings[house].logicalState == 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                return;
            }
            // mothers stay at home when enemies are around
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0) {
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                return;
            }
            switch (SEC_RNG::instance.currentNumber2 % 22) {
            case 0:
            case 1:
            case 2:
                if (house != DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID) {
                    DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = (short)house;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                }
                break;
            case 3:
            case 4:
            case 5: {
                int garden = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::pickARandomBuildingOfType,
                    DAT_BuildingsState::ptr)(owner, OpenSHC::Map::Buildings::BT_GARDEN);
                if (garden != 0
                    && garden
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetID_OR_targetBuildingID) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)garden;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit
                        = (SEC_RNG::instance.currentNumber2 & 3) + 2;
                }
                break;
            }
            case 6: {
                int church = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::pickARandomBuildingIDOfTheseThreeTypes,
                    DAT_BuildingsState::ptr)(owner, OpenSHC::Map::Buildings::BT_CHAPEL,
                    OpenSHC::Map::Buildings::BT_CHURCH, OpenSHC::Map::Buildings::BT_CATHEDRAL);
                if (church != 0
                    && church
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetID_OR_targetBuildingID) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)church;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                }
                break;
            }
            case 7: {
                int entertainment = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::pickARandomBuildingIDOfTheseThreeTypes,
                    DAT_BuildingsState::ptr)(owner, OpenSHC::Map::Buildings::BT_MAYPOLE,
                    OpenSHC::Map::Buildings::BT_STOCKS, OpenSHC::Map::Buildings::BT_GALLOWS);
                if (entertainment != 0
                    && entertainment
                        != DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetID_OR_targetBuildingID) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)entertainment;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION;
                }
                break;
            }
            case 8:
            case 9:
            case 10:
            case 11:
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::computeRandomWanderPath,
                        DAT_UnitsState::ptr)(unitID, 1, 1, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)120;
                }
                break;
            case 12:
            case 13:
            case 14:
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_STAND_UPUnk;
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_MOVE_TO_DESTINATION || state == (UnitState)120) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryY,
                    0);
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
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
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // strolling from garden to garden
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryX,
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID]
                        .buildingEntryY,
                    0);
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                return;
            }
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
            DAT_UnitsState::instance.units[unitID].resourceToDeposit -= 1;
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit <= 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                = (short)MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::findNextBuildingIDForOwnerAndType,
                    DAT_BuildingsState::ptr)(owner, OpenSHC::Map::Buildings::BT_GARDEN,
                    DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID);
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_IDLEUnk;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // fleeing home
            DAT_UnitsState::instance.units[unitID].movementSpeed = 2;
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 1;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x81;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                int house = DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID;
                if (house == 0
                    || DAT_BuildingsState::instance.buildings[house].uid
                        != DAT_UnitsState::instance.units[unitID].workplaceBuildingOrTraderUID) {
                    DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_BuildingsState::instance.buildings[house].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[house].buildingEntryY, 0)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
                unitID = DAT_CurrentUnitSlotID::instance;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // looking for another mother to chat with
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                DAT_UnitsState::instance.units[unitID].targetUnitId = 0;
                for (int i = 1; i < (int)DAT_UnitsState::instance.maxUnitCount; ++i) {
                    if (DAT_UnitsState::instance.units[i].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                        && DAT_UnitsState::instance.units[i].unitType == OpenSHC::Map::Units::UT_MOTHER
                        && DAT_UnitsState::instance.units[i].owner == owner
                        && (DAT_UnitsState::instance.units[i].state.generic
                                == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                            || DAT_UnitsState::instance.units[i].state.generic
                                == OpenSHC::Map::Units::States::US_IDLEUnk)) {
                        DAT_UnitsState::instance.units[i].state.generic
                            = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
                        DAT_UnitsState::instance.units[i].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                        DAT_UnitsState::instance.units[unitID].targetUnitId
                            = (short)i;
                        DAT_UnitsState::instance.units[i].targetUnitId
                            = (short)unitID;
                        break;
                    }
                }
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                if (DAT_UnitsState::instance.units[unitID].targetUnitId == 0) {
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                unitID, DAT_UnitsState::instance.units[unitID].targetUnitId);
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                return;
            }
            int other = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                            .targetUnitId;
            if (DAT_UnitsState::instance.units[other].destinationNeeded
                    == OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET
                && MACRO_CALL_MEMBER(
                       OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(other)
                    != FALSE) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // walking to the other mother
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID,
                    DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[unitID].targetUnitId]
                        .x,
                    DAT_UnitsState::instance
                        .units[DAT_UnitsState::instance.units[unitID].targetUnitId]
                        .y,
                    0);
                unitID = DAT_CurrentUnitSlotID::instance;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByAmount, DAT_UnitsState::ptr)(
                    unitID, 1);
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0) {
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            int other = DAT_UnitsState::instance.units[unitID]
                              .targetUnitId;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y,
                DAT_UnitsState::instance.units[other].x, DAT_UnitsState::instance.units[other].y);
            if (DAT_DirectionAlgorithmState::instance.distanceHigh <= 1) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            DAT_UnitsState::instance.units[other].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // chatting
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 1;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::setUnitFacingDirectionTowardsTarget, DAT_UnitsState::ptr)(
                unitID, DAT_UnitsState::instance.units[unitID].targetUnitId);
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker > 500) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // rocking the baby
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animMotherWithBaby[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame == 2
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                if ((SEC_RNG::instance.currentNumber2 & 1) != 0 && timeGetTime() - DWORD_00ee104c::instance > 8000) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_BABY);
                    DWORD_00ee104c::instance = timeGetTime();
                }
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame + 0x100;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (DAT_GameState::instance.playerDataArray[owner].sumOfTotalEnemyUnitsCount != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                    return;
                }
            } else if (DAT_GameState::instance.playerDataArray[owner].noEnemyThreatSkirmish == 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)2;
                return;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            }
            return;
        }
        if (state == (UnitState)2) {
            // frightened
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animMotherScream[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x110;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            if (timeGetTime() - DWORD_00ee1048::instance > 5000) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_GIRL_SCREAM);
                DWORD_00ee1048::instance = timeGetTime();
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
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
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = DAT_UnitsState::instance.units[unitID].stateAfterFade;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeAlphaStep != 0
                && DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].isFadeActive = 0;
            }
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::isUnitInDeathState,
                DAT_UnitsState::ptr)(unitID)
            != FALSE) {
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 32) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            int house = DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID;
            if (house != 0
                && DAT_BuildingsState::instance.buildings[house].uid
                    == DAT_UnitsState::instance.units[unitID].workplaceBuildingOrTraderUID) {
                DAT_BuildingsState::instance.buildings[house].unitRefID = 0;
            }
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
