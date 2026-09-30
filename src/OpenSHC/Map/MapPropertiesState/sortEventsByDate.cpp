#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BA7D0
    void MapPropertiesState::sortEventsByDate()
    {
        int* piVar1;
        int iVar2;
        int iVar3;
        IngameEventHeader* pIVar4;
        int* piVar5;
        int* piVar6;
        int local_f8;
        int local_f0[59];
        local_f8 = 0;
        if (this->eventsCount != 1 && -1 < this->eventsCount + -1) {
            do {
                iVar3 = 0;
                if (this->eventsCount - local_f8 != 1 && -1 < (this->eventsCount - local_f8) + -1) {
                    piVar1 = &this->scenarioEvents[0].header.year;
                    do {
                        if ((piVar1[0x39] < *piVar1)
                            || ((*piVar1 == piVar1[0x39]
                                && ((piVar1[0x38] < ((IngameEventHeader*)(piVar1 + -1))->month
                                    || ((((IngameEventHeader*)(piVar1 + -1))->month == piVar1[0x38]
                                        && (piVar1[0x3a] < piVar1[1])))))))) {
                            pIVar4 = (IngameEventHeader*)(piVar1 + -1);
                            piVar5 = local_f0;
                            for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
                                *piVar5 = pIVar4->month;
                                pIVar4 = (IngameEventHeader*)&pIVar4->year;
                                piVar5 = piVar5 + 1;
                            }
                            piVar5 = piVar1 + 0x38;
                            pIVar4 = (IngameEventHeader*)(piVar1 + -1);
                            for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
                                pIVar4->month = *piVar5;
                                piVar5 = piVar5 + 1;
                                pIVar4 = (IngameEventHeader*)&pIVar4->year;
                            }
                            piVar5 = local_f0;
                            piVar6 = piVar1 + 0x38;
                            for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
                                *piVar6 = *piVar5;
                                piVar5 = piVar5 + 1;
                                piVar6 = piVar6 + 1;
                            }
                        }
                        iVar3 = iVar3 + 1;
                        piVar1 = piVar1 + 0x39;
                    } while (iVar3 < (this->eventsCount - local_f8) + -1);
                }
                local_f8 = local_f8 + 1;
            } while (local_f8 < this->eventsCount + -1);
        }
    }

}
}
