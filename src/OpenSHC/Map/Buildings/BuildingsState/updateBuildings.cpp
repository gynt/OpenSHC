#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "MappersEnumShort": Some values do not have unique names
 */

/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00422E20
void BuildingsState::updateBuildings()

{
int *piVar1;
BuildingTypeShort BVar2;
int iVar3;
int iVar4;
short *psVar5;
BuildingTypeInt _buildingType;
int _owner;
int *_pTotalKillingPits;
int _buildingID;
short *_pAnimationIndex;
short *_pRecruitTimer;
short *_pIdleTimer;
int *_pPopulationCap;
short *_pFireDuration;
int _buildingID_3;
BuildingLogicalStateShort _logicalState;
uint *_pTimeAlive;

this->isFirstTickInLoop = (BOOLEnum)(DAT_GameCore::instance.performedGameTicksThisLoop == 0);
if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 5) {
this->maxBuildingsCount = 0;
DAT_CurrentBuildingID::instance = 1;
do {
if (this->buildings[DAT_CurrentBuildingID::instance].logicalState != ((BuildingLogicalState)0)) {
this->maxBuildingsCount = DAT_CurrentBuildingID::instance + 1;
}
DAT_CurrentBuildingID::instance = DAT_CurrentBuildingID::instance + 1;
} while (DAT_CurrentBuildingID::instance < 2000);
}
this->structCount = 0;
psVar5 = &DAT_GameState::instance.playerDataArray[0].dogCageCount;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[0] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[1] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[2] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[3] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[4] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[5] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[6] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[7] = 0;
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[8] = 0;
do {
*psVar5 = 0;
psVar5 = psVar5 + 0x1cfa;
} while ((int)psVar5 < 0x1180156);
this->field1_0x4 = 0;
DAT_CurrentBuildingID::instance = 1;
if (1 < this->maxBuildingsCount) {
do {
_buildingID = DAT_CurrentBuildingID::instance;
if (this->buildings[DAT_CurrentBuildingID::instance].logicalState != ((BuildingLogicalState)0)) {
this->structCount = this->structCount + 1;
_logicalState = this->buildings[DAT_CurrentBuildingID::instance].logicalState;
if (_logicalState == OpenSHC::Map::Buildings::BLS_INITIAL) {
this->buildings[DAT_CurrentBuildingID::instance].logicalState = OpenSHC::Map::Buildings::BLS_NORMAL;
}
else if (_logicalState == OpenSHC::Map::Buildings::BLS_REMOVE) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, this)(DAT_CurrentBuildingID::instance);
}
else {
if (this->buildings[DAT_CurrentBuildingID::instance].buildingType == OpenSHC::Map::Buildings::BT_KILLINGPIT) {
_pTotalKillingPits =
DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits +
this->buildings[DAT_CurrentBuildingID::instance].owner;
*_pTotalKillingPits = *_pTotalKillingPits + 1;
}
if (this->buildings[_buildingID].renderAnimation == 0) {
LAB_00422fc0:
this->buildings[_buildingID].animationActive = 0;
}
else {
piVar1 = &this->buildings[_buildingID].animStateCounter;
*piVar1 = *piVar1 + 1;
iVar3 = this->buildings[DAT_CurrentBuildingID::instance].animStateCounter;
_buildingID = DAT_CurrentBuildingID::instance;
if (iVar3 - this->buildings[DAT_CurrentBuildingID::instance].animStateCounterTracker
< this->buildings[DAT_CurrentBuildingID::instance].animAdvanceThrottle)
goto LAB_00422fc0;
this->buildings[DAT_CurrentBuildingID::instance].animStateCounterTracker = iVar3;
_pAnimationIndex = &this->buildings[DAT_CurrentBuildingID::instance].animationIndex;
*_pAnimationIndex =
*_pAnimationIndex +
this->buildings[DAT_CurrentBuildingID::instance].animationIncrement;
this->buildings[DAT_CurrentBuildingID::instance].animationActive = 1;
}
_pRecruitTimer = &this->buildings[DAT_CurrentBuildingID::instance].recruitTimer;
*_pRecruitTimer = *_pRecruitTimer + 1;
if (99 < this->buildings[DAT_CurrentBuildingID::instance].recruitTimer) {
this->buildings[DAT_CurrentBuildingID::instance].recruitTimer = 0;
}
_pTimeAlive = &this->buildings[DAT_CurrentBuildingID::instance].timeAlive;
*_pTimeAlive = *_pTimeAlive + 1;
_owner = (int)this->buildings[DAT_CurrentBuildingID::instance].owner;
if (this->buildings[DAT_CurrentBuildingID::instance].idleTimerUnk != 0) {
if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] == -1) &&
(DAT_GameSynchronyState::instance.currentAIArray[_owner] != 0)) {
_pIdleTimer = &this->buildings[DAT_CurrentBuildingID::instance].idleTimerUnk;
*_pIdleTimer = *_pIdleTimer + -1;
}
else {
this->buildings[DAT_CurrentBuildingID::instance].idleTimerUnk = 0;
}
}
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateNeededEmployeeCount, this)(DAT_CurrentBuildingID::instance);
psVar5 = &this->buildings[DAT_CurrentBuildingID::instance].field127_0x194;
if (0 < this->buildings[DAT_CurrentBuildingID::instance].field127_0x194) {
*psVar5 = *psVar5 + -1;
}
_buildingID_3 = DAT_CurrentBuildingID::instance;
_pPopulationCap = &DAT_GameState::instance.playerDataArray[_owner].populationCap;
*_pPopulationCap =
*_pPopulationCap +
(int)this->buildings[DAT_CurrentBuildingID::instance].numberOfPopulationProvided;
/* 
  update function happens here
 */

