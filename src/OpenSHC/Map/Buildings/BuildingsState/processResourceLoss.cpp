#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::Resources::ResourceType;
using OpenSHC::Game::GameMode2;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BD70
void BuildingsState::processResourceLoss(int playerID,ResourceType resourceType,int amount,int param_4)

{
int *piVar1;
int iVar2;
bool bVar3;
BuildingType BVar4;
Building * psVar7;
int *piVar5;
int _buildingID;

bVar3 = false;
if (resourceType != ((ResourceType)0)) {
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
if (param_4 == 0) {
piVar5 = DAT_GameState::instance.playerDataArray[playerID].startResources + resourceType;
*piVar5 = *piVar5 - amount;
return;
}
}
else {
BVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
if (BVar4 == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
if (param_4 == 0) {
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + resourceType;
*piVar5 = *piVar5 - amount;
return;
}
}
else {
_buildingID = 1;
if (1 < this->maxBuildingsCount) {
psVar7 = &this->buildings[1];
piVar5 = this->buildings[1].resources + resourceType;
do {
if ((((psVar7->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
((int)(short)psVar7->buildingType == BVar4)) &&
(psVar7->owner == playerID)) && (0 < *piVar5)) {
if (param_4 == 0) {
psVar7->someResourceNumber = 0;
}
iVar2 = *piVar5;
bVar3 = true;
if (iVar2 < amount) {
amount = amount - iVar2;
if (param_4 != 0) {
psVar7->someResourceNumber = (short)iVar2;
goto LAB_0041be9e;
}
piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + resourceType;
*piVar5 = 0;
*piVar1 = *piVar1 - iVar2;
LAB_0041bea2:
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, this)(_buildingID);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
}
else {
if (param_4 == 0) {
*piVar5 = iVar2 - amount;
piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + resourceType;
*piVar1 = *piVar1 - amount;
}
else {
psVar7->someResourceNumber = (short)amount;
}
amount = 0;
LAB_0041be9e:
if (param_4 == 0) goto LAB_0041bea2;
}
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(_buildingID);
}
_buildingID = _buildingID + 1;
psVar7 = psVar7 + 0x196;
piVar5 = piVar5 + 0xcb;
} while (_buildingID < this->maxBuildingsCount);
if (bVar3) {
return;
}
}
DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType] = 0;
}
}
}
return;
}


}
}
}