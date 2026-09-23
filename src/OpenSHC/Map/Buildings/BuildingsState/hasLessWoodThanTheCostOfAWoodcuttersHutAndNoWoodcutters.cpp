#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::GameMode2;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C1A0
uint BuildingsState::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters(int playerID,int param_2)

{
int _woodcutterID;

if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) && (param_2 == 3)) {
_woodcutterID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingOfType, this)(playerID, OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT);
if (_woodcutterID != 0) {
return 0;
}
return (uint)(DAT_GameState::instance.playerDataArray[playerID].currentResources[2] <
this->buildingCosts[3].requiredWood);
}
return 0;
}


}
}
}