#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419FA0
int BuildingsState::findClosestEnemyBuildingWithinRadius(int param_1,int param_2,int param_3,int param_4)

{
int iVar1;
int iVar2;
int iVar3;
int (*paiVar4) [2000];
int iVar5;
int local_c;
int local_8;

iVar2 = param_1 * 8000;
paiVar4 = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID + param_1;
param_1 = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1];
local_8 = 0;
local_c = 1000000;
iVar1 = 0;
if (0 < param_1) {
iVar2 = (iVar2 + 0x1183470) - (int)paiVar4;
do {
iVar1 = *(int *)(iVar2 + (int)paiVar4);
if (((this->buildings[iVar1].uid == (*paiVar4)[0]) &&
(iVar5 = param_2 - (short)this->buildings[iVar1].x,
iVar3 = param_3 - (short)this->buildings[iVar1].y,
iVar3 = iVar3 * iVar3 + iVar5 * iVar5, iVar3 <= param_4 * param_4)) && (iVar3 < local_c))
{
local_c = iVar3;
local_8 = iVar1;
}
paiVar4 = (int (*) [2000])(*paiVar4 + 1);
param_1 = param_1 + -1;
iVar1 = local_8;
} while (param_1 != 0);
}
return iVar1;
}


}
}
}