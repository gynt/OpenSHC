#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0051A0C0
        void TroopValueState::countAvailablePeopleValueSlots(int param_1)
        {
            AttackInfoSubArrayElement1* piVar1;
            int iVar1;
            DAT_TroopValueState::instance.attackInfo.people3 = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.people2) {
                piVar1 = &DAT_TroopValueState::instance.attackInfo.peopleValuesArray[0];
                iVar1 = DAT_TroopValueState::instance.attackInfo.people2;
                do {
                    if ((piVar1->unitID == 0) || (param_1 != 0)) {
                        DAT_TroopValueState::instance.attackInfo.people3
                            = DAT_TroopValueState::instance.attackInfo.people3 + 1;
                    }
                    piVar1 = piVar1 + 4;
                    iVar1 = iVar1 + -1;
                } while (iVar1 != 0);
            }
        }

    }
}
}
