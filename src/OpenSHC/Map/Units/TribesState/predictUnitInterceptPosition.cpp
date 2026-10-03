#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521500
        void TribesState::predictUnitInterceptPosition(
            int targetUnitID, int unitID, int* unitCurrentX, int* unitCurrentY)
        {
            UnitTypeShort UVar1;
            uint _xOff_2;
            uint _yOff_2;
            int _yOff_2b;
            uint _pathPlanPair;
            uint _xOff;
            uint _yOff;
            int _yOffb;
            int _tribeMinSpeedBounded;
            int iVar2;
            int _xOff_2b;
            int iVar3;
            int _targetTribeMinSpeedBounded;
            int iVar4;
            uint _currentIndexInPathPlan;
            int _unitAddressOffset;
            int local_8;
            int _unitCurrentX_2;
            short _targetTribeMinSpeed;
            short _tribeMinSpeed;
            int _unitID;
            _unitID = unitID;
            _unitAddressOffset = unitID * 0x490;
            *unitCurrentX = (int)DAT_UnitsState::instance.units[unitID].x;
            _yOffb = (int)DAT_UnitsState::instance.units[unitID].y;
            *unitCurrentY = _yOffb;
            if (DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging != 2) {}
            _targetTribeMinSpeed
                = this->tribes[DAT_UnitsState::instance.units[targetUnitID].tribeID].minimumMovementSpeed;
            _targetTribeMinSpeedBounded = (int)_targetTribeMinSpeed;
            if (_targetTribeMinSpeed < 2) {
                _targetTribeMinSpeedBounded = 1;
            }
            _tribeMinSpeed = this->tribes[DAT_UnitsState::instance.units[unitID].tribeID].minimumMovementSpeed;
            iVar3 = _targetTribeMinSpeedBounded * 4;
            _tribeMinSpeedBounded = (int)_tribeMinSpeed;
            if (_tribeMinSpeed < 2) {
                _tribeMinSpeedBounded = 1;
            }
            iVar4 = (int)DAT_UnitsState::instance.units[targetUnitID].x;
            iVar2 = (int)DAT_UnitsState::instance.units[targetUnitID].y;
            if (DAT_UnitsState::instance.units[targetUnitID].stateBasedSpeed < 1) {
                UVar1 = DAT_UnitsState::instance.units[targetUnitID].unitType;
                if ((UVar1 == OpenSHC::Map::Units::UT_E_KNIGHT)
                    && (DAT_UnitsState::instance.units[targetUnitID].isMatchingSpeed == false)) {
                    iVar3 = iVar3 / 3;
                } else if (UVar1 == OpenSHC::Map::Units::UT_E_SWORD)
                    goto LAB_005215e9;
            } else {
            LAB_005215e9:
                iVar3 = iVar3 / 2;
            }
            if (DAT_UnitsState::instance.units[unitID].stateBasedSpeed < 1) {
                UVar1 = DAT_UnitsState::instance.units[unitID].unitType;
                if ((UVar1 == OpenSHC::Map::Units::UT_E_KNIGHT)
                    && (DAT_UnitsState::instance.units[unitID].isMatchingSpeed == false)) {
                    unitID = iVar3 / 3;
                    goto LAB_0052163b;
                }
                unitID = iVar3;
                if (UVar1 != OpenSHC::Map::Units::UT_E_SWORD)
                    goto LAB_0052163b;
            }
            /*
              reused parameter!
             */
            unitID = iVar3 / 2;
        LAB_0052163b:
            _unitCurrentX_2 = *unitCurrentX;
            _xOff_2 = _unitCurrentX_2 - iVar4;
            _yOff_2 = _yOffb - iVar2;
            _xOff_2b = (_xOff_2 ^ (int)_xOff_2 >> 0x1f) - ((int)_xOff_2 >> 0x1f);
            _yOff_2b = (_yOff_2 ^ (int)_yOff_2 >> 0x1f) - ((int)_yOff_2 >> 0x1f);
            if (_yOff_2b < _xOff_2b) {
                _yOff_2b = _xOff_2b;
            }
            if ((-1 < (_yOff_2b + -2) * unitID)
                && (_currentIndexInPathPlan = (uint)DAT_UnitsState::instance.units[_unitID].currentIndexInPathPlan,
                    local_8 = _tribeMinSpeedBounded * 4,
                    (int)_currentIndexInPathPlan < (int)DAT_UnitsState::instance.units[_unitID].totalSizeOfPathPlan)) {
                do {
                    /*
                      get current value in pathPlan, each byte contains two move instructions
                     */
                    _pathPlanPair = (uint) * (char*)((int)_currentIndexInPathPlan / 2 + 0x138864a + _unitAddressOffset);
                    if ((_currentIndexInPathPlan & 1) == 0) {
                        /*
                          if index is even, retain the lowest 4 bits
                         */
                        _pathPlanPair = _pathPlanPair & 0xf;
                    } else {
                        /*
                          if index is odd retain the highest 4 bits
                         */
                        _pathPlanPair = (int)_pathPlanPair >> 4;
                    }
                    *unitCurrentX
                        = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_pathPlanPair].int_.xOffset
                        + _unitCurrentX_2;
                    *unitCurrentY = *unitCurrentY
                        + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix
                            + _pathPlanPair * 8 + 4);
                    _unitCurrentX_2 = *unitCurrentX;
                    _xOff = _unitCurrentX_2 - iVar4;
                    _yOff = *unitCurrentY - iVar2;
                    iVar3 = (_xOff ^ (int)_xOff >> 0x1f) - ((int)_xOff >> 0x1f);
                    _yOffb = (_yOff ^ (int)_yOff >> 0x1f) - ((int)_yOff >> 0x1f);
                    if (_yOffb < iVar3) {
                        _yOffb = iVar3;
                    }
                    if ((_yOffb + -2) * unitID < local_8) {}
                    local_8 = local_8 + _tribeMinSpeedBounded * 4;
                    _currentIndexInPathPlan = _currentIndexInPathPlan + 1;
                } while (
                    (int)_currentIndexInPathPlan < (int)DAT_UnitsState::instance.units[_unitID].totalSizeOfPathPlan);
            }
        }

    }
}
}
