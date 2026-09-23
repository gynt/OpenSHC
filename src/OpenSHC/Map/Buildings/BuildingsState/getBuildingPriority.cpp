#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F700
int BuildingsState::getBuildingPriority(int buildingType,int hasBurningBuilding)

{
int _index;

_index = 0;
/* 
  Low number means high priority!
 */

if (hasBurningBuilding == 0) {
do {
if ((short)DAT_BuildingDefinedData::instance.BuildingPrioritiesWhenNoFire[_index] == buildingType) {
return _index;
}
_index = _index + 1;
} while (_index < 30);
_index = 30;
}
else {
while ((short)DAT_BuildingDefinedData::instance.BuildingPrioritiesWhenFire[_index] != buildingType) {
_index = _index + 1;
if (30 < _index) {
return(int)( 30);
}
}
}
return _index;
}


}
}
}