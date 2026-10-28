#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF20
        int TroopValueState::findOrReserveArcherPointSlot(int tile)
        {
            // archer point record: {x, y, tile, counterStamp, tribeID, tribeUID, reservationTimer, 0}
            DAT_TroopValueState::instance.attackInfo.archerPointsNext = 0;
            for (int slot = 1; slot < 200; ++slot) {
                if (DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][2] == tile) {
                    return slot;
                }
                if (DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][2] == 0
                    && DAT_TroopValueState::instance.attackInfo.archerPointsNext == 0) {
                    DAT_TroopValueState::instance.attackInfo.archerPointsNext = slot;
                }
            }
            return 0;
        }

    }
}
}
