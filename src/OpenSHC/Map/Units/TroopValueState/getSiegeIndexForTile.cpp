#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B240
        int TroopValueState::getSiegeIndexForTile(int tile)
        {
            // The original scans slots 1..1999 (end 0x17A52AC), i.e. far past the 216 entries tentPointsValues is
            // declared with: the tent point table really has 2000 entries (AttackInfo+0x32550..+0x41F50).
            DAT_TroopValueState::instance.attackInfo.tentPointsNext = 0;
            for (int slot = 1; slot < 2000; ++slot) {
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].tile == tile) {
                    return slot;
                }
                if (DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].tile == 0
                    && DAT_TroopValueState::instance.attackInfo.tentPointsNext == 0) {
                    DAT_TroopValueState::instance.attackInfo.tentPointsNext = slot;
                }
            }
            return 0;
        }

    }
}
}
