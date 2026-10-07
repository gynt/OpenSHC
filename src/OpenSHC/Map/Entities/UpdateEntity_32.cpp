#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402620
    void Entities::UpdateEntity_32()
    {
        uint uVar1;
        uVar1 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 7U)
            + (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        DAT_EntityState::instance.entityArray[uVar1].unkMinusOne = 0;
        if (DAT_EntityState::instance.entityArray[uVar1].someCounter_OR_hitGround != 0) {
            DAT_EntityState::instance.entityArray[uVar1].logicalState = 3;
        }
    }

}
}
