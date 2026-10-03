#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005016D0
    void Version::UpgradeMapLogicToVersion_145()
    {
        int iVar1;
        for (iVar1 = 0; iVar1 < 0x13a10; iVar1++) {
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
        }
    }

}
}
