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
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040ADB0
int BuildingsState::findNextReachableDefensiveBuildingForPlayer(int param_1,int param_2,int param_3,int param_4)

{
ushort uVar1;
BuildingLogicalStateShort BVar2;
BuildingTypeShort BVar3;
short sVar4;
int iVar5;

uVar1 = DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2];
param_3 = 0;
if (0 < this->maxBuildingsCount) {
do {
param_4 = param_4 + 1;
if (this->maxBuildingsCount <= param_4) {
param_4 = 1;
}
BVar2 = this->buildings[param_4].logicalState;
if (((((BVar2 != ((BuildingLogicalState)0)) && (BVar2 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(iVar5 = (int)this->buildings[param_4].owner, iVar5 == param_1)) &&
((((BVar3 = this->buildings[param_4].buildingType, BVar3 == OpenSHC::Map::Buildings::BT_TOWER1 ||
(BVar3 == OpenSHC::Map::Buildings::BT_TOWER2)) ||
((BVar3 == OpenSHC::Map::Buildings::BT_TOWER3 || ((BVar3 == OpenSHC::Map::Buildings::BT_TOWER4 || (BVar3 == OpenSHC::Map::Buildings::BT_TOWER5)))))) ||
((BVar3 == OpenSHC::Map::Buildings::BT_MANORHOUSE ||
(((((BVar3 == OpenSHC::Map::Buildings::BT_STONEKEEP || (BVar3 == OpenSHC::Map::Buildings::BT_STRONGHOLD)) || (BVar3 == OpenSHC::Map::Buildings::BT_KEEPFOUR)) ||
((BVar3 == OpenSHC::Map::Buildings::BT_KEEPFIVE || (BVar3 == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE)))) ||
((BVar3 == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL || (BVar3 == OpenSHC::Map::Buildings::BT_SHRINE)))))))))) &&
((sVar4 = this->buildings[param_4].someX, sVar4 != 0 &&
(iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(iVar5, (dword)((int)((int)(short)uVar1)), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix
[this->buildings[param_4].someY].addXgetTile
+ (int)sVar4])), 0), iVar5 != 0)))) {
return param_4;
}
param_3 = param_3 + 1;
} while (param_3 < this->maxBuildingsCount);
}
return 0;
}


}
}
}