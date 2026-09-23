#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::Resources::ResourceType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041C240
void BuildingsState::applyFoodLossPercentageToPlayer(int param_1,int param_2)

{
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(param_1, OpenSHC::Game::Resources::RT_BREAD, 
(DAT_GameState::instance.playerDataArray[param_1].currentResources[10] * param_2)
/ 100, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(param_1, OpenSHC::Game::Resources::RT_CHEESE, 
(DAT_GameState::instance.playerDataArray[param_1].currentResources[0xb] * param_2) / 100
, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(param_1, OpenSHC::Game::Resources::RT_MEAT, 
(DAT_GameState::instance.playerDataArray[param_1].currentResources[0xc] * param_2) / 100
, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(param_1, OpenSHC::Game::Resources::RT_APPLE, 
(DAT_GameState::instance.playerDataArray[param_1].currentResources[0xd] * param_2) / 100
, 0);
return;
}


}
}
}