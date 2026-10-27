#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The rotation index is taken signed modulo 4 (and 0x80000003 / jns at 0x523429). The signpost fallback
        // scans 8 signpost IDs although signpostsMapEdge has only 7 rows (index 7 reads past it, as in machine
        // code 0x5234B0..0x5234FA).
        // FUNCTION: STRONGHOLDCRUSADER 0x00523410
        undefined4 TribesState::findRecentOrSignpostSpawnLocation(uint* outX, uint* outY)
        {
            for (int i = 0; i < 4; ++i) {
                short const storedX
                    = DAT_GameState::instance.mapAndTime
                          .lionLocationsXY[(DAT_GameState::instance.mapAndTime.animalSpawnLocationRotation + i) % 4]
                          .x;
                if (storedX != 0) {
                    *outX = storedX;
                    uint const storedY
                        = DAT_GameState::instance.mapAndTime
                              .lionLocationsXY[(DAT_GameState::instance.mapAndTime.animalSpawnLocationRotation + i)
                                  % 4]
                              .y;
                    *outY = storedY;
                    uint const x = *outX;
                    if (x <= 399 && storedY <= 399
                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[storedY * 400 + x] != 0
                        && (DAT_TileMapState::instance
                                   .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[storedY].addXgetTile
                                       + x]
                               & 0x4a5014b1U)
                            == 0) {
                        DAT_GameState::instance.mapAndTime.animalSpawnLocationRotation
                            = (short)((DAT_GameState::instance.mapAndTime.animalSpawnLocationRotation + i + 1) % 4);
                        return 1;
                    }
                }
            }
            for (int i = 0; i < 8; ++i) {
                if (DAT_GameState::instance.mapAndTime.signpostIDs[i] != 0) {
                    *outX = DAT_GameState::instance.mapAndTime.signpostsMapEdge[i][0].x;
                    *outY = DAT_GameState::instance.mapAndTime.signpostsMapEdge[i][0].y;
                    return 1;
                }
            }
            return 0;
        }

    }
}
}
