#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


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


// FUNCTION: STRONGHOLDCRUSADER 0x0041BB30
undefined4 BuildingsState::addResourceToStockpile(int buildingID,int buildingUID,ResourceType resourceType,int amount,int maxCapacity,int recomputeResources)

{
int *piVar1;
BuildingTypeShort BVar2;
int iVar3;
int playerID;

playerID = (int)this->buildings[buildingID].owner;
iVar3 = this->buildings[buildingID].resources[resourceType] + amount;
piVar1 = this->buildings[buildingID].resources + resourceType;
if (this->buildings[buildingID].uid == buildingUID) {
if (maxCapacity == 0) {
*piVar1 = 0;
}
else if ((-1 < iVar3) && (iVar3 <= maxCapacity)) {
if (recomputeResources != 0) {
*piVar1 = iVar3;
BVar2 = this->buildings[buildingID].buildingType;
if ((9 < (short)BVar2) && (((short)BVar2 < 0xc || (BVar2 == OpenSHC::Map::Buildings::BT_GRANARY)))) {
piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + resourceType;
*piVar1 = *piVar1 + amount;
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::extendResourceCountdownForPlayerBuildingsOfType, this)(
(int)(short)this->buildings[buildingID].buildingType, 600, (int)((int)(
DAT_GameSynchronyState::instance.currentPlayerSlotID)));
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, this)(buildingID);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(buildingID);
}
return(undefined4)( 1);
}
}
return(undefined4)( 0);
}


}
}
}