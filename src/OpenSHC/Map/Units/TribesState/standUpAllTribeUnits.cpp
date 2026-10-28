#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The tribe size is re-read through a saved pointer every iteration (0x5253D5).
        // FUNCTION: STRONGHOLDCRUSADER 0x00525370
        void TribesState::standUpAllTribeUnits(int tribeID)
        {
            short* const tribeSize = &this->tribes[tribeID].size;
            for (int unitSelectionIndex = 0; unitSelectionIndex < *tribeSize;) {
                int const unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(tribeID, unitSelectionIndex);
                ++unitSelectionIndex;
                if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_NORMAL
                    && DAT_UnitsState::instance.units[unitID].dying == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(unitID);
                    DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                    DAT_UnitsState::instance.units[unitID].rabbitMovementSlowdown = 0;
                }
            }
        }

    }
}
}
