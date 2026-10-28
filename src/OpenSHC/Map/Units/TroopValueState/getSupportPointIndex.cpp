#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B0C0
        int TroopValueState::getSupportPointIndex(int tile)
        {
            DAT_TroopValueState::instance.attackInfo.supportPointsNext = 0;
            for (int slot = 1; slot < 200; ++slot) {
                if (DAT_TroopValueState::instance.attackInfo.supportPointsArray[slot].tile == tile) {
                    return slot;
                }
                if (DAT_TroopValueState::instance.attackInfo.supportPointsArray[slot].tile == 0
                    && DAT_TroopValueState::instance.attackInfo.supportPointsNext == 0) {
                    DAT_TroopValueState::instance.attackInfo.supportPointsNext = slot;
                }
            }
            return 0;
        }

    }
}
}
