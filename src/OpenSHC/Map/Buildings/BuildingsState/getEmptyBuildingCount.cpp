#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A950
int BuildingsState::getEmptyBuildingCount(int playerID,BuildingType buildingType)

{
int _emptyBuildingCount;
Building * psVar2;
int iVar1;

_emptyBuildingCount = 0;
if (1 < this->maxBuildingsCount) {
psVar2 = &this->buildings[1];
iVar1 = this->maxBuildingsCount + -1;
do {
if ((((psVar2->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) && (psVar2->owner == playerID)) &&
((int)(short)psVar2->buildingType == buildingType)) &&
(psVar2->currentNumberOfResource < 1)) {
_emptyBuildingCount = _emptyBuildingCount + 1;
}
psVar2 = psVar2 + 0x196;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
}
return _emptyBuildingCount;
}


}
}
}