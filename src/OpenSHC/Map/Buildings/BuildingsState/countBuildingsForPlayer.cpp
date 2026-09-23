#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A9B0
int BuildingsState::countBuildingsForPlayer(PlayerID playerID,BuildingType buildingType,int includeBool)

{
int iVar1;
short *psVar2;
int iVar3;

iVar1 = 0;
if (1 < this->maxBuildingsCount) {
psVar2 = &this->buildings[1].owner;
iVar3 = this->maxBuildingsCount + -1;
do {
if ((((psVar2[-3] == OpenSHC::Map::Buildings::BLS_NORMAL) && (*psVar2 == playerID)) &&
((int)psVar2[-2] == buildingType)) && ((includeBool == 0 || (psVar2[0xf9] == 0)))) {
iVar1 = iVar1 + 1;
}
psVar2 = psVar2 + 0x196;
iVar3 = iVar3 + -1;
} while (iVar3 != 0);
}
return iVar1;
}


}
}
}