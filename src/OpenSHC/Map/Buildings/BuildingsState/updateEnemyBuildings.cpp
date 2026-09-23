#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::GameMode;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419D70
void BuildingsState::updateEnemyBuildings(int playerID)

{
int *piVar1;
Building * psVar2;
int _buildingID;
bool bVar2;

bVar2 = DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY;
DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID] = 0;
if ((((bVar2) || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1)) ||
(DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)) &&
(_buildingID = 1, 1 < this->maxBuildingsCount)) {
psVar2 = &this->buildings[1];
do {
/* 
  building owner team is not equal to playerID team
 */

if (((psVar2->logicalState != ((BuildingLogicalState)0)) &&
(DAT_GameState::instance.mapAndTime.playerTeams[psVar2->owner] !=
DAT_GameState::instance.mapAndTime.playerTeams[playerID])) &&
(psVar2->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) {
switch(psVar2->buildingType) {
case OpenSHC::Map::Buildings::BT_STOCKPILE:
case OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE:
case OpenSHC::Map::Buildings::BT_UNKNOWN1:
case OpenSHC::Map::Buildings::BT_MANORHOUSE:
case OpenSHC::Map::Buildings::BT_STONEKEEP:
case OpenSHC::Map::Buildings::BT_STRONGHOLD:
case OpenSHC::Map::Buildings::BT_KEEPFOUR:
case OpenSHC::Map::Buildings::BT_KEEPFIVE:
case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
case OpenSHC::Map::Buildings::BT_TUNNEL:
case OpenSHC::Map::Buildings::BT_CAMPFIRE:
case OpenSHC::Map::Buildings::BT_SIGNPOST:
case OpenSHC::Map::Buildings::BT_PARADEGROUND:
case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
case OpenSHC::Map::Buildings::BT_KILLINGPIT:
case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
case OpenSHC::Map::Buildings::BT_KEEPDOOR:
case OpenSHC::Map::Buildings::BT_CATAPULT:
case OpenSHC::Map::Buildings::BT_TREBUCHET:
case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
case OpenSHC::Map::Buildings::BT_SIEGETOWER:
case OpenSHC::Map::Buildings::BT_SHIELD:
case OpenSHC::Map::Buildings::BT_UNKNOWN4:
case OpenSHC::Map::Buildings::BT_POND:
break;
OpenSHC::Map::Buildings::default:
DAT_GameState::instance.mapAndTime.playerEnemyBuildingIDs[playerID]
[DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID]] = _buildingID;
DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID[playerID]
[DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[playerID]] = psVar2->uid;
piVar1 = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex + playerID;
*piVar1 = *piVar1 + 1;
}
}
_buildingID = _buildingID + 1;
psVar2 = psVar2 + 0x196;
} while (_buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}