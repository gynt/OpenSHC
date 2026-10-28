#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/g_tribeScanIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // g_tribeScanIndex is declared undefined4 but compared signed (jl at 0x5228BE).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522890
        int TribesState::createTribe(int playerID, int setAsCurrentTribeID)
        {
            for (g_tribeScanIndex::instance = 1; (int)g_tribeScanIndex::instance < 1250; ++g_tribeScanIndex::instance) {
                if (this->tribes[g_tribeScanIndex::instance].tribeState == 0) {
                    int const tribeID = g_tribeScanIndex::instance;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(this->tribes[tribeID]), 0, &this->tribes[tribeID]);
                    if (tribeID <= 0) {
                        return 0;
                    }
                    if (playerID == (int)DAT_GameSynchronyState::instance.currentPlayerSlotID
                        && setAsCurrentTribeID != 0) {
                        this->DAT_CurrentTribeID = tribeID;
                    }
                    this->tribes[tribeID].owner = playerID;
                    this->tribes[tribeID].tribeState = 2;
                    this->tribes[tribeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker++;
                    this->tribes[tribeID].tribeType = 0;
                    this->tribes[tribeID].initZero1c = 0;
                    this->tribes[tribeID].initZero1e = 0;
                    this->tribes[tribeID].tribeBehaviorType = 0;
                    this->tribes[tribeID].initZero30 = 0;
                    this->tribes[tribeID].leaderUnitID = 0;
                    this->tribes[tribeID].size = 0;
                    return tribeID;
                }
            }
            return 0;
        }

    }
}
}
