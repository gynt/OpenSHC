#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00402730
    void Entities::UpdateEntity_41()
    {
        short sVar1;
        int iVar2;
        short _playerID;
        uint _section1025ID;
        _section1025ID = DAT_CurrentEntityID::instance;
        _playerID = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
        DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].unkOne_1 = 2;
        sVar1 = DAT_EntityState::instance.entityArray[_section1025ID].unknownAnimationFrameRelated;
        if (DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[sVar1] < 1) {
            DAT_EntityState::instance.entityArray[_section1025ID].logicalState = 3;
            DAT_GameState::instance.playerDataArray[_playerID].someCount33 = 0x46;
        } else {
            DAT_EntityState::instance.entityArray[_section1025ID].unkMinusOne
                = (short)DAT_EntityDefinedData::instance.SharedEntityAnimationFrames[sVar1] + -1;
            DAT_EntityState::instance.entityArray[_section1025ID].graphicType2 = 1;
        }
        DAT_EntityState::instance.entityArray[_section1025ID].field82_0xbe = 0x2e;
        iVar2 = DAT_EntityState::instance.entityArray[_section1025ID].displayValue;
        if (iVar2 < 0x28) {
            DAT_EntityState::instance.entityArray[_section1025ID].field83_0xc0 = 0x82;
        } else {
            DAT_EntityState::instance.entityArray[_section1025ID].field83_0xc0 = (iVar2 < 0x3c) + 0x80;
        }
        DAT_EntityState::instance.entityArray[_section1025ID].field86_0xc8 = 0x16;
        _playerID = DAT_EntityState::instance.entityArray[_section1025ID].unknownAnimationFrameRelated;
        if (0x10 < _playerID) {
            DAT_EntityState::instance.entityArray[_section1025ID].field86_0xc8 = 0x26 - _playerID;
        }
        DAT_EntityState::instance.entityArray[_section1025ID].field87_0xca = 0x22;
        DAT_EntityState::instance.entityArray[_section1025ID].field88_0xcc = 0x32;
        _playerID = DAT_EntityState::instance.entityArray[_section1025ID].unknownAnimationFrameRelated;
        if (0x10 < _playerID) {
            DAT_EntityState::instance.entityArray[_section1025ID].field88_0xcc = _playerID + 0x22;
        }
        DAT_EntityState::instance.entityArray[_section1025ID].field89_0xce = 0x27;
    }

}
}
