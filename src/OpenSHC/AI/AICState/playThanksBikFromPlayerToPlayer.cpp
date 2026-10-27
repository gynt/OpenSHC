#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AICState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/thanksBikLastPlayTime.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0A80
    void AICState::playThanksBikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(playerID) == 0) {
            return;
        }

        int aicIndex = DAT_GameState::instance.playerDataArray[playerID].aiType - 1;
        DAT_GameState::instance.playerDataArray[playerID].aiRequestDelay = this->aics[aicIndex].aiRequestDelay;

        if (targetPlayerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .lordDeathStatusOrKiller
            != 0) {
            return;
        }

        DWORD now = timeGetTime();
        if (thanksBikLastPlayTime::instance != 0 && now - thanksBikLastPlayTime::instance < 1200000) {
            return;
        }

        thanksBikLastPlayTime::instance = now;
        MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(
            playerID, aicIndex, 15);
    }
}
}
