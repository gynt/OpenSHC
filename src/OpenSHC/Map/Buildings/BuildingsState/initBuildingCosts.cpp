#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419780
        void BuildingsState::initBuildingCosts()
        {
            // Copies all 110 building costs to the runtime structure (original loop ends at 0x5C2A6C = 0x5C21D4 + 110 * 0x14).
            for (int i = 0; i < 110; ++i) {
                this->buildingCosts[i].requiredWood = DAT_BuildingDefinedData::instance.BuildingCost[i][0];
                this->buildingCosts[i].requiredStone_0x4 = DAT_BuildingDefinedData::instance.BuildingCost[i][1];
                this->buildingCosts[i].requiredIron_0x8 = DAT_BuildingDefinedData::instance.BuildingCost[i][2];
                this->buildingCosts[i].requiredPitch_0xc = DAT_BuildingDefinedData::instance.BuildingCost[i][3];
                this->buildingCosts[i].requiredGold = DAT_BuildingDefinedData::instance.BuildingCost[i][4];
            }
        }

    }
}
}
