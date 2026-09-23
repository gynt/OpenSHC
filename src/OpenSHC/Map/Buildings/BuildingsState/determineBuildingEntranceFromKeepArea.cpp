#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
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

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041ADE0
undefined4 BuildingsState::determineBuildingEntranceFromKeepArea(int buildingID,int workerIndexPlus1,BOOLEnum flag)

{
int buildingSize;
ushort *puVar1;
ushort *puVar2;
short sVar3;
int _playerID;
int _buildingAtCandidateHeight;
dword _candidateArea;
dword _canNav;
int iVar4;
dword toArea;
int iVar5;
dword _keepArea;
int _index;
int _height;
int _candidateTile;
int iVar6;
uint _heightAtCandidate;
uint uVar7;
short _flagCopy;
ushort *local_2c;
int local_28;
ushort *local_24;
int _heightStep;
short _buildingAtCandidate;
int _buildingID;
int _index2;
int _count2;
int _accessibleTilesCount;
BOOLEnum _flag;
Building *_pBuilding1;
Building *_pBuilding2;
short *_pEntranceX;
short *_pEntranceY;

_flag = flag;
_buildingID = buildingID;
_playerID = (int)this->buildings[buildingID].owner;
_keepArea = (dword)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_GameState::instance.playerDataArray[_playerID].campground.tileEntry];
_index = 0;
local_28 = 0;
_heightStep = 0x10;
if (this->buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_QUARRY) {
_heightStep = 0x20;
}
buildingSize = this->buildings[buildingID].widthOrHeight + flag * 2;
_accessibleTilesCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
if (0 < _accessibleTilesCount) {
/* 
  this modulates what angle is chosen or at least makes sure it doesn't
   overflow
 */

_index = (int)(short)this->buildings[buildingID].entranceAttemptTileIndex %
_accessibleTilesCount;
this->buildings[buildingID].entranceAttemptTileIndex = (ushort)_index;
}
_pEntranceX = &this->buildings[buildingID].buildingEntryX;
_height = (int)this->buildings[buildingID].terrainHeightUnk;
*_pEntranceX = 0;
_pEntranceY = &this->buildings[buildingID].buildingEntryY;
*_pEntranceY = 0;
flag = FALSE;
_flagCopy = (short)_flag;
_index2 = _index;
if (0 < _accessibleTilesCount) {
_pBuilding1 = this->buildings + buildingID;
_pBuilding2 = this->buildings + buildingID;
/* 
  todo: feat: set this value based on direction of keep
 */

buildingID = _index;
do {
/* 
  offset is set here, for each try a different location is tried
 */

MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, buildingID, 0);
_candidateTile =
((*(int *)((int)DAT_ViewportRenderState::ptr +
(((int)(short)_pBuilding1->y - _flag) + this->DAT_TempYOffset) *
0xc + 0x188728) + (int)(short)_pBuilding2->x) - _flag) +
this->DAT_TempXOffset;
_buildingAtCandidate = *(short *)((int)DAT_TileMapState::ptr + _candidateTile * 2 + 0x2029b0);
_heightAtCandidate = (uint)*(byte *)((int)DAT_TileMapState::ptr + _candidateTile + 0x29fa30);
if (_buildingAtCandidate != 0) {
_buildingAtCandidateHeight =MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)_buildingAtCandidate);
_heightAtCandidate = _heightAtCandidate + _buildingAtCandidateHeight;
}
if (((((*(uint *)((int)DAT_TileMapState::ptr + _candidateTile * 4 + 0x165160) &0x50501481) == 0)
&& (_height <= (int)(_heightStep + _heightAtCandidate))) &&
((int)(_heightAtCandidate - _heightStep) <= _height)) &&
((((_keepArea == 0 ||
(_candidateArea =
(dword)*(short *)((int)DAT_TileMapState::ptr + _candidateTile * 2 + 0x363ed0),
_candidateArea == _keepArea)) ||
((_canNav = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(_playerID, (dword)((int)(_keepArea)), (dword)((int)(_candidateArea)), 0),
_canNav != 0 ||
(DAT_BuildingDefinedData::instance.ABuildingTypeValueArray
[(short)this->buildings[_buildingID].buildingType] != FALSE)))) &&
(local_28 = local_28 + 1, workerIndexPlus1 <= local_28)))) goto LAB_0041b11e_done;
buildingID = buildingID + 1;
if (_accessibleTilesCount <= buildingID) {
buildingID = 0;
}
flag = flag + TRUE;
_index2 = buildingID;
} while ((int)flag < _accessibleTilesCount);
}
buildingID = _index2;
_count2 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCountForOneLarger[buildingSize];
flag = FALSE;
if (0 < _count2) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(buildingSize, 1, buildingID, 0);
iVar6 = ((*(int *)((int)DAT_ViewportRenderState::ptr +
(((int)(short)this->buildings[_buildingID].y - _flag) +
this->DAT_TempYOffset) * 0xc + 0x188728) +
(int)(short)this->buildings[_buildingID].x) - _flag) +
this->DAT_TempXOffset;
sVar3 = *(short *)((int)DAT_TileMapState::ptr + iVar6 * 2 + 0x2029b0);
uVar7 = (uint)*(byte *)((int)DAT_TileMapState::ptr + iVar6 + 0x29fa30);
if (sVar3 != 0) {
iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)sVar3);
uVar7 = uVar7 + iVar4;
}
if ((((*(uint *)((int)DAT_TileMapState::ptr + iVar6 * 4 + 0x165160) &0x50501481) == 0) &&
(_height <= (int)(uVar7 + 0x10))) &&
((((int)(uVar7 - 0x10) <= _height &&
((((_keepArea == 0 ||
(toArea = (dword)*(short *)((int)DAT_TileMapState::ptr + iVar6 * 2 + 0x363ed0),
toArea == _keepArea)) ||
(iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(_playerID, (dword)((int)(_keepArea)), (dword)((int)(toArea)), 0), iVar6 != 0))
|| (DAT_BuildingDefinedData::instance.ABuildingTypeValueArray
[(short)this->buildings[_buildingID].buildingType] != FALSE)))) &&
(local_28 = local_28 + 1, workerIndexPlus1 <= local_28)))) {
LAB_0041b11e_done:
local_24 = &this->buildings[_buildingID].x;
local_2c = &this->buildings[_buildingID].y;
*_pEntranceX = (*local_24 - _flagCopy) + (short)this->DAT_TempXOffset;
*_pEntranceY = (*local_2c - _flagCopy) + (short)this->DAT_TempYOffset;
return(undefined4)( 1);
}
buildingID = buildingID + 1;
if (_count2 <= buildingID) {
buildingID = 0;
}
flag = flag + TRUE;
} while ((int)flag < _count2);
}
iVar6 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
if (iVar6 < 1) {
buildingID = 0;
}
else {
buildingID = (int)(short)this->buildings[_buildingID].entranceAttemptTileIndex %
iVar6;
this->buildings[_buildingID].entranceAttemptTileIndex = (ushort)buildingID;
}
flag = FALSE;
if (0 < iVar6) {
puVar1 = &this->buildings[_buildingID].y;
puVar2 = &this->buildings[_buildingID].x;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, buildingID, 0);
iVar4 = ((*(int *)((int)DAT_ViewportRenderState::ptr +
(((int)(short)*puVar1 - _flag) + this->DAT_TempYOffset) * 0xc +
0x188728) + (int)(short)*puVar2) - _flag) +
this->DAT_TempXOffset;
sVar3 = *(short *)((int)DAT_TileMapState::ptr + iVar4 * 2 + 0x2029b0);
uVar7 = (uint)*(byte *)((int)DAT_TileMapState::ptr + iVar4 + 0x29fa30);
if (sVar3 != 0) {
iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)sVar3);
uVar7 = uVar7 + iVar5;
}
if ((((*(uint *)((int)DAT_TileMapState::ptr + iVar4 * 4 + 0x165160) &0x50501481) == 0) &&
(_height <= (int)(uVar7 + 0x10))) &&
(((int)(uVar7 - 0x10) <= _height &&
((*(short *)((int)DAT_TileMapState::ptr + iVar4 * 2 + 0x363ed0) != 0 &&
(local_28 = local_28 + 1, workerIndexPlus1 <= local_28)))))) {
*_pEntranceX = (*puVar2 - _flagCopy) + (short)this->DAT_TempXOffset;
*_pEntranceY = (*puVar1 - _flagCopy) + (short)this->DAT_TempYOffset;
return(undefined4)( 2);
}
buildingID = buildingID + 1;
if (iVar6 <= buildingID) {
buildingID = 0;
}
flag = flag + TRUE;
} while ((int)flag < iVar6);
}
return(undefined4)( 0);
}


}
}
}