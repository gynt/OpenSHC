#include "../Audio.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentPlayerRanking.hpp"
#include "OpenSHC/Globals/unitValueKilledByCurrentPlayer.hpp"
#include "OpenSHC/Globals/unitValueKilledByCurrentPlayerHistory.hpp"
#include "OpenSHC/Globals/DAT_DestroyedBuildingsCountHistory.hpp"
#include "OpenSHC/Globals/DAT_IsKeepEnclosed.hpp"
#include "OpenSHC/Globals/lastKeepEnclosedCheckTime.hpp"
#include "OpenSHC/Globals/currentPlayerUnitValueLostHistory.hpp"
#include "OpenSHC/Globals/currentPlayerUnitValueLostToPlayer.hpp"
#include "OpenSHC/Globals/DWORD_KeepEnclosementTimer.hpp"
#include "OpenSHC/Globals/DWORD_LatestPLayerStatusMessageTime.hpp"
#include "OpenSHC/Globals/currentPlayerUnitValueLostToPlayerHistory.hpp"
#include "OpenSHC/Globals/INT_00b98484.hpp"
#include "OpenSHC/Globals/lastTeamBikMessageState.hpp"
#include "OpenSHC/Globals/INT_00b98698.hpp"

namespace OpenSHC {
namespace Audio {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044A720
    void ResetGreatestLordGenieSpeechState()
    {
        DAT_CurrentPlayerRanking::instance = -1;
        INT_00b98698::instance = -1;
        INT_00b98484::instance = -1;
        DAT_IsKeepEnclosed::instance = 0;

        unsigned int currentTime = timeGetTime();
        DWORD_KeepEnclosementTimer::instance = currentTime;
        DWORD_LatestPLayerStatusMessageTime::instance = currentTime;
        lastKeepEnclosedCheckTime::instance = currentTime;

        unitValueKilledByCurrentPlayer::instance = 0;
        for (int i = 0; i < 9; i++) {
            currentPlayerUnitValueLostToPlayer::instance[i] = 0;
        }
        memset(unitValueKilledByCurrentPlayerHistory::instance, 0, sizeof(unitValueKilledByCurrentPlayerHistory::instance));
        memset(
            currentPlayerUnitValueLostHistory::instance, 0, sizeof(currentPlayerUnitValueLostHistory::instance));
        MACRO_CALL(OS_Func::_memset)(currentPlayerUnitValueLostToPlayerHistory::ptr, 0,
            sizeof(currentPlayerUnitValueLostToPlayerHistory::instance));

        lastTeamBikMessageState::instance = 1;

        memset(DAT_DestroyedBuildingsCountHistory::instance, 0, sizeof(DAT_DestroyedBuildingsCountHistory::instance));
    }

}
}
