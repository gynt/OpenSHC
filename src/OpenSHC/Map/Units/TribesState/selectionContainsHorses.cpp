#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00524230
        BOOLEnum TribesState::selectionContainsHorses(int tribeID)
        {
            // Keeping the decompiler's guarded do-while: the equivalent for loop measured 0.97 instead of 1.00.
            UnitTypeShort _unitType;
            int unitID;
            int const _size = this->tribes[tribeID].size;
            int unitSelectionIndex = 0;
            if (0 < _size) {
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && (_unitType = DAT_UnitsState::instance.units[unitID].unitType,
                            _unitType == Map::Units::UT_A_HARCHER || (_unitType == Map::Units::UT_E_KNIGHT))) {
                        return TRUE;
                    }
                } while (unitSelectionIndex < _size);
            }
            return FALSE;
        }

    }
}
}
