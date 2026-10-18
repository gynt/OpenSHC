#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047EB80
    int GameSynchronyState::addPlayerToCurrentPlayerArray(int playerFullID)
    {
        int _slot;
        for (int _slot_2 = 1; _slot_2 < 9; _slot_2 = _slot_2 + 1) {
            if (this->currentPlayerFullIDArray[_slot_2] == playerFullID) {
                return _slot_2;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            for (_slot = 1; _slot < 9; _slot = _slot + 1) {
                if (((this->currentPlayerFullIDArray[_slot] == -1)
                        || (this->currentPlayerFullIDArray[_slot] == playerFullID))
                    && this->currentAIArray[_slot] <= 0)
                    goto LAB_0047ebf4;
            }
        }
        for (_slot = 1; _slot < 9; _slot = _slot + 1) {
            if ((this->currentPlayerFullIDArray[_slot] == -1)
                || (this->currentPlayerFullIDArray[_slot] == playerFullID))
                goto LAB_0047ebf4;
        }
        _slot = 0;
    LAB_0047ebf4:
        this->currentPlayerFullIDArray[_slot] = playerFullID;
        return _slot;
    }

}
}
