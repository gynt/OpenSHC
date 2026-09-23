#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040C300
void BuildingsState::countPlayerResources(int playerID)

{
BuildingTypeShort BVar1;
int iVar2;
int iVar3;
int *piVar4;
int *piVar5;
BuildingTypeShort *pBVar6;
int *piVar7;
int local_c;

iVar2 = DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf];
/* 
  Set calculated resources to 0
 */

iVar3 = 0;
do {
if (iVar3 != 0xf) {
DAT_GameState::instance.playerDataArray[playerID].currentResources[iVar3] = 0;
}
iVar3 = iVar3 + 1;
} while (iVar3 < 0x19);
local_c = 1;
if (this->maxBuildingsCount < 2) {
DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] = iVar2;
return;
}
pBVar6 = &this->buildings[1].buildingType;
piVar7 = this->buildings[1].resources + 0xb;
do {
if ((pBVar6[-1] == OpenSHC::Map::Buildings::BLS_NORMAL) && ((short)pBVar6[2] == playerID)) {
BVar1 = *pBVar6;
if (BVar1 == OpenSHC::Map::Buildings::BT_STOCKPILE) {
piVar4 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 3;
piVar5 = (int *)(pBVar6 + 0x2d);
iVar3 = 3;
do {
piVar4[-1] = piVar4[-1] + piVar5[-1];
*piVar4 = *piVar4 + *piVar5;
piVar4[1] = piVar4[1] + piVar5[1];
piVar4[2] = piVar4[2] + piVar5[2];
piVar4[3] = piVar4[3] + piVar5[3];
piVar5 = piVar5 + 5;
piVar4 = piVar4 + 5;
iVar3 = iVar3 + -1;
} while (iVar3 != 0);
}
else if (BVar1 == OpenSHC::Map::Buildings::BT_GRANARY) {
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 10;
*piVar5 = *piVar5 + piVar7[-1];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xb;
*piVar5 = *piVar5 + *piVar7;
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xc;
*piVar5 = *piVar5 + piVar7[1];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xd;
*piVar5 = *piVar5 + piVar7[2];
}
else if (BVar1 == OpenSHC::Map::Buildings::BT_ARMORY) {
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x11;
*piVar5 = *piVar5 + piVar7[6];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x12;
*piVar5 = *piVar5 + piVar7[7];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x13;
*piVar5 = *piVar5 + piVar7[8];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x14;
*piVar5 = *piVar5 + piVar7[9];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x15;
*piVar5 = *piVar5 + piVar7[10];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x16;
*piVar5 = *piVar5 + piVar7[0xb];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x17;
*piVar5 = *piVar5 + piVar7[0xc];
piVar5 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0x18;
*piVar5 = *piVar5 + piVar7[0xd];
}
}
local_c = local_c + 1;
pBVar6 = pBVar6 + 0x196;
piVar7 = piVar7 + 0xcb;
} while (local_c < this->maxBuildingsCount);
DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] = iVar2;
return;
}


}
}
}