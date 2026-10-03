#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401E20
    void Entities::UpdateEntity_20_37()
    {
        uint uVar1;
        short sVar2;
        uint uVar3;
        uVar1 = DAT_CurrentEntityID::instance;
        uVar3
            = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field12_0x1c + 8U & 0x8000000f;
        if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff0) + 1;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = uVar3
            + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field45_0x6a * 0x10
            + (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        sVar2 = DAT_EntityState::instance.entityArray[uVar1].someCounter_OR_hitGround;
        if ((sVar2 != 0)
            && (sVar2 = sVar2 + -1, DAT_EntityState::instance.entityArray[uVar1].someCounter_OR_hitGround = sVar2,
                sVar2 < 1)) {
            DAT_EntityState::instance.entityArray[uVar1].logicalState = 7;
        }
        if (DAT_EntityState::instance.entityArray[uVar1].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[uVar1].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[uVar1].logicalState = 7;
        }
    }

}
}
