#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // The second argument is never read (ret 0xC, only [esp+4] and [esp+0xC] are used).
        // FUNCTION: STRONGHOLDCRUSADER 0x00522950
        int TribesState::createPlayerTribe(int playerID, undefined4 one, int tribeID)
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->tribes[tribeID]), 0, &this->tribes[tribeID]);
            this->tribes[tribeID].tribeState = 2;
            this->tribes[tribeID].owner = playerID;
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
}
}
