#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005227E0
        int TribesState::createTribeForPlayer(int playerID)
        {
            for (int tribeID = 0x4E2 - playerID; tribeID > 0; tribeID -= 8) {
                if (this->tribes[tribeID].tribeState == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(this->tribes[tribeID]), 0, &this->tribes[tribeID]);
                    if (tribeID <= 0) {
                        return 0;
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
