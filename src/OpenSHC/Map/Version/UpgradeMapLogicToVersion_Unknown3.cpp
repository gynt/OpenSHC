#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00501760
    void Version::UpgradeMapLogicToVersion_Unknown3()
    {
        byte* pbVar1;
        pbVar1 = &DAT_TileMapState::instance.moats[0].stage;
        do {
            if (((pbVar1[-2] != '\0') && (*pbVar1 == 1))
                && ((DAT_TileMapState::instance.LogicLayer[*(int*)(pbVar1 + -0xe)] & 0x40000000U) != 0)) {
                *pbVar1 = 2;
                pbVar1[-1] = 4;
            }
            pbVar1 = pbVar1 + 0x10;
        } while ((int)pbVar1 < 0x1fd2286);
    }

}
}
