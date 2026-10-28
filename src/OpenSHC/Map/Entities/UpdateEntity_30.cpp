#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004024F0
    void Entities::UpdateEntity_30()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID++;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown = 1;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown = 0;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter >= 8) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 7;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter + 1;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter + 9;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = -1;
    }

}
}
