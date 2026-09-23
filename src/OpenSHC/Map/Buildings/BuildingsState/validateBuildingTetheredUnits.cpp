#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004173D0
void BuildingsState::validateBuildingTetheredUnits(int buildingID)

{
char *pcVar1;
short *psVar2;
int _counter;
short *_arrayPointer;

_counter = 0;
this->buildings[buildingID].randomOutpostField = '\0';
_arrayPointer = &this->buildings[buildingID].insideUnitID1;
do {
if (*_arrayPointer != 0) {
psVar2 = this->buildings[buildingID].quarryLinkedOxTethers + _counter * 2 + 0xf;
if (*(int *)psVar2 == DAT_UnitsState::instance.units[*_arrayPointer].uid) {
pcVar1 = &this->buildings[buildingID].randomOutpostField;
*pcVar1 = *pcVar1 + '\x01';
}
else {
*_arrayPointer = 0;
psVar2[0] = 0;
psVar2[1] = 0;
}
}
_counter = _counter + 1;
_arrayPointer = _arrayPointer + 1;
} while (_counter < 4);
return;
}


}
}
}