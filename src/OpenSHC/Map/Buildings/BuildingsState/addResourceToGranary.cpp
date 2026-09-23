#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BC10
void BuildingsState::addResourceToGranary(ResourceType resourceType,int playerID,int amount)

{
int iVar1;
int buildingID;
Building * pBVar2;

buildingID = 1;
if (1 < this->maxBuildingsCount) {
pBVar2 = &this->buildings[1];
do {
if ((pBVar2->owner == playerID) && (pBVar2->buildingType == OpenSHC::Map::Buildings::BT_GRANARY)) {
for (iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceCountThatCanBeDeposited, this)(buildingID, (undefined4)((int)(resourceType)), (int)((int)(250))); iVar1 != 0;
iVar1 = iVar1 + -1) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, this)(buildingID, pBVar2->uid, resourceType, 1, (int)((int)(250)), 1);
amount = amount + -1;
if (amount == 0) {
return;
}
}
}
buildingID = buildingID + 1;
pBVar2 = pBVar2 + 0x196;
} while (buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}