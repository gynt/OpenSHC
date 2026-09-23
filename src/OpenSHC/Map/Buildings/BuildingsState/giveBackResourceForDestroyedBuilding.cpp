#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::GameMode2;
using OpenSHC::Game::Resources::ResourceType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00421D70
void BuildingsState::giveBackResourceForDestroyedBuilding(int buildingIDORIfNegResourceType,int playerID,int param_3)

{
int *piVar1;
short *psVar2;
BuildingTypeShort BVar3;
Building *pBVar4;
int _stoneAmount;
BOOLEnum BVar5;
int iVar6;
short sVar7;
int iVar8;
int iVar9;
int amount;
int _playerID;
int amount_00;

_playerID = playerID;
if (param_3 != 0) {
iVar6 = param_3;
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
iVar6 = 100;
}
if (buildingIDORIfNegResourceType == -1) {
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
piVar1 = DAT_GameState::instance.playerDataArray[playerID].startResources + 4;
/* 
  return DAT_PlayerDataArray[playerID].field_0x47c
 */

*piVar1 = *piVar1 + 1;
return;
}
psVar2 = &DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction;
iVar6 = iVar6 * 2;
/* 
  Compiler magic for division by 100 and a signed divide by 4
 */

sVar7 = (((short)(iVar6 / 100) + (short)(iVar6 >> 0x1f)) -
(short)((longlong)iVar6 * 0x51eb851f >> 0x3f)) + *psVar2;
_stoneAmount = (int)((int)sVar7 + ((int)sVar7 >> 0x1f &3U)) >> 2;
*psVar2 = sVar7 + (short)_stoneAmount * -4;
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_STONE, _stoneAmount);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
return;
}
}
else if (buildingIDORIfNegResourceType == -2) {
psVar2 = &DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction;
iVar6 = iVar6 * 2;
sVar7 = (((short)(iVar6 / 100) + (short)(iVar6 >> 0x1f)) -
(short)((longlong)iVar6 * 0x51eb851f >> 0x3f)) + *psVar2;
iVar6 = (int)((int)sVar7 + ((int)sVar7 >> 0x1f &3U)) >> 2;
*psVar2 = sVar7 + (short)iVar6 * -4;
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_WOOD, iVar6);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
return;
}
}
else {
if (buildingIDORIfNegResourceType == -3) {
/* 
  Tower mangonel?
 */

iVar8 = this->buildingCosts[0x56].requiredStone_0x4 * iVar6;
iVar9 = this->buildingCosts[0x56].requiredIron_0x8 * iVar6;
amount_00 = (this->buildingCosts[0x56].requiredPitch_0xc * iVar6) / 100;
amount = (this->buildingCosts[0x56].requiredGold * iVar6) / 100;
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_WOOD, 
(this->buildingCosts[0x56].requiredWood * iVar6) /
100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(playerID);
}
_playerID = playerID;
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_STONE, iVar8 / 100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(_playerID, OpenSHC::Game::Resources::RT_IRON, iVar9 / 100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
}
else if (buildingIDORIfNegResourceType == -4) {
/* 
  Tower ballista?
 */

iVar8 = this->buildingCosts[0x57].requiredStone_0x4 * iVar6;
iVar9 = this->buildingCosts[0x57].requiredIron_0x8 * iVar6;
amount_00 = (this->buildingCosts[0x57].requiredPitch_0xc * iVar6) / 100;
amount = (this->buildingCosts[0x57].requiredGold * iVar6) / 100;
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_WOOD, 
(this->buildingCosts[0x57].requiredWood * iVar6) /
100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(playerID);
}
_playerID = playerID;
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_STONE, iVar8 / 100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(_playerID, OpenSHC::Game::Resources::RT_IRON, iVar9 / 100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
}
else {
BVar3 = this->buildings[buildingIDORIfNegResourceType].buildingType;
pBVar4 = this->buildings + buildingIDORIfNegResourceType;
iVar9 = (this->buildingCosts[(short)BVar3].requiredStone_0x4 * iVar6) / 100;
iVar8 = this->buildingCosts[(short)BVar3].requiredIron_0x8;
amount_00 = (this->buildingCosts[(short)BVar3].requiredPitch_0xc * iVar6) / 100
;
amount = (this->buildingCosts[(short)BVar3].requiredGold * iVar6) / 100;
buildingIDORIfNegResourceType = amount;
param_3 = iVar9;
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::resourceGainForKillingPitAndPitchDitch, this)((int)(short)pBVar4->buildingType, &param_3, 
&buildingIDORIfNegResourceType);
piVar1 = DAT_GameState::instance.playerDataArray[playerID].startResources + 4;
*piVar1 = *piVar1 + param_3;
piVar1 = DAT_GameState::instance.playerDataArray[playerID].startResources + 0xf;
*piVar1 = *piVar1 + buildingIDORIfNegResourceType;
return;
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(playerID, OpenSHC::Game::Resources::RT_WOOD, 
(this->buildingCosts[(short)BVar3].requiredWood *
iVar6) / 100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(_playerID, OpenSHC::Game::Resources::RT_STONE, iVar9);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(_playerID, OpenSHC::Game::Resources::RT_IRON, (iVar8 * iVar6) / 100);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(_playerID, OpenSHC::Game::Resources::RT_PITCH, amount_00);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
BVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, this)(_playerID, OpenSHC::Game::Resources::RT_GOLD, amount);
if (BVar5 == FALSE) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile, DAT_GameState::ptr)(_playerID);
}
}
}
return;
}


}
}
}