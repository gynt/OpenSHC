#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingType;
    using Map::Buildings::Building;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A340
    void Version::SetHovelBuildOrder()
    {
        Building* pBVar1;
        short sVar1;
        sVar1 = 0;
        pBVar1 = &DAT_BuildingsState::instance.buildings[1];
        do {
            if ((pBVar1->logicalState != ((BuildingLogicalState)0))
                && (pBVar1->buildingType == Map::Buildings::BT_HOVEL)) {
                pBVar1->buildMonthOrBuildOrder = sVar1;
                sVar1 = sVar1 + 1;
                *(undefined2*)&pBVar1->hovelVisualStyle = 0;
                *(undefined2*)((int)&pBVar1->hovelVisualStyle + 2) = 0;
            }
            pBVar1 = pBVar1 + 0x196;
        } while ((int)pBVar1 < 0x1124dc6);
    }

}
}
