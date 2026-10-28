// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // Clears the goods request the requester made to the denying player (word stores 0x4AE029 / 0x4AE032), then
    // posts "request denied" (ALLIES2 0) when the requester is the local slot (no human check, jne 0x4AE06E).
    // FUNCTION: STRONGHOLDCRUSADER 0x004AE010
    void Actions::ProcessAllyDeniesRequest(int requesterPlayerID, int denyingPlayerID)
    {
        DAT_GameState::instance.playerDataArray[denyingPlayerID].requestedGoodsTypeByPlayer[requesterPlayerID] = 0;
        DAT_GameState::instance.playerDataArray[denyingPlayerID].requestedGoodsAmountByPlayer[requesterPlayerID] = 0;
        if (requesterPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 0));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(requesterPlayerID, 0);
        }
    }

}
}
