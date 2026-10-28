// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // param_2 = goods index, resource = param_2 + 1 (lea edi, [edx + 1] at 0x4AD7C6). askee is the requester.
    // A human asked player stores the request (type = param_2 + 1, amount) and gets the chat when local;
    // an AI asked player sends non-gold goods at once (0x4AD8B4); gold requests to an AI are ignored.
    // FUNCTION: STRONGHOLDCRUSADER 0x004AD7C0
    void Actions::ProcessAllyRequestingGoods(int askedPlayerID, int param_2, int amount, int askee)
    {
        ResourceType resourceType = (ResourceType)(param_2 + 1);
        if (resourceType == OpenSHC::Game::Resources::RT_GOLD) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[askedPlayerID] != -1) {
                DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsTypeByPlayer[askee]
                    = (short)(param_2 + 1);
                DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsAmountByPlayer[askee]
                    = (short)amount;
                if (askedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    // "is requesting goods from you"
                    strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x48));
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(askee, 0);
                }
            }
        } else if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[askedPlayerID] != -1) {
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsTypeByPlayer[askee]
                = (short)(param_2 + 1);
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsAmountByPlayer[askee] = (short)amount;
            if (askedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                // "is requesting goods from you"
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x48));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(askee, 0);
            }
        } else {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playGoodsSentBikFromPlayerToPlayer, DAT_AICState::ptr)(
                askedPlayerID, askee);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                DAT_BuildingsState::ptr)(askee, resourceType, amount);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(askedPlayerID, resourceType, amount, 0);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[askee]
                += MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                    askedPlayerID, resourceType, amount);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[askedPlayerID]
                += MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                    askedPlayerID, resourceType, amount);
        }
    }

}
}
