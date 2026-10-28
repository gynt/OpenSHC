#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A100
        void TroopValueState::countAvailableLordValueSlots(int includeAssigned)
        {
            DAT_TroopValueState::instance.attackInfo.lordTargetsAvailable = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.lordTargetCount; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].unitID == 0 || includeAssigned != 0) {
                    DAT_TroopValueState::instance.attackInfo.lordTargetsAvailable++;
                }
            }
        }

    }
}
}
