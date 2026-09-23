#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A7A0
void BuildingsState::destroyBuilding(int buildingID)

{
int iVar1;
uint uVar2;
BOOLEnum BVar3;
Building * _buildingAddressOffset2;
int _index;

this->buildings[buildingID].logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
this->buildings[buildingID].noRubble = 1;
}
if (this->buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroySignpostData, this)(buildingID);
}
uVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isFearFactorBuilding, this)(buildingID);
if (uVar2 != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAllFearFactors, this)();
}
BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isReligiousBuilding, this)(buildingID);
if (BVar3 != FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recomputeReligionBonuses, DAT_GameState::ptr)();
}
iVar1 = this->buildings[buildingID].uidWhenPlaced;
if ((iVar1 != 0) && (_index = 1, 1 < this->maxBuildingsCount)) {
_buildingAddressOffset2 = &this->buildings[1];
do {
if (((_buildingAddressOffset2->logicalState != ((BuildingLogicalState)0)) &&
(_buildingAddressOffset2->uidWhenPlaced == iVar1)) &&
(_buildingAddressOffset2->logicalState = OpenSHC::Map::Buildings::BLS_REMOVE,
DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0)) {
_buildingAddressOffset2->noRubble = 1;
}
_index = _index + 1;
_buildingAddressOffset2 = _buildingAddressOffset2 + 0x196;
} while (_index < this->maxBuildingsCount);
}
DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
return;
}


}
}
}