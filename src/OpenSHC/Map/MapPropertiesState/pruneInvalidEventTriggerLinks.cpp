#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB990
    void MapPropertiesState::pruneInvalidEventTriggerLinks()
    {
        int iVar1;
        char* pcVar2;
        int* piVar3;
        char* pcVar4;
        int iVar5;
        iVar5 = 0;
        if (0 < this->eventsCount) {
            pcVar4 = (char*)((int)&this->scenarioEvents[0].data + 0xf);
            piVar3 = &this->scenarioEvents[0].header.tl_type;
            do {
                if ((*piVar3 == 3) && (*pcVar4 != '\0')) {
                    iVar1 = 1;
                    pcVar2 = pcVar4;
                    do {
                        pcVar2 = pcVar2 + 4;
                        if (*pcVar2 != '\0') {
                            *pcVar4 = '\0';
                            break;
                        }
                        iVar1 = iVar1 + 1;
                    } while (iVar1 < 0x28);
                }
                iVar5 = iVar5 + 1;
                piVar3 = piVar3 + 0x39;
                pcVar4 = pcVar4 + 0xe4;
            } while (iVar5 < this->eventsCount);
        }
    }

}
}
