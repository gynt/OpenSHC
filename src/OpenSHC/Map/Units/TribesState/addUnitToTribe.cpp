#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // unitID is divided signed (cdq at 0x5225AE).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522590
        void TribesState::addUnitToTribe(uint unitID, int tribeID)
        {
            ++this->tribes[tribeID].size;
            this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16]
                = this->tribes[tribeID].unitSelectionBitMasked[(int)unitID / 16]
                | DAT_UnitSelectionDefinedData::instance.BitMaskHelper[(int)unitID % 16];
            if (this->tribes[tribeID].leaderUnitID == 0) {
                this->tribes[tribeID].leaderUnitID = (short)unitID;
            }
            DAT_UnitsState::instance.units[unitID].selectionTargetUnitID = this->tribes[tribeID].leaderUnitID;
            DAT_UnitsState::instance.units[unitID].tribeID = (short)tribeID;
            DAT_UnitsState::instance.units[unitID].tribeUID = this->tribes[tribeID].uid;
            DAT_UnitsState::instance.units[unitID].idInTribe = this->tribes[tribeID].size;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits, this)(tribeID);
        }

    }
}
}
