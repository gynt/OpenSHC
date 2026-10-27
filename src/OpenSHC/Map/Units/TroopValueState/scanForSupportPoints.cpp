#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F4B0
        void TroopValueState::scanForSupportPoints()
        {
            DAT_TroopValueState::instance.attackInfo.supportPoints = 0;
            for (int tile = 0; tile < 80400; ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 1) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                for (int dir = 0; dir < 4; ++dir) {
                    if ((DAT_TileMapState::instance
                                .AIInfoLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][dir * 2] + tile]
                            & 0xf)
                            != 2
                        || (DAT_TileMapState::instance
                                   .RandomLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][dir * 2] + tile]
                               & 3)
                            != 0) {
                        continue;
                    }
                    int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    if (MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                            DAT_PathFindingState::ptr)(8, x, y, 0x40)
                        != FALSE) {
                        continue;
                    }
                    DAT_TileMapState::instance.AIInfoLayer[tile] |= 0x40;
                    int const slot = MACRO_CALL_MEMBER(TroopValueState_Func::getSupportPointIndex, this)(tile);
                    if (slot != 0) {
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[slot].attackCounterStamp
                            = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    }
                    else {
                        int const next = DAT_TroopValueState::instance.attackInfo.supportPointsNext;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[next].x = x;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[next].y = y;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[next].tile = tile;
                        DAT_TroopValueState::instance.attackInfo.supportPointsArray[next].attackCounterStamp
                            = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    }
                    DAT_TroopValueState::instance.attackInfo.supportPoints++;
                    if (DAT_TroopValueState::instance.attackInfo.supportPoints >= 200) {
                        return;
                    }
                    break;
                }
            }
        }

    }
}
}
