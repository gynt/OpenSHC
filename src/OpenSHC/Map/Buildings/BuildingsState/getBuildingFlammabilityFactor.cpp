#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410920
undefined4 BuildingsState::getBuildingFlammabilityFactor(int buildingID)

{
switch(this->buildings[buildingID].buildingType) {
case OpenSHC::Map::Buildings::BT_HOVEL:
case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
case OpenSHC::Map::Buildings::BT_OXTETHER:
case OpenSHC::Map::Buildings::BT_IRONMINE:
case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
case OpenSHC::Map::Buildings::BT_BARRACKS:
case OpenSHC::Map::Buildings::BT_ARMORY:
case OpenSHC::Map::Buildings::BT_FLETCHER:
case OpenSHC::Map::Buildings::BT_POLETURNER:
case OpenSHC::Map::Buildings::BT_ARMOURER:
case OpenSHC::Map::Buildings::BT_TANNER:
case OpenSHC::Map::Buildings::BT_BREWERY:
case OpenSHC::Map::Buildings::BT_GRANARY:
case OpenSHC::Map::Buildings::BT_QUARRY:
case OpenSHC::Map::Buildings::BT_APOTHECARY:
case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
case OpenSHC::Map::Buildings::BT_MARKETPLACE:
case OpenSHC::Map::Buildings::BT_WHEATFARM:
case OpenSHC::Map::Buildings::BT_HOPFARM:
case OpenSHC::Map::Buildings::BT_APPLEFARM:
case OpenSHC::Map::Buildings::BT_DAIRYFARM:
case OpenSHC::Map::Buildings::BT_MILL:
case OpenSHC::Map::Buildings::BT_STABLES:
case OpenSHC::Map::Buildings::BT_CHAPEL:
case OpenSHC::Map::Buildings::BT_CHURCH:
case OpenSHC::Map::Buildings::BT_CATHEDRAL:
case OpenSHC::Map::Buildings::BT_GALLOWS:
case OpenSHC::Map::Buildings::BT_STOCKS:
case OpenSHC::Map::Buildings::BT_MAYPOLE:
case OpenSHC::Map::Buildings::BT_BURNINGSTAKE:
case OpenSHC::Map::Buildings::BT_GIBBET:
case OpenSHC::Map::Buildings::BT_STRETCHINGRACK:
case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
return(undefined4)( 1);
OpenSHC::Map::Buildings::default:
return(undefined4)( 0);
case OpenSHC::Map::Buildings::BT_BLACKSMITH:
case OpenSHC::Map::Buildings::BT_BAKERY:
case OpenSHC::Map::Buildings::BT_INN:
case OpenSHC::Map::Buildings::BT_OILSMELTER:
return(undefined4)( 5);
case OpenSHC::Map::Buildings::BT_PARADEGROUND:
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
return(undefined4)( 4);
}
}


}
}
}