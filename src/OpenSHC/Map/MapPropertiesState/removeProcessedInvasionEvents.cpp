#include "../../Map.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C1320
    void MapPropertiesState::removeProcessedInvasionEvents()
    {
        undefined1 uVar1;
        undefined2 uVar2;
        undefined1* puVar3;
        int iVar4;
        undefined1* puVar5;
        undefined4* puVar6;
        undefined4* puVar7;
        int local_d0;
        undefined4 local_c8[7];
        undefined1 auStack_ac[80];
        undefined2 uStack_5c;
        undefined1 auStack_5a[86];
        local_d0 = 0;
        if (0 < this->eventsCount) {
            puVar5 = (undefined1*)((int)&this->scenarioEvents[0].data + 0xe);
            do {
                if (*(int*)(puVar5 + -0x16) == 3) {
                    puVar6 = (undefined4*)(puVar5 + -0x1e);
                    puVar7 = local_c8;
                    for (iVar4 = 0x2f; iVar4 != 0; iVar4 = iVar4 + -1) {
                        *puVar7 = *puVar6;
                        puVar6 = puVar6 + 1;
                        puVar7 = puVar7 + 1;
                    }
                    iVar4 = 0x28;
                    puVar3 = puVar5;
                    do {
                        puVar3[1] = 0;
                        *(undefined2*)(puVar3 + -2) = 0;
                        *puVar3 = 0;
                        puVar3 = puVar3 + 4;
                        iVar4 = iVar4 + -1;
                    } while (iVar4 != 0);
                    iVar4 = 0;
                    puVar3 = puVar5;
                    do {
                        uVar2 = *(undefined2*)(auStack_5a + iVar4 * 4 + -2);
                        puVar3[1] = auStack_ac[iVar4 * 4];
                        uVar1 = auStack_5a[iVar4 * 4];
                        *(undefined2*)(puVar3 + -2) = uVar2;
                        *puVar3 = uVar1;
                        iVar4 = iVar4 + 1;
                        puVar3 = puVar3 + 4;
                    } while (iVar4 < 0x14);
                }
                local_d0 = local_d0 + 1;
                puVar5 = puVar5 + 0xe4;
            } while (local_d0 < this->eventsCount);
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::pruneInvalidEventTriggerLinks, this)();
    }

}
}
