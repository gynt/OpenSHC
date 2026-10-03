#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402260
    void Entities::UpdateEntity_26()
    {
        short sVar1;
        uint uVar2;
        int iVar3;
        uVar2 = DAT_CurrentEntityID::instance;
        sVar1 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (sVar1 < 0x14) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 0x14 - sVar1;
        } else if (sVar1 < 0x28) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 0;
        } else if (sVar1 < 0x48) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = sVar1 + -0x28;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = 0x1f;
        }
        if (0x1f < DAT_EntityState::instance.entityArray[uVar2].unkMinusOne) {
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne = 0x1f;
        }
        if (DAT_EntityState::instance.entityArray[uVar2].unkMinusOne < 0) {
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne = 0;
        }
        iVar3 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 1;
        if (iVar3 < 0x48) {
            DAT_EntityState::instance.entityArray[uVar2].graphicType2 = iVar3;
        } else {
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
        }
        DAT_EntityState::instance.entityArray[uVar2].imageID
            = (short)DAT_EntityState::instance.entityArray[uVar2].graphicType2 + 0x50;
        DAT_EntityState::instance.entityArray[uVar2].unkMinusOne
            = -1 - DAT_EntityState::instance.entityArray[uVar2].unkMinusOne;
    }

}
}
