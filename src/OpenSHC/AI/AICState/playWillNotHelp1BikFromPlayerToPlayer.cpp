#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace AI {

    using AI::AIType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0DB0
    void AICState::playWillNotHelp1BikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        int iVar1;
        iVar1 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
            playerID);
        if ((iVar1 != 0) && (targetPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
            MACRO_CALL_MEMBER(
                Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(playerID,
                (int)((int)(DAT_GameState::instance.playerDataArray[playerID].aiType + ~AI::AIT_NULL)), 0x1a);
        }
    }

}
}
