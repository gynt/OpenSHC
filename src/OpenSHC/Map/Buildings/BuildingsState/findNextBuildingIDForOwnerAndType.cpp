#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AB90
int BuildingsState::findNextBuildingIDForOwnerAndType(int param_1,int param_2,int param_3)

{
BuildingLogicalStateShort BVar1;
int iVar2;

iVar2 = 0;
if (0 < this->maxBuildingsCount) {
do {
param_3 = param_3 + 1;
if (this->maxBuildingsCount <= param_3) {
param_3 = 1;
}
BVar1 = this->buildings[param_3].logicalState;
if ((((BVar1 != ((BuildingLogicalState)0)) && (BVar1 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(this->buildings[param_3].owner == param_1)) &&
((short)this->buildings[param_3].buildingType == param_2)) {
return param_3;
}
iVar2 = iVar2 + 1;
} while (iVar2 < this->maxBuildingsCount);
}
return 0;
}


}
}
}