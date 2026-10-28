#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00518130
        void TroopValueState::clearAttackInfo()
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_IntegerValue, DAT_LowLevelMemory::ptr)(
                sizeof(AttackInfo), 0, &DAT_TroopValueState::instance.attackInfo);
            DAT_TroopValueState::instance.attackInfo.nof_fpoints = 0;
            DAT_TroopValueState::instance.attackInfo.defenseScheduleTick = 0;
            DAT_TroopValueState::instance.attackInfo.attackWaveMusicPending = 0;
            DAT_TroopValueState::instance.attackInfo.activeAttackSignpostIndex = 0;
            DAT_TroopValueState::instance.attackInfo.tilemapOffset = 0;
            DAT_TroopValueState::instance.attackInfo.currentAttackWaveSlot = 1;
            DAT_TroopValueState::instance.attackInfo.aiTroops = -1;
        }

    }
}
}
