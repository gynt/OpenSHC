#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040AAD0
int BuildingsState::findFirstBuildingIDForPlayerAndType(int playerID,BuildingType buildingType)

{
int _index;
Building * _buildingAddressOffset;

_index = 1;
if (1 < this->maxBuildingsCount) {
/* 
  field_0x410 points to 0xd0 (208) in the Building structure
 */

_buildingAddressOffset = &this->buildings[1];
do {
/* 
  if building[_index].field_0xd0 is not 3 and not 0 and
   the building[_index].owner matches playerID and
   the building[_index].type matches buildingType then
   return _index (ID)
 */

if ((((_buildingAddressOffset->logicalState != ((BuildingLogicalState)0)) &&
(_buildingAddressOffset->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(_buildingAddressOffset->owner == playerID)) &&
((int)(short)_buildingAddressOffset->buildingType == buildingType)) {
return _index;
}
_index = _index + 1;
/* 
  add with 812
 */

_buildingAddressOffset = _buildingAddressOffset + 0x196;
} while (_index < this->maxBuildingsCount);
}
return 0;
}


}
}
}