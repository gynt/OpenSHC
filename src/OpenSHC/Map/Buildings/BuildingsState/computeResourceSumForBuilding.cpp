#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C130
uint BuildingsState::computeResourceSumForBuilding(int buildingID)

{
int _resourceSlot;
int *_ptrResource;
int *_ptrCurrentNumber;

this->buildings[buildingID].currentNumberOfResource = 0;
this->buildings[buildingID].currentLimitOfResource = 0;
_resourceSlot = 1;
_ptrResource = this->buildings[buildingID].resources;
do {
_ptrResource = _ptrResource + 1;
_ptrCurrentNumber = &this->buildings[buildingID].currentNumberOfResource;
*_ptrCurrentNumber = *_ptrCurrentNumber + *_ptrResource;
if ((*_ptrResource != 0) &&
(this->buildings[buildingID].currentLimitOfResource == 0)) {
this->buildings[buildingID].currentLimitOfResource =
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[_resourceSlot];
this->buildings[buildingID].currentStoredResourceType = (short)_resourceSlot;
}
_resourceSlot = _resourceSlot + 1;
} while (_resourceSlot < 0x19);
return(uint)( this->buildings[buildingID].currentNumberOfResource);
}


}
}
}