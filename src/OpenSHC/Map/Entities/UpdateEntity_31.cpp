#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402580
    void Entities::UpdateEntity_31()
    {
        short sVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        sVar1 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unitID_OR_seaGullID;
        if (!sVar1) {
            if (16
                < DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
                DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 0xf;
            }
            DAT_EntityState::instance.entityArray[uVar2].graphicType2
                = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 1;
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne
                = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated * 2;
        }
        if (sVar1 == 1) {
            if (7 < DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState = 3;
                DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated = 7;
            }
            DAT_EntityState::instance.entityArray[uVar2].graphicType2
                = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 0x11;
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne
                = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated * 3;
        }
    }

}
}
