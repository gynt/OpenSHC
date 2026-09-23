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


// FUNCTION: STRONGHOLDCRUSADER 0x0040D090
void BuildingsState::harmWheatFarmsOfPlayer(int playerID)

{
int *_ptrWheatFarmTileArray;
int iVar1;
int iVar2;
Building * psVar5;
int _tile;

iVar1 = 0;
if (0 < this->maxBuildingsCount) {
psVar5 = &this->buildings[0];
do {
if (((psVar5->logicalState != ((BuildingLogicalState)0)) && (psVar5->owner == playerID)) &&
(psVar5->buildingType == OpenSHC::Map::Buildings::BT_WHEATFARM)) {
_ptrWheatFarmTileArray = &psVar5->tileRef1;
iVar2 = 0x24;
do {
_tile = *_ptrWheatFarmTileArray;
_ptrWheatFarmTileArray = _ptrWheatFarmTileArray + 1;
iVar2 = iVar2 + -1;
DAT_TileMapState::instance.DamageLayer[_tile] =
((char)DAT_TileMapState::instance.DamageLayer[_tile] < '\b') - 1U &0x65;
} while (iVar2 != 0);
psVar5->growCounter = 64336;
*(undefined2 *)&psVar5->wheatGrowStateRelated = 2;
}
iVar1 = iVar1 + 1;
psVar5 = psVar5 + 0x196;
} while (iVar1 < this->maxBuildingsCount);
}
return;
}


}
}
}