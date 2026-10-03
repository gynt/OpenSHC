#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005229C0
        void TribesState::addUnitsToTribeAndComputeMovementSpeed(int playerID, int tribeID)
        {
            short sVar1;
            short _minimumSpeed;
            Unit* _pUnit;
            uint _unitID;
            int local_8;
            short _movementSpeed;
            short _maximumSpeed;
            short _targetUnit;
            local_8 = 0;
            _minimumSpeed = 100;
            _maximumSpeed = 0;
            if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                _unitID = 1;
                do {
                    if (((_pUnit->logicalState == OpenSHC::Map::Units::ULS_NORMAL) && (_pUnit->dying == 0))
                        && (_pUnit->ifSelectedThenPlayerID == playerID)) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, this)(
                            _unitID, tribeID);
                        _movementSpeed = _pUnit->movementSpeed;
                        if (_movementSpeed < _minimumSpeed) {
                            _minimumSpeed = _movementSpeed;
                        }
                        if (_maximumSpeed < _movementSpeed) {
                            _maximumSpeed = _movementSpeed;
                        }
                        local_8 = local_8 + _pUnit->healthPercentage;
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 0x248;
                } while ((int)_unitID < (int)DAT_UnitsState::instance.maxUnitCount);
            }
            sVar1 = this->tribes[tribeID].size;
            this->tribes[tribeID].size2Unk = sVar1;
            if (0 < sVar1) {
                _targetUnit = this->tribes[tribeID].selectionTargetUnitID;
                this->tribes[tribeID].facingDirection_1 = DAT_UnitsState::instance.units[_targetUnit].facingDirection;
                this->tribes[tribeID].facingDirection_2 = DAT_UnitsState::instance.units[_targetUnit].facingDirection;
                this->tribes[tribeID].facingDirection_3 = DAT_UnitsState::instance.units[_targetUnit].facingDirection;
                this->tribes[tribeID].field24_0x26 = DAT_UnitsState::instance.units[_targetUnit].movementRunUpTime;
                this->tribes[tribeID].maximumMovementSpeed = _maximumSpeed;
                this->tribes[tribeID].minimumMovementSpeed = _minimumSpeed;
                this->tribes[tribeID].movementSpeed = _minimumSpeed;
                this->tribes[tribeID].field62_0x200 = 0;
                this->tribes[tribeID].field63_0x202 = 0;
                this->tribes[tribeID].field64_0x204 = 0;
                this->tribes[tribeID].field66_0x208 = 0;
                this->tribes[tribeID].field68_0x20c = 0;
                this->tribes[tribeID].unitsHealthPercentage = (short)(local_8 / (int)sVar1);
            }
        }

    }
}
}
