#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C0D0
int BuildingsState::computeArmoryRemainingCapacity(int buildingID)

{
int iVar1;
int *piVar2;
int iVar3;

iVar1 = 0x32;
if ((this->buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
(this->buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_ARMORY)) {
iVar3 = 5;
piVar2 = this->buildings[buildingID].resources + 3;
do {
iVar1 = iVar1 - (piVar2[-3] + piVar2[-2] + piVar2[-1] + piVar2[1] + *piVar2);
iVar3 = iVar3 + -1;
piVar2 = piVar2 + 5;
} while (iVar3 != 0);
if (-1 < iVar1) {
return iVar1;
}
}
return 0;
}


}
}
}