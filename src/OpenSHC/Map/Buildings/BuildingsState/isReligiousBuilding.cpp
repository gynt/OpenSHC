#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A4A0
BOOLEnum BuildingsState::isReligiousBuilding(int buildingID)

{
BuildingTypeShort BVar1;

BVar1 = this->buildings[buildingID].buildingType;
if ((BVar1 != OpenSHC::Map::Buildings::BT_CHAPEL) && (BVar1 != OpenSHC::Map::Buildings::BT_CHURCH)) {
return (uint)(BVar1 == OpenSHC::Map::Buildings::BT_CATHEDRAL);
}
return TRUE;
}


}
}
}