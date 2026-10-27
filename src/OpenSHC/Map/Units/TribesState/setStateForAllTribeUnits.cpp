#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Only the low word of newState is stored (0x525347); the tribe size is re-read every iteration (0x525360).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525300
        void TribesState::setStateForAllTribeUnits(int tribeID, undefined4 newState)
        {
            for (int unitSelectionIndex = 0; unitSelectionIndex < this->tribes[tribeID].size;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    DAT_UnitsState::instance.units[unitID].state.generic = (States::UnitStateShort)newState;
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].seated = 0;
                }
            }
        }

    }
}
}
