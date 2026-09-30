#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:56:35.138000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004023F0
    uint Entities::UpdateEntity_29()
    {
        ushort uVar1;
        uint uVar2;
        short sVar3;
        short sVar4;
        uint uVar5;
        uVar2 = DAT_CurrentEntityID::instance;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].targetZ == 0) {
            uVar5 = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field12_0x1c + 0x91;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = uVar5;
            DAT_EntityState::instance.entityArray[uVar2].imageID
                = DAT_EntityState::instance.entityArray[uVar2].field12_0x1c + 0xa1;
            return uVar5;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_2 < 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 3;
        }
        if (7 < DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated) {
            DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 0;
        }
        DAT_EntityState::instance.entityArray[uVar2].graphicType2
            = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 1
            + DAT_EntityState::instance.entityArray[uVar2].field12_0x1c * 8;
        DAT_EntityState::instance.entityArray[uVar2].imageID
            = DAT_EntityState::instance.entityArray[uVar2].field12_0x1c + 0x81;
        sVar3 = SEC_RNG::instance.currentNumber2;
        sVar4 = DAT_EntityState::instance.entityArray[uVar2].rng_2;
        if ((0 < sVar4)
            && (sVar4 = sVar4 + -1, DAT_EntityState::instance.entityArray[uVar2].rng_2 = sVar4, sVar4 == 0)) {
            DAT_EntityState::instance.entityArray[uVar2].rng_2 = -10 - sVar3 % 0x32;
        }
        uVar1 = DAT_EntityState::instance.entityArray[uVar2].rng_2;
        uVar5 = (uint)uVar1;
        if ((short)uVar1 < 0) {
            uVar5 = uVar5 + 1;
            DAT_EntityState::instance.entityArray[uVar2].rng_2 = (short)uVar5;
            if ((short)uVar5 == 0) {
                uVar5 = (int)sVar3 / 200;
                DAT_EntityState::instance.entityArray[uVar2].rng_2 = sVar3 % 200 + 0xaa;
            }
        }
        return uVar5;
    }

}
}
