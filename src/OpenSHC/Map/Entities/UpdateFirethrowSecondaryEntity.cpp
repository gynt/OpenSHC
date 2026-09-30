#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:56:35.138000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00401D20
    void Entities::UpdateFirethrowSecondaryEntity()
    {
        short sVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        sVar1 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (sVar1 < DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkThree_1) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                + (int)sVar1;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
        if (DAT_EntityState::instance.entityArray[uVar2].gmLookupValue == 1) {
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne = 0x10;
        }
    }

}
}
