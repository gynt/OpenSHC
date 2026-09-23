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


// FUNCTION: STRONGHOLDCRUSADER 0x0040D6E0
undefined4 BuildingsState::isSpaceAvailableAtUnitRallyPoint(int playerID,int value0to6,int unitID)

{
int _searchOffset;
int _tile;
uint _y2;
uint _x2;
int _someIndex;
short *psVar1;
uint _y;
uint _x;
bool bVar2;
short *_pY;
short _someX;
short _someY;

if ((((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) &&
(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1)) &&
(DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)) &&
(DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType != 2)) {
_someIndex = DAT_GameState::instance.playerDataArray[playerID].keep.id;
if (_someIndex == 0) {
return(undefined4)( 0);
}
this->DAT_TempXOffset = (int)this->buildings[_someIndex].someX;
this->DAT_TempYOffset = (int)this->buildings[_someIndex].someY;
return(undefined4)( 1);
}
_someIndex = value0to6;
if (value0to6 == 6) {
_someIndex = 5;
}
/* 
  0xe7d * 4 = size of PlayerData
 */

/* 
  this looks a bit ugly, but basically the [0] is actually [playerID]. the
   array should read: array[iVar4]
 */

_searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffsetsUnk[_someIndex];
if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[value0to6].x == 0) {
if (0 < DAT_GameState::instance.playerDataArray[playerID].barracks.id) {
if (value0to6 == 6) {
if (DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[5].x != 0) {
_searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
}
}
else if ((value0to6 == 5) &&
(DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[6].x != 0)) {
_searchOffset = _searchOffset - DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
}
if (_searchOffset < 72) {
_pY = &DAT_GameState::instance.playerDataArray[playerID].barracksParadegroundLocations[_someIndex]
[_searchOffset].y;
while( true ) {
_x2 = (uint)_pY[-1];
_y2 = (uint)*_pY;
if (((_x2 < 400) && (_y2 < 400)) &&
((*(char *)(_y2 * 400 + 0x21aec98 + _x2) != '\0' &&
((((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[_y2].addXgetTile + _x2] == 0 ||
((short)DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[_y2].addXgetTile + _x2] == unitID
)) || (DAT_UnitsState::instance.units[unitID].movementRelated != 8)))))) break;
_searchOffset = _searchOffset + 1;
_pY = _pY + 2;
if (0x47 < _searchOffset) {
return(undefined4)( 0);
}
}
if (_x2 != (int)DAT_UnitsState::instance.units[unitID].x) {
this->DAT_TempXOffset = _x2;
this->DAT_TempYOffset = _y2;
return(undefined4)( 1);
}
bVar2 = _y2 == (int)DAT_UnitsState::instance.units[unitID].y;
this->DAT_TempXOffset = _x2;
this->DAT_TempYOffset = _y2;
LAB_0040d9a7:
if (!bVar2) {
return(undefined4)( 1);
}
return(undefined4)( 0);
}
}
}
else {
if (value0to6 == 6) {
_searchOffset = DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
_someIndex = value0to6;
}
else if (value0to6 == 5) {
_searchOffset = _searchOffset - DAT_GameState::instance.playerDataArray[playerID].rallySearchOffset;
}
_someX = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[_someIndex].x;
_someY = DAT_GameState::instance.playerDataArray[playerID].barracksAssemblyPoints[_someIndex].y;
if (_searchOffset < 49) {
psVar1 = &DAT_BuildingDefinedData::instance.SearchRelatedXYOffsets_1[_searchOffset].y;
do {
_y = (int)*psVar1 + (int)_someY;
_x = (int)((XYPairShort *)(psVar1 + -1))->x + (int)_someX;
_tile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x;
if (((((short)DAT_TileMapState::instance.UnitLayer[_tile] == 0) ||
((short)DAT_TileMapState::instance.UnitLayer[_tile] == unitID)) ||
(DAT_UnitsState::instance.units[unitID].movementRelated != 8)) &&
(_someIndex = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)(playerID, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_UnitsState::instance.units[unitID].tile])), (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile])), 0),
_someIndex != 0)) {
if (_x != (int)DAT_UnitsState::instance.units[unitID].x) {
this->DAT_TempXOffset = _x;
this->DAT_TempYOffset = _y;
return(undefined4)( 1);
}
bVar2 = _y == (int)DAT_UnitsState::instance.units[unitID].y;
this->DAT_TempXOffset = _x;
this->DAT_TempYOffset = _y;
goto LAB_0040d9a7;
}
psVar1 = psVar1 + 2;
} while ((int)psVar1 < 0x5c178e);
}
}
return(undefined4)( 0);
}


}
}
}