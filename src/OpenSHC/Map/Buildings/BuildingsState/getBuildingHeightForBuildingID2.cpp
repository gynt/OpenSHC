#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409E80
undefined4 BuildingsState::getBuildingHeightForBuildingID2(int buildingID)

{
if (this->buildings[buildingID].field62_0xb0 != 0) {
switch(this->buildings[buildingID].buildingType) {
case OpenSHC::Map::Buildings::BT_MANORHOUSE:
return(undefined4)( 56);
case OpenSHC::Map::Buildings::BT_STONEKEEP:
return(undefined4)( 74);
case OpenSHC::Map::Buildings::BT_STRONGHOLD:
return(undefined4)( 145);
case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
return(undefined4)( 108);
case OpenSHC::Map::Buildings::BT_TOWER1:
return(undefined4)( 276);
case OpenSHC::Map::Buildings::BT_TOWER2:
return(undefined4)( 128);
case OpenSHC::Map::Buildings::BT_TOWER3:
return(undefined4)( 150);
case OpenSHC::Map::Buildings::BT_TOWER4:
case OpenSHC::Map::Buildings::BT_TOWER5:
return(undefined4)( 172);
}
}
return(undefined4)( 0);
}


}
}
}