#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00418EC0
int BuildingsState::getRequiredEngineersCount(int buildingID)

{
BuildingTypeShort _buildingType;

_buildingType = this->buildings[buildingID].buildingType;
if (_buildingType == OpenSHC::Map::Buildings::BT_TREBUCHET) {
return(int)( 3 - this->buildings[buildingID].currentEmployeeCount);
}
if (_buildingType == OpenSHC::Map::Buildings::BT_CATAPULT) {
return(int)( 2 - this->buildings[buildingID].currentEmployeeCount);
}
if (_buildingType == OpenSHC::Map::Buildings::BT_FIREBALLISTA) {
return(int)( 2 - this->buildings[buildingID].currentEmployeeCount);
}
if (_buildingType == OpenSHC::Map::Buildings::BT_BATTERINGRAM) {
return(int)( 4 - this->buildings[buildingID].currentEmployeeCount);
}
if (_buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER) {
return(int)( 4 - this->buildings[buildingID].currentEmployeeCount);
}
if (_buildingType == OpenSHC::Map::Buildings::BT_SHIELD) {
return(int)( 1 - this->buildings[buildingID].currentEmployeeCount);
}
return 0;
}


}
}
}