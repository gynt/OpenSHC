#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  fixme: should this function not belong to cls_0x409330?
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00424220
void BuildingsState::recomputeAccessibilityForAllBuildings()

{
int buildingID;
Building * psVar1;

buildingID = 1;
if (1 < this->maxBuildingsCount) {
psVar1 = &this->buildings[1];
do {
if ((psVar1->logicalState != ((BuildingLogicalState)0)) && (psVar1->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(buildingID, 0);
}
buildingID = buildingID + 1;
psVar1 = psVar1 + 0x196;
} while (buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}