#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00578C40
        undefined4 UnitsState::processUnitMove(int unitID, int speedCategory)
        {
            if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_BURNINGMAN) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN
                    && (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_ASSASSIN_THROWING_HOOK
                        || this->units[unitID].state.generic
                            == OpenSHC::Map::Units::States::US_ASSASSIN_START_CLIMBING_DOWN
                        || this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_UP
                        || this->units[unitID].state.generic
                            == OpenSHC::Map::Units::States::US_ASSASSIN_CLIMBING_DOWN)) {
                    return 0;
                }
                if (this->units[unitID].dying != 0) {
                    return 0;
                }
            }
            if (this->units[unitID].movementState == 5) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(
                    unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
                this->units[unitID].faceViewer = 0;
                return 0;
            }
            if (this->units[unitID].movementState != 4 && this->units[unitID].movementState != 2) {
                this->units[unitID].subTileStepProgress = 8;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
                if (this->units[unitID].climbDataID != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateClimbing, this)(unitID) == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                        unitID, this->units[unitID].savedDestinationX, this->units[unitID].savedDestinationY, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
                }
                return 0;
            }
            this->units[unitID].faceViewer = 0;
            if (this->units[unitID].moveInstructionSpeedDelayTracker != 0) {
                this->units[unitID].moveInstructionSpeedDelayTracker
                    = this->units[unitID].moveInstructionSpeedDelayTracker - 1;
            }
            if (this->units[unitID].moveDelay > 1) {
                this->units[unitID].moveDelay = this->units[unitID].moveDelay - 2;
            } else {
                this->units[unitID].moveDelay = 0;
            }
            speedCategory += this->units[unitID].pendingMeleeEngage;
            for (int _step = 0; _step <= speedCategory; ++_step) {
                if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].hopGaitMode == '\x01') {
                    if (this->units[DAT_CurrentUnitSlotID::instance].animCycle16 <= 3
                        || this->units[DAT_CurrentUnitSlotID::instance].animCycle16 >= 0xc) {
                        continue;
                    }
                } else if (DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].hopGaitMode == '\x02') {
                    if (this->units[DAT_CurrentUnitSlotID::instance].animCycle16 <= 4) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].animCycle16 >= 10) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].animCycle16 >= 0xc) {
                            this->units[DAT_CurrentUnitSlotID::instance].animCycle16 = 3;
                        }
                        continue;
                    }
                }
                this->units[unitID].pendingPositionValid = 0;
                this->units[unitID].subTileStepProgress = this->units[unitID].subTileStepProgress + 1;
                if (this->units[unitID].subTileStepProgress >= 8) {
                    short _pathIndex = this->units[unitID].currentIndexInPathPlan;
                    if (_pathIndex >= this->units[unitID].totalSizeOfPathPlan
                        && this->units[unitID].blockedWaitCounter == 0) {
                        this->units[unitID].unknownMovementRelated_0x2d2 = 0;
                        this->units[unitID].movementState = 0;
                        this->units[unitID].subTileStepProgress = 8;
                        this->units[unitID].savedDestinationX = this->units[unitID].x;
                        this->units[unitID].savedDestinationY = this->units[unitID].y;
                        return 0;
                    }
                    this->units[unitID].subTileStepProgress = 0;
                    uint _direction = (char)this->units[unitID].pathPlanStart[_pathIndex / 2];
                    if ((_pathIndex & 1) != 0) {
                        _direction = (int)_direction >> 4;
                    } else {
                        _direction = _direction & 0xf;
                    }
                    this->units[unitID].facingDirection = (short)_direction;
                    if (this->units[unitID].blockedWaitCounter == 0) {
                        this->units[unitID].currentIndexInPathPlan = _pathIndex + 1;
                    }
                    if (this->units[unitID].pendingMeleeEngage != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::saveUnitStateBeforeInterruption, this)(
                            unitID);
                        this->units[unitID].subTileStepProgress = 8;
                        this->units[unitID].lookForEnemy = 0;
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MELEE_ATTACK;
                        this->units[unitID].SA = 0;
                        this->units[unitID].animationCycleNumber = 0;
                        return 0;
                    }
                    if (this->units[unitID].moveRelatedFlag != 1) {
                        if (this->units[unitID].blockedWaitCounter != 0
                            || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::doMoveFromTileToTile,
                                   DAT_PathFindingState::ptr)(unitID, this->units[unitID].tile, this->units[unitID].y,
                                   _direction, this->units[unitID].moveRelatedFlag, this->units[unitID].cannotClimb)
                                == FALSE) {
                            this->units[unitID].subTileStepProgress = 8;
                            if (this->units[unitID].blockedWaitCounter > 0) {
                                this->units[unitID].blockedWaitCounter = this->units[unitID].blockedWaitCounter - 1;
                                if (this->units[unitID].blockedWaitCounter > 0) {
                                    return 0;
                                }
                            }
                            this->blockedMoveGiveUpCount = this->blockedMoveGiveUpCount + 1;
                            int _destinationY = this->units[unitID].destinationYPosition;
                            int _destinationX = this->units[unitID].destinationXPosition;
                            bool _destinationReachable = false;
                            if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                    DAT_ViewportRenderState::ptr)(_destinationX, _destinationY)
                                == FALSE) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                      makeUnitStopWalkingByClearingPathProgressState,
                                    this)(unitID);
                            } else if ((short)DAT_TileMapState::instance
                                           .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                                    .translationMatrix[_destinationY]
                                                                    .addXgetTile
                                               + _destinationX]
                                != 0) {
                                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                          calculateCanPlayerUnitsNavigateToAreaFromArea,
                                        DAT_PathFindingState::ptr)(this->units[unitID].owner,
                                        (short)DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile],
                                        (short)DAT_TileMapState::instance
                                            .PathConnectionLayer[DAT_ViewportRenderState::instance
                                                                     .translationMatrix[_destinationY]
                                                                     .addXgetTile
                                                + _destinationX],
                                        0)
                                    != 0) {
                                    _destinationReachable = true;
                                }
                            }
                            if (!_destinationReachable) {
                                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                                    return 0;
                                }
                                if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                                    return 0;
                                }
                                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_CAGEDOG) {
                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                          makeUnitStopWalkingByClearingPathProgressState,
                                        this)(unitID);
                                    return 0;
                                }
                                if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_DISAPPEAR) {
                                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                                    this->units[unitID].updateTickTracker = 0;
                                    return 0;
                                }
                            }
                            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit,
                                    &DAT_UnitsState::instance)(
                                    DAT_CurrentUnitSlotID::instance, this->units[unitID].destinationXPosition,
                                    this->units[unitID].destinationYPosition, 0)
                                == FALSE) {
                                this->units[unitID].blockedWaitCounter = 0x28;
                                return 0;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(
                                unitID);
                            return 0;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::spawnCrowFromNearbyTree,
                            DAT_LandscapeState::ptr)(unitID);
                    }
                    this->units[unitID].moveFromTile = this->units[unitID].tile;
                    this->units[unitID].moveToTile
                        = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][_direction]
                        + this->units[unitID].tile;
                    this->units[unitID].mimicCurrentXPosition
                        = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.xOffset
                        + this->units[unitID].x;
                    this->units[unitID].mimicCurrentYPosition
                        = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.yOffset
                        + this->units[unitID].y;
                    this->units[unitID].microXPosition = this->units[unitID].x * 8 + 4;
                    this->units[unitID].microYPosition = this->units[unitID].y * 8 + 4;
                } else {
                    if (this->units[unitID].subTileStepProgress
                        >= DAT_UnitPropertiesDefinedData::instance
                               .moveStepCommitThreshold[this->units[unitID].facingDirection]) {
                        this->units[unitID].pendingPositionValid = 1;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(
                    unitID);
                switch (this->units[unitID].facingDirection) {
                case 0:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition - 1;
                    break;
                case 1:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition - 1;
                case 2:
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition + 1;
                    break;
                case 3:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition + 1;
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition + 1;
                    break;
                case 4:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition + 1;
                    break;
                case 5:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition + 1;
                case 6:
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition - 1;
                    break;
                case 7:
                    this->units[unitID].microYPosition = this->units[unitID].microYPosition - 1;
                    this->units[unitID].microXPosition = this->units[unitID].microXPosition - 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(unitID);
                if (this->units[unitID].pendingPositionValid != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(unitID);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processDamageFromKillingPit,
                        DAT_BuildingsState::ptr)(unitID);
                    int _buildingID
                        = DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile];
                    if (_buildingID != 0) {
                        int _buildingType = DAT_BuildingsState::instance.buildings[_buildingID].buildingType;
                        if (_buildingType == OpenSHC::Map::Buildings::BT_TOWER1
                            || _buildingType == OpenSHC::Map::Buildings::BT_TOWER4) {
                            DAT_BuildingsState::instance.buildings[_buildingID].hasUnitsOntop = 1;
                            DAT_BuildingsState::instance.buildings[_buildingID].unitsOnTopRecheckCountdown = 100;
                        }
                    }
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::
                            adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection,
                        this)(unitID);
                }
                this->units[unitID].pendingPositionValid = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateUnitFadeAndVisibilityNearStructures,
                    &DAT_UnitsState::instance)(unitID);
            }
            return 1;
        }

    }
}
}
