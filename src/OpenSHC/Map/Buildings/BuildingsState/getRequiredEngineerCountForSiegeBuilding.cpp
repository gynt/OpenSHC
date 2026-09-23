#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410200
undefined4 BuildingsState::getRequiredEngineerCountForSiegeBuilding(int buildingID)

{
if (buildingID != 0) {
switch(this->buildings[buildingID].buildingType) {
case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
case OpenSHC::Map::Buildings::BT_CATAPULT:
break;
OpenSHC::Map::Buildings::default:
return(undefined4)( 0);
case OpenSHC::Map::Buildings::BT_TREBUCHET:
return(undefined4)( 3);
case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
case OpenSHC::Map::Buildings::BT_SIEGETOWER:
return(undefined4)( 4);
case OpenSHC::Map::Buildings::BT_SHIELD:
return(undefined4)( 1);
}
}
return(undefined4)( 2);
}


}
}
}