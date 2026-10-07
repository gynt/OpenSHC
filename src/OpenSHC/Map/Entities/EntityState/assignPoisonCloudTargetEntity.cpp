#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00401910
        void EntityState::assignPoisonCloudTargetEntity(int param_1)
        {
            EntityTypeShort* pEVar1;
            int local_4;
            local_4 = 1;
            if (1 < this->maxEntityCount) {
                pEVar1 = &this->entityArray[1].entityType;
                do {
                    if ((((pEVar1[-1] == 2) && (*pEVar1 == Map::Entities::ET_COW_POISON_CLOUD))
                            && ((short)pEVar1[-0xb] < 0x3e9))
                        && ((pEVar1[0x54] == 0 && (pEVar1[0x58] == 0)))) {
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)(short)pEVar1[0xd], (int)((int)((short)pEVar1[0xe])),
                            (int)((int)(this->entityArray[param_1].xPosition)),
                            (int)((int)(this->entityArray[param_1].yPosition)));
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < 7) {
                            pEVar1[0x58] = (short)param_1;
                            *(int*)(pEVar1 + 0x59) = this->entityArray[param_1].uid;
                        }
                    }
                    local_4 = local_4 + 1;
                    pEVar1 = pEVar1 + 0x74;
                } while (local_4 < this->maxEntityCount);
            }
        }

    }
}
}
