#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E8F0
    int GameSynchronyState::checkPlayerSetValid()
    {
        int _somePlayerID;
        int _someCounter;
        int _validPlayerCount;
        int _teamMemberCounts[9];
        _someCounter = 0;
        _validPlayerCount = 0;
        _teamMemberCounts[0] = 0;
        _teamMemberCounts[1] = 0;
        _teamMemberCounts[2] = 0;
        _teamMemberCounts[3] = 0;
        _teamMemberCounts[4] = 0;
        _teamMemberCounts[5] = 0;
        _teamMemberCounts[6] = 0;
        _teamMemberCounts[7] = 0;
        _teamMemberCounts[8] = 0;
        for (_somePlayerID = 1; _somePlayerID < 9; _somePlayerID = _somePlayerID + 1) {
            if (this->currentPlayerFullIDArray[_somePlayerID] == -1) {
                /*
                  no human player in this slot
                 */
                if (this->currentAIArray[_somePlayerID] == 0) {
                    continue;
                }
            } else {
                _someCounter = _someCounter + 1;
            }
            _teamMemberCounts[DAT_GameState::instance.mapAndTime.playerTeams[_somePlayerID]]
                = _teamMemberCounts[DAT_GameState::instance.mapAndTime.playerTeams[_somePlayerID]] + 1;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER) {
                _someCounter = _someCounter + 1;
            }
        }
        if (_someCounter < 2) {
            return 0;
        }
        for (_somePlayerID = 1; _somePlayerID < 9; _somePlayerID = _somePlayerID + 1) {
            if (_teamMemberCounts[_somePlayerID] != 0) {
                _validPlayerCount = _validPlayerCount + 1;
                if (2 < _teamMemberCounts[_somePlayerID]) {
                    return 0;
                }
            }
        }
        return _validPlayerCount;
    }

}
}
