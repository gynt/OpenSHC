#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;
    using OpenSHC::Map::Buildings::Building;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A100
    void Version::UpgradeBuildingFlag1()
    {
        short sVar1;
        Building* pBVar2;
        pBVar2 = &DAT_BuildingsState::instance.buildings[1];
        do {
            if (pBVar2->logicalState != ((BuildingLogicalState)0)) {
                sVar1 = DAT_BuildingDefinedData::instance.field24_0x237c[(short)pBVar2->buildingType].shortValue;
                pBVar2->flag1
                    = DAT_BuildingDefinedData::instance.field16_0x15bc[(short)pBVar2->buildingType].shortValue;
                pBVar2->flag2 = sVar1;
            }
            pBVar2 = pBVar2 + 0x196;
        } while ((int)pBVar2 < 0x1124dc6);
    }

}
}
