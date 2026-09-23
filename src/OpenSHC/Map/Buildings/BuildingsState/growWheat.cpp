#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



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


// FUNCTION: STRONGHOLDCRUSADER 0x0040CC30
void BuildingsState::growWheat(int buildingID)

{
byte bVar1;
int iVar2;
int *piVar3;
int iVar4;
int iVar5;
int iVar6;
int iVar7;
int local_10;
int local_c;
int local_8;
int local_4;

iVar6 = 0;
iVar7 = 0;
iVar4 = 0;
iVar5 = 0;
local_10 = 0;
local_c = 0;
local_8 = 0;
piVar3 = &this->buildings[buildingID].tileRef2;
local_4 = 9;
do {
iVar2 = piVar3[-1];
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if (('\x01' < (char)bVar1) && ((char)bVar1 < 'g')) {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x01') {
local_10 = local_10 + 1;
}
else if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ((('\x04' < (char)bVar1) && ('\a' < (char)bVar1)) && ('\n' < (char)bVar1)) {
if ((char)bVar1 < 'e') {
iVar7 = iVar7 + 1;
}
else if ('e' < (char)bVar1) {
if ((char)bVar1 < 'g') {
local_c = local_c + 1;
}
else if ((char)bVar1 < 'x') {
local_8 = local_8 + 1;
}
else if (bVar1 == 0x78) {
iVar4 = iVar4 + 1;
}
else if (bVar1 == 0x79) {
iVar5 = iVar5 + 1;
}
}
}
iVar2 = *piVar3;
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if (('\x01' < (char)bVar1) && ((char)bVar1 < 'g')) {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x01') {
local_10 = local_10 + 1;
}
else if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ((('\x04' < (char)bVar1) && ('\a' < (char)bVar1)) && ('\n' < (char)bVar1)) {
if ((char)bVar1 < 'e') {
iVar7 = iVar7 + 1;
}
else if ('e' < (char)bVar1) {
if ((char)bVar1 < 'g') {
local_c = local_c + 1;
}
else if ((char)bVar1 < 'x') {
local_8 = local_8 + 1;
}
else if (bVar1 == 0x78) {
iVar4 = iVar4 + 1;
}
else if (bVar1 == 0x79) {
iVar5 = iVar5 + 1;
}
}
}
iVar2 = piVar3[1];
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if (('\x01' < (char)bVar1) && ((char)bVar1 < 'g')) {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x01') {
local_10 = local_10 + 1;
}
else if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ((('\x04' < (char)bVar1) && ('\a' < (char)bVar1)) && ('\n' < (char)bVar1)) {
if ((char)bVar1 < 'e') {
iVar7 = iVar7 + 1;
}
else if ('e' < (char)bVar1) {
if ((char)bVar1 < 'g') {
local_c = local_c + 1;
}
else if ((char)bVar1 < 'x') {
local_8 = local_8 + 1;
}
else if (bVar1 == 0x78) {
iVar4 = iVar4 + 1;
}
else if (bVar1 == 0x79) {
iVar5 = iVar5 + 1;
}
}
}
iVar2 = piVar3[2];
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if (('\x01' < (char)bVar1) && ((char)bVar1 < 'g')) {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x01') {
local_10 = local_10 + 1;
}
else if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ((('\x04' < (char)bVar1) && ('\a' < (char)bVar1)) && ('\n' < (char)bVar1)) {
if ((char)bVar1 < 'e') {
iVar7 = iVar7 + 1;
}
else if ('e' < (char)bVar1) {
if ((char)bVar1 < 'g') {
local_c = local_c + 1;
}
else if ((char)bVar1 < 'x') {
local_8 = local_8 + 1;
}
else if (bVar1 == 0x78) {
iVar4 = iVar4 + 1;
}
else if (bVar1 == 0x79) {
iVar5 = iVar5 + 1;
}
}
}
piVar3 = piVar3 + 4;
local_4 = local_4 + -1;
} while (local_4 != 0);
if (3 < iVar5) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 8;
return;
}
if ((0xb < iVar7) || ((iVar7 != 0 && (iVar4 != 0)))) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 6;
return;
}
if (iVar5 != 0) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 8;
return;
}
if (local_10 == 0) {
if (iVar4 != 0) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 3;
return;
}
if (local_c != 0) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 3;
return;
}
if (local_8 == 0) {
*(ushort *)&this->buildings[buildingID].wheatGrowStateRelated =
(-(ushort)(iVar6 != 0) &3) + 2;
return;
}
}
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 3;
return;
}


}
}
}