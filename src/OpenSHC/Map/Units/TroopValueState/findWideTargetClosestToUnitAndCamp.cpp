#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A5B0
        undefined4 TroopValueState::findWideTargetClosestToUnitAndCamp(int unitID)
        {
            // The header names the parameter playerID, but it is a unit ID (indexes units[], stored as the
            // entry's unitID). playerInfo is 1-based; wide entries are {tile, tile2, score, unitID}.
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int bestDistance = 1000;
            int bestIndex = -1;
            int const targetPlayer
                = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].currentPlayerID_OR_attackedPlayerID_OR_one;
            int const campX = DAT_GameState::instance.playerDataArray[targetPlayer].campground.xEntry;
            int const campY = DAT_GameState::instance.playerDataArray[targetPlayer].campground.yEntry;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wide2; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[i][2] >= 5999
                    || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[i][3] != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                            [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[i][1]];
                int x = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[i][1]
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                int distance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(campX, campY, x, y);
                distance += DAT_DirectionAlgorithmState::instance.distanceHigh;
                if (distance < bestDistance) {
                    this->y = y;
                    this->x = x;
                    this->tile = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[i][0];
                    bestDistance = distance;
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[bestIndex][3] = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideEntries[bestIndex][1];
            }
            return 0;
        }

    }
}
}
