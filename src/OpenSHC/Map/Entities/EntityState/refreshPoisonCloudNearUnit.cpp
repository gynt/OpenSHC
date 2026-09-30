#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00401880
        void EntityState::refreshPoisonCloudNearUnit(int param_1)
        {
            EntityTypeShort* pEVar1;
            int iVar2;
            iVar2 = 1;
            if (1 < this->maxEntityCount) {
                pEVar1 = &this->entityArray[1].entityType;
                do {
                    if ((((pEVar1[-1] == 2) && (*pEVar1 == OpenSHC::Map::Entities::ET_COW_POISON_CLOUD))
                            && ((short)pEVar1[-0xb] < 0x3e9))
                        && (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[param_1].x,
                                (int)((int)(DAT_UnitsState::instance.units[param_1].y)),
                                (int)((int)((short)pEVar1[0xd])), (int)((int)((short)pEVar1[0xe]))),
                            DAT_DirectionAlgorithmState::instance.distanceHigh < 7)) {
                        pEVar1[-0xb] = 0x3f8;
                    }
                    iVar2 = iVar2 + 1;
                    pEVar1 = pEVar1 + 0x74;
                } while (iVar2 < this->maxEntityCount);
            }
        }

    }
}
}
