#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

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
                1062748, 0, (void*)((int)(&DAT_TroopValueState::instance.attackInfo)));
            DAT_TroopValueState::instance.attackInfo.nof_fpoints = 0;
            DAT_TroopValueState::instance.attackInfo.field127522_0x2b574 = 0;
            DAT_TroopValueState::instance.attackInfo.field105440_0x25b00 = 0;
            DAT_TroopValueState::instance.attackInfo.field128056_0x469d4 = 0;
            DAT_TroopValueState::instance.attackInfo.tilemapOffset = 0;
            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
            DAT_TroopValueState::instance.attackInfo.aiTroops = -1;
        }

    }
}
}
