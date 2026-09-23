#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A400
uint BuildingsState::isFearFactorBuilding(int buildingID)

{
BuildingTypeShort BVar1;

BVar1 = this->buildings[buildingID].buildingType;
if (((((((BVar1 != OpenSHC::Map::Buildings::BT_GALLOWS) && (BVar1 != OpenSHC::Map::Buildings::BT_STOCKS)) && (BVar1 != OpenSHC::Map::Buildings::BT_WITCHHOIST)) &&
((BVar1 != OpenSHC::Map::Buildings::BT_CESSPIT && (BVar1 != OpenSHC::Map::Buildings::BT_BURNINGSTAKE)))) &&
((BVar1 != OpenSHC::Map::Buildings::BT_GIBBET && ((BVar1 != OpenSHC::Map::Buildings::BT_DUNGEON && (BVar1 != OpenSHC::Map::Buildings::BT_STRETCHINGRACK)))))) &&
(BVar1 != OpenSHC::Map::Buildings::BT_RACKFLOGGING)) &&
(((((BVar1 != OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK && (BVar1 != OpenSHC::Map::Buildings::BT_DUNKINGSTOOL)) && (BVar1 != OpenSHC::Map::Buildings::BT_MAYPOLE)) &&
(((BVar1 != OpenSHC::Map::Buildings::BT_GARDEN && (BVar1 != OpenSHC::Map::Buildings::BT_STATUE)) &&
((BVar1 != OpenSHC::Map::Buildings::BT_SHRINE && ((BVar1 != OpenSHC::Map::Buildings::BT_DANCINGBEAR && (BVar1 != OpenSHC::Map::Buildings::BT_POND)))))))) &&
(BVar1 != OpenSHC::Map::Buildings::BT_WELL)))) {
return (uint)(BVar1 == OpenSHC::Map::Buildings::BT_BEEHIVE);
}
return 1;
}


}
}
}