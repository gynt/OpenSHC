#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A140
        undefined4 TroopValueState::calculateTile2PeoplValueClosestToUnit(int unitID)
        {
            int bestDistance = 1000;
            int bestIndex = -1;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.peopleTargetCount; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].unitID != 0) {
                    continue;
                }
                int y = DAT_ViewportRenderState::instance
                            .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile2];
                int x = DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, x, y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < bestDistance) {
                    bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    this->y = y;
                    this->x = x;
                    this->tile = DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].tile;
                    bestIndex = i;
                }
            }
            if (bestIndex > -1) {
                DAT_TroopValueState::instance.attackInfo.peopleValuesArray[bestIndex].unitID = unitID;
                return DAT_TroopValueState::instance.attackInfo.peopleValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
