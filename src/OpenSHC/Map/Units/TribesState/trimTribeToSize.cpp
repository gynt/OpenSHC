#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Original bugs kept (machine code 0x522EF1 / 0x522F38..0x522F51):
        // - the tribeID argument is never read, the tribe is the global scan cursor g_tribeScanIndex;
        // - the index is incremented before the compare, so the member with index smallerSize - 1 is
        //   removed too (the tribe keeps smallerSize - 1 members).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522EF0
        void TribesState::trimTribeToSize(undefined4 tribeID, int smallerSize)
        {
            int const scanTribeID = g_tribeScanIndex::instance;
            int unitSelectionIndex = 0;
            if (this->tribes[scanTribeID].tribeState != 0) {
                int const size = this->tribes[scanTribeID].size;
                if (size >= smallerSize && size > 0) {
                    do {
                        int const unitID = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(scanTribeID,
                            unitSelectionIndex);
                        ++unitSelectionIndex;
                        if ((DAT_UnitsState::instance.units[unitID].logicalState == 1
                                || DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                                || DAT_UnitsState::instance.units[unitID].logicalState == ULS_TRANSITIONING)
                            && unitSelectionIndex >= smallerSize) {
                            DAT_UnitsState::instance.units[unitID].logicalState = ULS_REMOVE;
                        }
                    } while (unitSelectionIndex < this->tribes[scanTribeID].size);
                }
            }
        }

    }
}
}
