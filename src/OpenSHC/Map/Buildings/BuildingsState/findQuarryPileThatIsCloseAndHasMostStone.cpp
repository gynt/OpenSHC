#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"



#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00422400
int BuildingsState::findQuarryPileThatIsCloseAndHasMostStone(int playerID,int x,int y,int unitID)

{
int iVar1;
int _value;
int _buildingID;
Building * _ptrBuilding;
int _maxValue;
int _highestValueBuilding;
int _stone;
int _result;

_buildingID = 1;
_maxValue = 0;
_highestValueBuilding = 0;
_result = 0;
if (1 < this->maxBuildingsCount) {
_ptrBuilding = &this->buildings[1];
do {
/* 
  fixme
 */

if ((((_ptrBuilding->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
(_ptrBuilding->buildingType == OpenSHC::Map::Buildings::BT_QUARRYSTOCKPILE)) &&
(_ptrBuilding->owner == playerID)) &&
((_stone = _ptrBuilding->resources[4], 0 < _stone &&
(iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, this)(_buildingID, 1), iVar1 != 0)))) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, DAT_DirectionAlgorithmState::ptr)(x, y, (int)((int)((short)_ptrBuilding->x)), (int)((int)(
(short)_ptrBuilding->y)));
_value = 400 - DAT_DirectionAlgorithmState::instance.distanceHigh;
if ((DAT_UnitsState::instance.units[unitID].field300_0x410 != 0) && (7 < _stone)) {
if (_stone < 40) {
_value = _value + _stone / 2;
}
else {
_value = _value + _stone;
}
}
if (_maxValue <= _value) {
_maxValue = _value;
_highestValueBuilding = _buildingID;
}
}
_buildingID = _buildingID + 1;
_ptrBuilding = _ptrBuilding + 0x196;
_result = _highestValueBuilding;
} while (_buildingID < this->maxBuildingsCount);
}
return _result;
}


}
}
}