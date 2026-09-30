#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:56:35.138000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00401D70
    void Entities::UpdateArrowsSecondaryEntity()
    {
        short sVar1;
        short sVar2;
        sVar1 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        sVar2 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkThree_1;
        if (sVar2 <= sVar1) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
            = (short)(((int)sVar1 << 5) / (int)sVar2);
    }

}
}
