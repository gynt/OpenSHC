#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AB10
        void TroopValueState::countAvailableArcherValueSlots(int includeAssigned)
        {
            DAT_TroopValueState::instance.attackInfo.arch3 = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.arch2; ++i) {
                if (DAT_BuildingsState::instance
                            .buildings[DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[i].buildingID]
                            .adjacentAIZoneValue
                        < 9999
                    && (DAT_TroopValueState::instance.attackInfo.arch2ValuesArray[i].unitID == 0 || includeAssigned != 0)) {
                    DAT_TroopValueState::instance.attackInfo.arch3++;
                }
            }
        }

    }
}
}