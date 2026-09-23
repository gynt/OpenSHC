#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

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


// FUNCTION: STRONGHOLDCRUSADER 0x00421990
void BuildingsState::destroyBuildingAndLinkedDuplicates(uint param_1)

{
Building * psVar2;
uint buildingID;
Building * psVar3;
int _uid;

this->buildings[param_1].logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
this->buildings[param_1].noRubble = 1;
}
if (this->buildings[param_1].buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroySignpostData, this)(param_1);
}
_uid = this->buildings[param_1].uidWhenPlaced;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, this)(param_1);
if ((_uid != 0) && (buildingID = 1, 1 < this->maxBuildingsCount)) {
psVar3 = &this->buildings[1];
do {
if ((psVar3->logicalState != ((BuildingLogicalState)0)) && (psVar3->uidWhenPlaced == _uid)) {
psVar3->logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
psVar3->noRubble = 1;
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, this)(buildingID);
}
buildingID = buildingID + 1;
psVar3 = psVar3 + 0x196;
} while ((int)buildingID < this->maxBuildingsCount);
}
DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
return;
}


}
}
}