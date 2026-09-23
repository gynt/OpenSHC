#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041B940
BOOLEnum BuildingsState::hasBuildingAsNeighbour(int playerID,int x,int y,int size,BuildingType type)

{
int iVar1;
int buildingSize;
int _buildingID;
int try;

buildingSize = size;
iVar1 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[size];
try = 0;
size = 0;
if (0 < iVar1) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, try, 0);
_buildingID = (int)(short)DAT_TileMapState::instance.BuildingLayer
[DAT_ViewportRenderState::instance.translationMatrix
[this->DAT_TempYOffset + y].addXgetTile +
this->DAT_TempXOffset + x];
if ((((0 < _buildingID) &&
(this->buildings[_buildingID].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL)) &&
(this->buildings[_buildingID].owner == playerID)) &&
((int)(short)this->buildings[_buildingID].buildingType == type)) {
return TRUE;
}
try = try + 1;
if (iVar1 <= try) {
try = 0;
}
size = size + 1;
} while (size < iVar1);
}
return FALSE;
}


}
}
}