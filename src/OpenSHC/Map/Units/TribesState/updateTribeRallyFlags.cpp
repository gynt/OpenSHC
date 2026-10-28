#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // rallyRelatedFlag is cleared for every normal, alive member before the goToRallyPoint /
        // isSelectable_OR_matchTime test (0x523FC7); the tribe size is re-read every iteration (0x523FE7).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523F70
        undefined4 TribesState::updateTribeRallyFlags(int tribeID)
        {
            undefined4 anyFlagged = 0;
            for (int unitSelectionIndex = 0; unitSelectionIndex < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    DAT_UnitsState::instance.units[unitID].rallyRelatedFlag = 0;
                    if (DAT_UnitsState::instance.units[unitID].goToRallyPoint != 0
                        || DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
                        anyFlagged = 1;
                        DAT_UnitsState::instance.units[unitID].rallyRelatedFlag = 1;
                    }
                }
            }
            return anyFlagged;
        }

    }
}
}
