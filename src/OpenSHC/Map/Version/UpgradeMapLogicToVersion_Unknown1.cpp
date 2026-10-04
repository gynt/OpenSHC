#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    using Map::Buildings::BuildingTypeShort;


    // FUNCTION: STRONGHOLDCRUSADER 0x005011F0
    void Version::UpgradeMapLogicToVersion_Unknown1()
    {
        BuildingTypeShort BVar1;
        ushort* puVar2;
        puVar2 = DAT_TileMapState::instance.MiscDisplayLayer;
        do {
            if (((*puVar2 & 0x20) != 0)
                && (((puVar2[-0x7f968] == 0
                         || (BVar1 = DAT_BuildingsState::instance.buildings[(short)puVar2[-0x7f968]].buildingType,
                             (short)BVar1 < 0x2d))
                    || (0x2f < (short)BVar1)))) {
                *puVar2 = *puVar2 & 0xffdf;
            }
            if (((puVar2[1] & 0x20) != 0)
                && (((puVar2[-0x7f967] == 0
                         || (BVar1 = DAT_BuildingsState::instance.buildings[(short)puVar2[-0x7f967]].buildingType,
                             (short)BVar1 < 0x2d))
                    || (0x2f < (short)BVar1)))) {
                puVar2[1] = puVar2[1] & 0xffdf;
            }
            if (((puVar2[2] & 0x20) != 0)
                && (((puVar2[-0x7f966] == 0
                         || (BVar1 = DAT_BuildingsState::instance.buildings[(short)puVar2[-0x7f966]].buildingType,
                             (short)BVar1 < 0x2d))
                    || (0x2f < (short)BVar1)))) {
                puVar2[2] = puVar2[2] & 0xffdf;
            }
            if (((puVar2[3] & 0x20) != 0)
                && (((puVar2[-0x7f965] == 0
                         || (BVar1 = DAT_BuildingsState::instance.buildings[(short)puVar2[-0x7f965]].buildingType,
                             (short)BVar1 < 0x2d))
                    || (0x2f < (short)BVar1)))) {
                puVar2[3] = puVar2[3] & 0xffdf;
            }
            if (((puVar2[4] & 0x20) != 0)
                && (((puVar2[-0x7f964] == 0
                         || (BVar1 = DAT_BuildingsState::instance.buildings[(short)puVar2[-0x7f964]].buildingType,
                             (short)BVar1 < 0x2d))
                    || (0x2f < (short)BVar1)))) {
                puVar2[4] = puVar2[4] & 0xffdf;
            }
            if (((puVar2[5] & 0x20) != 0)
                && (((puVar2[-0x7f963] == 0
                         || (BVar1 = DAT_BuildingsState::instance.buildings[(short)puVar2[-0x7f963]].buildingType,
                             (short)BVar1 < 0x2d))
                    || (0x2f < (short)BVar1)))) {
                puVar2[5] = puVar2[5] & 0xffdf;
            }
            puVar2 = puVar2 + 6;
        } while ((int)puVar2 < 0x1dbc2a8);
    }

}
}
