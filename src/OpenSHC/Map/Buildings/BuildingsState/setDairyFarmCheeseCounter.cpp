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


// FUNCTION: STRONGHOLDCRUSADER 0x0040F040
void BuildingsState::setDairyFarmCheeseCounter(int param_1)

{
Building * psVar1;
int iVar1;

iVar1 = 0;
if (0 < this->maxBuildingsCount) {
psVar1 = &this->buildings[0];
do {
if (((psVar1->logicalState != ((BuildingLogicalState)0)) && (psVar1->owner == param_1)) &&
(psVar1->buildingType == OpenSHC::Map::Buildings::BT_DAIRYFARM)) {
psVar1->flagonsOfAleOrCheeseOrReleaseDogs = 1600;
}
iVar1 = iVar1 + 1;
psVar1 = psVar1 + 0x196;
} while (iVar1 < this->maxBuildingsCount);
}
return;
}


}
}
}