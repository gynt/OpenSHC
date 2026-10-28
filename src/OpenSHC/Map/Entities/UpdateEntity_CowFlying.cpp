#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402180
    void Entities::UpdateEntity_CowFlying()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown != 0) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter < 100) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 100;
            }
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter >= 0x78) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0x77;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown--;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].burnCyclesOrImpactCountdown <= 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                + (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter - 100) / 4 + 12;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID = 0;
        }
        else {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter >= 12) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
            }
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset
                + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
                = (short)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 + 0x11;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 7;
        }
    }

}
}
