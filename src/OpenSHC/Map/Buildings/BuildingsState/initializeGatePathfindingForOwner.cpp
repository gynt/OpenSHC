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


// FUNCTION: STRONGHOLDCRUSADER 0x00419A30
void BuildingsState::initializeGatePathfindingForOwner(int param_1)

{
BuildingTypeShort *pBVar1;
int buildingID;

buildingID = 1;
if (1 < this->maxBuildingsCount) {
pBVar1 = &this->buildings[1].buildingType;
do {
if ((((pBVar1[-1] != ((BuildingLogicalState)0)) && ((short)pBVar1[2] == param_1)) &&
((*pBVar1 == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE || (*pBVar1 == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL)))) && (pBVar1[0xfa] == 0)
) {
DAT_PathFindingState::instance.climbData[(short)pBVar1[0x100]].isRecognizedByPathfinding = 1;
*(byte *)(pBVar1 + 0xe8) = 0;
*(byte *)((int)pBVar1 + 0x1d1) = 0xb;
pBVar1[0xf3] = 0x9c4;
MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates, DAT_PathFindingState::ptr)(buildingID);
}
buildingID = buildingID + 1;
pBVar1 = pBVar1 + 0x196;
} while (buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}