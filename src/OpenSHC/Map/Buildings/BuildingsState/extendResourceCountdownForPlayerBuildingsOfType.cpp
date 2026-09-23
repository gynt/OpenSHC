#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BEE0
void BuildingsState::extendResourceCountdownForPlayerBuildingsOfType(BuildingType buildingType,int someCountdown,int playerID)

{
Building * _building;
int _buildingCounter;

_buildingCounter = 1;
if (1 < this->maxBuildingsCount) {
_building = &this->buildings[1];
do {
if ((((_building->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
((int)(short)_building->buildingType == buildingType)) &&
(_building->owner == playerID)) &&
(_building->resourceRelatedCountDown <= someCountdown)) {
_building->resourceRelatedCountDown = (short)someCountdown;
}
_buildingCounter = _buildingCounter + 1;
_building = _building + 0x196;
} while (_buildingCounter < this->maxBuildingsCount);
}
return;
}


}
}
}