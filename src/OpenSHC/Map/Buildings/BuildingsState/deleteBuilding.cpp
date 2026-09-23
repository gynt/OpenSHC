#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::UI::Enums::MenuViewType;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00421890
void BuildingsState::deleteBuilding(uint buildingID)

{
BuildingTypeShort _type;
short _tribe;
BuildingTypeShort _type_2;
int _uid;

if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU) &&
(this->menuSelectedBuildingID == buildingID)) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::subtractResourcesStoredInBuilding, this)(buildingID);
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setTowerSiegeEngineToIdle, DAT_UnitsState::ptr)(buildingID);
_type = this->buildings[buildingID].buildingType;
if (((_type == OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN) || (_type == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN)) &&
(_tribe = this->buildings[buildingID].tribeID, 0 < _tribe)) {
_uid = this->buildings[buildingID].tribeUID;
if (DAT_TribesState::instance.tribes[_tribe].uid == _uid) {
MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::aiRegisterTribeAndAssignTarget, DAT_AICState::ptr)((int)_tribe, _uid);
}
}
_type_2 = this->buildings[buildingID].buildingType;
if (_type_2 == OpenSHC::Map::Buildings::BT_OXTETHER) {
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::removeUnitFromItsTribe, DAT_UnitsState::ptr)((int)this->buildings[buildingID].oxTetherRelatedUnitID, 
this->buildings[buildingID].oxTetherRelatedUnitUID);
}
else if (_type_2 == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
DAT_GameState::instance.mapAndTime.cathedralRelated1 = 1;
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::spawnCrowForBuilding, this)(buildingID);
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingFromTerrain, DAT_TileMapState::ptr)(buildingID);
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updatePrimaryBuildingPlayerDataReferences, DAT_GameState::ptr)(buildingID);
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x32c, '\0', (void *)((int)(this->buildings + buildingID)));
return;
}


}
}
}