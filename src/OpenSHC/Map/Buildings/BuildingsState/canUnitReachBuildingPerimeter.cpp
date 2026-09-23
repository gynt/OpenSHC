#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410440
undefined4 BuildingsState::canUnitReachBuildingPerimeter(int param_1,int param_2)

{
byte bVar1;
ushort uVar2;
ushort uVar3;
uint size;
int iVar4;
int iVar5;
BOOLEnum BVar6;
int iVar7;
BOOLEnum BVar8;
uint uVar9;
uint uVar10;
int iVar11;

iVar5 = param_1;
if ((param_1 == 0) || (1999 < param_1)) {
return(undefined4)( 0);
}
uVar2 = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_2].tile];
bVar1 = DAT_TileMapState::instance.DefaultHeightLayer
[this->buildings[param_1].currentTilePositionAdjusted];
size = this->buildings[param_1].widthOrHeight;
iVar4 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
BVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsOnlyArabAssassins, DAT_UnitsState::ptr)();
param_1 = 0;
if (0 < iVar4) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupNextCandidateLocationComputeOffsets2, this)(size, 1, param_1, 0);
iVar11 = DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[iVar5].y + this->DAT_TempYOffset].
addXgetTile + (int)(short)this->buildings[iVar5].x +
this->DAT_TempXOffset;
uVar3 = DAT_TileMapState::instance.PathConnectionLayer[iVar11];
uVar9 = (uint)DAT_TileMapState::instance.HeightLayer[iVar11];
if (DAT_TileMapState::instance.BuildingLayer[iVar11] != 0) {
iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID, this)((int)(short)DAT_TileMapState::instance.BuildingLayer[iVar11]);
uVar9 = uVar9 + iVar7;
}
uVar9 = bVar1 - uVar9;
uVar10 = (int)uVar9 >> 0x1f;
if (((int)((uVar9 ^ uVar10) - uVar10) < 0x10) && ((int)(short)uVar3 != 0)) {
if (BVar6 == FALSE) {
iVar11 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)();
BVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[param_2].owner, (dword)((int)(
(int)(short)uVar2)), (dword)((int)((int)(short)uVar3)), iVar11);
}
else {
BVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanReachUsingCachedAreaLogic, DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[param_2].tile, iVar11);
}
if (BVar8 != FALSE) {
return(undefined4)( 1);
}
}
param_1 = param_1 + 1;
} while (param_1 < iVar4);
}
return(undefined4)( 0);
}


}
}
}