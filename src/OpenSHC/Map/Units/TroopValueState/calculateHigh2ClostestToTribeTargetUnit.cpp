#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A9F0
        int TroopValueState::calculateHigh2ClostestToTribeTargetUnit(int tribeID)
        {
            int const unitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            int bestDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.high2; ++i) {
                if (DAT_BuildingsState::instance
                            .buildings[DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].buildingID]
                            .adjacentAIZoneValue
                        >= 9999
                    || DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].unitID != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance
                            .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile2];
                int x = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                int const distance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                if (distance < bestDistance) {
                    this->y = y;
                    this->x = x;
                    bestDistance = distance;
                    this->tile = DAT_TroopValueState::instance.attackInfo.high2ValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.high2ValuesArray[bestIndex].unitID = unitID;
                return DAT_TroopValueState::instance.attackInfo.high2ValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}