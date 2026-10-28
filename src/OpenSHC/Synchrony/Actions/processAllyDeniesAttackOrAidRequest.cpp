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

    // responder state 2 = aid ("Will not come to your aid", ALLIES2 6), 1 = attack ("Will not attack", ALLIES2 5, with
    // the target); the chat is posted only for the local human requester. Both states are always cleared.
    // FUNCTION: STRONGHOLDCRUSADER 0x004AD1E0
    void Actions::processAllyDeniesAttackOrAidRequest(int requesterPlayerID, int responderPlayerID)
    {
        if (DAT_GameState::instance.playerDataArray[responderPlayerID].allyOrderState == 2) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[requesterPlayerID] != -1
                && requesterPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 6));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(responderPlayerID, 0);
            }
        } else if (DAT_GameState::instance.playerDataArray[responderPlayerID].allyOrderState == 1) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[requesterPlayerID] != -1
                && requesterPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 5));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(
                    responderPlayerID, DAT_GameState::instance.playerDataArray[responderPlayerID].allyRequestAttackTarget);
            }
        }
        DAT_GameState::instance.playerDataArray[responderPlayerID].allyOrderState = 0;
        DAT_GameState::instance.playerDataArray[requesterPlayerID].helpNeeded = 0;
    }

}
}
