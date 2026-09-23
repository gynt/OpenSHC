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


// FUNCTION: STRONGHOLDCRUSADER 0x00419960
void BuildingsState::updatePathLinkageTileMap(int param_1)

{
Building * _buildingPtr;
int _buildingID;

_buildingID = 1;
if (1 < this->maxBuildingsCount) {
_buildingPtr = &this->buildings[1];
do {
if ((_buildingPtr->logicalState != ((BuildingLogicalState)0)) &&
((_buildingPtr->buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE ||
(_buildingPtr->buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL)))) {
if (param_1 == 1) {
_buildingPtr->pathLinkageRelated1 =
(short)(char)_buildingPtr->pathLinkageRelated2;
_buildingPtr->pathLinkageRelated2 = 2;
}
else if (param_1 == 2) {
_buildingPtr->pathLinkageRelated1 =
(short)(char)_buildingPtr->pathLinkageRelated2;
_buildingPtr->pathLinkageRelated2 = 0;
}
else {
_buildingPtr->pathLinkageRelated2 = (byte)_buildingPtr->pathLinkageRelated1;
}
if (_buildingPtr->pathLinkageRelated2 == 2) {
DAT_PathFindingState::instance.climbData[_buildingPtr->laddermanDataID].
isRecognizedByPathfinding = 0;
}
else {
DAT_PathFindingState::instance.climbData[_buildingPtr->laddermanDataID].
isRecognizedByPathfinding = 1;
}
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates, DAT_PathFindingState::ptr)(_buildingID);
}
_buildingID = _buildingID + 1;
_buildingPtr = _buildingPtr + 0x196;
} while (_buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}