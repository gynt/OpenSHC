#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x005241C0
        undefined4 TribesState::tribeContainsUnitThatCanClimb(int tribeID)
        {
            // Keeping the decompiler's guarded do-while: the equivalent for loop measured 0.97 instead of 1.00.
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
                        && DAT_UnitsState::instance.units[unitID].unitCanClimb != 0) {
                        return 1;
                    }
                } while (unitSelectionIndex < _size);
            }
            return 0;
        }

    }
}
}
