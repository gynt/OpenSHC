#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501440
    void Version::UpgradeMapLogicToVersion_128()
    {
        int targetedTile;
        for (targetedTile = 0; targetedTile < 0x13a10; targetedTile++) {
            if ((DAT_TileMapState::instance.LogicLayer[targetedTile] & 0x40000000U) != 0) {
                int iVar1 = MACRO_CALL_MEMBER(
                    Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(targetedTile);
                if (((iVar1 != 0) && (DAT_TileMapState::instance.moats[iVar1].stage == 2))
                    && (DAT_TileMapState::instance.moats[iVar1].fillProgress == 4)) {
                    DAT_TileMapState::instance.HeightLayer[targetedTile] = 0;
                }
            }
        }
    }

}
}
