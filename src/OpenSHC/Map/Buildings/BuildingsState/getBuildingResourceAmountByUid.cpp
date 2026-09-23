#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00409330
int BuildingsState::getBuildingResourceAmountByUid(int buildingID,int param_2,ResourceType param_3)

{
if (this->buildings[buildingID].uid != param_2) {
return 0;
}
return this->buildings[buildingID].resources[param_3];
}


}
}
}