#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AF70
        void TroopValueState::pruneStaleArcherPoints()
        {
            // archer point record: {x, y, tile, counterStamp, tribeID, tribeUID, reservationTimer, 0}
            for (int slot = 1; slot < 200; ++slot) {
                if (DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][3]
                    != DAT_TroopValueState::instance.attackInfo.someCounter1) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot]), 0,
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot]);
                }
                else {
                    if (DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][4] != 0
                        && MACRO_CALL_MEMBER(TribesState_Func::tribeCorrespondsWithUID, DAT_TribesState::ptr)(
                               DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][4],
                               DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][5])
                            == FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue,
                            DAT_LowLevelMemory::ptr)(sizeof(DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot]),
                            0, DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot]);
                    }
                    if (DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][6] > 0) {
                        DAT_TroopValueState::instance.attackInfo.archerPointRecords[slot][6]--;
                    }
                }
            }
        }

    }
}
}
