#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnumInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041B890
void BuildingsState::findQuarryPileLocation(int playerID,int x,int y,int buildingSize,int pileSize,int tryUnk,MappersEnum commandBuildingType)

{
int _tryUnk;
int _buildingSize;
int _triesUnk;

_buildingSize = buildingSize;
_triesUnk = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
/* 
  seems to do the opposite of the above line, silly
 */

_tryUnk = (int)(_triesUnk + (_triesUnk >> 0x1f &3U)) >> 2;
/* 
  reuse!
 */

buildingSize = 0;
if (0 < _triesUnk) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(_buildingSize, pileSize, _tryUnk, tryUnk);
DAT_TileMapState::instance.DAT_TempBuildingRotation = 0;
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::checkBuildingCanBePlacedHere, DAT_TileMapState::ptr)(playerID, (uint)((int)(this->DAT_TempXOffset + x)), (uint)((int)(
this->DAT_TempYOffset + y)), commandBuildingType, pileSize);
if (DAT_TileMapState::instance.buildingPlacementFail == FALSE) {
return;
}
_tryUnk = _tryUnk + 1;
if (_triesUnk <= _tryUnk) {
_tryUnk = 0;
}
buildingSize = buildingSize + 1;
} while (buildingSize < _triesUnk);
}
return;
}


}
}
}