#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525370
        void TribesState::standUpAllTribeUnits(int tribeID)
        {
            int unitID;
            /*
              A cursor on the size field rather than on the tribe: diff_anchor's territory -
              the original's `lea eax, [eax + ebp + 0x5c]` points at Tribe::size and reads
              it as [eax], where a Tribe* reads it as [eax + 0x34].
             */
            short* _tribeSize = &this->tribes[tribeID].size;
            int unitSelectionIndex = 0;
            if (0 < *_tribeSize) {
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[unitID].dying == 0) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::standUpIfSeated, DAT_UnitsState::ptr)(unitID);
                        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[unitID].rabbitMovementSlowdown = '\0';
                    }
                } while (unitSelectionIndex < *_tribeSize);
            }
        }

    }
}
}
