#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00421BE0
char BuildingsState::resolveBuildingEntryAccessibility(int buildingID,int param_2,int x,int y)

{
short sVar1;
bool bVar2;
int iVar3;
int iVar4;
char cVar5;
dword fromArea;
uint uVar6;
uint uVar7;

if (buildingID < 1) {
return '\0';
}
fromArea = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
sVar1 = this->buildings[buildingID].buildingEntryX;
uVar7 = (uint)*(byte *)(DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[buildingID].y].addXgetTile +
0x1d32c38 + (int)(short)this->buildings[buildingID].x);
if ((sVar1 == 0) && (this->buildings[buildingID].buildingEntryY == 0)) {
bVar2 = true;
}
else {
iVar4 = (int)sVar1 +
DAT_ViewportRenderState::instance.translationMatrix
[this->buildings[buildingID].buildingEntryY].addXgetTile;
uVar6 = (uint)DAT_TileMapState::instance.HeightLayer[iVar4];
if (DAT_TileMapState::instance.BuildingLayer[iVar4] != 0) {
iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)(short)DAT_TileMapState::instance.BuildingLayer[iVar4]);
uVar6 = uVar6 + iVar3;
}
bVar2 = (DAT_TileMapState::instance.LogicLayer[iVar4] &0x50501481U) != 0 ||
((int)(uVar7 + 0x10) < (int)uVar6 || (int)(uVar6 + 0x10) < (int)uVar7);
if (((fromArea != 0) && ((int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar4] != fromArea))
&& (iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(
(int)this->buildings[buildingID].owner, (dword)((int)(fromArea)), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar4])), 0), iVar4 == 0
)) {
bVar2 = true;
}
}
cVar5 = '\x01';
this->buildings[buildingID].hasAccessToKeep = 1;
if (bVar2) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(buildingID, 0);
iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromCustomArea, this)(buildingID, param_2, 0, x, y);
if (iVar4 == 0) {
this->buildings[buildingID].hasAccessToKeep = 0;
return '\0';
}
cVar5 = (iVar4 == 2) + '\x01';
}
return cVar5;
}


}
}
}