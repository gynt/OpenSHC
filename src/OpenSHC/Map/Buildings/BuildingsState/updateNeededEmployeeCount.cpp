#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F620
void BuildingsState::updateNeededEmployeeCount(int buildingID)

{
short *psVar1;
short _reqEmployees;
BOOLEnum _hasWorker;
int _workerID;
short _countRequired;
short _owner;
bool _sleeping;
int *_totalReqEmployees;
BuildingTypeShort _type;

_countRequired = this->buildings[buildingID].buildingTypeBasedEmployeeCount;
_workerID = 0;
if ((((0 < _countRequired) &&
(_sleeping = this->buildings[buildingID].sleeping,
this->buildings[buildingID].currentlyNeededEmployeeCount = 0, _sleeping == false
)) && (_type = this->buildings[buildingID].buildingType,
_type != OpenSHC::Map::Buildings::BT_MERCENARYPOST)) && (_type != OpenSHC::Map::Buildings::BT_BARRACKS)) {
_owner = this->buildings[buildingID].owner;
this->buildings[buildingID].currentEmployeeCount = 0;
if (0 < _countRequired) {
do {
_hasWorker = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, _workerID);
if (_hasWorker == FALSE) {
this->buildings[buildingID].workerUID[_workerID] = 0;
this->buildings[buildingID].workerID[_workerID] = 0;
}
else {
psVar1 = &this->buildings[buildingID].currentEmployeeCount;
*psVar1 = *psVar1 + 1;
}
_workerID = _workerID + 1;
} while (_workerID < this->buildings[buildingID].buildingTypeBasedEmployeeCount);
}
_reqEmployees =
this->buildings[buildingID].buildingTypeBasedEmployeeCount -
this->buildings[buildingID].currentEmployeeCount;
_totalReqEmployees = &DAT_GameState::instance.playerDataArray[_owner].countEconomyBuilding_fixme;
this->buildings[buildingID].currentlyNeededEmployeeCount = _reqEmployees;
*_totalReqEmployees = *_totalReqEmployees + (int)_reqEmployees;
}
return;
}


}
}
}