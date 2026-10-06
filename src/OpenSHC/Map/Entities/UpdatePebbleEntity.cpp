#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401CC0
    void Entities::UpdatePebbleEntity()
    {
        uint uVar1;
        short sVar2;
        uVar1 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        sVar2 = DAT_EntityState::instance.entityArray[uVar1].someCounter_OR_hitGround;
        if ((sVar2)
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
