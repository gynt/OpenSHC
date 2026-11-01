#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005236A0
        void TribesState::countDeerEfficiently()
        {
            DAT_GameState::instance.mapAndTime.aliveDeerCount = 0;
            /*
              The original walks the unit array three units at a time, but MSVC unrolls this
              plain loop to the same code: the hand-written three-block form, an outer loop
              stepping by 3 with an inner 0..2, and this all measure identically, so the
              short form is kept (style guide rule 8).
             */
            for (int i = 1; i < 2500; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState == Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[i].dying == 0
                    && DAT_UnitsState::instance.units[i].unitType == Map::Units::UT_ANTELOPESHDEER) {
                    ++DAT_GameState::instance.mapAndTime.aliveDeerCount;
                }
            }
        }

    }
}
}
