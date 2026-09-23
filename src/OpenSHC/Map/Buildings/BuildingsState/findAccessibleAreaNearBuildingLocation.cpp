#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BAB0
int BuildingsState::findAccessibleAreaNearBuildingLocation(int x,int y,int buildingSize)

{
int _tile;
int _try;
int _maxTries;

_maxTries = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingSize];
_try = 0;
if (0 < _maxTries) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingSize, 1, _try, 0);
_tile = DAT_ViewportRenderState::instance.translationMatrix[this->DAT_TempYOffset + y].
addXgetTile + this->DAT_TempXOffset + x;
if (DAT_TileMapState::instance.PathConnectionLayer[_tile] != 0) {
return (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
}
_try = _try + 1;
} while (_try < _maxTries);
}
return 0;
}


}
}
}