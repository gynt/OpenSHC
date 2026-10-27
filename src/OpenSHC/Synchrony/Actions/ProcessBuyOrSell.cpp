#include "OpenSHC/Synchrony/Actions.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // Buy: price <= gold is signed (jg 0x465E90), gold and marketGold are reduced only if processResourceGain
    // succeeded. Sell: stock >= 0 is signed (jl 0x465ED4).
    // FUNCTION: STRONGHOLDCRUSADER 0x00465E60
    void Actions::ProcessBuyOrSell(int playerID, int buyOrSell, ResourceType resourceType)
    {
        if (buyOrSell == 0) {
            int price = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBatchBuyPrice,
                DAT_GameState::ptr)(playerID, resourceType);
            if (price <= DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD]
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                       DAT_BuildingsState::ptr)(playerID, resourceType, 5)
                    != FALSE) {
                DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD] -= price;
                DAT_GameState::instance.playerDataArray[playerID].marketGold -= price;
            }
        } else if (buyOrSell == 1 && DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] >= 0) {
            int amount = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellResourceAmount,
                DAT_GameState::ptr)(playerID, resourceType);
            int price = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalesPrice,
                DAT_GameState::ptr)(playerID, resourceType);
            DAT_GameSynchronyState::instance.finalResults.finalGold[playerID] += price;
            DAT_GameState::instance.playerDataArray[playerID].currentResources[OpenSHC::Game::Resources::RT_GOLD] += price;
            DAT_GameState::instance.playerDataArray[playerID].marketGold += price;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(playerID, resourceType, amount, 0);
        }
    }

}
}
