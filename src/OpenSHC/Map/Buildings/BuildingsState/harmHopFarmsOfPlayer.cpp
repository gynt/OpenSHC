#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040EF40
void BuildingsState::harmHopFarmsOfPlayer(int param_1)

{
int iVar1;
int *piVar2;
int iVar3;
int iVar4;
short *psVar5;

iVar3 = 0;
if (0 < this->maxBuildingsCount) {
psVar5 = &this->buildings[0].owner;
do {
if (((psVar5[-3] != ((BuildingLogicalState)0)) && (*psVar5 == param_1)) && (psVar5[-2] == OpenSHC::Map::Buildings::BT_HOPFARM)) {
piVar2 = (int *)(psVar5 + 0x79);
iVar4 = 0x18;
do {
iVar1 = *piVar2;
piVar2 = piVar2 + 1;
iVar4 = iVar4 + -1;
DAT_TileMapState::instance.DamageLayer[iVar1] =
((char)DAT_TileMapState::instance.DamageLayer[iVar1] < '\x06') - 1U &0x1c;
} while (iVar4 != 0);
psVar5[0x77] = -0x708;
psVar5[0xc1] = 2;
}
iVar3 = iVar3 + 1;
psVar5 = psVar5 + 0x196;
} while (iVar3 < this->maxBuildingsCount);
}
return;
}


}
}
}