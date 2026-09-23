#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041B2B0
undefined4 BuildingsState::determineBuildingEntranceFromCustomArea(int buildingID,int param_2,int param_3,int x,int y)

{
int buildingSize;
short *psVar1;
short *psVar2;
ushort *puVar3;
ushort *puVar4;
short sVar5;
int playerID;
int iVar6;
dword dVar7;
dword fromArea;
int iVar8;
int iVar9;
int iVar10;
int iVar11;
uint uVar12;
short sVar13;
int local_24;
int local_18;
int _accessibleTiles;

iVar11 = buildingID;
playerID = (int)this->buildings[buildingID].owner;
iVar8 = 0;
fromArea = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
local_24 = 0;
local_18 = 0x10;
if (this->buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_QUARRY) {
local_18 = 0x20;
}
buildingSize = this->buildings[buildingID].widthOrHeight + param_3 * 2;
iVar10 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
if (0 < iVar10) {
iVar8 = (int)(short)this->buildings[buildingID].entranceAttemptTileIndex % iVar10;
this->buildings[buildingID].entranceAttemptTileIndex = (ushort)iVar8;
}
psVar1 = &this->buildings[buildingID].buildingEntryX;
iVar9 = (int)this->buildings[buildingID].terrainHeightUnk;
*psVar1 = 0;
psVar2 = &this->buildings[buildingID].buildingEntryY;
*psVar2 = 0;
y = 0;
sVar13 = (short)param_3;
if (0 < iVar10) {
puVar3 = &this->buildings[buildingID].y;
puVar4 = &this->buildings[buildingID].x;
buildingID = iVar8;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, buildingID, 0);
iVar8 = (*(int *)((int)DAT_ViewportRenderState::ptr +
(((short)*puVar3 - param_3) + this->DAT_TempYOffset) * 0xc +
0x188728) - param_3) + (int)(short)*puVar4 +
this->DAT_TempXOffset;
sVar5 = *(short *)((int)DAT_TileMapState::ptr + iVar8 * 2 + 0x2029b0);
uVar12 = (uint)*(byte *)((int)DAT_TileMapState::ptr + iVar8 + 0x29fa30);
if (sVar5 != 0) {
iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)sVar5);
uVar12 = uVar12 + iVar6;
}
if ((((((*(uint *)((int)DAT_TileMapState::ptr + iVar8 * 4 + 0x165160) &0x50501481) == 0) &&
(iVar9 <= (int)(local_18 + uVar12))) && ((int)(uVar12 - local_18) <= iVar9)) &&
(((fromArea == 0 ||
(dVar7 = (dword)*(short *)((int)DAT_TileMapState::ptr + iVar8 * 2 + 0x363ed0),
dVar7 == fromArea)) ||
(iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(playerID, (dword)((int)(fromArea)), (dword)((int)(dVar7)), 0), iVar8 != 0)))) &&
(local_24 = local_24 + 1, param_2 <= local_24)) {
*psVar1 = ((short)this->DAT_TempXOffset - sVar13) + *puVar4;
*psVar2 = (*puVar3 - sVar13) + (short)this->DAT_TempYOffset;
return(undefined4)( 1);
}
buildingID = buildingID + 1;
if (iVar10 <= buildingID) {
buildingID = 0;
}
y = y + 1;
iVar8 = buildingID;
} while (y < iVar10);
}
buildingID = iVar8;
iVar8 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCountForOneLarger[buildingSize];
y = 0;
if (0 < iVar8) {
puVar3 = &this->buildings[iVar11].y;
puVar4 = &this->buildings[iVar11].x;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(buildingSize, 1, buildingID, 0);
iVar10 = (*(int *)((int)DAT_ViewportRenderState::ptr +
(((short)*puVar3 - param_3) + this->DAT_TempYOffset) * 0xc +
0x188728) - param_3) + (int)(short)*puVar4 +
this->DAT_TempXOffset;
sVar5 = *(short *)((int)DAT_TileMapState::ptr + iVar10 * 2 + 0x2029b0);
uVar12 = (uint)*(byte *)((int)DAT_TileMapState::ptr + iVar10 + 0x29fa30);
if (sVar5 != 0) {
iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)sVar5);
uVar12 = uVar12 + iVar6;
}
if (((((*(uint *)((int)DAT_TileMapState::ptr + iVar10 * 4 + 0x165160) &0x50501481) == 0) &&
(iVar9 <= (int)(uVar12 + 0x10))) &&
(((int)(uVar12 - 0x10) <= iVar9 &&
((((fromArea == 0 ||
(dVar7 = (dword)*(short *)((int)DAT_TileMapState::ptr + iVar10 * 2 + 0x363ed0),
dVar7 == fromArea)) ||
(iVar10 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(playerID, (dword)((int)(fromArea)), (dword)((int)(dVar7)), 0), iVar10 != 0)) ||
(DAT_BuildingDefinedData::instance.ABuildingTypeValueArray
[(short)this->buildings[iVar11].buildingType] != FALSE)))))) &&
(local_24 = local_24 + 1, param_2 <= local_24)) {
*psVar1 = ((short)this->DAT_TempXOffset - sVar13) + *puVar4;
*psVar2 = (*puVar3 - sVar13) + (short)this->DAT_TempYOffset;
return(undefined4)( 1);
}
buildingID = buildingID + 1;
if (iVar8 <= buildingID) {
buildingID = 0;
}
y = y + 1;
} while (y < iVar8);
}
_accessibleTiles = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
if (_accessibleTiles < 1) {
buildingID = 0;
}
else {
buildingID = (int)(short)this->buildings[iVar11].entranceAttemptTileIndex %
_accessibleTiles;
this->buildings[iVar11].entranceAttemptTileIndex = (ushort)buildingID;
}
y = 0;
if (0 < _accessibleTiles) {
puVar3 = &this->buildings[iVar11].y;
puVar4 = &this->buildings[iVar11].x;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, buildingID, 0);
iVar11 = (*(int *)((int)DAT_ViewportRenderState::ptr +
(((short)*puVar3 - param_3) + this->DAT_TempYOffset) * 0xc +
0x188728) - param_3) + (int)(short)*puVar4 +
this->DAT_TempXOffset;
sVar5 = *(short *)((int)DAT_TileMapState::ptr + iVar11 * 2 + 0x2029b0);
uVar12 = (uint)*(byte *)((int)DAT_TileMapState::ptr + iVar11 + 0x29fa30);
if (sVar5 != 0) {
iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)sVar5);
uVar12 = uVar12 + iVar8;
}
if ((((*(uint *)((int)DAT_TileMapState::ptr + iVar11 * 4 + 0x165160) &0x50501481) == 0) &&
(iVar9 <= (int)(uVar12 + 0x10))) &&
(((int)(uVar12 - 0x10) <= iVar9 &&
((*(short *)((int)DAT_TileMapState::ptr + iVar11 * 2 + 0x363ed0) != 0 &&
(local_24 = local_24 + 1, param_2 <= local_24)))))) {
*psVar1 = ((short)this->DAT_TempXOffset - sVar13) + *puVar4;
*psVar2 = (*puVar3 - sVar13) + (short)this->DAT_TempYOffset;
return(undefined4)( 2);
}
buildingID = buildingID + 1;
if (_accessibleTiles <= buildingID) {
buildingID = 0;
}
y = y + 1;
} while (y < _accessibleTiles);
}
return(undefined4)( 0);
}


}
}
}