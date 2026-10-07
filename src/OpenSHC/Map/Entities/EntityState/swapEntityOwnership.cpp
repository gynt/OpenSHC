#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401B20
        void EntityState::swapEntityOwnership(int param_1, int param_2)
        {
            Entity* psVar1;
            int iVar1;
            psVar1 = &this->entityArray[1];
            iVar1 = 2999;
            do {
                if (psVar1->logicalState == 2) {
                    if (psVar1->owner == param_1) {
                        psVar1->owner = (short)param_2;
                    } else if (psVar1->owner == param_2) {
                        psVar1->owner = (short)param_1;
                    }
                }
                psVar1 = psVar1 + 0x74;
                iVar1 = iVar1 + -1;
            } while (iVar1);
        }

    }
}
}
