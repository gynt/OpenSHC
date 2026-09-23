#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"

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


// FUNCTION: STRONGHOLDCRUSADER 0x0040F4F0
void BuildingsState::refreshAllBuildingTileDisplays()

{
int buildingID;
BuildingLogicalStateShort *pBVar1;

buildingID = 1;
if (1 < this->maxBuildingsCount) {
pBVar1 = &this->buildings[1].logicalState;
do {
if (*pBVar1 != ((BuildingLogicalState)0)) {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearBuildingDisplayFlagsAndEntities, DAT_TileMapState::ptr)(buildingID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, DAT_TileMapState::ptr)(buildingID);
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