#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BA00
int BuildingsState::findParticularBuilding(undefined4 param_1,int x,int y,int buildingSize,BuildingType buildingType,int buildingID)

{
int iVar1;
int iVar2;
int try;
int _buildingSize;

_buildingSize = buildingSize;
iVar1 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
try = 0;
buildingSize = 0;
if (0 < iVar1) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(_buildingSize, 1, try, 0);
iVar2 = (int)(short)DAT_TileMapState::instance.BuildingLayer
[DAT_ViewportRenderState::instance.translationMatrix
[this->DAT_TempYOffset + y].addXgetTile +
this->DAT_TempXOffset + x];
if ((((0 < iVar2) && (buildingID != iVar2)) &&
(this->buildings[iVar2].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL)) &&
((int)(short)this->buildings[iVar2].buildingType == buildingType)) {
return iVar2;
}
try = try + 1;
if (iVar1 <= try) {
try = 0;
}
buildingSize = buildingSize + 1;
} while (buildingSize < iVar1);
}
return 0;
}


}
}
}