#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
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


// FUNCTION: STRONGHOLDCRUSADER 0x00419BE0
void BuildingsState::rebuildTileLogicLayerForKeeps()

{
int iVar1;
BuildingTypeShort *pBVar2;
int buildingSizeTileIndex;

pBVar2 = &this->buildings[1].buildingType;
do {
if ((pBVar2[-1] != ((BuildingLogicalState)0)) && (DAT_BuildingDefinedData::instance.BuildingIsKeepArray[(short)*pBVar2] != 0)) {
buildingSizeTileIndex = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(buildingSizeTileIndex, (int)((int)(*(uint *)(pBVar2 + 0x13))));
iVar1 = DAT_ViewportRenderState::instance.translationMatrix
[(short)pBVar2[0xf] + DAT_TileMapState::instance.buildingY].addXgetTile +
(int)(short)pBVar2[0xe] + DAT_TileMapState::instance.buildingX;
buildingSizeTileIndex = buildingSizeTileIndex + 1;
DAT_TileMapState::instance.LogicLayer[iVar1] =
DAT_TileMapState::instance.LogicLayer[iVar1] &0xfffffbffU | 0x10000000;
} while (buildingSizeTileIndex < DAT_TileMapState::instance.constructionTileCount);
}
pBVar2 = pBVar2 + 0x196;
} while ((int)pBVar2 < 0x1124dc6);
return;
}


}
}
}