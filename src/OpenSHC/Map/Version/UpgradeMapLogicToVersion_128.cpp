#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00501440
    void Version::UpgradeMapLogicToVersion_128()
    {
        int iVar1;
        int targetedTile;
        targetedTile = 0;
        do {
            if ((DAT_TileMapState::instance.LogicLayer[targetedTile] & 0x40000000U) != 0) {
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, DAT_TileMapState::ptr)(targetedTile);
                if (((iVar1 != 0) && (DAT_TileMapState::instance.moats[iVar1].stage == 2))
                    && (DAT_TileMapState::instance.moats[iVar1].fillProgress == 4)) {
                    DAT_TileMapState::instance.HeightLayer[targetedTile] = 0;
                }
            }
            targetedTile = targetedTile + 1;
        } while (targetedTile < 0x13a10);
    }

}
}
