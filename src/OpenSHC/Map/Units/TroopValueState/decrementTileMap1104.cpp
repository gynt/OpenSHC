#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Amortized decay of SEC_TileMap1104: one 200-tile window per call, wrapping after the window at 80200.
        // FUNCTION: STRONGHOLDCRUSADER 0x0051D5D0
        void TroopValueState::decrementTileMap1104()
        {
            for (int i = 0; i < 200; ++i) {
                if (DAT_TileMapState::instance.SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + i]
                    > 0) {
                    DAT_TileMapState::instance
                        .SEC_TileMap1104[DAT_TroopValueState::instance.attackInfo.tilemapOffset + i]--;
                }
            }
            if (DAT_TroopValueState::instance.attackInfo.tilemapOffset < 80200) {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset += 200;
            }
            else {
                DAT_TroopValueState::instance.attackInfo.tilemapOffset = 0;
            }
        }

    }
}
}
