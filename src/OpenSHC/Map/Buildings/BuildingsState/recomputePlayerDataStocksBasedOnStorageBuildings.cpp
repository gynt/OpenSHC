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


// FUNCTION: STRONGHOLDCRUSADER 0x0040C4B0
void BuildingsState::recomputePlayerDataStocksBasedOnStorageBuildings()

{
PlayerData * _pPlayerData2;
PlayerData * _pPlayerData;
int *piVar1;
int iVar2;
int iVar3;
Building * pBVar6;
int _playerGoldArray [8];
int *_pPlayerGoldArray;
BuildingTypeShort _buildingType;

_pPlayerData2 = (PlayerData *)DAT_GameState::instance.playerDataArray[1];
_pPlayerGoldArray = _playerGoldArray;
do {
*_pPlayerGoldArray = _pPlayerData2->currentResources[0xf];
_pPlayerData2->currentResources[0] = 0;
_pPlayerData2->currentResources[1] = 0;
_pPlayerData2->currentResources[2] = 0;
_pPlayerData2->currentResources[3] = 0;
_pPlayerData2->currentResources[4] = 0;
_pPlayerData2->currentResources[5] = 0;
_pPlayerData2->currentResources[6] = 0;
_pPlayerData2->currentResources[7] = 0;
_pPlayerData2->currentResources[8] = 0;
_pPlayerData2->currentResources[9] = 0;
_pPlayerData2->currentResources[10] = 0;
_pPlayerData2->currentResources[0xb] = 0;
_pPlayerData2->currentResources[0xc] = 0;
_pPlayerData2->currentResources[0xd] = 0;
_pPlayerData2->currentResources[0xe] = 0;
_pPlayerData2->currentResources[0xf] = 0;
_pPlayerData2->currentResources[0x10] = 0;
_pPlayerData2->currentResources[0x11] = 0;
_pPlayerData2->currentResources[0x12] = 0;
_pPlayerData2->currentResources[0x13] = 0;
_pPlayerData2->currentResources[0x14] = 0;
_pPlayerData2->currentResources[0x15] = 0;
_pPlayerData2->currentResources[0x16] = 0;
_pPlayerData2->currentResources[0x17] = 0;
_pPlayerData2->currentResources[0x18] = 0;
_pPlayerData2 = (PlayerData *)((int)(_pPlayerData2 + 0x94) + 0x24);
_pPlayerGoldArray = _pPlayerGoldArray + 1;
} while ((int)_pPlayerData2 < 0x117cc5c);
iVar2 = 1;
if (1 < this->maxBuildingsCount) {
pBVar6 = &this->buildings[1];
do {
if ((pBVar6->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) &&
(((_buildingType = pBVar6->buildingType, _buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE ||
(_buildingType == OpenSHC::Map::Buildings::BT_GRANARY)) || (_buildingType == OpenSHC::Map::Buildings::BT_ARMORY)))) {
_pPlayerData = (PlayerData *)
(&DAT_GameState::instance.playerDataArray[pBVar6->owner]);
piVar1 = pBVar6->resources + 1;
iVar3 = 5;
do {
_pPlayerData->currentResources[0] =
_pPlayerData->currentResources[0] + piVar1[-1];
_pPlayerData->currentResources[1] = _pPlayerData->currentResources[1] + *piVar1;
_pPlayerData->currentResources[2] =
_pPlayerData->currentResources[2] + piVar1[1];
_pPlayerData->currentResources[3] =
_pPlayerData->currentResources[3] + piVar1[2];
_pPlayerData->currentResources[4] =
_pPlayerData->currentResources[4] + piVar1[3];
piVar1 = piVar1 + 5;
/* 
  fixme: yea no this breaks the offset logic
 */

_pPlayerData = (PlayerData *)(_pPlayerData->currentResources + 6);
iVar3 = iVar3 + -1;
} while (iVar3 != 0);
}
iVar2 = iVar2 + 1;
pBVar6 = pBVar6 + 0x196;
} while (iVar2 < this->maxBuildingsCount);
}
DAT_GameState::instance.playerDataArray[1].currentResources[0xf] = _playerGoldArray[0];
DAT_GameState::instance.playerDataArray[2].currentResources[0xf] = _playerGoldArray[1];
DAT_GameState::instance.playerDataArray[3].currentResources[0xf] = _playerGoldArray[2];
DAT_GameState::instance.playerDataArray[4].currentResources[0xf] = _playerGoldArray[3];
DAT_GameState::instance.playerDataArray[5].currentResources[0xf] = _playerGoldArray[4];
DAT_GameState::instance.playerDataArray[6].currentResources[0xf] = _playerGoldArray[5];
DAT_GameState::instance.playerDataArray[7].currentResources[0xf] = _playerGoldArray[6];
DAT_GameState::instance.playerDataArray[8].currentResources[0xf] = _playerGoldArray[7];
return;
}


}
}
}