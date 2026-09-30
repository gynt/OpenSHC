#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        /*
          decompilerscript: committed: 2025-01-30 21:56:35.138000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00404A10
        int EntityState::arrowShootingRelated(
            int microX, int microY, int height, int destMicroX, int destMicroY, int destHeight)
        {
            uint uVar1;
            uVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                microX, microY, height, destMicroX, destMicroY, destHeight, 0);
            if (uVar1 == 0) {
                uVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    destMicroX, destMicroY, destHeight, microX, microY, height, 0);
            }
            return (int)(uVar1);
        }

    }
}
}
