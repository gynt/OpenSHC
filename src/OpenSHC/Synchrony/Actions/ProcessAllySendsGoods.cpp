// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // Gold: amount is capped at the sender's gold (signed jge 0x4ADDFB) and moved directly. Other goods
    // (partial pitch counts as pitch, 0x4ADE29) go through processResourceGain/Loss; both stats add getSellPrice
    // priced for the receiver (0x4ADE63, 0x4ADE77). The deposit sound, the chat lines and the final compare
    // use the original goodsType (jump table 0x4ADFE4/0x4ADFF0: iron/gold, weapons/armour, rest).
    // FUNCTION: STRONGHOLDCRUSADER 0x004ADDD0
    void Actions::ProcessAllySendsGoods(int receiverPlayerID, ResourceType goodsType, int amount, int senderPlayerID)
    {
        if (goodsType == OpenSHC::Game::Resources::RT_GOLD) {
            if (DAT_GameState::instance.playerDataArray[senderPlayerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                < amount) {
                amount = DAT_GameState::instance.playerDataArray[senderPlayerID]
                             .currentResources[OpenSHC::Game::Resources::RT_GOLD];
            }
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[receiverPlayerID] += amount;
            DAT_GameState::instance.playerDataArray[receiverPlayerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                += amount;
            DAT_GameState::instance.playerDataArray[senderPlayerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                -= amount;
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[senderPlayerID] += amount;
        } else {
            ResourceType resourceType = goodsType;
            if (goodsType == OpenSHC::Game::Resources::RT_PARTIALPITCH) {
                resourceType = OpenSHC::Game::Resources::RT_PITCH;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                DAT_BuildingsState::ptr)(receiverPlayerID, resourceType, amount);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(senderPlayerID, resourceType, amount, 0);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[receiverPlayerID]
                += MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                    receiverPlayerID, resourceType, amount);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[senderPlayerID]
                += MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                    receiverPlayerID, resourceType, amount);
        }
        if (receiverPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            switch (goodsType) {
            case OpenSHC::Game::Resources::RT_IRON:
            case OpenSHC::Game::Resources::RT_GOLD:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::scheduleSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_IRON_DEPOSIT);
                break;
            case OpenSHC::Game::Resources::RT_BOW:
            case OpenSHC::Game::Resources::RT_CROSSBOW:
            case OpenSHC::Game::Resources::RT_SPEAR:
            case OpenSHC::Game::Resources::RT_PIKE:
            case OpenSHC::Game::Resources::RT_MACE:
            case OpenSHC::Game::Resources::RT_SWORD:
            case OpenSHC::Game::Resources::RT_LEATHERARMOR:
            case OpenSHC::Game::Resources::RT_IRONARMOR:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::scheduleSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_SWORD_DEPOSIT);
                break;
            default:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::scheduleSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_FLOUR_DEPOSIT);
                break;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
            if (receiverPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                // "Goods received from ally"
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 1));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(senderPlayerID, 0);
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__d__s___005a7674,
                    amount,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, goodsType));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(senderPlayerID, receiverPlayerID);
            }
            if (senderPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                // "Goods sent to ally"
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 2));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(senderPlayerID, 0);
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__d__s_005a766c,
                    amount,
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, goodsType));
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(senderPlayerID, 0);
            }
        }
        if (goodsType
            == DAT_GameState::instance.playerDataArray[senderPlayerID].requestedGoodsTypeByPlayer[receiverPlayerID]) {
            DAT_GameState::instance.playerDataArray[senderPlayerID].requestedGoodsTypeByPlayer[receiverPlayerID] = 0;
            DAT_GameState::instance.playerDataArray[senderPlayerID].requestedGoodsAmountByPlayer[receiverPlayerID] = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playThanksBikFromPlayerToPlayer, DAT_AICState::ptr)(
            receiverPlayerID, senderPlayerID);
    }

}
}
