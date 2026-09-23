#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A860
void BuildingsState::destroyBuildings(int playerID)

{
Building * psVar1;
int _buildingID;

_buildingID = 1;
if (1 < this->maxBuildingsCount) {
psVar1 = &this->buildings[1];
do {
if ((psVar1->logicalState != ((BuildingLogicalState)0)) && (psVar1->owner == playerID)) {
DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding =
(int)(DAT_BuildingDefinedData::instance.BuildingShowRubbleWhenDestroyed
[(short)psVar1->buildingType] == 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, this)(_buildingID);
}
_buildingID = _buildingID + 1;
psVar1 = psVar1 + 0x196;
} while (_buildingID < this->maxBuildingsCount);
}
return;
}


}
}
}