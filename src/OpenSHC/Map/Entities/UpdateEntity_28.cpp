#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004023A0
    void Entities::UpdateEntity_28()
    {
        int iVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        if (0xb < DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownAnimationFrameRelated = 0;
        }
        iVar1 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated + 1
            + DAT_EntityState::instance.entityArray[uVar2].screenDirection * 0xc;
        DAT_EntityState::instance.entityArray[uVar2].graphicType2 = iVar1;
        DAT_EntityState::instance.entityArray[uVar2].imageID = (short)iVar1;
    }

}
}
