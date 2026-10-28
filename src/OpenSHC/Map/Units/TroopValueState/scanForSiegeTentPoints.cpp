#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Ring 2 walks the direction row of the candidate tile (y), not of the ring-1 tile (0x0051F69D).
        // A ring-2 failure only ends that ring-2 walk; a ring-1 failure ends the whole check.
        // FUNCTION: STRONGHOLDCRUSADER 0x0051F5C0
        void TroopValueState::scanForSiegeTentPoints()
        {
            DAT_TroopValueState::instance.attackInfo.tentPoints = 0;
            for (int tile = 0; tile < 80400; ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 8) {
                    continue;
                }
                int passCount = 0;
                if (DAT_TileMapState::instance.UnitLayer[tile] != 0) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int const height = DAT_TileMapState::instance.HeightLayer[tile];
                for (int dir1 = 0; dir1 < 8; ++dir1) {
                    int const ring1Tile = DAT_TileMapState::instance.directionTranslationMatrix[y][dir1] + tile;
                    if (DAT_TileMapState::instance.HeightLayer[ring1Tile] > height + 6
                        || DAT_TileMapState::instance.HeightLayer[ring1Tile] < height - 6
                        || DAT_TileMapState::instance.UnitLayer[ring1Tile] != 0
                        || (short)DAT_TileMapState::instance.PathConnectionLayer[ring1Tile]
                            != DAT_TroopValueState::instance.attackInfo.startCon
                        || (DAT_TileMapState::instance.LogicLayer[ring1Tile] & 0x2000) != 0
                            || (DAT_TileMapState::instance.LogicLayer[ring1Tile] & 0x20000000) != 0
                            || (DAT_TileMapState::instance.LogicLayer[ring1Tile] & 0x80000000) != 0
                            || (DAT_TileMapState::instance.LogicLayer[ring1Tile] & 0x400) != 0) {
                        break;
                    }
                    for (int dir2 = 0; dir2 < 8; ++dir2) {
                        int const ring2Tile = DAT_TileMapState::instance.directionTranslationMatrix[y][dir2] + ring1Tile;
                        if (DAT_TileMapState::instance.HeightLayer[ring2Tile] > height + 8
                            || DAT_TileMapState::instance.HeightLayer[ring2Tile] < height - 8
                            || DAT_TileMapState::instance.UnitLayer[ring2Tile] != 0
                            || (short)DAT_TileMapState::instance.PathConnectionLayer[ring2Tile]
                                != DAT_TroopValueState::instance.attackInfo.startCon
                            || (DAT_TileMapState::instance.LogicLayer[ring2Tile] & 0x2000) != 0
                            || (DAT_TileMapState::instance.LogicLayer[ring2Tile] & 0x20000000) != 0
                            || (DAT_TileMapState::instance.LogicLayer[ring2Tile] & 0x80000000) != 0
                            || (DAT_TileMapState::instance.LogicLayer[ring2Tile] & 0x400) != 0) {
                            break;
                        }
                        passCount++;
                    }
                }
                if (passCount < 64) {
                    continue;
                }
                int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                if (MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                        DAT_PathFindingState::ptr)(6, x, y, 0x80)
                    != FALSE) {
                    continue;
                }
                DAT_TileMapState::instance.AIInfoLayer[tile] |= 0x80;
                int const slot = MACRO_CALL_MEMBER(TroopValueState_Func::getSiegeIndexForTile, this)(tile);
                if (slot != 0) {
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[slot].attackCounterStamp
                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                }
                else {
                    int const next = DAT_TroopValueState::instance.attackInfo.tentPointsNext;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].x = x;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].y = y;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].tile = tile;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].attackCounterStamp
                        = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].zero = 0;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].reservationTimer = 0;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].tribeUID = 0;
                    DAT_TroopValueState::instance.attackInfo.tentPointsValues[next].tribeID = 0;
                }
                DAT_TroopValueState::instance.attackInfo.tentPoints++;
                if (DAT_TroopValueState::instance.attackInfo.tentPoints >= 2000) {
                    return;
                }
            }
        }

    }
}
}
