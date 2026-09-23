#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"



#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00422C60
void BuildingsState::spreadFireRandomlyToBuildings(int param_1,int param_2)

{
int iVar1;
int iVar2;
int iVar3;
BuildingLogicalStateShort *pBVar4;
int iVar5;
int iVar6;
int iVar7;
int local_4;

iVar3 = this->maxBuildingsCount;
iVar7 = 1;
iVar5 = 0;
if (((0 < param_2) && (0 < DAT_GameState::instance.playerDataArray[param_1].campground.id)) &&
(1 < this->maxBuildingsCount)) {
pBVar4 = &this->buildings[1].logicalState;
do {
if (((*pBVar4 != ((BuildingLogicalState)0)) && (*pBVar4 != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(((short)pBVar4[3] == param_1 && ((pBVar4[0xf7] == 0 && (pBVar4[0xfa] == 0)))))) {
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(iVar7);
if ((iVar1 != 0) && (iVar1 != 4)) {
iVar5 = iVar5 + 1;
}
if (iVar1 == 5) {
iVar5 = iVar5 + 4;
}
}
iVar7 = iVar7 + 1;
pBVar4 = pBVar4 + 0x196;
} while (iVar7 < iVar3);
if (iVar5 != 0) {
while ((0 < param_2 && (0 < iVar5))) {
iVar7 = (int)SEC_RNG::instance.currentNumber2;
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
iVar3 = this->maxBuildingsCount;
iVar1 = 1;
local_4 = iVar5;
if (1 < this->maxBuildingsCount) {
pBVar4 = &this->buildings[1].logicalState;
iVar7 = iVar7 % iVar5;
do {
iVar6 = iVar7;
if (((((*pBVar4 != ((BuildingLogicalState)0)) && (*pBVar4 != OpenSHC::Map::Buildings::BLS_REMOVE)) && ((short)pBVar4[3] == param_1)) &&
((pBVar4[0xf7] == 0 && (pBVar4[0xfa] == 0)))) &&
((iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(iVar1), iVar2 != 0 &&
(iVar2 != 4)))) {
iVar6 = iVar7 + -1;
iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(iVar1);
if (iVar2 == 5) {
iVar6 = iVar7 + -5;
}
if (iVar6 < 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::lightUpBuilding, this)(iVar1, 0, 0);
MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)((int)(short)this->buildings[iVar1].x, (int)((int)(
(short)this->buildings[iVar1].y)));
iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(2000);
local_4 = iVar5 + -1;
if (iVar3 == 5) {
local_4 = iVar5 + -5;
}
break;
}
}
iVar1 = iVar1 + 1;
pBVar4 = pBVar4 + 0x196;
iVar7 = iVar6;
} while (iVar1 < iVar3);
}
param_2 = param_2 + -1;
iVar5 = local_4;
}
}
}
return;
}


}
}
}