#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A220
        int TroopValueState::findEnemyLord(undefined4 unitID)
        {
            if (DAT_TroopValueState::instance.attackInfo.lordTargetCount <= 0) {
                return 0;
            }
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.lordTargetCount; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].unitID == 0) {
                    this->y = DAT_ViewportRenderState::instance
                                  .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile2];
                    this->x = DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile2
                        - DAT_ViewportRenderState::instance.translationMatrix[this->y].addXgetTile;
                    this->tile = DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile;
                    DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].unitID = unitID;
                    return DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile2;
                }
            }
            // all lord targets are taken: share the first one without assigning it
            this->y = DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile2];
            this->x = DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile2
                - DAT_ViewportRenderState::instance.translationMatrix[this->y].addXgetTile;
            this->tile = DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile;
            return DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile2;
        }

    }
}
}
