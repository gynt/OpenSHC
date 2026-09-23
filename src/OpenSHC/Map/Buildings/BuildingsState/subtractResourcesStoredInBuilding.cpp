#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BF50
void BuildingsState::subtractResourcesStoredInBuilding(int buildingID)

{
int _resourceIndexUnk;
int _playerIndex;
int *_ptrBuildingResources;
BuildingTypeShort _buildingType;
int *_ptrPlayerResources;

_buildingType = this->buildings[buildingID].buildingType;
if (((_buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE) || (_buildingType == OpenSHC::Map::Buildings::BT_GRANARY)) ||
(_buildingType == OpenSHC::Map::Buildings::BT_ARMORY)) {
_playerIndex = (int)this->buildings[buildingID].owner;
_resourceIndexUnk = 1;
_ptrBuildingResources = this->buildings[buildingID].resources;
do {
_ptrBuildingResources = _ptrBuildingResources + 1;
if (*_ptrBuildingResources != 0) {
_ptrPlayerResources =
DAT_GameState::instance.playerDataArray[_playerIndex].currentResources + _resourceIndexUnk;
*_ptrPlayerResources = *_ptrPlayerResources - *_ptrBuildingResources;
if (*_ptrPlayerResources < 0) {
DAT_GameState::instance.playerDataArray[_playerIndex].currentResources[_resourceIndexUnk] = 0;
}
}
_resourceIndexUnk = _resourceIndexUnk + 1;
} while (_resourceIndexUnk < 0x19);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(_playerIndex);
}
return;
}


}
}
}