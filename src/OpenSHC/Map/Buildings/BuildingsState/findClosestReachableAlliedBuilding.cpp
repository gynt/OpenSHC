#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

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


// FUNCTION: STRONGHOLDCRUSADER 0x00410B10
int BuildingsState::findClosestReachableAlliedBuilding(int param_1)

{
ushort uVar1;
int iVar2;
int iVar3;
BuildingLogicalStateShort *pBVar4;
int local_8;
int local_4;

uVar1 = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_1].tile];
iVar3 = 1;
local_4 = 0;
local_8 = 1000;
if (1 < this->maxBuildingsCount) {
pBVar4 = &this->buildings[1].logicalState;
do {
if ((((*pBVar4 != ((BuildingLogicalState)0)) && (*pBVar4 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(DAT_GameState::instance.mapAndTime.playerTeams[(short)pBVar4[3]] ==
DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[param_1].owner])) &&
(((pBVar4[0xf7] != 0 &&
(MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[param_1].x, (int)((int)(
DAT_UnitsState::instance.units[param_1].y)), (int)((int)((short)pBVar4[0x17])), (int)((int)(
(short)pBVar4[0x18]))), DAT_DirectionAlgorithmState::instance.distanceHigh < local_8
)) && (iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[param_1].owner, (dword)((int)(
(int)(short)uVar1)), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[(int)(short)pBVar4[0x17] +
DAT_ViewportRenderState::instance.translationMatrix
[(short)pBVar4[0x18]].addXgetTile])), 0), iVar2 != 0)
))) {
local_8 = DAT_DirectionAlgorithmState::instance.distanceHigh;
local_4 = iVar3;
}
iVar3 = iVar3 + 1;
pBVar4 = pBVar4 + 0x196;
} while (iVar3 < this->maxBuildingsCount);
if (local_4 != 0) {
return local_4;
}
}
return 0;
}


}
}
}