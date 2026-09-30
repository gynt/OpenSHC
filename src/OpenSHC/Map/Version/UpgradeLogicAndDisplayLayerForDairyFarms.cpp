#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::Building;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0041A420
    void Version::UpgradeLogicAndDisplayLayerForDairyFarms()
    {
        Building* pBVar1;
        pBVar1 = &DAT_BuildingsState::instance.buildings[1];
        do {
            if ((pBVar1->logicalState != ((BuildingLogicalState)0))
                && (pBVar1->buildingType == OpenSHC::Map::Buildings::BT_DAIRYFARM)) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, DAT_TileMapState::ptr)(
                    (int)(short)pBVar1->x, (int)((int)((short)pBVar1->y)), 10);
            }
            pBVar1 = pBVar1 + 0x196;
        } while ((int)pBVar1 < 0x1124dc6);
    }

}
}
