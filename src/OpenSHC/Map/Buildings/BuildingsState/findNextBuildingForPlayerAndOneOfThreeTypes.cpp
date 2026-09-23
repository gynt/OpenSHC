#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AC00
int BuildingsState::findNextBuildingForPlayerAndOneOfThreeTypes(int param_1,int param_2,int param_3,int param_4,int param_5)

{
BuildingLogicalStateShort BVar1;
int iVar2;
int iVar3;

iVar3 = 0;
if (0 < this->maxBuildingsCount) {
do {
param_5 = param_5 + 1;
if (this->maxBuildingsCount <= param_5) {
param_5 = 1;
}
BVar1 = this->buildings[param_5].logicalState;
if (((BVar1 != ((BuildingLogicalState)0)) && (BVar1 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(this->buildings[param_5].owner == param_1)) {
iVar2 = (int)(short)this->buildings[param_5].buildingType;
if (iVar2 == param_2) {
return param_5;
}
if (iVar2 == param_3) {
return param_5;
}
if (iVar2 == param_4) {
return param_5;
}
}
iVar3 = iVar3 + 1;
} while (iVar3 < this->maxBuildingsCount);
}
return 0;
}


}
}
}