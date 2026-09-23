#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409DB0
undefined4 BuildingsState::getBuildingHeightForBuildingID(int buildingID)

{
switch(this->buildings[buildingID].buildingType) {
case OpenSHC::Map::Buildings::BT_MANORHOUSE:
return(undefined4)( 64);
case OpenSHC::Map::Buildings::BT_STONEKEEP:
return(undefined4)( 92);
case OpenSHC::Map::Buildings::BT_STRONGHOLD:
return(undefined4)( 190);
OpenSHC::Map::Buildings::default:
return(undefined4)( 0);
case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
return(undefined4)( 128);
case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
return(undefined4)( 118);
case OpenSHC::Map::Buildings::BT_TOWER1:
return(undefined4)( 296);
case OpenSHC::Map::Buildings::BT_TOWER2:
return(undefined4)( 148);
case OpenSHC::Map::Buildings::BT_TOWER3:
return(undefined4)( 180);
case OpenSHC::Map::Buildings::BT_TOWER4:
case OpenSHC::Map::Buildings::BT_TOWER5:
return(undefined4)( 192);
}
}


}
}
}