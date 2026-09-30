#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B8000
    void MapPropertiesState::sumUnitCounts()
    {
        IngameInvasionEventItemContent* piVar1;
        int iVar1;
        this->DAT_InvasionEventItemUnitCountSum = 0;
        iVar1 = 5;
        piVar1 = (IngameInvasionEventItemContent*)((int)&this->scenarioEvents[this->currentEventID].data + 0x10);
        do {
            this->DAT_InvasionEventItemUnitCountSum = this->DAT_InvasionEventItemUnitCountSum
                + piVar1->unitCountsPerUnitType[0] + piVar1->unitCountsPerUnitType[1] + piVar1->unitCountsPerUnitType[2]
                + piVar1->unitCountsPerUnitType[4] + piVar1->unitCountsPerUnitType[3];
            iVar1 = iVar1 + -1;
            piVar1 = (IngameInvasionEventItemContent*)(piVar1->unitCountsPerUnitType + 8);
        } while (iVar1 != 0);
    }

}
}
