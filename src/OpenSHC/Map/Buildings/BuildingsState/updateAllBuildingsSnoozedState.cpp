#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F750
void BuildingsState::updateAllBuildingsSnoozedState(int playerID,int buildingType)

{
short *psVar1;
int iVar2;
int *piVar3;
short *psVar4;
int _buildingType;

_buildingType = buildingType;
if ((buildingType < 0x5b) && (buildingType = 1, 1 < this->maxBuildingsCount)) {
psVar1 = &this->buildings[1].owner;
do {
if (((psVar1[-3] == OpenSHC::Map::Buildings::BLS_NORMAL) && (*psVar1 == playerID)) && (psVar1[-2] == _buildingType)) {
*(bool *)(psVar1 + 0xe0) = *(bool *)(playerID * 0x39f4 + 0x115df8c + _buildingType);
psVar1[0x62] = 0;
psVar1[-0x5b] = 0;
psVar1[-0x58] = 0;
*(undefined4 *)(psVar1 + 0x21) = 0;
*(undefined4 *)(psVar1 + 0x23) = 0;
*(int *)(psVar1 + 0x25) = 0;
*(int *)(psVar1 + 0x27) = 0;
*(int *)(psVar1 + 0x29) = 0;
*(int *)(psVar1 + 0x2b) = 0;
*(int *)(psVar1 + 0x2d) = 0;
*(int *)(psVar1 + 0x2f) = 0;
*(int *)(psVar1 + 0x31) = 0;
*(int *)(psVar1 + 0x33) = 0;
*(int *)(psVar1 + 0x35) = 0;
*(int *)(psVar1 + 0x37) = 0;
*(int *)(psVar1 + 0x39) = 0;
*(int *)(psVar1 + 0x3b) = 0;
*(int *)(psVar1 + 0x3d) = 0;
*(int *)(psVar1 + 0x3f) = 0;
*(int *)(psVar1 + 0x41) = 0;
*(int *)(psVar1 + 0x43) = 0;
*(int *)(psVar1 + 0x45) = 0;
*(int *)(psVar1 + 0x47) = 0;
*(int *)(psVar1 + 0x49) = 0;
*(int *)(psVar1 + 0x4b) = 0;
*(int *)(psVar1 + 0x4d) = 0;
*(int *)(psVar1 + 0x4f) = 0;
*(int *)(psVar1 + 0x51) = 0;
*(int *)(psVar1 + 0x53) = 0;
*(int *)(psVar1 + 0x55) = 0;
psVar4 = psVar1 + 100;
piVar3 = (int *)(psVar1 + 0x69);
iVar2 = 4;
do {
*piVar3 = 0;
*psVar4 = 0;
piVar3 = piVar3 + 1;
psVar4 = psVar4 + 1;
iVar2 = iVar2 + -1;
} while (iVar2 != 0);
}
buildingType = buildingType + 1;
psVar1 = psVar1 + 0x196;
} while (buildingType < this->maxBuildingsCount);
}
return;
}


}
}
}