#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The leader is cleared before the loop (0x52529C); the tribe size is re-read every iteration (0x5252E7).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525280
        void TribesState::electTribeLeader(int tribeID)
        {
            int unitSelectionIndex = 0;
            short const tribeSize = this->tribes[tribeID].size;
            this->tribes[tribeID].leaderUnitID = 0;
            if (tribeSize > 0) {
                do {
                    int const unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                        this)(tribeID, unitSelectionIndex);
                    ++unitSelectionIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        short const leaderUnitID = this->tribes[tribeID].leaderUnitID;
                        if (leaderUnitID == 0) {
                            this->tribes[tribeID].leaderUnitID = (short)unitID;
                            DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = (short)unitID;
                        }
                        else {
                            DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = leaderUnitID;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
