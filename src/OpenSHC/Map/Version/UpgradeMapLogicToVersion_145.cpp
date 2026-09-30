#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005016D0
    void Version::UpgradeMapLogicToVersion_145()
    {
        int iVar1;
        iVar1 = 0;
        do {
            if ((DAT_TileMapState::instance.LogicLayer[iVar1] & 1) != 0) {
                DAT_TileMapState::instance.HeightLayer[iVar1] = 0;
                DAT_TileMapState::instance.DefaultHeightLayer[iVar1] = 0;
            }
            if (((DAT_TileMapState::instance.LogicLayer[iVar1] & 0x100000U) == 0)
                && ((DAT_TileMapState::instance.Logic2Layer[iVar1] & 0x20) != 0)) {
                DAT_TileMapState::instance.HeightLayer[iVar1] = 0;
                DAT_TileMapState::instance.DefaultHeightLayer[iVar1] = 0;
            }
            DAT_TileMapState::instance.LogicLayer[iVar1] = DAT_TileMapState::instance.LogicLayer[iVar1] & 0xffffffb3;
            iVar1 = iVar1 + 1;
        } while (iVar1 < 0x13a10);
    }

}
}
