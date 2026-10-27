#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005211B0
        void TribesState::clearAllTribes()
        {
            this->activeTribeCount = 0;
            this->highestActiveTribeID = 1;
            this->clearedOnReset24 = 0;
            // g_tribeScanIndex is declared undefined4 but compared signed (jl at 0x521200)
            for (g_tribeScanIndex::instance = 1; (int)g_tribeScanIndex::instance < 1250; g_tribeScanIndex::instance++) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(this->tribes[g_tribeScanIndex::instance]), 0, &this->tribes[g_tribeScanIndex::instance]);
            }
        }

    }
}
}
