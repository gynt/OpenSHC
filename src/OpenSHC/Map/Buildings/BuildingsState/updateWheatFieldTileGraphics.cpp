#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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


// FUNCTION: STRONGHOLDCRUSADER 0x0040CF20
void BuildingsState::updateWheatFieldTileGraphics(int buildingID)

{
int iVar1;
uint uVar2;
int iVar3;
uint uVar4;
int iVar5;
int local_8;
byte uVar1;

iVar3 = 0;
uVar4 = 0;
local_8 = 3;
if (this->field14_0x18e024 == 0) {
iVar3 = (int)*(short *)&this->buildings[buildingID].field_0x2fc;
}
iVar5 = 0;
do {
iVar1 = *(int *)(this->buildings[buildingID].workers +
DAT_BuildingDefinedData::instance.WheatFieldTile_Unknown[(iVar5 + iVar3) % 0x24] * 2 + 6);
uVar1 = DAT_TileMapState::instance.DamageLayer[iVar1];
if (uVar1 == 0) {
uVar4 = 0;
LAB_0040d024:
uVar2 = ((byte)DAT_TileMapState::instance.RandomLayer[iVar1] &3) + GMTotalPicturesProcessed::instance[0xe] +
uVar4;
}
else {
if ((char)uVar1 < '\x01') {
uVar4 = 0;
goto LAB_0040d024;
}
if ((char)uVar1 < '\x02') {
uVar4 = 4;
goto LAB_0040d024;
}
if ((char)uVar1 < '\x05') {
uVar4 = 8;
goto LAB_0040d024;
}
if ((char)uVar1 < '\b') {
uVar4 = 0xc;
goto LAB_0040d024;
}
if ((char)uVar1 < '\v') {
uVar4 = 0x10;
goto LAB_0040d024;
}
if ((char)uVar1 < 'e') {
uVar4 = 0x14;
goto LAB_0040d024;
}
if ((char)uVar1 < 'f') {
uVar4 = 0x1c;
goto LAB_0040d024;
}
if ((char)uVar1 < 'g') {
uVar4 = 0x20;
goto LAB_0040d024;
}
if ((char)uVar1 < 'x') {
uVar4 = 0x20;
goto LAB_0040d024;
}
if (uVar1 == 0x78) {
uVar4 = 0x18;
goto LAB_0040d024;
}
if (uVar1 == 0x79) {
uVar4 = 0x24;
}
else if (uVar4 < 0x24) goto LAB_0040d024;
uVar2 = GMTotalPicturesProcessed::instance[0xe] + uVar4;
}
if (uVar2 == DAT_TileMapState::instance.GfxLayer[iVar1]) {
local_8 = local_8 + -1;
if (local_8 != 0) goto LAB_0040d041;
}
else {
DAT_TileMapState::instance.GfxLayer[iVar1] = (ushort)uVar2;
LAB_0040d041:
if (this->field14_0x18e024 == 0) {
*(short *)&this->buildings[buildingID].field_0x2fc =
(short)((iVar5 + 1 + iVar3) % 0x24);
return;
}
}
iVar5 = iVar5 + 1;
if (0x23 < iVar5) {
return;
}
} while( true );
}


}
}
}