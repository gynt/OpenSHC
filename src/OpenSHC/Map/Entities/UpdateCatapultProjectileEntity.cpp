#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401C30
    void Entities::UpdateCatapultProjectileEntity()
    {
        uint uVar1;
        short sVar2;
        int iVar3;
        uVar1 = DAT_CurrentEntityID::instance;
        sVar2 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround;
        if (sVar2 == 0) {
            if (7 < DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
            }
            iVar3 = (int)DAT_EntityState::instance.entityArray[uVar1].graphicType2RelatedOffset
                + (int)DAT_EntityState::instance.entityArray[uVar1].unknownAnimationFrameRelated;
        } else {
            sVar2 = sVar2 + -1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround = sVar2;
            if (sVar2 < 1) {
                DAT_EntityState::instance.entityArray[uVar1].logicalState = 7;
            }
            iVar3 = (int)DAT_EntityState::instance.entityArray[uVar1].graphicType2RelatedOffset;
        }
        DAT_EntityState::instance.entityArray[uVar1].graphicType2 = iVar3;
        if (DAT_EntityState::instance.entityArray[uVar1].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[uVar1].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[uVar1].logicalState = 7;
        }
    }

}
}
