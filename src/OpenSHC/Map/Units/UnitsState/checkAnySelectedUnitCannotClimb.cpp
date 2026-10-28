#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536970
        undefined4 UnitsState::allSelectedUnitsCanClimbLadders()
        {
            int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            int _unitID;
            for (_unitID = 1, DAT_CurrentUnitSlotID::instance = _unitID; _unitID < (int)this->maxUnitCount;
                _unitID = _unitID + 1, DAT_CurrentUnitSlotID::instance = _unitID) {
                if (this->units[_unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[_unitID].dying != 0) {
                    continue;
                }
                if (this->units[_unitID].isSelected == 0) {
                    continue;
                }
                if (this->units[_unitID].owner != _currentPlayerSlotID) {
                    return 0;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::checkUnitHasPropertyBasedOnUnitType, this)(
                        _unitID, 1)
                    == 0) {
                    return 0;
                }
            }
            return 1;
        }

    }
}
}
