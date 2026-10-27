#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // fixedRng & 7 is compared signed (jg at 0x5235FE).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523590
        void TribesState::updateAnimalHerdBehaviorState(int tribeID)
        {
            if (tribeID > 0 && this->tribes[tribeID].wildlifeAlarmTimer == 0) {
                for (int unitSelectionIndex = 0; unitSelectionIndex < this->tribes[tribeID].size;) {
                    int const unitID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID,
                        unitSelectionIndex);
                    ++unitSelectionIndex;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue == 2) {
                        int const rngBits = (int)(DAT_UnitsState::instance.units[unitID].fixedRng & 7);
                        if (rngBits <= 1) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 0;
                        } else {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = (rngBits > 5) + 1;
                        }
                    }
                }
            }
        }

    }
}
}
