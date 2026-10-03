#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004024F0
    void Entities::UpdateEntity_30()
    {
        short* psVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID != 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0;
            psVar1 = &DAT_EntityState::instance.entityArray[uVar2].unitID;
            *psVar1 = *psVar1 + 1;
            DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 0;
            DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround = 1;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].someCounter_OR_hitGround = 0;
        if (7 < DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated) {
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
            DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 7;
        }
        DAT_EntityState::instance.entityArray[uVar2].graphicType2
            = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 1;
        DAT_EntityState::instance.entityArray[uVar2].imageID
            = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 9;
        DAT_EntityState::instance.entityArray[uVar2].unkMinusOne = -1;
    }

}
}
