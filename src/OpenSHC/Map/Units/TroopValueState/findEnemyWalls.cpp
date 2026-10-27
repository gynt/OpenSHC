#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519CC0
        undefined4 TroopValueState::findEnemyWalls(int unitID)
        {
            // playerInfo is 1-based; hack entries are {tile, tile2, score, unitID}
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int bestDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].hack2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[i * 4 + 2] >= 9999
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[i * 4 + 3] != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[i * 4 + 1]];
                int x = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[i * 4 + 1]
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                DAT_DirectionAlgorithmState::instance.distanceHigh
                    += DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[i * 4 + 2] * 8;
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = y;
                    this->x = x;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[i * 4];
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[bestIndex * 4 + 3] = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field4_0x10[bestIndex * 4 + 1];
            }
            return 0;
        }

    }
}
}
