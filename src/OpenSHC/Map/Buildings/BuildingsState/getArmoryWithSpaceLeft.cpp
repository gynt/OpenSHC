#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00422370
uint BuildingsState::getArmoryWithSpaceLeft(uint targetBuildingID,undefined4 producedItemTypeUnk,int playerID,int resourceToDeposit)

{
uint uVar1;
int iVar2;
Building * pBVar3;
uint _buildingID;

if (targetBuildingID != 0) {
uVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(targetBuildingID, (undefined4)((int)(producedItemTypeUnk)), playerID, 
resourceToDeposit);
return uVar1;
}
_buildingID = 1;
if (1 < this->maxBuildingsCount) {
pBVar3 = &this->buildings[1];
do {
if (pBVar3->buildingType == OpenSHC::Map::Buildings::BT_ARMORY) {
iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(_buildingID, 0);
if (iVar2 != 0) {
uVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(_buildingID, (undefined4)((int)(producedItemTypeUnk)), playerID, 
resourceToDeposit);
if (uVar1 != 0) {
return _buildingID;
}
}
}
_buildingID = _buildingID + 1;
pBVar3 = pBVar3 + 0x196;
} while ((int)_buildingID < this->maxBuildingsCount);
}
return 0;
}


}
}
}