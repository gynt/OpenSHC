#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00417450
void BuildingsState::removeTetheredUnitFromBuilding(int buildingID,int unitID)

{
byte *pbVar1;
short *psVar2;
int _counter;
short *_arrayPointer;

_counter = 0;
_arrayPointer = &this->buildings[buildingID].insideUnitID1;
do {
if ((*_arrayPointer == unitID) &&
(psVar2 = this->buildings[buildingID].quarryLinkedOxTethers + _counter * 2 + 0xf
, *(int *)(this->buildings[buildingID].quarryLinkedOxTethers +
_counter * 2 + 0xf) == DAT_UnitsState::instance.units[unitID].uid)) {
pbVar1 = &this->buildings[buildingID].numberOfAnimals;
*pbVar1 = *pbVar1 - 1;
*_arrayPointer = 0;
psVar2[0] = 0;
psVar2[1] = 0;
}
_counter = _counter + 1;
_arrayPointer = _arrayPointer + 1;
} while (_counter < 4);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::validateBuildingTetheredUnits, this)(buildingID);
return;
}


}
}
}