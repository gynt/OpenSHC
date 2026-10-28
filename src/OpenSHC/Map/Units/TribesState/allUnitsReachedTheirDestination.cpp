#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is re-read every iteration (0x525447).
        // FUNCTION: STRONGHOLDCRUSADER 0x005253F0
        BOOLEnum TribesState::allUnitsReachedTheirDestination(int tribeID)
        {
            for (int unitSelectionIndex = 0; unitSelectionIndex < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::hasUnitReachedDestination,
                           DAT_UnitsState::ptr)(unitID)
                        == FALSE) {
                    return FALSE;
                }
            }
            return TRUE;
        }

    }
}
}
