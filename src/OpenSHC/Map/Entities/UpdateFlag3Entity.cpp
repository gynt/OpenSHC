#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402A20
    void Entities::UpdateFlag3Entity()
    {
        uint uVar1;
        int iVar2;
        uVar1 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2RelatedOffset;
        if (DAT_LandscapeState::instance.wind.countdown
            <= (int)((byte)DAT_EntityState::instance.entityArray[uVar1].yPosition & 0x1f)) {
            DAT_EntityState::instance.entityArray[uVar1].rng_2 = (short)DAT_LandscapeState::instance.wind.value;
        }
        iVar2 = (int)DAT_EntityState::instance.entityArray[uVar1].someTracker;
        if (!iVar2) {
            iVar2 = DAT_EntityDefinedData::instance
                        .field64_0x15dc[DAT_EntityState::instance.entityArray[uVar1].unknownAnimationFrameRelated];
        } else {
            if (1 < iVar2 - 1U) {}
            iVar2 = DAT_EntityDefinedData::instance
                        .field65_0x17a4[DAT_EntityState::instance.entityArray[uVar1].unknownAnimationFrameRelated];
        }
        if (0 < iVar2) {
            DAT_EntityState::instance.entityArray[uVar1].graphicType2
                = DAT_EntityState::instance.entityArray[uVar1].graphicType2 + iVar2 + -1;
        }
        DAT_EntityState::instance.entityArray[uVar1].unknownAnimationFrameRelated = 0;
        DAT_EntityState::instance.entityArray[uVar1].someTracker = DAT_EntityState::instance.entityArray[uVar1].rng_2;
    }

}
}
