#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  merge with cls_409330?
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AC80
int BuildingsState::canNavigateToDefensiveBuilding(int playerID,int buildingXPosition,int buildingYPosition,int buildingID)

{
BuildingLogicalStateShort BVar1;
short sVar2;
int iVar3;
ushort _areaNumber;
BuildingTypeShort _buildingType;

_areaNumber = DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix[buildingYPosition].addXgetTile +
buildingXPosition];
/* 
  now it means buildingID
 */

buildingYPosition = 0;
if (0 < this->maxBuildingsCount) {
do {
buildingID = buildingID + 1;
if (this->maxBuildingsCount <= buildingID) {
buildingID = 1;
}
BVar1 = this->buildings[buildingID].logicalState;
if (((((BVar1 != ((BuildingLogicalState)0)) && (BVar1 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(iVar3 = (int)this->buildings[buildingID].owner, iVar3 == playerID)) &&
((((_buildingType = this->buildings[buildingID].buildingType,
_buildingType == OpenSHC::Map::Buildings::BT_TOWER1 || (_buildingType == OpenSHC::Map::Buildings::BT_TOWER2)) ||
((_buildingType == OpenSHC::Map::Buildings::BT_TOWER3 ||
((_buildingType == OpenSHC::Map::Buildings::BT_TOWER4 || (_buildingType == OpenSHC::Map::Buildings::BT_TOWER5)))))) ||
((_buildingType == OpenSHC::Map::Buildings::BT_MANORHOUSE ||
(((((_buildingType == OpenSHC::Map::Buildings::BT_STONEKEEP || (_buildingType == OpenSHC::Map::Buildings::BT_STRONGHOLD)) ||
(_buildingType == OpenSHC::Map::Buildings::BT_KEEPFOUR)) ||
((_buildingType == OpenSHC::Map::Buildings::BT_KEEPFIVE || (_buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE)))) ||
(_buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL)))))))) &&
((sVar2 = this->buildings[buildingID].someX, sVar2 != 0 &&
(iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(iVar3, (dword)((int)((int)(short)_areaNumber)), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix
[this->buildings[buildingID].someY].
addXgetTile + (int)sVar2])), 0), iVar3 != 0)))) {
return buildingID;
}
buildingYPosition = buildingYPosition + 1;
} while (buildingYPosition < this->maxBuildingsCount);
}
return 0;
}


}
}
}