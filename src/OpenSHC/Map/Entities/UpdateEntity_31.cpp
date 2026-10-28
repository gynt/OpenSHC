#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402580
    void Entities::UpdateEntity_31()
    {
        short variant = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID;
        if (variant == 0) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter >= 16) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 15;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter + 1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter * 2;
            return;
        }
        if (variant == 1) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter >= 8) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 7;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter + 0x11;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter * 3;
        }
    }

}
}
