#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00419EB0
int BuildingsState::aiFindBuildingToAttack(int param_1,int param_2,int param_3,int param_4)

{
int buildingID;
int iVar1;
int iVar2;
int iVar3;
int (*paiVar4) [2000];
int local_c;
int local_8;

iVar1 = param_1 * 8000;
paiVar4 = DAT_GameState::instance.mapAndTime.playerEnemyBuildingUID + param_1;
param_1 = DAT_GameState::instance.mapAndTime.playerBuildingInfoIndex[param_1];
local_8 = 0;
local_c = 1000000;
if (0 < param_1) {
iVar1 = (iVar1 + 0x1183470) - (int)paiVar4;
do {
buildingID = *(int *)((int)paiVar4 + iVar1);
if ((this->buildings[buildingID].uid == (*paiVar4)[0]) &&
(this->buildings[buildingID].fireDuration == 0)) {
iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID);
if ((iVar2 != 0) &&
(((iVar2 != 4 &&
(iVar3 = param_2 - (short)this->buildings[buildingID].x,
iVar2 = param_3 - (short)this->buildings[buildingID].y,
iVar2 = iVar2 * iVar2 + iVar3 * iVar3, iVar2 <= param_4 * param_4)) &&
(iVar2 < local_c)))) {
local_c = iVar2;
local_8 = buildingID;
}
}
paiVar4 = (int (*) [2000])(*paiVar4 + 1);
param_1 = param_1 + -1;
} while (param_1 != 0);
return local_8;
}
return 0;
}


}
}
}