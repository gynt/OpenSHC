#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401D70
    void Entities::UpdateArrowsSecondaryEntity()
    {
        short animFrame = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter;
        short frameCount = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCount;
        if (animFrame >= frameCount) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            return;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = (animFrame * 32) / frameCount;
    }

}
}
