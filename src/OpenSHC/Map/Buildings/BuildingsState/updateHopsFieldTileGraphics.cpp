#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040EDF0
void BuildingsState::updateHopsFieldTileGraphics(int buildingID)

{
byte bVar1;
int iVar2;
uint uVar3;
int iVar4;
int iVar5;
int local_8;

iVar4 = 0;
local_8 = 3;
if (this->field14_0x18e024 == 0) {
iVar4 = (int)*(short *)&this->buildings[buildingID].field_0x2fc;
}
iVar5 = 0;
do {
iVar2 = *(int *)(this->buildings[buildingID].workers +
((iVar5 + iVar4) % 0x18) * 2 + 8);
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if (bVar1 == 0) {
uVar3 = 0;
}
else if ((char)bVar1 < '\x02') {
uVar3 = 0;
}
else if ((char)bVar1 < '\x04') {
uVar3 = 1;
}
else if ((char)bVar1 < '\x06') {
uVar3 = 2;
}
else if ((char)bVar1 < '\b') {
uVar3 = 3;
}
else if ((char)bVar1 < '\n') {
uVar3 = 4;
}
else if ((char)bVar1 < '\f') {
uVar3 = 5;
}
else if ((char)bVar1 < '\x0e') {
uVar3 = 6;
}
else if ((char)bVar1 < '\x1c') {
uVar3 = 7;
}
else {
uVar3 = ('\x1f' < (char)bVar1) - 1 &8;
}
uVar3 = GMTotalPicturesProcessed::instance[0xe] + ((byte)DAT_TileMapState::instance.RandomLayer[iVar2] &1) * 9 +
0x25 + uVar3;
if (uVar3 == DAT_TileMapState::instance.GfxLayer[iVar2]) {
local_8 = local_8 + -1;
if (local_8 != 0) goto LAB_0040eef3;
}
else {
DAT_TileMapState::instance.GfxLayer[iVar2] = (ushort)uVar3;
LAB_0040eef3:
if (this->field14_0x18e024 == 0) {
*(short *)&this->buildings[buildingID].field_0x2fc =
(short)((iVar5 + 1 + iVar4) % 0x24);
return;
}
}
iVar5 = iVar5 + 1;
if (0x17 < iVar5) {
return;
}
} while( true );
}


}
}
}