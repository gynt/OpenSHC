#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Units::UnitType;


/* 
  Loops through the buildingID queue and assignes peasants to them
   decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F9D0
void BuildingsState::processBuildingIDsNeedPeasantsQueue(int playerID)

{
BOOLEnum BVar1;
int _unitID;
int _buildingID;
int workerIndex;
short *_buildingIDToBeProcessedPtr;
int i;
BuildingTypeShort _buildingType;
UnitType _unitType;
UnitTypeInt _unitTypePriest;

i = 0;
if (0 < this->DAT_CountOfBuildingsNeedPeasants) {
_buildingIDToBeProcessedPtr = this->DAT_BuildingIDsNeedPeasantsQueue;
do {
_unitTypePriest = DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[0x25];
_buildingID = (int)*_buildingIDToBeProcessedPtr;
if (this->buildings[_buildingID].buildingTypeBasedEmployeeCount == 1) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(
DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType
[(short)this->buildings[_buildingID].buildingType], 
_buildingID, playerID, 0);
workerIndex = 0;
LAB_0040fc05:
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, workerIndex);
}
else {
_buildingType = this->buildings[_buildingID].buildingType;
if (_buildingType == OpenSHC::Map::Buildings::BT_QUARRY) {
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 0);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_QUARRYMASON, _buildingID, playerID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, 0);
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 1);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_QUARRYMASON, _buildingID, playerID, 1);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, 1);
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 2);
if (BVar1 == FALSE) {
_unitType = OpenSHC::Map::Units::UT_QUARRYMASON;
LAB_0040fbf9:
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(_unitType, _buildingID, playerID, 2);
workerIndex = 2;
goto LAB_0040fc05;
}
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_IRONMINE) {
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 0);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_MINER, _buildingID, playerID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, 0);
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 1);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_TRANSPORTMINER, _buildingID, playerID, 1);
workerIndex = 1;
goto LAB_0040fc05;
}
}
else {
_unitType = DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[0x22];
if ((_buildingType == OpenSHC::Map::Buildings::BT_MILL) ||
(_unitType = DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[0x46],
_buildingType == OpenSHC::Map::Buildings::BT_WATERPOT)) {
LAB_0040fb97:
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 0);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(_unitType, _buildingID, playerID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, 0);
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 1);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(_unitType, _buildingID, playerID, 1);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, 1);
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 2);
if (BVar1 == FALSE) goto LAB_0040fbf9;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_CHURCH) {
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 0);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(_unitTypePriest, _buildingID, playerID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(_buildingID, _unitID, 0);
}
BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(_buildingID, 1);
if (BVar1 == FALSE) {
_unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(_unitTypePriest, _buildingID, playerID, 1);
workerIndex = 1;
goto LAB_0040fc05;
}
}
else {
_unitType = DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[0x26];
if (_buildingType == OpenSHC::Map::Buildings::BT_CATHEDRAL) goto LAB_0040fb97;
}
}
}
_buildingIDToBeProcessedPtr = _buildingIDToBeProcessedPtr + 1;
i = i + 1;
} while (i < this->DAT_CountOfBuildingsNeedPeasants);
}
return;
}


}
}
}