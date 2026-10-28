#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is read once before the loop (kept in a stack slot, 0x52364E..0x523657).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523630
        int TribesState::getNonDyingUnit(int tribeID)
        {
            if (tribeID <= 0) {
                return 0;
            }
            int unitSelectionIndex = 0;
            int const tribeSize = this->tribes[tribeID].size;
            int unitID;
            do {
                if (unitSelectionIndex >= tribeSize) {
                    return 0;
                }
                unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
            } while (DAT_UnitsState::instance.units[unitID].logicalState != ULS_NORMAL
                || DAT_UnitsState::instance.units[unitID].dying != 0
                || DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue != 1);
            return unitID;
        }

    }
}
}
