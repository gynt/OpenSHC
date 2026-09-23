#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040D120
void BuildingsState::setupBarracksCampgroundPositions(int buildingID)

{
BuildingTypeShort BVar1;
ushort uVar2;
ushort uVar3;
int iVar4;
short *psVar5;
short *psVar6;
Building * pBVar7;
short *psVar7;
int iVar8;
int iVar9;
int local_1c;
int local_18;
int local_14;
int *local_10;
short *local_c;
int *local_4;

local_1c = 0;
local_18 = 0;
local_14 = 0;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(1728, '\0', (void *)((int)(
DAT_GameState::instance.playerDataArray[buildingID].barracksParadegroundLocations)));
iVar8 = DAT_GameState::instance.playerDataArray[buildingID].barracks.id;
DAT_GameState::instance.playerDataArray[buildingID].barracksParadegroundLocationsTotal = 0;
if ((0 < iVar8) && (iVar8 = 1, 1 < this->maxBuildingsCount)) {
pBVar7 = &this->buildings[1];
do {
iVar9 = local_1c;
iVar4 = local_18;
if ((((((pBVar7->logicalState != ((BuildingLogicalState)0)) && (pBVar7->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(pBVar7->owner == buildingID)) &&
(((BVar1 = pBVar7->buildingType, BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND2 ||
(BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND3)) || (BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND4)))) &&
((this->buildings[(short)pBVar7->quarryStockpileID].buildingType ==
OpenSHC::Map::Buildings::BT_BARRACKS && (iVar9 = iVar8, BVar1 != OpenSHC::Map::Buildings::BT_PARADEGROUND2)))) &&
((iVar9 = local_1c, iVar4 = iVar8, BVar1 != OpenSHC::Map::Buildings::BT_PARADEGROUND3 &&
(iVar4 = local_18, BVar1 == OpenSHC::Map::Buildings::BT_PARADEGROUND4)))) {
local_14 = iVar8;
}
local_18 = iVar4;
local_1c = iVar9;
iVar8 = iVar8 + 1;
pBVar7 = pBVar7 + 0x196;
} while (iVar8 < this->maxBuildingsCount);
if (((local_1c != 0) && (local_18 != 0)) && (local_14 != 0)) {
local_c = &DAT_GameState::instance.playerDataArray[buildingID].barracksParadegroundLocations[0][24].y;
DAT_GameState::instance.playerDataArray[buildingID].barracksParadegroundLocationsTotal = 72;
local_10 = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[0] + 1;
local_4 = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_1;
buildingID = iVar8;
do {
iVar8 = (*(int (*) [3])(local_10 + -1))[0];
iVar9 = local_1c;
if (((iVar8 == 0) || (iVar9 = local_18, iVar8 == 1)) || (iVar9 = local_14, iVar8 == 2)) {
buildingID = iVar9;
}
uVar2 = this->buildings[buildingID].x;
uVar3 = this->buildings[buildingID].y;
psVar7 = local_c + -48;
psVar6 = &DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[*local_4][0].y;
iVar8 = 0x18;
psVar5 = psVar6;
do {
psVar7[-1] = ((XYPairShort *)(psVar5 + -1))->x + uVar2;
*psVar7 = *psVar5 + uVar3;
psVar5 = psVar5 + 2;
psVar7 = psVar7 + 2;
iVar8 = iVar8 + -1;
} while (iVar8 != 0);
iVar8 = *local_10;
if (iVar8 == 0) {
buildingID = local_1c;
}
else if (iVar8 == 1) {
buildingID = local_18;
}
else if (iVar8 == 2) {
buildingID = local_14;
}
uVar2 = this->buildings[buildingID].x;
uVar3 = this->buildings[buildingID].y;
iVar8 = 0x18;
psVar5 = psVar6;
psVar7 = local_c;
do {
((XYPairShort *)(psVar7 + -1))->x = ((XYPairShort *)(psVar5 + -1))->x + uVar2;
*psVar7 = *psVar5 + uVar3;
psVar5 = psVar5 + 2;
psVar7 = psVar7 + 2;
iVar8 = iVar8 + -1;
} while (iVar8 != 0);
iVar8 = local_10[1];
if (iVar8 == 0) {
buildingID = local_1c;
}
else if (iVar8 == 1) {
buildingID = local_18;
}
else if (iVar8 == 2) {
buildingID = local_14;
}
/* 
  0x32c = 812, which is the size of Building
 */

uVar2 = this->buildings[buildingID].x;
uVar3 = this->buildings[buildingID].y;
psVar5 = local_c + 0x30;
iVar8 = 0x18;
do {
psVar5[-1] = ((XYPairShort *)(psVar6 + -1))->x + uVar2;
*psVar5 = *psVar6 + uVar3;
psVar6 = psVar6 + 2;
psVar5 = psVar5 + 2;
iVar8 = iVar8 + -1;
} while (iVar8 != 0);
local_10 = local_10 + 3;
local_c = local_c + 0x90;
local_4 = local_4 + 1;
} while ((int)local_4 < 0x5c1680);
}
}
return;
}


}
}
}