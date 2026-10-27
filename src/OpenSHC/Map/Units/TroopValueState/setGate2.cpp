#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A2D0
        void TroopValueState::setGate2(int includeAssigned, int playerID)
        {
            // playerInfo is 1-based; gate entries are {tile, tile2, score, unitID}
            DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].some1000ArrayIndex_2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field71_0xbbf4[i][2] < 5999
                    && (DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].field71_0xbbf4[i][3] == 0
                        || includeAssigned != 0)) {
                    DAT_TroopValueState::instance.attackInfo.playerInfo[playerID - 1].gate2++;
                }
            }
        }

    }
}
}