#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401690
        void EntityState::flagUnitsWithActiveEntity()
        {
            Entity* psVar1;
            int iVar1;
            iVar1 = 1;
            if (1 < this->maxEntityCount) {
                psVar1 = &this->entityArray[1];
                do {
                    if ((psVar1->logicalState == 2) && (0 < psVar1->unitID)) {
                        DAT_UnitsState::instance.units[psVar1->unitID].field233_0x39a = 1;
                    }
                    iVar1 = iVar1 + 1;
                    psVar1 = psVar1 + 0x74;
                } while (iVar1 < this->maxEntityCount);
            }
        }

    }
}
}
