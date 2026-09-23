#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F3D0
void BuildingsState::setBuildingToAppleFarm(int buildingID)

{
this->buildings[buildingID].field66_0xbe = 0x20;
return;
}


}
}
}