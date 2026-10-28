#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402660
    void Entities::UpdateEntity_40()
    {
        int ownerID = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].ticksPerAnimFrame = 2;
        int animTick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter;
        if (DAT_EntityDefinedData::instance.popupFadeLevels[animTick] <= 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
            DAT_GameState::instance.playerDataArray[ownerID].popupEntity40Cooldown = 0x46;
        }
        else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].fadeLevel
                = (short)DAT_EntityDefinedData::instance.popupFadeLevels[animTick] - 1;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 1;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupIconGmID = 0x2e;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupIconFrame = 0xab;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupIconOffsetX = 0x16;
        short tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter;
        if (tick > 0x10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupIconOffsetX = 0x26 - tick;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupIconOffsetY = 0x28;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupNumberOffsetX = 0x32;
        tick = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter;
        if (tick > 0x10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupNumberOffsetX = tick + 0x22;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].popupNumberOffsetY = 0x27;
    }

}
}
