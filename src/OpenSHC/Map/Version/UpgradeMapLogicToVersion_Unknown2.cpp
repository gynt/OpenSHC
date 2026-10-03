#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501350
    void Version::UpgradeMapLogicToVersion_Unknown2()
    {
        int iVar1;
        iVar1 = 0;
        do {
            if (((DAT_TileMapState::instance.LogicLayer[iVar1] & 0x800U) != 0)
                && (DAT_TileMapState::instance.HeightLayer[iVar1]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[iVar1])) {
                DAT_TileMapState::instance.HeightLayer[iVar1] = DAT_TileMapState::instance.DefaultHeightLayer[iVar1];
                DAT_TileMapState::instance.LogicLayer[iVar1]
                    = DAT_TileMapState::instance.LogicLayer[iVar1] & 0xffbef4ff;
            }
            if (((DAT_TileMapState::instance.LogicLayer[iVar1 + 1] & 0x800U) != 0)
                && (DAT_TileMapState::instance.HeightLayer[iVar1 + 1]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 1])) {
                DAT_TileMapState::instance.HeightLayer[iVar1 + 1]
                    = DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 1];
                DAT_TileMapState::instance.LogicLayer[iVar1 + 1]
                    = DAT_TileMapState::instance.LogicLayer[iVar1 + 1] & 0xffbef4ff;
            }
            if (((DAT_TileMapState::instance.LogicLayer[iVar1 + 2] & 0x800U) != 0)
                && (DAT_TileMapState::instance.HeightLayer[iVar1 + 2]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 2])) {
                DAT_TileMapState::instance.HeightLayer[iVar1 + 2]
                    = DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 2];
                DAT_TileMapState::instance.LogicLayer[iVar1 + 2]
                    = DAT_TileMapState::instance.LogicLayer[iVar1 + 2] & 0xffbef4ff;
            }
            if (((DAT_TileMapState::instance.LogicLayer[iVar1 + 3] & 0x800U) != 0)
                && (DAT_TileMapState::instance.HeightLayer[iVar1 + 3]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 3])) {
                DAT_TileMapState::instance.HeightLayer[iVar1 + 3]
                    = DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 3];
                DAT_TileMapState::instance.LogicLayer[iVar1 + 3]
                    = DAT_TileMapState::instance.LogicLayer[iVar1 + 3] & 0xffbef4ff;
            }
            if (((DAT_TileMapState::instance.LogicLayer[iVar1 + 4] & 0x800U) != 0)
                && (DAT_TileMapState::instance.HeightLayer[iVar1 + 4]
                    <= DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 4])) {
                DAT_TileMapState::instance.HeightLayer[iVar1 + 4]
                    = DAT_TileMapState::instance.DefaultHeightLayer[iVar1 + 4];
                DAT_TileMapState::instance.LogicLayer[iVar1 + 4]
                    = DAT_TileMapState::instance.LogicLayer[iVar1 + 4] & 0xffbef4ff;
            }
            iVar1 = iVar1 + 5;
        } while (iVar1 < 0x13a10);
    }

}
}
