#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // No alive check; the tribe size is re-read every iteration (0x5254AD).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525470
        void TribesState::removeAllTribeUnits(int tribeID)
        {
            for (int unitSelectionIndex = 0; unitSelectionIndex < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex++);
                DAT_UnitsState::instance.units[unitID].logicalState = ULS_REMOVE;
            }
        }

    }
}
}
