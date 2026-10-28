#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A330
        undefined4 TroopValueState::findEnemyTowersOrGates(int unitID)
        {
            // playerInfo is 1-based; gate entries are {tile, tile2, score, unitID}
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int bestDistance = 1000;
            int bestIndex = -1;
            int i;
            for (i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex_2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][2] >= 5999
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][3] != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][1]];
                int x = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][1]
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->x = x;
                    this->y = y;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][0];
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[bestIndex][3] = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[bestIndex][1];
            }

            // every gate is taken: release them all and pick the nearest one again (without assigning it)
            for (i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex_2; ++i) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][3] = 0;
            }
            bestDistance = 1000;
            for (i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].some1000ArrayIndex_2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][2] >= 5999
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][3] != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][1]];
                int x = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][1]
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->x = x;
                    this->y = y;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[i][0];
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].field71_0xbbf4[bestIndex][1];
            }
            return 0;
        }

    }
}
}
