#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BCA0
void BuildingsState::addResourceToArmory(ResourceType resourceType,int playerID,int amount)

{
int iVar1;
uint uVar2;
int *piVar3;
uint uVar4;

iVar1 = this->maxBuildingsCount;
uVar4 = 1;
if (1 < this->maxBuildingsCount) {
do {
uVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(uVar4, (undefined4)((int)(resourceType)), playerID, amount);
if (uVar2 != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, this)(uVar4, this->buildings[uVar4].uid, resourceType, 
amount, (int)((int)(50)), 1);
return;
}
uVar4 = uVar4 + 1;
} while ((int)uVar4 < iVar1);
}
uVar4 = 1;
if (1 < iVar1) {
piVar3 = &this->buildings[1].uid;
do {
uVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(uVar4, (undefined4)((int)(resourceType)), playerID, 1);
while (uVar2 != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile, this)(uVar4, (int)((int)(*piVar3)), resourceType, 1, 0x32, 1);
amount = amount + -1;
if (amount == 0) {
return;
}
uVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getArmoryIDIfSpaceLeft, this)(uVar4, (undefined4)((int)(resourceType)), playerID, 1);
}
uVar4 = uVar4 + 1;
piVar3 = piVar3 + 0xcb;
} while ((int)uVar4 < this->maxBuildingsCount);
}
return;
}


}
}
}