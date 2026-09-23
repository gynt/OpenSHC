#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Game::Resources::ResourceType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A8A0
int BuildingsState::chooseProductionItemType(int playerID,BuildingType buildingType)

{
int iVar1;
ResourceTypeShort *pRVar2;
int iVar3;
int iVar4;
bool bVar5;

iVar4 = 0;
iVar3 = 0;
if (1 < this->maxBuildingsCount) {
pRVar2 = &this->buildings[1].producedItemTypeNext;
iVar1 = this->maxBuildingsCount + -1;
do {
if (((pRVar2[-0xdf] == OpenSHC::Map::Buildings::BLS_NORMAL) && ((short)pRVar2[-0xdc] == playerID)) &&
((int)(short)pRVar2[-0xde] == buildingType)) {
if (buildingType == OpenSHC::Map::Buildings::BT_BLACKSMITH) {
bVar5 = *pRVar2 == OpenSHC::Game::Resources::RT_SWORD;
}
else if (buildingType == OpenSHC::Map::Buildings::BT_POLETURNER) {
bVar5 = *pRVar2 == OpenSHC::Game::Resources::RT_SPEAR;
}
else {
if (buildingType != OpenSHC::Map::Buildings::BT_FLETCHER) goto LAB_0040a90a;
bVar5 = *pRVar2 == OpenSHC::Game::Resources::RT_BOW;
}
if (bVar5) {
iVar4 = iVar4 + 1;
}
else {
iVar3 = iVar3 + 1;
}
}
LAB_0040a90a:
pRVar2 = pRVar2 + 0x196;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
}
iVar1 = 0;
if (buildingType == OpenSHC::Map::Buildings::BT_BLACKSMITH) {
return (iVar4 <= iVar3) + 0x15;
}
if (buildingType != OpenSHC::Map::Buildings::BT_POLETURNER) {
if (buildingType == OpenSHC::Map::Buildings::BT_FLETCHER) {
iVar1 = (iVar3 < iVar4) + 0x11;
}
return iVar1;
}
return (iVar3 < iVar4) + 0x13;
}


}
}
}