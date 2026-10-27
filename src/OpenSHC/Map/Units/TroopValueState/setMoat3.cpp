#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A720
        void TroopValueState::setMoat3(int includeAssigned, int playerID)
        {
            // playerInfo is 1-based; moat entries are {tile, tile2, score, unitID}
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field89_0xfa88; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatEntries[i][2] < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moatEntries[i][3] == 0
                        || includeAssigned != 0)) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].moat2++;
                }
            }
        }

    }
}
}