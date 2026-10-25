#include "../GreatestLord.func.hpp"

#include "OpenSHC/Audio/SFX.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044B760
    int GreatestLord::GetPlayerAtRank(int rankingPosition)
    {
        int _ranking[9];
        _ranking[0] = -1;
        _ranking[1] = -1;
        _ranking[2] = -1;
        _ranking[3] = -1;
        _ranking[4] = -1;
        _ranking[5] = -1;
        _ranking[6] = -1;
        _ranking[7] = -1;
        _ranking[8] = -1;
        for (int _playerID = 0; _playerID < 9; _playerID = _playerID + 1) {
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1)
            || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {
            int _rank = MACRO_CALL(OpenSHC::Audio::SFX_Func::ComputePlayerRanking)(_playerID);
            _ranking[_rank] = _playerID;
            }
        }
        return _ranking[rankingPosition + 1];
    }

}
}
