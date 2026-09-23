#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
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

using OpenSHC::Map::Units::UnitType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040E120
int BuildingsState::findFreeEngineerAssemblyTile(int playerIndex,int param_2)

{
short sVar1;
short sVar2;
int iVar3;
uint uVar4;
int iVar5;
short *psVar6;
uint uVar7;
short *psVar8;
int iVar9;
bool _isLadderman;

iVar5 = (int)(short)DAT_GameState::instance.playerDataArray[playerIndex].someCount28;
_isLadderman = DAT_UnitsState::instance.units[param_2].unitType == OpenSHC::Map::Units::UT_E_LADDER;
iVar3 = DAT_GameState::instance.playerDataArray[playerIndex].someCount27 - iVar5;
if (_isLadderman) {
iVar3 = iVar5;
}
sVar1 = DAT_GameState::instance.playerDataArray[playerIndex].engineersAssemblyPoints[_isLadderman].x;
if (sVar1 == 0) {
if (iVar3 < 25) {
psVar8 = &DAT_GameState::instance.playerDataArray[playerIndex].engineersParadegroundLocations[iVar3].y;
psVar6 = (short *)((int)DAT_GameState::ptr + (playerIndex * 0xe7d - iVar3) * 4 + 0x319c2);
while( true ) {
if (_isLadderman) {
sVar1 = psVar6[-1];
sVar2 = *psVar6;
}
else {
sVar1 = ((XYPairShort *)(psVar8 + -1))->x;
sVar2 = *psVar8;
}
uVar7 = (uint)sVar1;
uVar4 = (uint)sVar2;
if ((((uVar7 < 400) && (uVar4 < 400)) &&
(*(char *)(uVar4 * 400 + 0x21aec98 + uVar7) != '\0')) &&
((((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[uVar4].addXgetTile + uVar7] == 0 ||
((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[uVar4].addXgetTile + uVar7] ==
param_2)) || (DAT_UnitsState::instance.units[param_2].movementRelated != 8)))) break;
iVar3 = iVar3 + 1;
psVar8 = psVar8 + 2;
psVar6 = psVar6 + -2;
if (0x18 < iVar3) {
return 0;
}
}
this->DAT_TempXOffset = uVar7;
this->DAT_TempYOffset = uVar4;
if (uVar7 == (int)DAT_UnitsState::instance.units[param_2].x) {
_isLadderman = uVar4 == (int)DAT_UnitsState::instance.units[param_2].y;
LAB_0040e310:
if (_isLadderman) {
return 0;
}
}
return 1;
}
}
else {
sVar2 = DAT_GameState::instance.playerDataArray[playerIndex].engineersAssemblyPoints[_isLadderman].y;
if (iVar3 < 0x31) {
psVar8 = &DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[iVar3].y;
do {
iVar5 = (int)*psVar8 + (int)sVar2;
iVar9 = (int)((XYPairShort *)(psVar8 + -1))->x + (int)sVar1;
iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile + iVar9;
if (((((short)DAT_TileMapState::instance.UnitLayer[iVar3] == 0) ||
((short)DAT_TileMapState::instance.UnitLayer[iVar3] == param_2)) ||
(DAT_UnitsState::instance.units[param_2].movementRelated != 8)) &&
(iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(playerIndex, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_UnitsState::instance.units[param_2].tile])), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar3])), 0),
iVar3 != 0)) {
if (iVar9 != DAT_UnitsState::instance.units[param_2].x) {
this->DAT_TempXOffset = iVar9;
this->DAT_TempYOffset = iVar5;
return 1;
}
_isLadderman = iVar5 == DAT_UnitsState::instance.units[param_2].y;
this->DAT_TempXOffset = iVar9;
this->DAT_TempYOffset = iVar5;
goto LAB_0040e310;
}
psVar8 = psVar8 + 2;
} while ((int)psVar8 < 0x5c178e);
}
}
return 0;
}


}
}
}