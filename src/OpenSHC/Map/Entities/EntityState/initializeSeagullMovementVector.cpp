#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00403790
        void EntityState::initializeSeagullMovementVector(
            int seagullID, int param_2, int param_3, int param_4, int param_5)
        {
            short sVar1;
            short sVar2;
            int iVar3;
            short sVar4;
            int iVar5;
            short sVar6;
            if (param_5 < param_3) {
                iVar5 = param_3 - param_5;
            } else {
                iVar5 = param_5 - param_3;
            }
            if (param_4 < param_2) {
                iVar3 = param_2 - param_4;
                this->seagullArray[seagullID].field23_0x30 = -1;
            } else {
                iVar3 = param_4 - param_2;
                this->seagullArray[seagullID].field23_0x30 = 1;
            }
            this->seagullArray[seagullID].field24_0x32 = (ushort)(param_3 <= param_5) * 2 + -1;
            sVar4 = (short)iVar5;
            sVar1 = (short)iVar3;
            if (iVar3 == 0) {
                if (iVar5 != 0) {
                    this->seagullArray[seagullID].field22_0x2e = 1;
                    goto LAB_0040383b;
                }
                this->seagullArray[seagullID].field22_0x2e = 0;
            } else {
                if (iVar5 == 0) {
                    this->seagullArray[seagullID].field22_0x2e = 2;
                } else if (iVar3 < iVar5) {
                    this->seagullArray[seagullID].field22_0x2e = 3;
                } else {
                    this->seagullArray[seagullID].field22_0x2e = 4;
                }
            LAB_0040383b:
                sVar2 = sVar1;
                if (iVar5 < iVar3)
                    goto LAB_00403843;
            }
            sVar2 = sVar4;
        LAB_00403843:
            this->seagullArray[seagullID].field27_0x38 = sVar2;
            sVar2 = this->seagullArray[seagullID].field22_0x2e;
            if (sVar2 == 3) {
                sVar2 = sVar1 * 2;
                this->seagullArray[seagullID].field19_0x28 = sVar2;
                sVar6 = sVar2 + sVar4 * -2;
                sVar2 = sVar2 - sVar4;
            } else {
                if (sVar2 != 4) {}
                sVar2 = sVar4 * 2;
                this->seagullArray[seagullID].field19_0x28 = sVar2;
                sVar6 = sVar2 + sVar1 * -2;
                sVar2 = sVar2 - sVar1;
            }
            this->seagullArray[seagullID].field21_0x2c = sVar2;
            this->seagullArray[seagullID].field20_0x2a = sVar6;
        }

    }
}
}
