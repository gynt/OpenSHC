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


// FUNCTION: STRONGHOLDCRUSADER 0x0040E410
undefined4 BuildingsState::findFreeTunnelerAssemblyTile(int param_1,int param_2)

{
short sVar1;
short sVar2;
int iVar3;
uint uVar4;
uint uVar5;
short *psVar6;
int iVar7;
int iVar8;

sVar1 = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildAssemblyPointX;
iVar3 = DAT_GameState::instance.playerDataArray[param_1].someCount29;
if (sVar1 != 0) {
sVar2 = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildAssemblyPointY;
if (iVar3 < 0x31) {
psVar6 = &DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[iVar3].y;
do {
iVar7 = (int)*psVar6 + (int)sVar2;
iVar8 = (int)((XYPairShort *)(psVar6 + -1))->x + (int)sVar1;
iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar7].addXgetTile + iVar8;
if (((((short)DAT_TileMapState::instance.UnitLayer[iVar3] == 0) ||
((short)DAT_TileMapState::instance.UnitLayer[iVar3] == param_2)) ||
(DAT_UnitsState::instance.units[param_2].movementRelated != 8)) &&
(iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(param_1, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_UnitsState::instance.units[param_2].tile])), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar3])), 0),
iVar3 != 0)) {
this->DAT_TempXOffset = iVar8;
this->DAT_TempYOffset = iVar7;
if ((iVar8 == DAT_UnitsState::instance.units[param_2].x) &&
(iVar7 == DAT_UnitsState::instance.units[param_2].y)) {
return(undefined4)( 0);
}
return(undefined4)( 1);
}
psVar6 = psVar6 + 2;
} while ((int)psVar6 < 0x5c178e);
}
return(undefined4)( 0);
}
if (iVar3 < 0x19) {
psVar6 = &DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocations[iVar3].y;
while( true ) {
uVar5 = (uint)((XYPairShort *)(psVar6 + -1))->x;
uVar4 = (uint)*psVar6;
if ((((uVar5 < 400) && (uVar4 < 400)) && (*(char *)(uVar4 * 400 + 0x21aec98 + uVar5) != '\0'))
&& ((((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[uVar4].addXgetTile + uVar5] == 0 ||
((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[uVar4].addXgetTile + uVar5] ==
param_2)) || (DAT_UnitsState::instance.units[param_2].movementRelated != 8)))) break;
iVar3 = iVar3 + 1;
psVar6 = psVar6 + 2;
if (0x18 < iVar3) {
return(undefined4)( 0);
}
}
this->DAT_TempXOffset = uVar5;
this->DAT_TempYOffset = uVar4;
if ((uVar5 != (int)DAT_UnitsState::instance.units[param_2].x) ||
(uVar4 != (int)DAT_UnitsState::instance.units[param_2].y)) {
return(undefined4)( 1);
}
}
return(undefined4)( 0);
}


}
}
}