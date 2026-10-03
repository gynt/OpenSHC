#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00401FF0
    void Entities::UpdateEntity_PoisonCloud()
    {
        short* psVar1;
        short sVar2;
        uint uVar3;
        uint uVar4;
        uVar3 = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkMinusOne = -1;
        psVar1 = &DAT_EntityState::instance.entityArray[uVar3].rng_2;
        *psVar1 = *psVar1 + 1;
        sVar2 = DAT_EntityState::instance.entityArray[uVar3].unknownAnimationFrameRelated;
        if (sVar2 < 8) {
            DAT_EntityState::instance.entityArray[uVar3].graphicType2
                = ((int)DAT_EntityState::instance.entityArray[uVar3].graphicType2RelatedOffset - (int)sVar2) + 0xf;
        } else if (sVar2 < 0x3f9) {
            if (0xf < sVar2) {
                DAT_EntityState::instance.entityArray[uVar3].unknownAnimationFrameRelated = 8;
            }
            uVar4 = DAT_EntityState::instance.entityArray[uVar3].rng_1 + -8
                    + (int)DAT_EntityState::instance.entityArray[uVar3].unknownAnimationFrameRelated
                & 0x80000007;
            if ((int)uVar4 < 0) {
                uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
            }
            DAT_EntityState::instance.entityArray[uVar3].graphicType2
                = uVar4 + (int)DAT_EntityState::instance.entityArray[uVar3].graphicType2RelatedOffset;
            if (799 < DAT_EntityState::instance.entityArray[uVar3].rng_2) {
                DAT_EntityState::instance.entityArray[uVar3].unknownAnimationFrameRelated = 0x3f8;
            }
        } else if (sVar2 == 0x400) {
            DAT_EntityState::instance.entityArray[uVar3].logicalState = 3;
        } else {
            DAT_EntityState::instance.entityArray[uVar3].graphicType2
                = DAT_EntityState::instance.entityArray[uVar3].graphicType2RelatedOffset + -0x3f0 + (int)sVar2;
            sVar2 = (DAT_EntityState::instance.entityArray[uVar3].unknownAnimationFrameRelated + -0x3f8) * 4;
            DAT_EntityState::instance.entityArray[uVar3].unkMinusOne = sVar2;
            if (0x1f < sVar2) {
                DAT_EntityState::instance.entityArray[uVar3].unkMinusOne = 0x1f;
            }
            DAT_EntityState::instance.entityArray[uVar3].unkMinusOne
                = -1 - DAT_EntityState::instance.entityArray[uVar3].unkMinusOne;
        }
        DAT_EntityState::instance.entityArray[uVar3].imageID
            = (short)DAT_EntityState::instance.entityArray[uVar3].graphicType2 + 0x10;
        sVar2 = DAT_EntityState::instance.entityArray[uVar3].unknownDistanceRelatedValue;
        if (sVar2 != 0) {
            if (DAT_EntityState::instance.entityArray[uVar3].uidRef
                == DAT_EntityState::instance.entityArray[sVar2].uid) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)((int)DAT_EntityState::instance.entityArray[sVar2].xPosition,
                    (int)((int)(DAT_EntityState::instance.entityArray[sVar2].yPosition)),
                    (int)((int)(DAT_EntityState::instance.entityArray[uVar3].xPosition)),
                    (int)((int)(DAT_EntityState::instance.entityArray[uVar3].yPosition)));
                if (6 < DAT_DirectionAlgorithmState::instance.distanceHigh) {
                    DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unknownDistanceRelatedValue
                        = 0;
                }
            } else {
                DAT_EntityState::instance.entityArray[uVar3].unknownDistanceRelatedValue = 0;
            }
        }
    }

}
}
