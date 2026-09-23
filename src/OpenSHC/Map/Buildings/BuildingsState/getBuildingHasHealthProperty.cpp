#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B900
BOOLEnum BuildingsState::getBuildingHasHealthProperty(uint buildingID)

{
BuildingTypeInt iVar1;

if (buildingID == 0) {
return FALSE;
}
iVar1 = (BuildingTypeInt)(short)this->buildings[buildingID].buildingType;
switch(iVar1) {
case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
case OpenSHC::Map::Buildings::BT_TOWER1:
case OpenSHC::Map::Buildings::BT_TOWER2:
case OpenSHC::Map::Buildings::BT_TOWER3:
case OpenSHC::Map::Buildings::BT_TOWER4:
case OpenSHC::Map::Buildings::BT_TOWER5:
return TRUE;
OpenSHC::Map::Buildings::default:
return (uint)(DAT_BuildingDefinedData::instance.BuildingTypeHasHealth[iVar1] != 0);
}
}


}
}
}