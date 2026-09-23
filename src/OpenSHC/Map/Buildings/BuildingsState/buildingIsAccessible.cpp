#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  returns 2 if a gate is locked. returns 1 if accessible.
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00421A40
int BuildingsState::buildingIsAccessible(int buildingID,int amountUnk)

{
short sVar1;
bool bVar2;
uint uVar3;
int _buildingHeight;
int _canNav;
dword _areaNumber;
int _tileNumber;
uint _height1005_2;

if (buildingID < 1) {
return 0;
}
_canNav = (int)this->buildings[buildingID].owner;
_areaNumber = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_GameState::instance.playerDataArray[_canNav].campground.tileEntry];
uVar3 = (uint)*(byte *)(DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[buildingID].y].addXgetTile +
0x1d32c38 + (int)(short)this->buildings[buildingID].x);
sVar1 = this->buildings[buildingID].buildingEntryX;
if ((sVar1 == 0) && (this->buildings[buildingID].buildingEntryY == 0)) {
bVar2 = true;
}
else {
_tileNumber = (int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[this->buildings[buildingID].buildingEntryY].addXgetTile;
_height1005_2 = (uint)DAT_TileMapState::instance.HeightLayer[_tileNumber];
if (DAT_TileMapState::instance.BuildingLayer[_tileNumber] != 0) {
_buildingHeight =MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)(short)DAT_TileMapState::instance.BuildingLayer[_tileNumber]);
_height1005_2 = _height1005_2 + _buildingHeight;
}
bVar2 = (DAT_TileMapState::instance.LogicLayer[_tileNumber] &0x50501481U) != 0 ||
((int)(uVar3 + 0x10) < (int)_height1005_2 || (int)(_height1005_2 + 0x10) < (int)uVar3);
if ((((_areaNumber != 0) &&
((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tileNumber] != _areaNumber)) &&
(DAT_BuildingDefinedData::instance.ABuildingTypeValueArray
[(short)this->buildings[buildingID].buildingType] == FALSE)) &&
(_canNav = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(_canNav, (dword)((int)(_areaNumber)), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tileNumber])), 0),
_canNav == 0)) {
bVar2 = true;
}
}
_canNav = 1;
this->buildings[buildingID].hasAccessToKeep = 1;
if (bVar2) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(buildingID, 0);
_canNav = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea, this)(buildingID, amountUnk, FALSE);
if (_canNav == 0) {
this->buildings[buildingID].hasAccessToKeep = 0;
return 0;
}
_canNav = (_canNav == 2) + 1;
}
return _canNav;
}


}
}
}