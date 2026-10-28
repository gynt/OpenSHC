#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519DE0
        void TroopValueState::setScale3(int one, int playerID)
        {
            // playerInfo is 1-based; scale entries are {tile, tile2, score, unitID}
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field31_0x3ebc[i][2] < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field31_0x3ebc[i][3] == 0
                        || one != 0)) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].scale3++;
                }
            }
        }

    }
}
}
