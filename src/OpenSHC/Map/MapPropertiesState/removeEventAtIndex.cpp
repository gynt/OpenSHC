#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BA8B0
    void MapPropertiesState::removeEventAtIndex(int param_1)
    {
        InGameEventUnionVersion* pIVar1;
        int iVar2;
        InGameEventUnionVersion* pIVar3;
        InGameEventUnionVersion* pIVar4;
        this->eventsCount = this->eventsCount + -1;
        if (param_1 < this->eventsCount) {
            pIVar1 = this->scenarioEvents + param_1;
            do {
                param_1 = param_1 + 1;
                pIVar3 = pIVar1 + 1;
                pIVar4 = pIVar1;
                for (iVar2 = 57; iVar2 != 0; iVar2 = iVar2 + -1) {
                    (pIVar4->header).month = (pIVar3->header).month;
                    pIVar3 = (InGameEventUnionVersion*)&(pIVar3->header).year;
                    pIVar4 = (InGameEventUnionVersion*)&(pIVar4->header).year;
                }
                pIVar1 = pIVar1 + 1;
            } while (param_1 < this->eventsCount);
        }
    }

}
}
