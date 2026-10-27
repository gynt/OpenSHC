#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402260
    void Entities::UpdateEntity_26()
    {
        short animTick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter;
        if (animTick < 0x14) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0x14 - animTick;
        }
        else if (animTick < 0x28) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0;
        }
        else if (animTick < 0x48) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = animTick - 0x28;
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0x1f;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel > 0x1f) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0x1f;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel < 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel = 0;
        }
        int nextFrame = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter + 1;
        if (nextFrame > 0x47) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = nextFrame;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = (short)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 + 0x50;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel
            = -1 - DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel;
    }

}
}
