#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F8A0
void BuildingsState::applySnoozedStateBasedOnPlayerData()

{
Building * pBVar1;
int iVar1;
int iVar2;
int *piVar3;
short *psVar4;
bool _isBuildingTypeSnoozed;

iVar2 = 1;
if (1 < this->maxBuildingsCount) {
pBVar1 = &this->buildings[1];
do {
if (pBVar1->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) {
if ((short)pBVar1->buildingType < 91) {
/* 
  *(char*)(PlayerDataArray[building.ownerPlayerIndex].buildingSnoozedState +
   buildingType)
 */

_isBuildingTypeSnoozed =
*(bool *)(pBVar1->owner * 0x39f4 + 0x115df8c +
(int)(short)pBVar1->buildingType);
if (pBVar1->sleeping != _isBuildingTypeSnoozed) {
/* 
  if it was not snoozed, set it to snoozed
 */

pBVar1->sleeping = _isBuildingTypeSnoozed;
/* 
  currentemployeecount
 */

pBVar1->currentEmployeeCount = 0;
pBVar1->animationIndex = 0;
pBVar1->renderAnimation = 0;
/* 
  fixme: set resources to 0?
 */

*(undefined4 *)&pBVar1->state = 0;
*(undefined4 *)&pBVar1->killingPitField = 0;
pBVar1->resources[0] = 0;
pBVar1->resources[1] = 0;
pBVar1->resources[2] = 0;
pBVar1->resources[3] = 0;
pBVar1->resources[4] = 0;
pBVar1->resources[5] = 0;
pBVar1->resources[6] = 0;
pBVar1->resources[7] = 0;
pBVar1->resources[8] = 0;
pBVar1->resources[9] = 0;
pBVar1->resources[10] = 0;
pBVar1->resources[0xb] = 0;
pBVar1->resources[0xc] = 0;
pBVar1->resources[0xd] = 0;
pBVar1->resources[0xe] = 0;
pBVar1->resources[0xf] = 0;
pBVar1->resources[0x10] = 0;
pBVar1->resources[0x11] = 0;
pBVar1->resources[0x12] = 0;
pBVar1->resources[0x13] = 0;
pBVar1->resources[0x14] = 0;
pBVar1->resources[0x15] = 0;
pBVar1->resources[0x16] = 0;
pBVar1->resources[0x17] = 0;
pBVar1->resources[0x18] = 0;
psVar4 = pBVar1->workerID;
piVar3 = pBVar1->workerUID;
iVar1 = 4;
do {
*piVar3 = 0;
*psVar4 = 0;
piVar3 = piVar3 + 1;
psVar4 = psVar4 + 1;
iVar1 = iVar1 + -1;
} while (iVar1 != 0);
}
}
else {
pBVar1->sleeping = false;
}
}
iVar2 = iVar2 + 1;
pBVar1 = pBVar1 + 0x196;
} while (iVar2 < this->maxBuildingsCount);
}
return;
}


}
}
}