#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Units::UnitLogicState;
using OpenSHC::Map::Units::UnitType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040E990
uint BuildingsState::getActiveEngineerForBuilding(int buildingID)

{
uint uVar1;

uVar1 = (uint)this->buildings[buildingID].workerID[0];
if ((((this->buildings[buildingID].workerUID[0] == DAT_UnitsState::instance.units[uVar1].uid)
&& (DAT_UnitsState::instance.units[uVar1].logicalState == OpenSHC::Map::Units::ULS_NORMAL)) &&
(DAT_UnitsState::instance.units[uVar1].unitType == OpenSHC::Map::Units::UT_E_ENGINEER)) &&
((DAT_UnitsState::instance.units[uVar1].dying == 0 &&
(DAT_UnitsState::instance.units[uVar1].workplaceBuildingID_1 == buildingID)))) {
return -(uint)(DAT_UnitsState::instance.units[uVar1].field252_0x3c4 != 0) &uVar1;
}
return 0;
}


}
}
}