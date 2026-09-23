#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C060
uint BuildingsState::getArmoryIDIfSpaceLeft(uint buildingID,undefined4 resourceID,int playerID,int resourceCount)

{
Building * piVar1;
int _spaceLeft;
int iVar1;

if (((this->buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_ARMORY) &&
(this->buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL)) &&
(this->buildings[buildingID].owner == playerID)) {
_spaceLeft = 50;
iVar1 = 5;
piVar1 = (Building *)(&this->buildings[buildingID]);
do {
_spaceLeft = _spaceLeft -
(piVar1->resources[0] + piVar1->resources[1] +
piVar1->resources[2] + piVar1->resources[4] +
piVar1->resources[3]);
iVar1 = iVar1 + -1;
piVar1 = (Building *)(piVar1->resources + 8);
} while (iVar1 != 0);
/* 
  if false then return buildingID
 */

return (_spaceLeft < resourceCount) - 1 &buildingID;
}
return 0;
}


}
}
}