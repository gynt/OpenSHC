#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00486A70
    int GameSynchronyState::getLordTypeForPlayer(int playerID)
    {
        if (this->currentPlayerFullIDArray[playerID] != -1) {
            return DAT_GameCore::instance.selectedLordTypes[playerID];
        }
        switch (DAT_GameState::instance.playerDataArray[playerID].aiType) {
        case OpenSHC::AI::AIT_RAT:
        case OpenSHC::AI::AIT_SNAKE:
        case OpenSHC::AI::AIT_PIG:
        case OpenSHC::AI::AIT_WOLF:
        case OpenSHC::AI::AIT_RICHARD:
        case OpenSHC::AI::AIT_FREDERICK:
        case OpenSHC::AI::AIT_PHILIPP:
        case OpenSHC::AI::AIT_SHERIFF:
        case OpenSHC::AI::AIT_MARSHAL:
        case OpenSHC::AI::AIT_ABBOT:
            return 0;
        default:
            return 1;
        }
    }

}
}
