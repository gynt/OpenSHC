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


// FUNCTION: STRONGHOLDCRUSADER 0x0040EBF0
void BuildingsState::growHops(int buildingID)

{
byte bVar1;
int iVar2;
int *piVar3;
int iVar4;
int iVar5;
int iVar6;
int local_4;

iVar6 = 0;
iVar5 = 0;
iVar4 = 0;
piVar3 = &this->buildings[buildingID].tileRef2;
local_4 = 6;
do {
iVar2 = piVar3[-1];
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ('\x01' < (char)bVar1) {
if ((char)bVar1 < 'U') {
if (((char)bVar1 < 'P') && ('\x1f' < (char)bVar1)) {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ('\r' < (char)bVar1) {
if ((char)bVar1 < '\x1c') {
iVar5 = iVar5 + 1;
}
else if ('P' < (char)bVar1) {
iVar4 = iVar4 + 1;
}
}
iVar2 = *piVar3;
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ('\x01' < (char)bVar1) {
if ((char)bVar1 < 'U') {
if (((char)bVar1 < 'P') && ('\x1f' < (char)bVar1)) {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ('\r' < (char)bVar1) {
if ((char)bVar1 < '\x1c') {
iVar5 = iVar5 + 1;
}
else if ('P' < (char)bVar1) {
iVar4 = iVar4 + 1;
}
}
iVar2 = piVar3[1];
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ('\x01' < (char)bVar1) {
if ((char)bVar1 < 'U') {
if (((char)bVar1 < 'P') && ('\x1f' < (char)bVar1)) {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ('\r' < (char)bVar1) {
if ((char)bVar1 < '\x1c') {
iVar5 = iVar5 + 1;
}
else if ('P' < (char)bVar1) {
iVar4 = iVar4 + 1;
}
}
iVar2 = piVar3[2];
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ('\x01' < (char)bVar1) {
if ((char)bVar1 < 'U') {
if (((char)bVar1 < 'P') && ('\x1f' < (char)bVar1)) {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = bVar1 + 1;
}
}
else {
DAT_TileMapState::instance.DamageLayer[iVar2] = 0;
}
}
bVar1 = DAT_TileMapState::instance.DamageLayer[iVar2];
if ((char)bVar1 < '\x02') {
iVar6 = iVar6 + 1;
}
else if ('\r' < (char)bVar1) {
if ((char)bVar1 < '\x1c') {
iVar5 = iVar5 + 1;
}
else if ('P' < (char)bVar1) {
iVar4 = iVar4 + 1;
}
}
piVar3 = piVar3 + 4;
local_4 = local_4 + -1;
} while (local_4 != 0);
if (5 < iVar5) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 5;
return;
}
if ((iVar5 != 0) && (iVar4 != 0)) {
*(undefined2 *)&this->buildings[buildingID].wheatGrowStateRelated = 5;
return;
}
*(ushort *)&this->buildings[buildingID].wheatGrowStateRelated = (iVar6 != 0) + 2;
return;
}


}
}
}