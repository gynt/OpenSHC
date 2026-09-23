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


// FUNCTION: STRONGHOLDCRUSADER 0x0040E330
void BuildingsState::setupTunnelersGuildCampgroundPositions(int param_1)

{
ushort uVar1;
ushort uVar2;
Building * psVar3;
short *psVar4;
int iVar5;
short *psVar6;
int iVar7;

iVar7 = 0;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(100, '\0', (void *)((int)(
DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocations)));
iVar5 = DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.id;
DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocationsTotal = 0;
if ((0 < iVar5) && (iVar5 = 1, 1 < this->maxBuildingsCount)) {
psVar3 = &this->buildings[1];
do {
if ((((psVar3->logicalState != ((BuildingLogicalState)0)) && (psVar3->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) &&
(psVar3->owner == param_1)) && (psVar3->buildingType == OpenSHC::Map::Buildings::BT_PARADEGROUND5)) {
iVar7 = iVar5;
}
iVar5 = iVar5 + 1;
psVar3 = psVar3 + 0x196;
} while (iVar5 < this->maxBuildingsCount);
if (iVar7 != 0) {
DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocationsTotal = 25;
uVar1 = this->buildings[iVar7].x;
uVar2 = this->buildings[iVar7].y;
psVar4 = &DAT_BuildingDefinedData::instance.TunnelersGuildParadegroundLocationOffsets[0].y;
psVar6 = &DAT_GameState::instance.playerDataArray[param_1].tunnelersGuildParadegroundLocations[0].y;
do {
((XYPairShort *)(psVar6 + -1))->x = ((XYPairShort *)(psVar4 + -1))->x + uVar1;
*psVar6 = *psVar4 + uVar2;
psVar4 = psVar4 + 2;
psVar6 = psVar6 + 2;
} while ((int)psVar4 < 0x5c1916);
}
}
return;
}


}
}
}