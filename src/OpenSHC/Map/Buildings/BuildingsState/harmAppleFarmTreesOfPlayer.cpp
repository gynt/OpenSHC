#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F090
void BuildingsState::harmAppleFarmTreesOfPlayer(int param_1)

{
ushort uVar1;
int *piVar2;
short *psVar3;
int iVar4;

iVar4 = 0;
if (0 < this->maxBuildingsCount) {
psVar3 = &this->buildings[0].owner;
piVar2 = &this->buildings[0].tileRef2;
do {
if (((psVar3[-3] != ((BuildingLogicalState)0)) && (*psVar3 == param_1)) && (psVar3[-2] == OpenSHC::Map::Buildings::BT_APPLEFARM)) {
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[-1]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[*piVar2];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[1]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[2]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[3]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[4]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[5]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
uVar1 = DAT_TileMapState::instance.OrganismLayer[piVar2[6]];
DAT_LandscapeState::instance.trees[(short)uVar1].stage = 4;
DAT_LandscapeState::instance.trees[(short)uVar1].stageTracker = -0x4b0;
}
iVar4 = iVar4 + 1;
psVar3 = psVar3 + 0x196;
piVar2 = piVar2 + 0xcb;
} while (iVar4 < this->maxBuildingsCount);
}
return;
}


}
}
}