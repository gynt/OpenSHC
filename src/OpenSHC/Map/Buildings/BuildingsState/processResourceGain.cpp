#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Game::Resources::ResourceType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041C310
BOOLEnum BuildingsState::processResourceGain(int playerID,ResourceType resourceType,int amount)

{
int *piVar1;
int _space;
BuildingType _storageType;
int _buildingSpace;
int *_pBuildingStorage;
Building * _pOwner;
Building * psVar5;
int iVar2;
int local_8;
int *local_4;
ResourceType _resource;

_resource = resourceType;
_space = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceSpace, this)(playerID, (int *)((int)(resourceType)));
if (_space < amount) {
return FALSE;
}
if (0 < amount) {
_storageType = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
if (_storageType != OpenSHC::Map::Buildings::BT_MANORHOUSE) {
if (_storageType == OpenSHC::Map::Buildings::BT_ARMORY) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToArmory, this)(resourceType, playerID, amount);
return TRUE;
}
if (_storageType != OpenSHC::Map::Buildings::BT_GRANARY) {
iVar2 = 1;
if (1 < this->maxBuildingsCount) {
_pBuildingStorage = this->buildings[1].resources + resourceType;
_pOwner = &this->buildings[1];
do {
if (((((_pOwner->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) && (_pOwner->owner == playerID))
&& ((int)(short)_pOwner->buildingType == _storageType)) &&
((_pOwner->currentNumberOfResource != 0 && (*_pBuildingStorage != 0)))) &&
(_pOwner->currentNumberOfResource != 0)) {
if (*_pBuildingStorage <
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[_resource]) {
_buildingSpace =
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[_resource] -
*_pBuildingStorage;
resourceType = ((ResourceType)0);
if (0 < _buildingSpace) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, this)(iVar2, _pOwner->uid, _resource, 1, (int)((int)(
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[_resource])), 1);
amount = amount + -1;
if (amount < 1) {
return TRUE;
}
resourceType = resourceType + OpenSHC::Game::Resources::RT_LOGS;
} while ((int)resourceType < _buildingSpace);
}
}
}
iVar2 = iVar2 + 1;
_pBuildingStorage = _pBuildingStorage + 0xcb;
_pOwner = _pOwner + 0x196;
} while (iVar2 < this->maxBuildingsCount);
}
local_8 = 1;
if (1 < this->maxBuildingsCount) {
local_4 = this->buildings[1].resources + _resource;
psVar5 = &this->buildings[1];
do {
if (((psVar5->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) && (psVar5->owner == playerID)) &&
(((int)(short)psVar5->buildingType == _storageType &&
(psVar5->currentNumberOfResource == 0)))) {
iVar2 = DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[_resource] - *local_4;
resourceType = ((ResourceType)0);
if (0 < iVar2) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, this)(local_8, psVar5->uid, _resource, 1, (int)((int)(
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[_resource])), 1);
amount = amount + -1;
if (amount < 1) {
return TRUE;
}
resourceType = resourceType + OpenSHC::Game::Resources::RT_LOGS;
} while ((int)resourceType < iVar2);
}
}
local_4 = local_4 + 0xcb;
local_8 = local_8 + 1;
psVar5 = psVar5 + 0x196;
} while (local_8 < this->maxBuildingsCount);
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
return FALSE;
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToGranary, this)(resourceType, playerID, amount);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countPlayerResources, this)(playerID);
return TRUE;
}
piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + resourceType;
*piVar1 = *piVar1 + amount;
}
return TRUE;
}


}
}
}