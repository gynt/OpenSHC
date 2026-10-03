#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401BA0
    void Entities::UpdateArrowEntity()
    {
        short sVar1;
        uint _entityID;
        _entityID = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field45_0x6a * 0x10
            + (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].field12_0x1c
            + (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        sVar1 = DAT_EntityState::instance.entityArray[_entityID].someCounter_OR_hitGround;
        if (sVar1 != 0) {
            DAT_EntityState::instance.entityArray[_entityID].someCounter_OR_hitGround = sVar1 + -1;
            if (DAT_EntityState::instance.entityArray[_entityID].rng_2 != 0) {
                DAT_EntityState::instance.entityArray[_entityID].someCounter_OR_hitGround = 0;
            }
            if (DAT_EntityState::instance.entityArray[_entityID].someCounter_OR_hitGround < 1) {
                DAT_EntityState::instance.entityArray[_entityID].logicalState = 7;
            }
        }
        if (DAT_EntityState::instance.entityArray[_entityID].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[_entityID].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[_entityID].logicalState = 7;
        }
    }

}
}
