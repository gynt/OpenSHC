#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523590
        void TribesState::updateAnimalHerdBehaviorState(int tribeID)
        {
            int unitID;
            int unitSelectionIndex;
            /*
              The comma assignment is load-bearing: initialising unitSelectionIndex above
              the `if` instead measured 0.92 where this form measures 1.00, because the
              original only zeroes the index once the two guards have passed.
             */
            if (0 < tribeID && this->tribes[tribeID].predatorNearby == 0
                && (unitSelectionIndex = 0, 0 < this->tribes[tribeID].size)) {
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0
                        && DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue == 2) {
                        /*
                          Signed, and tested against 1 rather than 2. The original has
                          `cmp ecx, 1; jg` and derives the second value with `setg`, where
                          a `uint` gives `jae` and `seta`. Written `< 2` the literal does
                          not appear in the compare at all - MSVC puts 2 in a register and
                          emits `cmp ecx, ebx; jge` - so the bound is written as `<= 1`,
                          which is the same test on ints and the instruction the original
                          has. The arms are already the right way round: the original's
                          `jg` skips the nine bytes of the zero store, so that store is
                          its fall-through.
                         */
                        int rngBucket = DAT_UnitsState::instance.units[unitID].fixedRng & 7;
                        if (rngBucket <= 1) {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 0;
                        } else {
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = (5 < rngBucket) + 1;
                        }
                    }
                } while (unitSelectionIndex < this->tribes[tribeID].size);
            }
        }

    }
}
}
