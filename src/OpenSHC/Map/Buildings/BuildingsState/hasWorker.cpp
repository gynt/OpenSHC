#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Units::UnitLogicState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F540
BOOLEnum BuildingsState::hasWorker(int buildingID,int workerSlot)

{
UnitLogicStateShort UVar1;
int iVar2;

iVar2 = (int)this->buildings[buildingID].workerID[workerSlot];
if (iVar2 < 1) {
return FALSE;
}
UVar1 = DAT_UnitsState::instance.units[iVar2].logicalState;
if (((UVar1 != OpenSHC::Map::Units::ULS_REMOVE) && (UVar1 != OpenSHC::Map::Units::ULS_INVISIBLE)) &&
(DAT_UnitsState::instance.units[iVar2].buildingID == buildingID)) {
return (uint)(DAT_UnitsState::instance.units[iVar2].uid ==
this->buildings[buildingID].workerUID[workerSlot]);
}
return FALSE;
}


}
}
}