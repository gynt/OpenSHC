#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004109F0
void BuildingsState::extinguishBuildingFire(int buildingID)

{
BuildingTypeShort BVar1;
int iVar2;
uint buildingWidthOrHeight;
int iVar3;
int iVar4;
int try;

iVar4 = 0;
if (this->buildings[buildingID].fireDuration != 0) {
iVar2 = (int)(short)this->buildings[buildingID].y;
buildingWidthOrHeight = this->buildings[buildingID].widthOrHeight;
iVar3 = (int)(short)this->buildings[buildingID].x;
this->buildings[buildingID].fireDuration = 0;
this->buildings[buildingID].cooldownTimer = 2000;
BVar1 = this->buildings[buildingID].buildingType;
if (BVar1 == OpenSHC::Map::Buildings::BT_WHEATFARM) {
buildingWidthOrHeight = 9;
}
else if (BVar1 == OpenSHC::Map::Buildings::BT_HOPFARM) {
buildingWidthOrHeight = 9;
}
else if (BVar1 == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
buildingWidthOrHeight = 10;
}
else if (BVar1 == OpenSHC::Map::Buildings::BT_APPLEFARM) {
buildingWidthOrHeight = 0xb;
}
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(iVar4, (int)((int)(buildingWidthOrHeight)));
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::updateAllFireEntitiesAtTile, DAT_EntityState::ptr)(
DAT_ViewportRenderState::instance.translationMatrix[iVar2 + DAT_TileMapState::instance.buildingY].
addXgetTile + DAT_TileMapState::instance.buildingX + iVar3);
iVar4 = iVar4 + 1;
} while (iVar4 < DAT_TileMapState::instance.constructionTileCount);
iVar4 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[buildingWidthOrHeight];
try = 0;
if (0 < iVar4) {
do {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset, this)(buildingWidthOrHeight, 1, try, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::updateAllFireEntitiesAtTile, DAT_EntityState::ptr)(
DAT_ViewportRenderState::instance.translationMatrix
[this->DAT_TempYOffset + iVar2].addXgetTile + iVar3 +
this->DAT_TempXOffset);
try = try + 1;
} while (try < iVar4);
}
}
return;
}


}
}
}