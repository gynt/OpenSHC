#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          called when pathfinding with walls   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4930
        int PathFindingState::setClimbBasedOnClosestClimbData(int unitID, int ladderWallGroup, int ladderArea)
        {
            int iVar1;
            int fromXPosition;
            int _downOrUp1;
            int _climbDataID;
            int _climbData2;
            int _minDistance;
            int _downOrUp;
            int _distance;
            _minDistance = 1000;
            _climbData2 = 0;
            _downOrUp = 0;
            if (this->areaSearchLadderPass == 0) {
                return 200;
            }
            for (int i = 1; i < this->maxClimbDataCount; i = i + 1) {
                if ((this->climbData[i].canBeUsed == 1) && (this->climbData[i].isRecognizedByPathfinding != 0)) {
                    iVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::checkUnitHasPropertyBasedOnUnitType,
                        DAT_UnitsState::ptr)(unitID, this->climbData[i].type);
                    if ((iVar1 != 0) && (this->climbData[i].type == 1)) {
                        if (this->climbData[i].area == ladderWallGroup) {
                            _downOrUp1 = 0;
                            if (this->climbData[i].topArea != ladderArea) {
                                continue;
                            }
                            iVar1 = this->climbData[i].bottomYPosition;
                            fromXPosition = this->climbData[i].bottomXPosition;
                        } else {
                            if (this->climbData[i].area != ladderArea) {
                                continue;
                            }
                            _downOrUp1 = 1;
                            if (this->climbData[i].topArea != ladderWallGroup) {
                                continue;
                            }
                            iVar1 = this->climbData[i].topYPosition;
                            fromXPosition = this->climbData[i].topXPosition;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                            (int)(DAT_UnitsState::instance.units[unitID].y), fromXPosition, iVar1);
                        _distance = DAT_DirectionAlgorithmState::instance.distanceHigh
                            + this->climbData[i].numberOfUnitsUsing * 8;
                        if (_distance < _minDistance) {
                            _minDistance = _distance;
                            _climbData2 = i;
                            _downOrUp = _downOrUp1;
                            if (_downOrUp1 == 0) {
                                this->climbX = this->climbData[i].bottomXPosition;
                                this->climbY = this->climbData[i].bottomYPosition;
                            } else {
                                this->climbX = this->climbData[i].topXPosition;
                                this->climbY = this->climbData[i].topYPosition;
                            }
                        }
                    }
                }
            }
            DAT_UnitsState::instance.units[unitID].climbDirection = (short)_downOrUp;
            if (_climbData2 == 0) {
                for (_climbDataID = 1; _climbDataID < 200; _climbDataID = _climbDataID + 1) {
                    if ((this->climbData[_climbDataID].canBeUsed == 1)
                        && (this->climbData[_climbDataID].isRecognizedByPathfinding != 0)) {
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::checkUnitHasPropertyBasedOnUnitType,
                            DAT_UnitsState::ptr)(unitID, this->climbData[_climbDataID].type);
                        if ((iVar1 != 0) && (0 < this->climbData[_climbDataID].buildingArea)) {
                            if (this->climbData[_climbDataID].area == ladderArea) {
                                this->climbX = this->climbData[_climbDataID].bottomXPosition;
                                this->climbY = this->climbData[_climbDataID].bottomYPosition;
                                return _climbDataID;
                            }
                            if (this->climbData[_climbDataID].topArea == ladderArea) {
                                this->climbX = this->climbData[_climbDataID].topXPosition;
                                this->climbY = this->climbData[_climbDataID].topYPosition;
                                return _climbDataID;
                            }
                        }
                    }
                }
            }
            return _climbData2;
        }
    }
}
}
