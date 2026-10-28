#include "OpenSHC/Map/Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // The return value is not meaningful (the callers ignore it); it reproduces what the original leaves in eax.
    // FUNCTION: STRONGHOLDCRUSADER 0x004023F0
    uint Entities::UpdateEntity_29()
    {
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].targetZ == 0) {
            uint result = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex + 0x91;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = result;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
                = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex + 0xa1;
            return result;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime < 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 3;
        }
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter >= 8) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter = 0;
        }
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].animFrameCounter + 1
            + DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex * 8;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].imageID
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].screenDirectionIndex + 0x81;
        short randomValue = SEC_RNG::instance.currentNumber2;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime > 0) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime--;
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime == 0) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime
                    = -10 - randomValue % 50;
            }
        }
        uint result = (ushort)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime;
        if ((short)result < 0) {
            result++;
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime = (short)result;
            if ((short)result == 0) {
                result = randomValue / 200;
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].variantOrLifetime
                    = randomValue % 200 + 0xaa;
            }
        }
        return result;
    }

}
}
