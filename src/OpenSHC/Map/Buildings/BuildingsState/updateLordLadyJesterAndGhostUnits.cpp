#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/MapType2.hpp"



#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Game::GameMode;
using OpenSHC::Map::Units::States::UnitState;
using OpenSHC::Map::Units::UnitLogicState;
using OpenSHC::Map::Units::UnitType;
using OpenSHC::Game::GameMode2;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::AI::AIType;
using OpenSHC::Map::MapType2;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040FC40
void BuildingsState::updateLordLadyJesterAndGhostUnits(int playerID)

{
int iVar1;
AITypeInt AVar2;
short sVar3;
BOOLEnum BVar4;
int iVar5;
short sVar6;
bool bVar7;
short local_10;
int local_c;
int _lordID;
int _jesterID;
int _ladyID;
int _lordID2;
int _jesterID2;
int _someUnitID;
int _lordHealth;
int _lordHitpoints;
int _maxHealth;

MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, DAT_GameState::ptr)(playerID, 0);
iVar5 = DAT_GameState::instance.playerDataArray[playerID].keep.id;
_maxHealth = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;
iVar1 = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
local_c = _maxHealth + -1;
if ((iVar5 != 0) && (this->buildings[iVar5].buildingType == OpenSHC::Map::Buildings::BT_MANORHOUSE)) {
local_c = _maxHealth;
}
if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
if ((iVar5 < 1) || (DAT_GameState::instance.playerDataArray[playerID].playerDeathRelated != 0)) {
_ladyID = DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk;
if (_ladyID != 0) {
DAT_UnitsState::instance.units[_ladyID].dying = 1;
DAT_UnitsState::instance.units[_ladyID].animationCycleNumber = 0;
DAT_UnitsState::instance.units[_ladyID].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
DAT_UnitsState::instance.units[_ladyID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = 0;
}
_lordID2 = DAT_GameState::instance.playerDataArray[playerID].lordID;
if (_lordID2 != 0) {
DAT_UnitsState::instance.units[_lordID2].dying = 1;
DAT_UnitsState::instance.units[_lordID2].animationCycleNumber = 0;
DAT_UnitsState::instance.units[_lordID2].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
DAT_UnitsState::instance.units[_lordID2].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
DAT_GameState::instance.playerDataArray[playerID].lordID = 0;
}
_jesterID2 = DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk;
if (_jesterID2 != 0) {
DAT_UnitsState::instance.units[_jesterID2].dying = 1;
DAT_UnitsState::instance.units[_jesterID2].animationCycleNumber = 0;
DAT_UnitsState::instance.units[_jesterID2].state.generic = OpenSHC::Map::Units::States::US_DEATH_03;
DAT_UnitsState::instance.units[_jesterID2].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = 0;
}
_someUnitID = DAT_GameState::instance.playerDataArray[playerID].someUnitID01;
if (_someUnitID == 0) {
return;
}
DAT_GameState::instance.playerDataArray[playerID].someUnitID01 = 0;
DAT_UnitsState::instance.units[_someUnitID].animationCycleNumber = 0;
DAT_UnitsState::instance.units[_someUnitID].dying = 1;
DAT_UnitsState::instance.units[_someUnitID].state.generic = ((UnitState)2);
return;
}
}
else if ((DAT_GameCore::instance.mapU4Int0 != 0) && (playerID == DAT_GameState::instance.mapAndTime.somePlayerID)) {
return;
}
_maxHealth = DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk;
local_10 = (short)iVar1;
sVar3 = (short)iVar5;
sVar6 = (short)local_c;
if (_maxHealth == 0) {
if ((DAT_GameState::instance.mapAndTime.unitLadyRelated != 0) &&
(_maxHealth = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID, playerID, iVar1 * 8, local_c * 8, (int)((int)(
this->buildings[iVar5].terrainHeightUnk)), OpenSHC::Map::Units::UT_LADY),
_maxHealth != 0)) {
DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef =
DAT_UnitsState::instance.units[_maxHealth].uid;
DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = _maxHealth;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_maxHealth);
DAT_UnitsState::instance.units[_maxHealth].state.generic = ((UnitState)2);
goto LAB_0040fe33;
}
}
else {
LAB_0040fe33:
if (DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef ==
DAT_UnitsState::instance.units[_maxHealth].uid) {
DAT_UnitsState::instance.units[_maxHealth].workplaceBuildingID_1 = sVar3;
DAT_UnitsState::instance.units[_maxHealth].targetX_2 = local_10;
DAT_UnitsState::instance.units[_maxHealth].targetY_2 = sVar6;
}
else {
DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = 0;
DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef = 0;
}
}
_lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
if (_lordID == 0) {
_lordID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID, playerID, iVar1 * 8, local_c * 8, (int)((int)(
this->buildings[iVar5].terrainHeightUnk)), OpenSHC::Map::Units::UT_LORD);
if (_lordID != 0) {
DAT_GameState::instance.playerDataArray[playerID].lordUID = DAT_UnitsState::instance.units[_lordID].uid;
DAT_GameState::instance.playerDataArray[playerID].lordID = _lordID;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_lordID);
bVar7 = DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY;
DAT_UnitsState::instance.units[_lordID].state.generic = ((UnitState)2);
if (bVar7) {
if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) && (DAT_GameCore::instance.selectedLordType_2Unk == 1))
{
DAT_UnitsState::instance.units[_lordID].unknownLordTypeBasedMissionSpecificValue_01 = 1;
}
}
else {
_maxHealth = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer, DAT_GameSynchronyState::ptr)(playerID);
if (_maxHealth == 1) {
DAT_UnitsState::instance.units[_lordID].unknownLordTypeBasedMissionSpecificValue_01 = 1;
}
BVar4 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(playerID);
if (BVar4 != FALSE) {
AVar2 = DAT_GameState::instance.playerDataArray[playerID].aiType;
_lordHealth = DAT_UnitsState::instance.units[_lordID].health;
/* 
  set ai lord health based on a mapping of ai type and health
 */

_maxHealth = DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[AVar2 + ~OpenSHC::AI::AIT_NULL].
maxHealthMultiplier;
DAT_UnitsState::instance.units[_lordID].maxHealthRatingLord =
(short)DAT_SkirmishDefinedData::instance.MaxLordHealthMapping[AVar2 + ~OpenSHC::AI::AIT_NULL].aiTypeA;
_lordHitpoints = DAT_UnitsState::instance.units[_lordID].maxHealth;
DAT_UnitsState::instance.units[_lordID].health = (_lordHealth * _maxHealth) / 100;
DAT_UnitsState::instance.units[_lordID].maxHealth = (_lordHitpoints * _maxHealth) / 100;
}
}
goto LAB_0040ffba;
}
}
else {
LAB_0040ffba:
if (DAT_GameState::instance.playerDataArray[playerID].lordUID == DAT_UnitsState::instance.units[_lordID].uid) {
DAT_UnitsState::instance.units[_lordID].workplaceBuildingID_1 = sVar3;
DAT_UnitsState::instance.units[_lordID].targetX_2 = local_10;
DAT_UnitsState::instance.units[_lordID].targetY_2 = sVar6;
}
else if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk) &&
(DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_JUST_BUILD)) {
DAT_GameState::instance.playerDataArray[playerID].lordID = 0;
DAT_GameState::instance.playerDataArray[playerID].lordUID = 0;
}
}
_jesterID = DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk;
if (_jesterID == 0) {
if ((DAT_GameState::instance.mapAndTime.unitJesterRelated == 0) ||
(_jesterID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID, playerID, iVar1 * 8, local_c * 8, (int)((int)(
this->buildings[iVar5].terrainHeightUnk)), OpenSHC::Map::Units::UT_JESTER),
_jesterID == 0)) goto LAB_004100da;
iVar5 = DAT_UnitsState::instance.units[_jesterID].uid;
DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = _jesterID;
DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2 = iVar5;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_jesterID);
DAT_UnitsState::instance.units[_jesterID].state.generic = ((UnitState)2);
}
if (DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2 ==
DAT_UnitsState::instance.units[_jesterID].uid) {
DAT_UnitsState::instance.units[_jesterID].workplaceBuildingID_1 = sVar3;
DAT_UnitsState::instance.units[_jesterID].targetX_2 = local_10;
DAT_UnitsState::instance.units[_jesterID].targetY_2 = sVar6;
}
else {
DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = 0;
DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2 = 0;
}
LAB_004100da:
if ((((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) &&
(playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)) &&
(iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType, this)(playerID, OpenSHC::Map::Buildings::BT_SHRINE),
0 < iVar5)) && (0x27 < DAT_GameState::instance.playerDataArray[playerID].currentPopulation)) {
_maxHealth = DAT_GameState::instance.playerDataArray[playerID].someUnitID01;
if (_maxHealth == 0) {
_maxHealth = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID, playerID, (int)((int)(
this->buildings[iVar5].buildingEntryX * 8)), (int)((int)(
this->buildings[iVar5].buildingEntryY * 8)), (int)((int)(
this->buildings[iVar5].terrainHeightUnk)), OpenSHC::Map::Units::UT_GHOST);
if (_maxHealth == 0) {
return;
}
iVar1 = DAT_UnitsState::instance.units[_maxHealth].uid;
DAT_GameState::instance.playerDataArray[playerID].someUnitID01 = _maxHealth;
DAT_GameState::instance.playerDataArray[playerID].field714_0x22cc = iVar1;
DAT_UnitsState::instance.units[_maxHealth].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
DAT_UnitsState::instance.units[_maxHealth].disappearFadeAlphaCountdown = 0x20;
}
if (DAT_GameState::instance.playerDataArray[playerID].field714_0x22cc !=
DAT_UnitsState::instance.units[_maxHealth].uid) {
DAT_GameState::instance.playerDataArray[playerID].someUnitID01 = 0;
DAT_GameState::instance.playerDataArray[playerID].field714_0x22cc = 0;
return;
}
DAT_UnitsState::instance.units[_maxHealth].workplaceBuildingID_1 = (short)iVar5;
DAT_UnitsState::instance.units[_maxHealth].targetX_2 = this->buildings[iVar5].buildingEntryX;
DAT_UnitsState::instance.units[_maxHealth].targetY_2 = this->buildings[iVar5].buildingEntryY;
}
return;
}


}
}
}