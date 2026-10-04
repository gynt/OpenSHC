#include "../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;

    // FUNCTION: STRONGHOLDCRUSADER 0x00406FD0
    void Entities::UpdateEntityType8()
    {
        short sVar1;
        uint uVar2;
        uVar2 = DAT_CurrentEntityID::instance;
        sVar1 = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].travelledDistance;
        if (sVar1 < 0xe) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 8;
        } else if (sVar1 < 0x10) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 9;
        } else if (sVar1 < 0x12) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 10;
        } else if (sVar1 < 0x14) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xb;
        } else if (sVar1 < 0x16) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xc;
        } else if (sVar1 < 0x18) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xd;
        } else if (sVar1 < 0x1a) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xe;
        } else if (sVar1 < 0x1c) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0xf;
        } else {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].graphicType2 = 0x10;
        }
        if ((DAT_EntityState::instance.entityArray[uVar2].rng_1 & 3) == 0) {
            DAT_EntityState::instance.entityArray[uVar2].graphicType2
                = DAT_EntityState::instance.entityArray[uVar2].graphicType2 + 0x10;
        }
        if (DAT_EntityState::instance.entityArray[uVar2].someCounter_OR_hitGround != 0) {
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
            MACRO_CALL(Map::Entities_Func::SomeFireSpreadFunction)(
                (int)DAT_EntityState::instance.entityArray[uVar2].owner,
                (int)((int)(DAT_EntityState::instance.entityArray[uVar2].microX)),
                (int)((int)(DAT_EntityState::instance.entityArray[uVar2].microY)),
                (int)((int)(DAT_TileMapState::instance.HeightLayer[DAT_EntityState::instance.entityArray[uVar2].tile]
                    + 8)),
                5);
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (int)DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].xPosition,
                (int)((int)(DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].yPosition)),
                DE::SHCDE::FX_FIRE_START);
        }
        uVar2 = DAT_CurrentEntityID::instance;
        if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation == 0x4c) {
            DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].orientation = 0x3c;
            DAT_EntityState::instance.entityArray[uVar2].logicalState = 3;
        }
    }

}
}
