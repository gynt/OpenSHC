#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419AC0
void BuildingsState::rebuildTileLogicLayerForGatesAndWalls()

{
byte bVar1;
short sVar2;
int iVar3;
int iVar4;
int buildingSizeTileIndex;

iVar4 = 0x32c;
do {
if ((*(short *)((int)this->buildings[0].resources + iVar4 + -0x50) != 0) &&
(((sVar2 = *(short *)((int)this->buildings[0].resources + iVar4 + -0x4e),
sVar2 == 0x2d || (sVar2 == 0x2e)) || (sVar2 == 0x2f)))) {
buildingSizeTileIndex = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(buildingSizeTileIndex, 
*(int *)((int)this->buildings[0].resources + iVar4 + -0x28));
iVar3 = DAT_ViewportRenderState::instance.translationMatrix
[*(short *)((int)this->buildings[0].resources + iVar4 + -0x30) +
DAT_TileMapState::instance.buildingY].addXgetTile +
(int)*(short *)((int)this->buildings[0].resources + iVar4 + -0x32) +
DAT_TileMapState::instance.buildingX;
if (*(short *)((int)this->buildings[0].resources + iVar4 + -0x4e) == 0x2f) {
bVar1 = *(byte *)((int)this->buildings[0].resources + iVar4 + -0x34);
DAT_TileMapState::instance.LogicLayer[iVar3] =
DAT_TileMapState::instance.LogicLayer[iVar3] &0xfffefeffU | 0x10000000;
DAT_TileMapState::instance.MiscDisplayLayer[iVar3] =
DAT_TileMapState::instance.MiscDisplayLayer[iVar3] &0xffdf;
DAT_TileMapState::instance.HeightLayer[iVar3] = bVar1;
}
else {
DAT_TileMapState::instance.LogicLayer[iVar3] = DAT_TileMapState::instance.LogicLayer[iVar3] | 0x100;
DAT_TileMapState::instance.WallOwnerLayer[iVar3] =
*(char *)((int)this->buildings[0].resources + iVar4 + -0x4a) - 1U |
DAT_TileMapState::instance.WallOwnerLayer[iVar3] &0xf8;
}
DAT_TileMapState::instance.LogicLayer[iVar3] = DAT_TileMapState::instance.LogicLayer[iVar3] &0xfffffbff;
buildingSizeTileIndex = buildingSizeTileIndex + 1;
} while (buildingSizeTileIndex < DAT_TileMapState::instance.constructionTileCount);
}
iVar4 = iVar4 + 0x32c;
} while (iVar4 < 0x18c7c0);
return;
}


}
}
}