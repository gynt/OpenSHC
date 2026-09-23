#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  Sorts the buildingID queue by their building priorities
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041C6F0
void BuildingsState::sortBuildingIDsNeedPeasantsQueue(int playerID)

{
short _currentBuildingID;
int _hasBurningBuilding;
int _buildingBeforePrio;
int _currBuildingPrio;
short *_ptrQueue;
int i;
short _currentIdleValue;
bool _needsSorting;
short _previousBuildingID;
short _previousIdleValue;

_buildingBeforePrio = this->DAT_CountOfBuildingsNeedPeasants;
if (1 < this->DAT_CountOfBuildingsNeedPeasants) {
_hasBurningBuilding = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::playerHasBurningBuilding, this)(playerID);
do {
_needsSorting = false;
i = 0;
if (_buildingBeforePrio == 1 || _buildingBeforePrio + -1 < 0) {
return;
}
_ptrQueue = this->DAT_BuildingIDsNeedPeasantsQueue;
do {
_ptrQueue = _ptrQueue + 1;
_currentBuildingID = *_ptrQueue;
_previousBuildingID = _ptrQueue[-1];
_currentIdleValue = this->buildings[_currentBuildingID].idleTimerUnk;
_previousIdleValue = this->buildings[_previousBuildingID].idleTimerUnk;
if (_currentIdleValue < _previousIdleValue) {
LAB_0041c7c3:
_needsSorting = true;
/* 
  swap buildings in queue
 */

*_ptrQueue = _previousBuildingID;
_ptrQueue[-1] = _currentBuildingID;
}
else {
_buildingBeforePrio =MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority, this)(
(int)(short)this->buildings[_previousBuildingID].
buildingType, _hasBurningBuilding);
_currBuildingPrio =MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingPriority, this)(
(int)(short)this->buildings[_currentBuildingID].
buildingType, _hasBurningBuilding);
if ((_currBuildingPrio < _buildingBeforePrio) && (_currentIdleValue <= _previousIdleValue)
) {
_currentBuildingID = *_ptrQueue;
goto LAB_0041c7c3;
}
}
i = i + 1;
} while (i < this->DAT_CountOfBuildingsNeedPeasants + -1);
_buildingBeforePrio = this->DAT_CountOfBuildingsNeedPeasants;
} while (_needsSorting);
}
return;
}


}
}
}