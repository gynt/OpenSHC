#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Entities::EntityType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00405C00
    void Entities::UpdateHeadsOnSpikesEntity()
    {
        short* psVar1;
        int _rng;
        uint _id;
        short _x;
        short _y;
        _id = DAT_CurrentEntityID::instance;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2
            = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].rng_1 + 1;
        psVar1 = &DAT_EntityState::instance.entityArray[_id].rng_2;
        *psVar1 = *psVar1 + -1;
        if (DAT_EntityState::instance.entityArray[_id].rng_2 == 0) {
            _rng = (int)SEC_RNG::instance.currentNumber2;
            DAT_EntityState::instance.entityArray[_id].rng_2 = SEC_RNG::instance.currentNumber2 % 500 + 300;
            _x = DAT_EntityState::instance.entityArray[_id].xPosition;
            _y = DAT_EntityState::instance.entityArray[_id].yPosition;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                (undefined4)((int)((int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner)), 0,
                (int)((int)(DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microX)),
                (int)((int)(DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].microY)),
                (int)((int)(DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].height + 0x32)),
                (_x + -0x32 + _rng % 100) * 8, (_y + -0x32 + (_rng >> 8) % 100) * 8, 0xfa, OpenSHC::Map::Entities::EntityTypeInt__ET_CROW,
                0);
        }
    }

}
}
