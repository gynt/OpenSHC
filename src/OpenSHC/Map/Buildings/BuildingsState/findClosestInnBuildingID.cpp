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


// FUNCTION: STRONGHOLDCRUSADER 0x0040B1A0
int BuildingsState::findClosestInnBuildingID(int unitID)

{
int iVar1;
int _buildingID;
int _distanceLimit;
BuildingLogicalStateShort *_pBuildingLogicalState;
short _playerID;
int _unitID;

_unitID = unitID;
_playerID = DAT_UnitsState::instance.units[unitID].owner;
_buildingID = 1;
_distanceLimit = 10000;
unitID = 0;
iVar1 = 0;
if (1 < this->maxBuildingsCount) {
_pBuildingLogicalState = &this->buildings[1].logicalState;
do {
/* 
  ownerPlayerIndex
 */

/* 
  buildingType == INN
 */

/* 
  flagonsOfAle
 */

if ((((*_pBuildingLogicalState != ((BuildingLogicalState)0)) && (*_pBuildingLogicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(_pBuildingLogicalState[3] == _playerID)) &&
(((_pBuildingLogicalState[1] == OpenSHC::Map::Buildings::BT_INN && (0 < (short)_pBuildingLogicalState[0xf0])) &&
(MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x, (int)((int)(
DAT_UnitsState::instance.units[_unitID].y)), (int)((int)((short)_pBuildingLogicalState[0x17])), (int)((int)(
(short)_pBuildingLogicalState[0x18]))),
DAT_DirectionAlgorithmState::instance.distanceHigh < _distanceLimit)))) {
_distanceLimit = DAT_DirectionAlgorithmState::instance.distanceHigh;
unitID = _buildingID;
}
_buildingID = _buildingID + 1;
_pBuildingLogicalState = _pBuildingLogicalState + 0x196;
iVar1 = unitID;
} while (_buildingID < this->maxBuildingsCount);
}
return iVar1;
}


}
}
}