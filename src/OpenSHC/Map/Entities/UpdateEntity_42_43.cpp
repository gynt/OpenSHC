#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/PTR_ARRAY_Unknown_UnitGMHeights.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402820
    void Entities::UpdateEntity_42_43()
    {
        short sVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 2;
        sVar1 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
        if (DAT_EntityDefinedData::instance.field60_0x107c[sVar1] < 1) {
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
        } else {
            DAT_EntityState::instance.entityArray[uVar2].unkMinusOne
                = (short)DAT_EntityDefinedData::instance.field60_0x107c[sVar1] + -1;
            DAT_EntityState::instance.entityArray[uVar2].graphicType2 = 1;
        }
        DAT_EntityState::instance.entityArray[uVar2].field82_0xbe = 0x2e;
        DAT_EntityState::instance.entityArray[uVar2].field86_0xc8 = 0x16;
        sVar1 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
        if (0x10 < sVar1) {
            DAT_EntityState::instance.entityArray[uVar2].field86_0xc8 = 0x26 - sVar1;
        }
        DAT_EntityState::instance.entityArray[uVar2].field87_0xca = 0x2d
            - *(short*)((int)PTR_ARRAY_Unknown_UnitGMHeights::instance
                  + (GMTotalPicturesProcessed::instance[DAT_EntityState::instance.entityArray[uVar2].field82_0xbe]
                        + (int)DAT_EntityState::instance.entityArray[uVar2].field83_0xc0)
                      * 0x10
                  + 0x72)
                / 2;
        DAT_EntityState::instance.entityArray[uVar2].field88_0xcc = 0x32;
        sVar1 = DAT_EntityState::instance.entityArray[uVar2].unknownAnimationFrameRelated;
        if (0x10 < sVar1) {
            DAT_EntityState::instance.entityArray[uVar2].field88_0xcc = sVar1 + 0x22;
        }
        DAT_EntityState::instance.entityArray[uVar2].field89_0xce = 0x27;
    }

}
}
