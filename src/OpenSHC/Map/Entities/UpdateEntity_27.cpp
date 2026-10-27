#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402330
    void Entities::UpdateEntity_27()
    {
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 & 7) + 1
            + (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID % 3) * 8;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime++;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime > 10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 8;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
    }

}
}
