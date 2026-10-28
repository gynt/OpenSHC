#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // attackInfo.field_0x20e00 (declared undefined1[4]) is the archer point count of the last full scan, an int
        // (0x0051F343 mov eax, [0x1784154]; signed jge chain).
        // FUNCTION: STRONGHOLDCRUSADER 0x0051F340
        void TroopValueState::scanForArcherPoints()
        {
            int spacingRadius;
            DAT_TroopValueState::instance.attackInfo.archerPoints = 0;
            if (*(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 0) {
                spacingRadius = 8;
            }
            else if (*(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 2) {
                spacingRadius = 5;
            }
            else if (*(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 4) {
                spacingRadius = 6;
            }
            else if (*(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 8) {
                spacingRadius = 7;
            }
            else if (*(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00 < 20) {
                spacingRadius = 8;
            }
            else {
                spacingRadius = 10;
            }
            for (int tile = 0; tile < 80400; ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 2) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                for (int dir = 0; dir < 4; ++dir) {
                    if ((DAT_TileMapState::instance
                                .AIInfoLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][dir * 2] + tile]
                            & 0xf)
                            != 4
                        || (DAT_TileMapState::instance
                                   .RandomLayer[DAT_TileMapState::instance.directionTranslationMatrix[y][dir * 2] + tile]
                               & 3)
                            != 0) {
                        continue;
                    }
                    int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                    if (MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                            DAT_PathFindingState::ptr)(spacingRadius, x, y, 0x10)
                        != FALSE) {
                        continue;
                    }
                    DAT_TileMapState::instance.AIInfoLayer[tile] |= 0x10;
                    int const slot = MACRO_CALL_MEMBER(TroopValueState_Func::findOrReserveArcherPointSlot, this)(tile);
                    if (slot != 0) {
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][3]
                            = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    }
                    else {
                        int const next = DAT_TroopValueState::instance.attackInfo.archerPointsNext;
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[next][0] = x;
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[next][1] = y;
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[next][2] = tile;
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[next][3]
                            = DAT_TroopValueState::instance.attackInfo.someCounter1;
                    }
                    DAT_TroopValueState::instance.attackInfo.archerPoints++;
                    if (DAT_TroopValueState::instance.attackInfo.archerPoints >= 200) {
                        return;
                    }
                    break;
                }
            }
            *(int*)DAT_TroopValueState::instance.attackInfo.field_0x20e00
                = DAT_TroopValueState::instance.attackInfo.archerPoints;
        }

    }
}
}
