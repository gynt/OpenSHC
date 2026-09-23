#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
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


// FUNCTION: STRONGHOLDCRUSADER 0x0040EA00
undefined4 BuildingsState::setNewOnFarmDestination(int buildingID)

{
byte bVar1;
ushort uVar2;
short sVar3;
short sVar4;
int tile;
Building *pBVar5;
int iVar6;
uint uVar7;
int iVar8;
uint uVar9;
uint uVar10;
int iVar11;
int iVar12;
int local_8;

iVar6 = buildingID;
uVar9 = (uint)this->buildings[buildingID].buildingEntryX;
uVar7 = (uint)this->buildings[buildingID].buildingEntryY;
if (((uVar9 < 400) && (uVar7 < 400)) && (*(char *)(uVar7 * 400 + 0x21aec98 + uVar9) != '\0')) {
uVar2 = DAT_TileMapState::instance.PathConnectionLayer
[DAT_ViewportRenderState::instance.translationMatrix[uVar7].addXgetTile + uVar9];
pBVar5 = this->buildings + buildingID;
buildingID = buildingID * 0x32c + 0xf986fc;
local_8 = 0;
iVar12 = (uint)(*(short *)&pBVar5->field_0x26e == 0x51) * 2 + 2;
do {
tile = *(int *)buildingID;
sVar3 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
bVar1 = DAT_TileMapState::instance.DamageLayer[tile];
this->farmerDestinationTile = tile;
uVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(tile);
sVar4 = *(short *)&this->buildings[iVar6].wheatGrowStateRelated;
if (sVar4 == 5) {
if ((int)(char)bVar1 - 0xeU < 0xe) {
iVar11 = 0;
do {
this->hopFarmerDestinationOffsetX =
DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar12].int.xOffset;
this->hopFarmerDestinationOffsetY =
*(int *)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix +
iVar12 * 8 + 4);
iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][iVar12] + tile;
if ((DAT_TileMapState::instance.PathConnectionLayer[iVar8] == uVar2) &&
(uVar9 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(iVar8),
uVar10 = (int)(uVar9 - uVar7) >> 0x1f,
(int)((uVar9 - uVar7 ^ uVar10) - uVar10) < 0x10)) {
return(undefined4)( 1);
}
iVar12 = iVar12 + 2;
if (7 < iVar12) {
iVar12 = 0;
}
iVar11 = iVar11 + 1;
} while (iVar11 < 4);
}
}
else {
if (sVar4 != 3) {
return(undefined4)( 0);
}
if ((uint)(int)(char)bVar1 < 2) {
iVar11 = 0;
do {
this->hopFarmerDestinationOffsetX =
DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[iVar12].int.xOffset;
this->hopFarmerDestinationOffsetY =
*(int *)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix +
iVar12 * 8 + 4);
iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][iVar12] + tile;
if ((DAT_TileMapState::instance.PathConnectionLayer[iVar8] == uVar2) &&
(uVar9 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(iVar8),
uVar10 = (int)(uVar9 - uVar7) >> 0x1f,
(int)((uVar9 - uVar7 ^ uVar10) - uVar10) < 0x10)) {
return(undefined4)( 1);
}
iVar12 = iVar12 + 2;
if (7 < iVar12) {
iVar12 = 0;
}
iVar11 = iVar11 + 1;
} while (iVar11 < 4);
}
}
buildingID = buildingID + 4;
local_8 = local_8 + 1;
if (0x17 < local_8) {
return(undefined4)( 0);
}
} while( true );
}
return(undefined4)( 0);
}


}
}
}