#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00523630
        int TribesState::getNonDyingUnit(int tribeID)
        {
            int iVar1;
            int unitSelectionIndex;
            short _size;
            if (tribeID < 1) {
                return 0;
            }
            unitSelectionIndex = 0;
            _size = this->tribes[tribeID].size;
            do {
                if (_size <= unitSelectionIndex) {
                    return 0;
                }
                iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
            } while (((DAT_UnitsState::instance.units[iVar1].logicalState != OpenSHC::Map::Units::ULS_NORMAL)
                         || (DAT_UnitsState::instance.units[iVar1].dying != 0))
                || (DAT_UnitsState::instance.units[iVar1].antelopeBasedRngValue != 1));
            return iVar1;
        }

    }
}
}
