#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A550
        void TroopValueState::setWide3(int includeAssigned, int playerID)
        {
            // playerInfo is 1-based; wide entries are {tile, tile2, score, unitID}
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideEntries[i][2] < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wideEntries[i][3] == 0
                        || includeAssigned != 0)) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].wide3++;
                }
            }
        }

    }
}
}