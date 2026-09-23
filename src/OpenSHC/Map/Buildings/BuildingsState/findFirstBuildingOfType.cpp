#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AA80
int BuildingsState::findFirstBuildingOfType(int playerID,BuildingType buildingType)

{
int iVar1;
short *psVar2;

iVar1 = 1;
if (1 < this->maxBuildingsCount) {
psVar2 = &this->buildings[1].owner;
do {
if (((psVar2[-3] == OpenSHC::Map::Buildings::BLS_NORMAL) && (*psVar2 == playerID)) && ((int)psVar2[-2] == buildingType)
) {
return iVar1;
}
iVar1 = iVar1 + 1;
psVar2 = psVar2 + 0x196;
} while (iVar1 < this->maxBuildingsCount);
}
return 0;
}


}
}
}