#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419780
void BuildingsState::initBuildingCosts()

{
int *_address;
int *_runtimeAddress;

/* 
  copies the building costs to the runtime address
 */

_address = DAT_BuildingDefinedData::instance.BuildingCost[0] + 1;
_runtimeAddress = &this->buildingCosts[0].requiredStone_0x4;
do {
((BuildingCostStruct *)(_runtimeAddress + -1))->requiredWood =
(*(int (*) [5])(_address + -1))[0];
*_runtimeAddress = *_address;
_runtimeAddress[1] = _address[1];
_runtimeAddress[2] = _address[2];
_runtimeAddress[3] = _address[3];
_address = _address + 5;
_runtimeAddress = _runtimeAddress + 5;
/* 
  only copies 2000 bytes, not 2200, last 200 bytes in the structure are all
   zeros...
 */

} while ((int)_address < 0x5c2a6c);
return;
}


}
}
}