#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C1F0
int BuildingsState::getResourceSpace(int param_1,int *resourceType)

{
BuildingTypeShort BVar1;
int iVar2;
BuildingType BVar3;
int iVar4;
BuildingTypeShort *pBVar5;
int iVar6;
int _buildingID;
int *_resourceType;

_resourceType = resourceType;
iVar6 = -1;
BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)((ResourceType)resourceType);
iVar2 = this->maxBuildingsCount;
if (BVar3 == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
return 1000000;
}
_buildingID = 1;
if (1 < this->maxBuildingsCount) {
resourceType = this->buildings[1].resources + (int)resourceType;
pBVar5 = &this->buildings[1].buildingType;
do {
if (((pBVar5[-1] != OpenSHC::Map::Buildings::BLS_NORMAL) || ((short)pBVar5[2] != param_1)) ||
(BVar1 = *pBVar5, (int)(short)BVar1 != BVar3)) goto LAB_0040c2cb;
if (iVar6 == -1) {
iVar6 = 0;
}
if (BVar1 == OpenSHC::Map::Buildings::BT_ARMORY) {
iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeArmoryRemainingCapacity, this)(_buildingID);
LAB_0040c2c9:
iVar6 = iVar6 + iVar4;
}
else {
if (BVar1 == OpenSHC::Map::Buildings::BT_GRANARY) {
iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceCountThatCanBeDeposited, this)(_buildingID, (undefined4)((int)(_resourceType)), (int)((int)(250)));
goto LAB_0040c2c9;
}
if (*(int *)(pBVar5 + 0x59) == 0) {
LAB_0040c2ad:
iVar6 = iVar6 + DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[(int)_resourceType];
}
else if (*resourceType != 0) {
if (*(int *)(pBVar5 + 0x59) == 0) goto LAB_0040c2ad;
if (*resourceType <
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[(int)_resourceType]) {
iVar4 = DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[(int)_resourceType] -
*resourceType;
goto LAB_0040c2c9;
}
}
}
LAB_0040c2cb:
resourceType = resourceType + 0xcb;
_buildingID = _buildingID + 1;
pBVar5 = pBVar5 + 0x196;
} while (_buildingID < iVar2);
}
return iVar6;
}


}
}
}