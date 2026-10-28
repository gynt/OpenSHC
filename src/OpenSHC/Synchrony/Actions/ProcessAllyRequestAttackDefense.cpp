// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // param_4 = request kind: 10 cancels, 11 = defend requestedByPlayerID, anything else = attack targetPlayerID.
    // A human asked player gets the chat (if local) and the request state; an AI decides immediately
    // (determineAIPlayerHelp 0x4AD3A1 / determineAIPlayerAttackRequestResponse 0x4AD447).
    // FUNCTION: STRONGHOLDCRUSADER 0x004AD2F0
    void Actions::ProcessAllyRequestAttackDefense(int targetPlayerID, int playerID, int requestedByPlayerID, int param_4)
    {
        if (param_4 == 10) {
            DAT_GameState::instance.playerDataArray[playerID].allyOrderState = 0;
            DAT_GameState::instance.playerDataArray[requestedByPlayerID].helpNeeded = 0;
            return;
        }
        if (param_4 == 11) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    // "requests you defend him"
                    strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x46));
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(requestedByPlayerID, 0);
                }
                DAT_GameState::instance.playerDataArray[playerID].allyRequestByPlayerID = requestedByPlayerID;
                DAT_GameState::instance.playerDataArray[playerID].allyOrderState = 2;
                DAT_GameState::instance.playerDataArray[requestedByPlayerID].helpNeeded = 1;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::determineAIPlayerHelp, DAT_AICState::ptr)(
                    playerID, requestedByPlayerID)
                != FALSE) {
                DAT_GameState::instance.playerDataArray[playerID].allyRequestByPlayerID = requestedByPlayerID;
                DAT_GameState::instance.playerDataArray[playerID].allyOrderState = 2;
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                // "request you attack"
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x47));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(requestedByPlayerID, targetPlayerID);
            }
            DAT_GameState::instance.playerDataArray[playerID].allyRequestByPlayerID = requestedByPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].allyRequestAttackTarget = targetPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].allyOrderState = 1;
            DAT_GameState::instance.playerDataArray[requestedByPlayerID].helpNeeded = 0;
            return;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::determineAIPlayerAttackRequestResponse, DAT_AICState::ptr)(
                playerID, targetPlayerID, requestedByPlayerID)
            != FALSE) {
            DAT_GameState::instance.playerDataArray[playerID].allyOrderState = 1;
            DAT_GameState::instance.playerDataArray[playerID].allyRequestAttackTarget = targetPlayerID;
            DAT_GameState::instance.playerDataArray[playerID].allyRequestByPlayerID = requestedByPlayerID;
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::abortAttackAndGoIdle, DAT_AICState::ptr)(playerID);
        }
    }

}
}
