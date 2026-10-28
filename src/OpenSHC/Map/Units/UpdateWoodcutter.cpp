#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitAnimationFinished.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0054C710
    void Units::UpdateWoodcutter()
    {
        int unitID = DAT_CurrentUnitSlotID::instance;
        int tree = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceTileOrTreeID;
        int woodcuttersHut = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID;
        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].unitTypeSpecificRestingState = 10;
        UnitStateShort state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk) {
            DAT_UnitsState::instance.units[unitID].gfxNumber = 0x3d8;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            if (DAT_UnitsState::instance.units[unitID].isFadeActive != 0) {
                DAT_UnitsState::instance.units[unitID].fadeLevel -= 1;
                if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel >= 0) {
                    return;
                }
                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                DAT_UnitsState::instance.units[unitID].isFadeActive = 0;
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].goToRallyPoint != 0) {
                DAT_UnitsState::instance.units[unitID].goToRallyPoint = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)9;
                DAT_UnitsState::instance.units[unitID].destinationNeeded
                    = (OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum)2;
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber += 1;
            if (DAT_UnitsState::instance.units[unitID].animationCycleNumber < 10) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID,
                    DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID]
                        .uid,
                    OpenSHC::Game::Resources::RT_LOGS)
                >= 3) {
                // enough logs to saw planks
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(
                    unitID);
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
                DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
                return;
            }
            int newTree = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::findTree, DAT_LandscapeState::ptr)(
                DAT_UnitsState::instance.units[unitID].owner, DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y);
            if (newTree != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceTileOrTreeID
                    = (short)newTree;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workTargetUID
                    = DAT_LandscapeState::instance.trees[newTree].uid;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findClosestReachableNeighborOfTarget,
                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    (short)DAT_LandscapeState::instance.trees[newTree].xPosition,
                    (short)DAT_LandscapeState::instance.trees[newTree].yPosition);
                if (DAT_PathFindingState::instance.climbX
                        == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x
                    && DAT_PathFindingState::instance.climbY
                        == DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance);
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, DAT_PathFindingState::instance.climbX,
                        DAT_PathFindingState::instance.climbY, 0)
                    != FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_IDLEUnk;
                    DAT_BuildingsState::instance
                        .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                .workplaceOrHomeBuildingID]
                        .woodcutterTreePathLength
                        = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].totalSizeOfPathPlan;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)10;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)10;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_IDLEUnk) {
            // walking to the tree
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                if (DAT_UnitsState::instance.units[unitID].unitOrderWhenOnSameTile != 0) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                              findNeighbourTileThatCanServeAsClimbPointClosestToXY,
                            DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                            DAT_UnitsState::instance.units[unitID].y,
                            (short)DAT_LandscapeState::instance.trees[tree].xPosition,
                            (short)DAT_LandscapeState::instance.trees[tree].yPosition)
                            != 0
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                               DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance,
                               DAT_PathFindingState::instance.climbX, DAT_PathFindingState::instance.climbY, 0)
                            != FALSE) {
                        // another woodcutter stands on this tile
                        unitID = DAT_CurrentUnitSlotID::instance;
                        DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_IDLEUnk;
                    } else {
                        unitID = DAT_CurrentUnitSlotID::instance;
                        DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)9;
                        DAT_UnitsState::instance.units[unitID].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    }
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAliveAndMatchingUID,
                               DAT_LandscapeState::ptr)(tree, DAT_UnitsState::instance.units[unitID].workTargetUID)
                    != FALSE) {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)2;
                    DAT_UnitsState::instance.units[unitID].woodCutterChopsCount = 0;
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAdult, DAT_LandscapeState::ptr)(
                               tree, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workTargetUID)
                    != FALSE) {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)3;
                    DAT_UnitsState::instance.units[unitID].woodCutterChopsCount = 0;
                } else {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                }
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            return;
        }
        if (state == (UnitState)2) {
            // felling the tree
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y, (short)DAT_LandscapeState::instance.trees[tree].xPosition,
                (short)DAT_LandscapeState::instance.trees[tree].yPosition);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            DAT_DirectionAlgorithmState::instance.orientation += 2;
            if (DAT_DirectionAlgorithmState::instance.orientation >= 8) {
                DAT_DirectionAlgorithmState::instance.orientation -= 8;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames.animWoodcutterFellTree
                      [DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber];
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame == 12
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                        .animationCycleNumberHasJustIncremented
                    != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_CHOP);
            }
            if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame <= 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame = 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                    = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                          .facingDirectionMapOrientationCorrected
                    + 0x359;
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::LandscapeState_Func::isTreeAliveAndMatchingUID, DAT_LandscapeState::ptr)(
                        tree, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workTargetUID)
                    != FALSE) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::damageTreeAndTriggerDeathIfDepleted,
                            DAT_LandscapeState::ptr)(
                            tree, -1, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workTargetUID)
                        == 0) {
                        return;
                    }
                    if (DAT_LandscapeState::instance.trees[tree].stage <= 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            OpenSHC::DE::SHCDE::FX_LILTREE_FALL);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                            OpenSHC::DE::SHCDE::FX_TREE_FALL);
                    }
                } else if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAdult, DAT_LandscapeState::ptr)(
                               tree, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workTargetUID)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)3;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].woodCutterChopsCount = 0;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].gfxNumber
                = DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].facingDirectionMapOrientationCorrected
                + 0x2f9 + DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationFrame * 8;
            return;
        }
        if (state == (UnitState)3) {
            // chopping the fallen tree
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculateOrientation,
                DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y, (short)DAT_LandscapeState::instance.trees[tree].xPosition,
                (short)DAT_LandscapeState::instance.trees[tree].yPosition);
            if (DAT_DirectionAlgorithmState::instance.orientation == 15) {
                DAT_DirectionAlgorithmState::instance.orientation = 4;
            }
            unitID = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[unitID].facingDirection
                = (short)DAT_DirectionAlgorithmState::instance.orientation;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (DAT_UnitsState::instance.units[unitID].woodCutterChopsCount == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterCutTrunkFirst[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterCutTrunk[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame == 7
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_CHOP);
                unitID = DAT_CurrentUnitSlotID::instance;
            }
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame = 1;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x3b1;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::isTreeAdult, DAT_LandscapeState::ptr)(
                        tree, DAT_UnitsState::instance.units[unitID].workTargetUID)
                    == FALSE) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].woodCutterChopsCount += 1;
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].woodCutterChopsCount <= 3) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::advanceTreeDecayState, DAT_LandscapeState::ptr)(
                    tree, DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workTargetUID);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                        DAT_UnitsState::ptr)(DAT_CurrentUnitSlotID::instance, 1)
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetX_2,
                        DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetY_2, 0);
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk;
                    return;
                }
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                    = OpenSHC::Map::Units::ULS_REMOVE;
                return;
            }
            DAT_UnitsState::instance.units[unitID].gfxNumber
                = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x359
                + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
            // carrying the logs to the hut
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                != FALSE) {
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 10;
                DAT_UnitsState::instance.units[unitID].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID,
                    DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID]
                        .uid,
                    OpenSHC::Game::Resources::RT_LOGS, 1, 3, 1);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y, OpenSHC::DE::SHCDE::FX_DROP_LOG);
                unitID = DAT_CurrentUnitSlotID::instance;
            }
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x101;
            if (DAT_UnitsState::instance.units[unitID].movementRunUpTime != 0) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x181;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
            // the planks are sawn
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID, 1)
                == 0) {
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID,
                DAT_BuildingsState::instance
                    .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID]
                    .uid,
                OpenSHC::Game::Resources::RT_WOOD, 1, 3, 1);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
            // sawing
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 48) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID, 3);
                return;
            }
            int hut = DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID;
            int hutUID = DAT_BuildingsState::instance.buildings[hut].uid;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                    DAT_BuildingsState::ptr)(hut, hutUID, OpenSHC::Game::Resources::RT_LOGS)
                > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                    DAT_BuildingsState::ptr)(hut, hutUID, OpenSHC::Game::Resources::RT_LOGS, -1, 3, 1);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID, 2);
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                    = OpenSHC::Map::Units::States::US_AIM_WEAPONUnk;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                DAT_BuildingsState::ptr)(hut, hutUID, OpenSHC::Game::Resources::RT_WOOD, -3, 0, 1);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateWorkshopProgressSign,
                DAT_BuildingsState::ptr)(
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceOrHomeBuildingID, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resetUnitMovementState, DAT_UnitsState::ptr)(
                DAT_CurrentUnitSlotID::instance);
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                = OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk;
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
            // leaving the hut with the planks
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x201;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].busyThisTick = 1;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker <= 20) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            int stockpile
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(
                    OpenSHC::Game::Resources::RT_WOOD, 1, DAT_UnitsState::instance.units[unitID].owner);
            if (stockpile == 0
                && DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL(OpenSHC::Map::Units_Func::PlayStockpileIsFullWarning)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                    DAT_BuildingsState::ptr)(stockpile, 1)
                == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    DAT_CurrentUnitSlotID::instance, DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0)
                == FALSE) {
                return;
            }
            unitID = DAT_CurrentUnitSlotID::instance;
            DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID = (short)stockpile;
            DAT_UnitsState::instance.units[unitID].targetUID = DAT_BuildingsState::instance.buildings[stockpile].uid;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_STAND_UPUnk;
            DAT_UnitsState::instance.units[unitID].resourceToDeposit
                = (short)MACRO_CALL(OpenSHC::Map::Units_Func::ComputeGoodsProduced)(unitID, 12, TRUE);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_STAND_UPUnk) {
            // carrying the planks to the stockpile
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x201;
            if (DAT_UnitsState::instance.units[unitID].movementRunUpTime != 0) {
                DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 0x281;
            }
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker < 5) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker = 0;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::canBuildingStoreTheAmount,
                    DAT_BuildingsState::ptr)(DAT_UnitsState::instance.units[unitID].targetID_OR_targetBuildingID,
                    OpenSHC::Game::Resources::RT_WOOD, 48)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, DAT_BuildingsState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID,
                    OpenSHC::Game::Resources::RT_WOOD, 1, 48, 1);
                DAT_GameSynchronyState::instance.finalResults
                    .finalWoodProduced[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner] += 1;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit -= 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].x,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].y,
                    OpenSHC::DE::SHCDE::FX_STOCK_WOOD);
            } else {
                int stockpile = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingThatCanStoreThisResource,
                    DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1,
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner);
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                        DAT_BuildingsState::ptr)(stockpile, 1)
                    != 0) {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetID_OR_targetBuildingID
                        = (short)stockpile;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].targetUID
                        = DAT_BuildingsState::instance.buildings[stockpile].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        DAT_CurrentUnitSlotID::instance,
                        DAT_BuildingsState::instance.buildings[stockpile].buildingEntryX,
                        DAT_BuildingsState::instance.buildings[stockpile].buildingEntryY, 0);
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].resourceToDeposit = 0;
                }
            }
            unitID = DAT_CurrentUnitSlotID::instance;
            if (DAT_UnitsState::instance.units[unitID].resourceToDeposit > 0) {
                return;
            }
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, TRUE);
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setWorkplaceBuildingEntryAsTarget,
                    DAT_UnitsState::ptr)(unitID, 1)
                != 0) {
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic = (UnitState)9;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].destinationNeeded
                    = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].animationSheetFrameOffset = 1;
                return;
            }
            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].logicalState
                = OpenSHC::Map::Units::ULS_REMOVE;
            return;
        }
        if (state == (UnitState)9) {
            // walking to the hut
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::IncrementAndOptionalUpdateAVValueRelated)(unitID, FALSE);
            if (DAT_UnitsState::instance.units[unitID].destinationNeeded
                != OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET) {
                if (MACRO_CALL(OpenSHC::Map::Units_Func::UpdateWorker_ConsiderTakingFearFactorBreak)(unitID) != FALSE) {
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                        unitID, DAT_UnitsState::instance.units[unitID].targetX_2,
                        DAT_UnitsState::instance.units[unitID].targetY_2, 0)
                    != FALSE) {
                    unitID = DAT_CurrentUnitSlotID::instance;
                    DAT_UnitsState::instance.units[unitID].destinationNeeded
                        = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_HAS_BEEN_SET;
                } else {
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].state.generic
                        = OpenSHC::Map::Units::States::US_DISAPPEAR;
                    DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].updateTickTracker = 0;
                    return;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination, DAT_UnitsState::ptr)(
                    unitID)
                == FALSE) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 10;
            DAT_UnitsState::instance.units[unitID].substate = (DAT_GameCore::instance.mapTimeInTicks & 1) + 2;
            DAT_UnitsState::instance.units[unitID].state.generic = (UnitState)10;
            return;
        }
        if (state == (UnitState)121) {
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0x10;
            MACRO_CALL(OpenSHC::Map::Units_Func::SetRestingForUnit)(unitID);
            return;
        }
        if (state == (UnitState)10) {
            // idling in the hut
            DAT_UnitsState::instance.units[unitID].animationSpeed = 2;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].faceViewer = 1;
            DAT_UnitsState::instance.units[unitID].busyThisTick = 1;
            if (DAT_UnitsState::instance.units[unitID].substate == 0) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime0[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 1) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime1[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 2) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime2[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 3) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime3[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 4) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime4[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 5) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime5[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            } else if (DAT_UnitsState::instance.units[unitID].substate == 6) {
                DAT_UnitsState::instance.units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                          .animWoodcutterFreetime6[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            }
            int idle;
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x3d8;
                DAT_UnitAnimationFinished::instance = 1;
                idle = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x3c0;
                idle = DAT_UnitAnimationFinished::instance;
            }
            if (MACRO_CALL(OpenSHC::Map::Units_Func::SetStateToFreetimeWalking)(unitID, idle, 7) != 0) {
                return;
            }
            if (idle == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].substate += 1;
            if (DAT_UnitsState::instance.units[unitID].substate >= 7) {
                DAT_UnitsState::instance.units[unitID].substate = 0;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            DAT_UnitsState::instance.units[unitID].state.generic
                = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
            return;
        }
        if (state == (UnitState)0x6c) {
            DAT_UnitsState::instance.units[unitID].stateBasedSpeed = 0;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationSheetFrameOffset = 1;
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
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x3f0;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x3d8;
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
                DAT_UnitsState::instance.units[unitID].gfxNumber = 0x408;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].animationFrame + 0x3f0;
            }
            if (DAT_UnitAnimationFinished::instance != 0) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            return;
        }
        state = DAT_UnitsState::instance.units[unitID].state.generic;
        if (state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
            DAT_UnitsState::instance.units[unitID].animationSpeed = 3;
            DAT_UnitsState::instance.units[unitID].field_0x30_animRelated = 0;
            DAT_UnitsState::instance.units[unitID].animationFrame
                = (char)DAT_UnitPropertiesDefinedData::instance.animationFrames
                      .animWoodcutterMelee[DAT_UnitsState::instance.units[unitID].animationCycleNumber];
            if (DAT_UnitsState::instance.units[unitID].animationFrame <= 0) {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x361;
                DAT_UnitAnimationFinished::instance = 1;
            } else {
                DAT_UnitsState::instance.units[unitID].gfxNumber
                    = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected + 0x359
                    + DAT_UnitsState::instance.units[unitID].animationFrame * 8;
            }
            if (DAT_UnitsState::instance.units[unitID].meleeOpponentUnitID != 0
                && DAT_UnitsState::instance.units[unitID].animationCycleNumberHasJustIncremented != FALSE
                && DAT_UnitsState::instance.units[unitID].animationCycleNumber == 5) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y,
                    OpenSHC::DE::SHCDE::FX_SWISH);
                unitID = DAT_CurrentUnitSlotID::instance;
            }
            if (DAT_UnitAnimationFinished::instance == 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::resumeMovementIfNoAttackTarget,
                DAT_UnitsState::ptr)(unitID);
            return;
        }
        if (state == OpenSHC::Map::Units::States::US_DISAPPEAR) {
            DAT_UnitsState::instance.units[unitID].fadeLevel += 1;
            if ((char)DAT_UnitsState::instance.units[unitID].fadeLevel > 32) {
                DAT_UnitsState::instance.units[unitID].fadeLevel = 32;
            }
            DAT_UnitsState::instance.units[unitID].updateTickTracker += 1;
            if (DAT_UnitsState::instance.units[unitID].updateTickTracker > 32) {
                DAT_BuildingsState::instance.buildings[woodcuttersHut].aiAbandonCounter += 10;
                DAT_UnitsState::instance.units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                if (DAT_UnitsState::instance.units[unitID].isDisbanded == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::setLastEncounteredTroopUnit,
                        DAT_GameState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitID);
                    unitID = DAT_CurrentUnitSlotID::instance;
                }
            }
            DAT_BuildingsState::instance.buildings[DAT_UnitsState::instance.units[unitID].workplaceOrHomeBuildingID]
                .aiRestaffCountdown = 4000;
            return;
        }
        DAT_UnitsState::instance.units[unitID].state.generic
            = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState,
            DAT_UnitsState::ptr)(unitID);
    }

}
}
