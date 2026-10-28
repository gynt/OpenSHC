#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519E40
        undefined4 TroopValueState::findNearestAvailableScalePoint(int unitID)
        {
            // playerInfo is 1-based; scale entries are {tile, tile2, score, unitID}
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int bestDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].scale2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[i][2] >= 5999
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[i][3] != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[i][1]];
                int x = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[i][1]
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = y;
                    this->x = x;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[i][0];
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[bestIndex][3] = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field31_0x3ebc[bestIndex][1];
            }
            return 0;
        }

    }
}
}
