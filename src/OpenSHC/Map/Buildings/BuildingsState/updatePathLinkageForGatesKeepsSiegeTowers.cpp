#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"



#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419C70
void BuildingsState::updatePathLinkageForGatesKeepsSiegeTowers()

{
int _buildingID;
Building * _ptr;
BuildingTypeShort _buildingType;

if (0 < this->pathLinkageKeepWasUpdatedUnk) {
this->counter = this->counter + 1;
this->pathLinkageKeepWasUpdatedUnk = 0;
_buildingID = 1;
_ptr = &this->buildings[1];
do {
if ((_ptr->logicalState != ((BuildingLogicalState)0)) && (_ptr->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) {
_buildingType = _ptr->buildingType;
if (_buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_WOODGATE1) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_STONEKEEP) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_STRONGHOLD) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_KEEPFOUR) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_KEEPFIVE) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToKeeps, DAT_PathFindingState::ptr)(_buildingID);
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED) {
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToSiegeTower, DAT_PathFindingState::ptr)(_buildingID);
}
}
_ptr = _ptr + 406;
_buildingID = _buildingID + 1;
} while ((int)_ptr < 0x1124dc6);
}
return;
}


}
}
}