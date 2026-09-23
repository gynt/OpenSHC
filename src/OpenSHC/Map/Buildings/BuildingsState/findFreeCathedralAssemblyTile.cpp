#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
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


// FUNCTION: STRONGHOLDCRUSADER 0x0040E610
undefined4 BuildingsState::findFreeCathedralAssemblyTile(int param_1,int param_2)

{
short sVar1;
short sVar2;
int iVar3;
int iVar4;
int iVar5;
int iVar6;

sVar1 = DAT_GameState::instance.playerDataArray[param_1].cathedralAssemblyPointX;
if (sVar1 == 0) {
return(undefined4)( 0);
}
iVar4 = (int)(short)DAT_GameState::instance.playerDataArray[param_1].someCount30;
sVar2 = DAT_GameState::instance.playerDataArray[param_1].cathedralAssemblyPointY;
while( true ) {
if (0x30 < iVar4) {
return(undefined4)( 0);
}
iVar5 = (int)DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[3].y + (int)sVar2;
iVar6 = (int)DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[3].x + (int)sVar1;
iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile + iVar6;
if (((((short)DAT_TileMapState::instance.UnitLayer[iVar3] == 0) ||
((short)DAT_TileMapState::instance.UnitLayer[iVar3] == param_2)) ||
(DAT_UnitsState::instance.units[param_2].movementRelated != 8)) &&
(iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(param_1, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_UnitsState::instance.units[param_2].tile])), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar3])), 0), iVar3 != 0))
break;
iVar4 = iVar4 + 1;
}
this->DAT_TempXOffset = iVar6;
this->DAT_TempYOffset = iVar5;
if ((iVar6 == DAT_UnitsState::instance.units[param_2].x) && (iVar5 == DAT_UnitsState::instance.units[param_2].y)) {
return(undefined4)( 0);
}
return(undefined4)( 1);
}


}
}
}