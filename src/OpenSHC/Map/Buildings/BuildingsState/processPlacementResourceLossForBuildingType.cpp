#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Game::GameMode2;
using OpenSHC::Game::GameMode;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Game::Resources::ResourceType;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041BFD0
void BuildingsState::processPlacementResourceLossForBuildingType(int playerID,BuildingType buildingType,int param_3)

{
short *psVar1;
int amount;
int iVar2;
short sVar3;
uint uVar4;
int amount_00;
int iVar5;
int local_4;
BuildingType _buildingType;
GameMode2Int _gamemode2;
int _playerID;

_buildingType = buildingType;
_playerID = playerID;
_gamemode2 = DAT_GameCore::instance.gameMode_2;
local_4 = (int)this;
if ((((DAT_GameCore::instance.solitaryAllBuildingsAreFree == FALSE) &&
(DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)) &&
((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY ||
((((buildingType != OpenSHC::Map::Buildings::BT_MANORHOUSE && (buildingType != OpenSHC::Map::Buildings::BT_STONEKEEP)) &&
(buildingType != OpenSHC::Map::Buildings::BT_STRONGHOLD)) &&
((buildingType != OpenSHC::Map::Buildings::BT_KEEPFOUR && (buildingType != OpenSHC::Map::Buildings::BT_KEEPFIVE)))))))) &&
(uVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters, this)(playerID, (int)((int)(buildingType))), iVar5 = param_3, uVar4 == 0)) {
if (_gamemode2 == OpenSHC::Game::GM_SIEGE_THAT) {
if (_buildingType == OpenSHC::Map::Buildings::BT_PITCHDITCH) {
return;
}
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_PITCHDITCH) {
psVar1 = &DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4;
if (*psVar1 == 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(playerID, OpenSHC::Game::Resources::RT_PITCH, 1, param_3);
if (iVar5 != 0) {
return;
}
*psVar1 = 1;
return;
}
if (param_3 != 0) {
return;
}
sVar3 = *psVar1 + 1;
*psVar1 = sVar3;
if (sVar3 != 4) {
return;
}
*psVar1 = 0;
return;
}
buildingType = this->buildingCosts[_buildingType].requiredStone_0x4;
amount = this->buildingCosts[_buildingType].requiredWood;
amount_00 = this->buildingCosts[_buildingType].requiredIron_0x8;
iVar2 = this->buildingCosts[_buildingType].requiredPitch_0xc;
local_4 = this->buildingCosts[_buildingType].requiredGold;
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
amount_00 = 0;
playerID = 0;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::resourceGainForKillingPitAndPitchDitch, this)(_buildingType, (int *)&buildingType, &local_4);
iVar5 = param_3;
iVar2 = playerID;
}
else if (amount != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(playerID, OpenSHC::Game::Resources::RT_WOOD, amount, param_3);
}
playerID = iVar2;
if (buildingType != ((BuildingType)0)) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(_playerID, OpenSHC::Game::Resources::RT_STONE, (int)((int)(buildingType)), iVar5);
}
if (amount_00 != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(_playerID, OpenSHC::Game::Resources::RT_IRON, amount_00, iVar5);
}
if (playerID != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(_playerID, OpenSHC::Game::Resources::RT_PITCH, playerID, iVar5);
}
if (local_4 != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(_playerID, OpenSHC::Game::Resources::RT_GOLD, local_4, iVar5);
}
}
return;
}


}
}
}