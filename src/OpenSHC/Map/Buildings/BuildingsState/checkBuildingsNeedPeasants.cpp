#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
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


// FUNCTION: STRONGHOLDCRUSADER 0x00422B80
void BuildingsState::checkBuildingsNeedPeasants(int playerID)

{
ushort uVar1;
int canNavigate;
Building * buildingTypePtr;
int buildingID;

uVar1 = DAT_TileMapState::instance.PathConnectionLayer
[DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry];
buildingID = 1;
/* 
  loop through all buildings of playerID, add buildingID to array if it needs
   peasants
 */

this->DAT_CountOfBuildingsNeedPeasants = 0;
if (1 < this->maxBuildingsCount) {
buildingTypePtr = &this->buildings[1];
do {
/* 
  check if 0 < building.requiredEmployeeCount && building.ownerPlayerID ==
   playerID
 */

if ((((buildingTypePtr->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
(buildingTypePtr->owner == playerID)) &&
(0 < buildingTypePtr->currentlyNeededEmployeeCount)) &&
((buildingTypePtr->buildingType != OpenSHC::Map::Buildings::BT_MERCENARYPOST &&
(buildingTypePtr->buildingType != OpenSHC::Map::Buildings::BT_BARRACKS)))) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(buildingID, 0);
canNavigate = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, DAT_PathFindingState::ptr)((int)buildingTypePtr->owner, (dword)((int)(
(int)(short)DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix
[buildingTypePtr->buildingEntryY].addXgetTile +
(int)buildingTypePtr->buildingEntryX])), (dword)((int)(
(int)(short)uVar1)), 0);
if (canNavigate != 0) {
this->DAT_BuildingIDsNeedPeasantsQueue
[this->DAT_CountOfBuildingsNeedPeasants] = (short)buildingID;
this->DAT_CountOfBuildingsNeedPeasants =
this->DAT_CountOfBuildingsNeedPeasants + 1;
}
}
buildingID = buildingID + 1;
buildingTypePtr = buildingTypePtr + 0x196;
} while (buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}