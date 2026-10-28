#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00519FB0
        undefined4 TroopValueState::findEnemyBuildingsClosestToUnit(int unitID)
        {
            // playerInfo is 1-based; town entries are {tile, tile2, score, unitID}
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int bestDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[i].field3_0xc != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[i].field1_0x4];
                int x = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[i].field1_0x4
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                DAT_DirectionAlgorithmState::instance.distanceHigh
                    += (100 - DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[i].field2_0x8) * 2;
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = y;
                    this->x = x;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[i].tile;
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[bestIndex].field3_0xc = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000Array[bestIndex].field1_0x4;
            }
            return 0;
        }

    }
}
}
