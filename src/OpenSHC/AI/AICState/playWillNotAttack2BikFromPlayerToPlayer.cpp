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

    using OpenSHC::AI::AIType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004D0EF0
    void AICState::playWillNotAttack2BikFromPlayerToPlayer(int playerID, int targetPlayerID)
    {
        int iVar1;
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
            playerID);
        if ((iVar1 != 0) && (targetPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) {
            MACRO_CALL_MEMBER(
                OpenSHC::Rendering::Bink::AIMessageQueue_Func::playBikVideoFromPlayer, DAT_VideoBikQueue::ptr)(playerID,
                (int)((int)(DAT_GameState::instance.playerDataArray[playerID].aiType + ~OpenSHC::AI::AIT_NULL)), 0x19);
        }
    }

}
}
