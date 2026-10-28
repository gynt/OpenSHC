#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is read once before the loop (0x524242).
        // FUNCTION: STRONGHOLDCRUSADER 0x00524230
        BOOLEnum TribesState::selectionContainsHorses(int tribeID)
        {
            int const tribeSize = this->tribes[tribeID].size;
            for (int unitSelectionIndex = 0; unitSelectionIndex < tribeSize;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && (DAT_UnitsState::instance.units[unitID].unitType == UT_A_HARCHER
                        || DAT_UnitsState::instance.units[unitID].unitType == UT_E_KNIGHT)) {
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
