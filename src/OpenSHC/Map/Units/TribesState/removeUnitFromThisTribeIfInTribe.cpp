#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The membership bit is only tested when the unit has no tribe at all (0x522644): a unit in any tribe is
        // removed from this tribe's counters even if it is not a member. unitID is divided signed (cdq at 0x522658).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522630
        void TribesState::removeUnitFromThisTribeIfInTribe(uint unitID, int tribeID)
        {
            if (DAT_UnitsState::instance.units[unitID].tribeID == 0
                && ((unsigned short)DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16]
                       & this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16])
                    == 0) {
                return;
            }
            if (this->tribes[tribeID].size > 0) {
                --this->tribes[tribeID].size;
            }
            if (this->tribes[tribeID].size <= 0) {
                this->tribes[tribeID].tribeState = 3;
            }
            this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16]
                = this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16]
                & DAT_UnitSelectionDefinedData::instance.BitMaskHelper2[(int)unitID % 16];
            if (DAT_UnitsState::instance.units[unitID].tribeID == tribeID) {
                DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = 0;
                DAT_UnitsState::instance.units[unitID].tribeID = 0;
                DAT_UnitsState::instance.units[unitID].idInTribe = 0;
            }
            if (this->tribes[tribeID].leaderUnitID == (int)unitID) {
                this->tribes[tribeID].leaderUnitID = -1;
            }
        }

    }
}
}
