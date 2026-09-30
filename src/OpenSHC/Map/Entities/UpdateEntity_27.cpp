#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      decompilerscript: committed: 2025-01-30 21:56:35.138000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00402330
    void Entities::UpdateEntity_27()
    {
        short* psVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 7U) + 1
            + ((int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID % 3) * 8;
        psVar1 = &DAT_EntityState::instance.entityArray[uVar2].rng_2;
        *psVar1 = *psVar1 + 1;
        if (10 < DAT_EntityState::instance.entityArray[uVar2].rng_2) {
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 8;
        }
        if (DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround != 0) {
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
        }
    }

}
}
