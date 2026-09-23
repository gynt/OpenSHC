#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410C40
undefined4 BuildingsState::playerHasBurningBuilding(int playerID)

{
Building * psVar1;
int iVar1;

iVar1 = 1;
if (1 < this->maxBuildingsCount) {
psVar1 = &this->buildings[1];
do {
if ((((psVar1->fireDuration != 0) && (psVar1->owner == playerID)) &&
(psVar1->logicalState != ((BuildingLogicalState)0))) && (psVar1->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) {
return(undefined4)( 1);
}
iVar1 = iVar1 + 1;
psVar1 = psVar1 + 0x196;
} while (iVar1 < this->maxBuildingsCount);
}
return(undefined4)( 0);
}


}
}
}