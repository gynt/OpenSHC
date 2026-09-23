#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410290
void BuildingsState::updateVisuallyActiveState(int buildingID)

{
short _indicator;

_indicator = this->buildings[buildingID].tickRelatedVisuallyActiveIndicator;
if (this->buildings[buildingID].buildingIsVisuallyActive == 0) {
if (0 < _indicator) {
if (_indicator == 5) {
this->buildings[buildingID].tickRelatedVisuallyActiveIndicator = 4;
}
else {
this->buildings[buildingID].tickRelatedVisuallyActiveIndicator =
_indicator - (undefined2)this->isFirstTickInLoop;
}
}
this->buildings[buildingID].buildingIsVisuallyActive =
(ushort)(this->buildings[buildingID].tickRelatedVisuallyActiveIndicator != 0);
}
else if (_indicator < 5) {
if (_indicator == 0) {
this->buildings[buildingID].tickRelatedVisuallyActiveIndicator = 1;
return;
}
this->buildings[buildingID].tickRelatedVisuallyActiveIndicator =
(undefined2)this->isFirstTickInLoop + _indicator;
return;
}
return;
}


}
}
}