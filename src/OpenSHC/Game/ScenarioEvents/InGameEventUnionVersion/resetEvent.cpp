#include "../../../Game.func.hpp"
#include "../InGameEventUnionVersion.func.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B7730
        undefined4 InGameEventUnionVersion::resetEvent()
        {
            (this->header).month = 0;
            (this->header).year = 1181;
            (this->data).invasion.repeatMonths = 0;
            (this->header).tl_type = 1;
            (this->data).invasion.crusaderArabian = 0;
            (this->data).scenario.actionData = 0;
            (this->data).scenario.ScenarioEventType = 0;
            (this->data).invasion.unitCountsPerUnitType[1] = 0;
            (this->data).invasion.unitCountsPerUnitType[2] = 0;
            (this->data).invasion.unitCountsPerUnitType[3] = 0;
            (this->data).invasion.unitCountsPerUnitType[4] = 0;
            (this->data).invasion.unitCountsPerUnitType[5] = 0;
            (this->data).invasion.unitCountsPerUnitType[6] = 0;
            (this->data).invasion.unitCountsPerUnitType[7] = 0;
            (this->data).invasion.unitCountsPerUnitType[8] = 0;
            (this->data).invasion.unitCountsPerUnitType[9] = 0;
            (this->data).invasion.unitCountsPerUnitType[10] = 0;
            (this->data).invasion.unitCountsPerUnitType[0xb] = 0;
            (this->data).invasion.unitCountsPerUnitType[0xc] = 0;
            (this->data).invasion.unitCountsPerUnitType[0xd] = 0;
            (this->data).invasion.unitCountsPerUnitType[0xe] = 0;
            (this->data).invasion.unitCountsPerUnitType[0xf] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x10] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x11] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x12] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x13] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x14] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x15] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x16] = 0;
            (this->data).invasion.unitCountsPerUnitType[0x17] = 0;
            (this->data).invasion.invasionPoint = 0;
            return (undefined4)(0);
        }

    }
}
}
