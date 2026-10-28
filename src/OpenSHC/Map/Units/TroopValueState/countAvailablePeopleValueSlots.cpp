#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A0C0
        void TroopValueState::countAvailablePeopleValueSlots(int includeAssigned)
        {
            DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable = 0;
            for (int i = 0; i < DAT_TroopValueState::instance.attackInfo.peopleTargetCount; ++i) {
                if (DAT_TroopValueState::instance.attackInfo.peopleValuesArray[i].unitID == 0 || includeAssigned != 0) {
                    DAT_TroopValueState::instance.attackInfo.peopleTargetsAvailable++;
                }
            }
        }

    }
}
}
