#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::GameMode;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040D9C0
undefined4 BuildingsState::getKeepLocationForAIUnit(int playerID,int param_2,int unitID)

{
short sVar1;
short sVar2;
short *psVar3;
int iVar4;
int iVar5;
int iVar6;
bool bVar7;

if ((((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) &&
(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1)) &&
(DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)) &&
(DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2)) {
/* 
  if not in solitary;
   playerID is an AI;
   and the unit is not doing ai behavior type 2;
   and the player has a keep;
   return the keep location and true;
 */

iVar4 = DAT_GameState::instance.playerDataArray[playerID].keep.id;
if (iVar4 != 0) {
this->DAT_TempXOffset = (int)this->buildings[iVar4].someX;
this->DAT_TempYOffset = (int)this->buildings[iVar4].someY;
return(undefined4)( 1);
}
return(undefined4)( 0);
}
iVar4 = param_2;
/* 
  this applies to solitary game mode, so not sure what to think of this now
 */

if (param_2 == 0x10) {
iVar4 = 0xd;
}
/* 
  fixme
 */

/* 
  fixme
 */

iVar5 = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[iVar4];
if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[param_2 + -10][0] == 0) {
if (0 < DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id) {
if (param_2 == 0x10) {
/* 
  fixme
 */

if (DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[3][0] != 0) {
iVar5 = DAT_GameState::instance.playerDataArray[playerID].someCount23;
}
}
else if ((param_2 == 0xd) &&
((short)DAT_GameState::instance.playerDataArray[playerID].countPitchRigs != 0)) {
iVar5 = iVar5 - DAT_GameState::instance.playerDataArray[playerID].someCount23;
}
if (iVar5 < 0x48) {
psVar3 = DAT_GameState::instance.playerDataArray[playerID].enemyIDArray +
iVar4 * 0x90 + iVar5 * 2 + 0x57d;
while( true ) {
iVar4 = (int)*psVar3;
iVar6 = (int)psVar3[-1];
if ((((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar6] == 0)
|| ((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar6] ==
unitID)) || (DAT_UnitsState::instance.units[unitID].movementRelated != 8)) break;
iVar5 = iVar5 + 1;
psVar3 = psVar3 + 2;
if (0x47 < iVar5) {
return(undefined4)( 0);
}
}
this->DAT_TempXOffset = iVar6;
this->DAT_TempYOffset = iVar4;
if (iVar6 == DAT_UnitsState::instance.units[unitID].x) {
bVar7 = iVar4 == DAT_UnitsState::instance.units[unitID].y;
LAB_0040dc5b:
if (bVar7) {
return(undefined4)( 0);
}
}
return(undefined4)( 1);
}
}
}
else {
if (param_2 == 0x10) {
iVar5 = DAT_GameState::instance.playerDataArray[playerID].someCount23;
iVar4 = param_2;
}
else if (param_2 == 0xd) {
iVar5 = iVar5 - DAT_GameState::instance.playerDataArray[playerID].someCount23;
}
/* 
  fixme
 */

sVar1 = DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[iVar4 + -10][0];
/* 
  fixme
 */

sVar2 = DAT_GameState::instance.playerDataArray[playerID].mercenaryAssemblyPoints[iVar4 + -10][1];
if (iVar5 < 0x31) {
psVar3 = &DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[iVar5].y;
do {
iVar5 = (int)*psVar3 + (int)sVar2;
iVar6 = (int)((XYPairShort *)(psVar3 + -1))->x + (int)sVar1;
iVar4 = DAT_ViewportRenderState::instance.translationMatrix[iVar5].addXgetTile + iVar6;
if (((((short)DAT_TileMapState::instance.UnitLayer[iVar4] == 0) ||
((short)DAT_TileMapState::instance.UnitLayer[iVar4] == unitID)) ||
(DAT_UnitsState::instance.units[unitID].movementRelated != 8)) &&
(iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(playerID, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_UnitsState::instance.units[unitID].tile])), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar4])), 0),
iVar4 != 0)) {
if (iVar6 != DAT_UnitsState::instance.units[unitID].x) {
this->DAT_TempXOffset = iVar6;
this->DAT_TempYOffset = iVar5;
return(undefined4)( 1);
}
bVar7 = iVar5 == DAT_UnitsState::instance.units[unitID].y;
this->DAT_TempXOffset = iVar6;
this->DAT_TempYOffset = iVar5;
goto LAB_0040dc5b;
}
psVar3 = psVar3 + 2;
} while ((int)psVar3 < 0x5c178e);
}
}
return(undefined4)( 0);
}


}
}
}