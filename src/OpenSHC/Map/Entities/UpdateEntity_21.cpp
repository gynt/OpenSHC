#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401EA0
    void Entities::UpdateEntity_21()
    {
        short sVar1;
        uint uVar2;
        int iVar3;
        uVar2 = DAT_CurrentEntityID::instance;
        sVar1 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID == 2) {
            iVar3 = sVar1 * 7;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = ((short)(iVar3 / 200) + (sVar1 >> 0xf) + 0x18) - (short)((longlong)iVar3 * 0x51eb851f >> 0x3f);
            sVar1 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
            if (sVar1 < 200) {
                if (sVar1 < 0xc) {
                    DAT_EntityState::instance.entityArray[uVar2].graphicType2
                        = ((int)DAT_EntityState::instance.entityArray[uVar2].graphicType2RelatedOffset - (sVar1 / 4))
                        + 0xf;
                    iVar3 = (int)DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
                    DAT_EntityState::instance.entityArray[uVar2].unkMinusOne = 0x1f - (short)(iVar3 / 4);
                }
                iVar3 = ((int)sVar1 << 4) / 200;
                if (3 < iVar3) {
                    iVar3 = 4;
                }
                DAT_EntityState::instance.entityArray[uVar2].graphicType2
                    = DAT_EntityState::instance.entityArray[uVar2].graphicType2RelatedOffset + 0xb + iVar3;
            }
        } else {
            iVar3 = sVar1 * 0xf;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne
                = ((short)(iVar3 / 400) + (sVar1 >> 0xf) + 0x10) - (short)((longlong)iVar3 * 0x51eb851f >> 0x3f);
            sVar1 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
            if (sVar1 < 400) {
                if (sVar1 < 8) {
                    DAT_EntityState::instance.entityArray[uVar2].graphicType2
                        = ((int)DAT_EntityState::instance.entityArray[uVar2].graphicType2RelatedOffset - (int)sVar1)
                        + 7;
                }
                DAT_EntityState::instance.entityArray[uVar2].graphicType2
                    = (sVar1 * 0xf) / 400 + (int)DAT_EntityState::instance.entityArray[uVar2].graphicType2RelatedOffset;
            }
        }
        DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
    }

}
}
