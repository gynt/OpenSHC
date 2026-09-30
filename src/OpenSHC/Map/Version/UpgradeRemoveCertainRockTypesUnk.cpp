#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3840
    void Version::UpgradeRemoveCertainRockTypesUnk()
    {
        Rock* puVar1;
        int iVar1;
        iVar1 = 1;
        puVar1 = &DAT_LandscapeState::instance.rocks[1];
        do {
            if ((puVar1->one != 0)
                && (((int)DAT_TileMapState::instance.OrganismLayer[puVar1->tile] != iVar1 + 2000
                    || ((DAT_TileMapState::instance.LogicLayer[puVar1->tile] & 0x80) == 0)))) {
                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(iVar1);
            }
            puVar1 = puVar1 + 8;
            iVar1 = iVar1 + 1;
        } while ((int)puVar1 < 0xf98334);
    }

}
}
