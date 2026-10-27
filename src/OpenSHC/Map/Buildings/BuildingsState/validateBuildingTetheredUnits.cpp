#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x004173D0
        void BuildingsState::validateBuildingTetheredUnits(int buildingID)
        {
            // Counts the valid tethered units and clears the slots of units that do not exist anymore
            this->buildings[buildingID].horsesInUseOrOutpostArcherCap = 0;
            for (int i = 0; i < 4; ++i) {
                int unitID = this->buildings[buildingID].insideUnitIDs[i];
                if (unitID != 0) {
                    if (this->buildings[buildingID].insideUnitUIDs[i]
                        == DAT_UnitsState::instance.units[unitID].uid) {
                        ++this->buildings[buildingID].horsesInUseOrOutpostArcherCap;
                    } else {
                        this->buildings[buildingID].insideUnitIDs[i] = 0;
                        this->buildings[buildingID].insideUnitUIDs[i] = 0;
                    }
                }
            }
        }

    }
}
}
