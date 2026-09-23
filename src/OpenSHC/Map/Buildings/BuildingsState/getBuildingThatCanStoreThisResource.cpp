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
  param_1 is 0xd (13) for apple farms. index in resource array of building?
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00422230
int BuildingsState::getBuildingThatCanStoreThisResource(ResourceType resourceType,int amount,int playerID)

{
BuildingType BVar1;
int _buildingID;
uint uVar2;
int iVar3;
Building * _ptrBuilding;
Building * pBVar3;
int *_resourceSlot;
BuildingTypeShort *pBVar4;

/* 
  get the building we are looking for for this resource type:
   granary or stockpile?
 */

BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingStorageTypeForResourceType, this)(resourceType);
/* 
  check if we are looking for a stockpile
 */

if (BVar1 == OpenSHC::Map::Buildings::BT_STOCKPILE) {
_buildingID = 1;
if (1 < this->maxBuildingsCount) {
_ptrBuilding = &this->buildings[1];
_resourceSlot = this->buildings[1].resources + resourceType;
do {
/* 
  check if the building type is a stockpile, and whether it is owned by the
   right person, and whether it already has resources on it, but is not full yet
   
 */

if (((_ptrBuilding->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
(_ptrBuilding->buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE)) &&
((_ptrBuilding->owner == playerID &&
((*_resourceSlot != 0 &&
(*_resourceSlot < DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]))
)))) {
return _buildingID;
}
_buildingID = _buildingID + 1;
_ptrBuilding = _ptrBuilding + 0x196;
_resourceSlot = _resourceSlot + 0xcb;
} while (_buildingID < this->maxBuildingsCount);
}
_buildingID = 1;
if (1 < this->maxBuildingsCount) {
pBVar3 = &this->buildings[1];
do {
if ((((pBVar3->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
(pBVar3->buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE)) && (pBVar3->owner == playerID)) &&
(pBVar3->currentNumberOfResource < 1)) {
return _buildingID;
}
_buildingID = _buildingID + 1;
pBVar3 = pBVar3 + 0x196;
} while (_buildingID < this->maxBuildingsCount);
}
}
else if ((BVar1 == OpenSHC::Map::Buildings::BT_GRANARY) && (_buildingID = 1, 1 < this->maxBuildingsCount)) {
pBVar4 = &this->buildings[1].buildingType;
while ((((pBVar4[-1] != OpenSHC::Map::Buildings::BLS_NORMAL || (*pBVar4 != OpenSHC::Map::Buildings::BT_GRANARY)) || ((short)pBVar4[2] != playerID)
) || ((uVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeResourceSumForBuilding, this)(_buildingID),
0xf9 < (int)uVar2 ||
(iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(_buildingID, 0), iVar3 == 0)))))
{
_buildingID = _buildingID + 1;
pBVar4 = pBVar4 + 0x196;
if (this->maxBuildingsCount <= _buildingID) {
return 0;
}
}
/* 
  land here if the building was a granary, and owned by the right player, not
   filled over 249, and ... accessibility??
 */

return _buildingID;
}
return 0;
}


}
}
}