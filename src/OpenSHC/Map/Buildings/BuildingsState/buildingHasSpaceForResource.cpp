#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040BE70
BOOLEnum BuildingsState::buildingHasSpaceForResource(int buildingID,ResourceType resourceType)

{
int iVar1;

iVar1 = this->buildings[buildingID].currentNumberOfResource;
if (iVar1 != 0) {
if (this->buildings[buildingID].resources[resourceType] == 0) {
return FALSE;
}
if (iVar1 != 0) {
return (uint)(this->buildings[buildingID].resources[resourceType] <
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[resourceType]);
}
}
return TRUE;
}


}
}
}