(*DAT_BuildingDefinedData::instance.BuildingUpdateFunctions
[(short)this->buildings[_buildingID_3].buildingType])();
if (this->buildings[DAT_CurrentBuildingID::instance].logicalState != ((BuildingLogicalState)0)) {
if ((DAT_TileMapState::instance.refreshRelatedTwo != 0) &&
(this->buildings[DAT_CurrentBuildingID::instance].gfxOffset != 0)) {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance);
}
/* 
  building is on fire
 */

if (this->buildings[DAT_CurrentBuildingID::instance].fireDuration != 0) {
if (DAT_GameState::instance.gameTicksLoadBalancer % 20 == 5) {
iVar3 = 1;
switch(this->buildings[DAT_CurrentBuildingID::instance].buildingType) {
case OpenSHC::Map::Buildings::BT_HOVEL:
case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
case OpenSHC::Map::Buildings::BT_WHEATFARM:
case OpenSHC::Map::Buildings::BT_HOPFARM:
case OpenSHC::Map::Buildings::BT_APPLEFARM:
case OpenSHC::Map::Buildings::BT_DAIRYFARM:
iVar3 = 4;
}
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(
this->buildings[DAT_CurrentBuildingID::instance].
currentTilePositionAdjusted, (uint)((int)(
(int)(short)this->buildings[DAT_CurrentBuildingID::instance].x)), (uint)((int)(
(int)(short)this->buildings[DAT_CurrentBuildingID::instance].y)), iVar3, 0
, (int)((int)((short)this->buildings[DAT_CurrentBuildingID::instance].
ifFireThenResponsiblePlayer)), FALSE, 0);
_buildingType =
(BuildingTypeInt)
(short)this->buildings[DAT_CurrentBuildingID::instance].buildingType;
if ((_buildingType == OpenSHC::Map::Buildings::BT_PARADEGROUND) || (_buildingType - OpenSHC::Map::Buildings::BT_CAMPGROUND < 5)) {
psVar5 = &this->buildings[DAT_CurrentBuildingID::instance].currentHealth;
*psVar5 = *psVar5 + -1;
if (this->buildings[DAT_CurrentBuildingID::instance].currentHealth < 490) {
this->buildings[DAT_CurrentBuildingID::instance].currentHealth = 500;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::extinguishBuildingFire, this)(DAT_CurrentBuildingID::instance);
this->buildings[DAT_CurrentBuildingID::instance].fireDuration = -1;
}
}
}
_pFireDuration = &this->buildings[DAT_CurrentBuildingID::instance].fireDuration;
*_pFireDuration = *_pFireDuration + 1;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::spawnRandomFireEffectOnBuilding, this)(DAT_CurrentBuildingID::instance, (undefined4)((int)(
(int)(short)this->buildings[DAT_CurrentBuildingID::instance].
ifFireThenResponsiblePlayer)));
}
if ((((this->buildings[DAT_CurrentBuildingID::instance].unknownSiegeTentRelated01 ==
2) && (this->buildings[DAT_CurrentBuildingID::instance].attackWave == 0)) &&
((BVar2 = this->buildings[DAT_CurrentBuildingID::instance].buildingType,
BVar2 == OpenSHC::Map::Buildings::BT_FIREBALLISTA || (BVar2 == OpenSHC::Map::Buildings::BT_CATAPULT)))) &&
(((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_owner] == -1 &&
(DAT_GameSynchronyState::instance.currentAIArray[_owner] != 0)) &&
(2400 < (int)this->buildings[DAT_CurrentBuildingID::instance].timeAlive)))) {
this->buildings[DAT_CurrentBuildingID::instance].logicalState = OpenSHC::Map::Buildings::BLS_REMOVE;
}
psVar5 = &this->buildings[DAT_CurrentBuildingID::instance].cooldownTimer;
if (this->buildings[DAT_CurrentBuildingID::instance].cooldownTimer != 0) {
*psVar5 = *psVar5 + -1;
}
iVar3 = 0;
do {
iVar4 = iVar3 + 1;
this->buildings[DAT_CurrentBuildingID::instance].workers[iVar3] = 0;
iVar3 = iVar4;
} while (iVar4 < 4);
}
}
}
DAT_CurrentBuildingID::instance = DAT_CurrentBuildingID::instance + 1;
} while (DAT_CurrentBuildingID::instance < this->maxBuildingsCount);
}
this->field14_0x18e024 = 0;
this->field34_0x18e074 = 0;
this->unknownCountdown01 = 2000 - this->structCount;
if (0 < this->field4_0x10) {
this->field4_0x10 = this->field4_0x10 + -1;
}
return;
}


}
}
}