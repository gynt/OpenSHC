#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F5C0
void BuildingsState::assignWorkerToBuilding(int buildingID,int unitID,int workerIndex)

{
this->buildings[buildingID].workerID[workerIndex] = (short)unitID;
this->buildings[buildingID].workerUID[workerIndex] = DAT_UnitsState::instance.units[unitID].uid
;
DAT_UnitsState::instance.units[unitID].workerIndex = (short)workerIndex;
DAT_UnitsState::instance.units[unitID].buildingID = (short)buildingID;
return;
}


}
}
}