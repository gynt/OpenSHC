#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"



#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::GameMode;
using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Game::Player::PlayerDataBuildingCategoryEnum;
using OpenSHC::Game::Resources::ResourceType;
using OpenSHC::Game::GameMode2;
using OpenSHC::Map::MapType2;
using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
using OpenSHC::UI::Enums::MenuViewType;
using OpenSHC::Commands::MappersEnum;
using OpenSHC::Map::Units::UnitInstructionType;
using OpenSHC::Map::Entities::EntityType;
using OpenSHC::DE::SHCDE::eSFX;
using OpenSHC::Map::Units::UnitType;
using OpenSHC::Map::Units::States::UnitState;


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


// FUNCTION: STRONGHOLDCRUSADER 0x00420D20
int BuildingsState::setupBuildingData(int playerID,uint x,uint y,undefined4 averageHeight,BuildingType buildingType,uint width,int playerID_dup,int variationIndex)

{
short *psVar1;
ResourceTypeShort *pRVar2;
ResourceTypeShort *pRVar3;
ushort *puVar4;
short sVar5;
short _handledVariation;
Building * _pBuilding;
ResourceTypeShort RVar6;
int _buildingID2;
Building * psVar5;
int _dog1ID;
int _dog2ID;
int _dog3ID;
int _dog4ID;
uint _isFFBuilding;
uint _isReligiousBuilding;
uint _rng1;
int iVar7;
int *piVar8;
int _dogCount;
short _buildingID_2;
uint _buildingID;
int iVar9;
UnitInstructionType instructionType;

if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
playerID_dup = 0;
}
if (((399 < x) || (399 < y)) || (*(char *)(y * 400 + 0x21aec98 + x) == '\0')) {
return 0;
}
_buildingID = 1;
_pBuilding = &this->buildings[1];
do {
if (_pBuilding->logicalState == ((BuildingLogicalState)0)) break;
if (1999 < (int)_buildingID) {
return 0;
}
_buildingID = _buildingID + 1;
_pBuilding = _pBuilding + 0x196;
} while ((int)_buildingID < 2000);
if (this->maxBuildingsCount <= (int)_buildingID) {
this->maxBuildingsCount = _buildingID + 1;
}
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(0x32c, '\0', (void *)((int)(this->buildings + _buildingID)));
_buildingID2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType, this)(playerID, buildingType);
if ((_buildingID2 != 0) && (this->buildings[_buildingID2].sleeping != false)) {
this->buildings[_buildingID].sleeping = true;
}
this->unknownCountdown01 = this->unknownCountdown01 + -1;
this->buildings[_buildingID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
this->buildings[_buildingID].owner = (short)playerID;
this->buildings[_buildingID].logicalState = OpenSHC::Map::Buildings::BLS_INITIAL;
this->buildings[_buildingID].widthOrHeight = width;
this->buildings[_buildingID].x = (ushort)x;
this->buildings[_buildingID].y = (ushort)y;
this->buildings[_buildingID].buildingType = (BuildingTypeShort)buildingType;
this->buildings[_buildingID].currentTilePositionAdjusted =
DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
this->buildings[_buildingID].microX = (ushort)x * 8;
this->buildings[_buildingID].microY = (ushort)y * 8;
this->buildings[_buildingID].terrainHeightUnk = (short)averageHeight;
if (buildingType == OpenSHC::Map::Buildings::BT_GARDEN) {
this->buildings[_buildingID].ffBuildingVariation =
DAT_BuildingDefinedData::instance.GardenVariations[variationIndex];
_handledVariation = 0xf;
}
else if (buildingType == OpenSHC::Map::Buildings::BT_UNKNOWN1) {
/* 
  unknown1
 */

this->buildings[_buildingID].ffBuildingVariation =
DAT_BuildingDefinedData::instance.UnknownVariations[variationIndex];
_handledVariation = 0xf;
}
else if (buildingType == OpenSHC::Map::Buildings::BT_CESSPIT) {
/* 
  cesspit
 */

this->buildings[_buildingID].ffBuildingVariation =
DAT_BuildingDefinedData::instance.CesspitVariations[variationIndex];
_handledVariation = 0xf;
}
else if (buildingType == OpenSHC::Map::Buildings::BT_STATUE) {
/* 
  statue
 */

this->buildings[_buildingID].ffBuildingVariation =
DAT_BuildingDefinedData::instance.StatueVariations[variationIndex];
_handledVariation = 0xf;
}
else if (buildingType == OpenSHC::Map::Buildings::BT_SHRINE) {
/* 
  shrine
 */

this->buildings[_buildingID].ffBuildingVariation =
DAT_BuildingDefinedData::instance.ShrineVariations[variationIndex];
_handledVariation = 0xf;
}
else if (buildingType == OpenSHC::Map::Buildings::BT_POND) {
/* 
  pond
 */

this->buildings[_buildingID].ffBuildingVariation =
DAT_BuildingDefinedData::instance.PondVariations[variationIndex];
_handledVariation = 0xf;
}
else {
_handledVariation = (short)variationIndex;
this->buildings[_buildingID].ffBuildingVariation = 0;
}
this->buildings[_buildingID].playerColorUnk = playerID_dup;
this->buildings[_buildingID].buildingVariation = _handledVariation;
this->buildings[_buildingID].oldVisualActiveState = -1;
this->buildings[_buildingID].fireRelatedRNG1 = (int)SEC_RNG::instance.currentNumber2;
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
/* 
  init building's rendering data
 */

*(short *)&this->buildings[_buildingID].spriteSheetID =
DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[buildingType].shortValue;
this->buildings[_buildingID].spriteID =
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[buildingType] +
this->buildings[_buildingID].ffBuildingVariation;
this->buildings[_buildingID].visuallyActiveSpriteID =
DAT_BuildingDefinedData::instance.VisuallyActiveSpriteIDOffsets[buildingType];
this->buildings[_buildingID].gfxOffset =
DAT_BuildingDefinedData::instance.GFXOffsets[buildingType];
this->buildings[_buildingID].gfxOffset2 =
DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[buildingType];
this->buildings[_buildingID].gfxOffset3 =
DAT_BuildingDefinedData::instance.GFXOffsets3[buildingType];
this->buildings[_buildingID].spriteOffetX =
DAT_BuildingDefinedData::instance.SpriteOffsets1[buildingType][0][0];
this->buildings[_buildingID].spriteOffetY =
DAT_BuildingDefinedData::instance.SpriteOffsets1[buildingType][1][0];
this->buildings[_buildingID].animAdvanceThrottle =
DAT_BuildingDefinedData::instance.AnimAdvanceThrottles[buildingType];
this->buildings[_buildingID].animationFrame = 0;
this->buildings[_buildingID].campgroundVclock = 0;
this->buildings[_buildingID].field25_0x4c = 0;
this->buildings[_buildingID].field26_0x50 = 0;
this->buildings[_buildingID].field27_0x54 = 0;
this->buildings[_buildingID].spriteID2 =
DAT_BuildingDefinedData::instance.SpriteIDs2[buildingType].shortValue;
this->buildings[_buildingID].animStateCounterTracker = 0;
this->buildings[_buildingID].animStateCounter = 0;
if (((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) ||
(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1)) ||
(DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0)) {
this->buildings[_buildingID].cooldownTimer = 400;
}
else {
this->buildings[_buildingID].cooldownTimer = 2000;
}
this->buildings[_buildingID].currentlyNeededEmployeeCount = 0;
this->buildings[_buildingID].renderAnimation = 0;
this->buildings[_buildingID].unknownStockpileOrSignpostRelated = 1;
this->buildings[_buildingID].numberOfPopulationProvided =
DAT_BuildingDefinedData::instance.BuildingNumberOfPopulationProvided[buildingType].shortValue;
psVar1 = &this->buildings[_buildingID].unknownStockpileOrSignpostRelated;
this->buildings[_buildingID].buildingTypeBasedEmployeeCount =
DAT_BuildingDefinedData::instance.EmployeeCountPerBuildingType[buildingType].shortValue;
this->buildings[_buildingID].unknownFlag3 =
DAT_BuildingDefinedData::instance.field15_0x1404[buildingType].shortValue;
this->buildings[_buildingID].flag1 =
DAT_BuildingDefinedData::instance.field16_0x15bc[buildingType].shortValue;
this->buildings[_buildingID].unknownFlag4 =
DAT_BuildingDefinedData::instance.field18_0x192c[buildingType].byteValue;
this->buildings[_buildingID].flag2 =
DAT_BuildingDefinedData::instance.field24_0x237c[buildingType].shortValue;
sVar5 = DAT_BuildingDefinedData::instance.BuildingHP[buildingType].shortValue;
this->buildings[_buildingID].maxHealth = sVar5;
this->buildings[_buildingID].currentHealth = sVar5;
this->buildings[_buildingID].buildMonthOrBuildOrder =
(short)DAT_GameState::instance.mapAndTime.month + (short)DAT_GameState::instance.mapAndTime.year * 12;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(_buildingID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea, this)(_buildingID, 1, FALSE);
switch(buildingType) {
case OpenSHC::Map::Buildings::BT_HOVEL:
case OpenSHC::Map::Buildings::BT_HOUSE:
this->buildings[_buildingID].field_0x2a5 =
(char)((this->buildings[_buildingID].fireRelatedRNG1 >> 5) % 3) + '\x01';
break;
case OpenSHC::Map::Buildings::BT_OXTETHER:
this->buildings[_buildingID].field28_0x58 = 0x32;
break;
case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_MERCENARYPOST);
break;
case OpenSHC::Map::Buildings::BT_BARRACKS:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_BARRACKS);
break;
case OpenSHC::Map::Buildings::BT_STOCKPILE:
*psVar1 = 0;
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_STOCKPILE);
break;
case OpenSHC::Map::Buildings::BT_ARMORY:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_ARMORY);
break;
case OpenSHC::Map::Buildings::BT_FLETCHER:
RVar6 = OpenSHC::Game::Resources::RT_BOW;
goto LAB_004212f6;
case OpenSHC::Map::Buildings::BT_BLACKSMITH:
pRVar2 = &this->buildings[_buildingID].producedItemTypeNext;
pRVar3 = &this->buildings[_buildingID].producedItemType;
if (DAT_GameCore::instance.swordProducible_logic == 0) {
*pRVar2 = OpenSHC::Game::Resources::RT_MACE;
*pRVar3 = OpenSHC::Game::Resources::RT_MACE;
}
else {
*pRVar2 = OpenSHC::Game::Resources::RT_SWORD;
*pRVar3 = OpenSHC::Game::Resources::RT_SWORD;
}
if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1) &&
(DAT_GameCore::instance.missionNumber1to20 == 36)) {
*pRVar2 = OpenSHC::Game::Resources::RT_MACE;
*pRVar3 = OpenSHC::Game::Resources::RT_MACE;
}
break;
case OpenSHC::Map::Buildings::BT_POLETURNER:
RVar6 = OpenSHC::Game::Resources::RT_SPEAR;
LAB_004212f6:
this->buildings[_buildingID].producedItemTypeNext = RVar6;
this->buildings[_buildingID].producedItemType = RVar6;
break;
case OpenSHC::Map::Buildings::BT_GRANARY:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_GRANARY);
break;
case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_ENGINEERSGUILD);
break;
case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_TUNNELERSGUILD);
break;
case OpenSHC::Map::Buildings::BT_MARKETPLACE:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_MARKETPLACE);
break;
case OpenSHC::Map::Buildings::BT_OILSMELTER:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_OILSMELTER);
if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) &&
(DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
this->buildings[_buildingID].resources[7] =
DAT_BuildingDefinedData::instance.StorageLimitResourceTypeArray[7];
}
break;
case OpenSHC::Map::Buildings::BT_WHEATFARM:
case OpenSHC::Map::Buildings::BT_HOPFARM:
case OpenSHC::Map::Buildings::BT_APPLEFARM:
goto switchD_00421124_caseD_1e;
case OpenSHC::Map::Buildings::BT_DAIRYFARM:
this->field4_0x10 = 3;
goto switchD_00421124_caseD_1e;
case OpenSHC::Map::Buildings::BT_MANORHOUSE:
case OpenSHC::Map::Buildings::BT_STONEKEEP:
case OpenSHC::Map::Buildings::BT_STRONGHOLD:
case OpenSHC::Map::Buildings::BT_KEEPFOUR:
case OpenSHC::Map::Buildings::BT_KEEPFIVE:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_KEEP);
if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
}
break;
case OpenSHC::Map::Buildings::BT_SIGNPOST:
*psVar1 = 0;
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addSignpostToBuildingEntryData, DAT_GameState::ptr)(_buildingID);
break;
case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
case OpenSHC::Map::Buildings::BT_CATAPULT:
case OpenSHC::Map::Buildings::BT_TREBUCHET:
case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
case OpenSHC::Map::Buildings::BT_SIEGETOWER:
case OpenSHC::Map::Buildings::BT_SHIELD:
this->buildings[_buildingID].playerColorUnk = playerID;
if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) break;
_buildingID2 = this->buildings[_buildingID].uid;
instructionType = OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED;
goto LAB_00421335;
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding, DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_CAMPGROUND);
break;
case OpenSHC::Map::Buildings::BT_KILLINGPIT:
if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
this->buildings[_buildingID].state = -1;
}
break;
case OpenSHC::Map::Buildings::BT_UNKNOWN4:
if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) break;
_buildingID2 = this->buildings[_buildingID].uid;
instructionType = ((UnitInstructionType)0x15);
LAB_00421335:
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(this->DAT_DraggedTileCountVerified, instructionType, (int)((int)(
_buildingID)), _buildingID2, 0);
break;
case OpenSHC::Map::Buildings::BT_CESSPIT:
iVar9 = (int)width / 2;
_buildingID2 = (short)this->buildings[_buildingID].y + iVar9;
puVar4 = &this->buildings[_buildingID].x;
iVar7 = (int)(short)*puVar4;
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0, (iVar7 + iVar9) * 8, _buildingID2 * 8, 
(uint)*(byte *)(DAT_ViewportRenderState::instance.translationMatrix[_buildingID2].addXgetTile +
iVar7 + 0x1d32c38 + iVar9), 0, 0, 0, OpenSHC::Map::Entities::ET_COW_POISON_CLOUD, 0);
MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)((short)*puVar4 + iVar9, 
(short)this->buildings[_buildingID].y + iVar9, OpenSHC::DE::SHCDE::FX_FLIES);
break;
case OpenSHC::Map::Buildings::BT_DOGCAGE:
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(_buildingID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea, this)(_buildingID, 1, FALSE);
piVar8 = &this->buildings[_buildingID].insideUnitUID1;
psVar5 = (Building *)&this->buildings[_buildingID];
_dogCount = 4;
do {
psVar5->logicalState = ((BuildingLogicalState)0);
*piVar8 = 0;
psVar5 = &psVar5->buildingType;
piVar8 = piVar8 + 1;
_dogCount = _dogCount + -1;
} while (_dogCount != 0);
_dog1ID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID, (int)((int)(
this->buildings[_buildingID].buildingEntryX * 8)), (int)((int)(
this->buildings[_buildingID].buildingEntryY * 8)), (int)((int)(
this->buildings[_buildingID].terrainHeightUnk)), OpenSHC::Map::Units::UT_CAGEDOG)
;
_buildingID_2 = (short)_buildingID;
if (_dog1ID != 0) {
DAT_UnitsState::instance.units[_dog1ID].workplaceBuildingID_1 = _buildingID_2;
DAT_UnitsState::instance.units[_dog1ID].workplaceBuildingUID =
this->buildings[_buildingID].uid;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_dog1ID);
variationIndex._0_2_ = (short)_dog1ID;
DAT_UnitsState::instance.units[_dog1ID].state.generic = OpenSHC::Map::Units::States::0xd2;
DAT_UnitsState::instance.units[_dog1ID].cagedogReleaseCheckMoment = 0;
this->buildings[_buildingID].insideUnitID1 = (short)variationIndex;
this->buildings[_buildingID].insideUnitUID1 = DAT_UnitsState::instance.units[_dog1ID].uid;
}
_dog2ID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID, (int)((int)(
this->buildings[_buildingID].buildingEntryX * 8)), (int)((int)(
this->buildings[_buildingID].buildingEntryY * 8)), (int)((int)(
this->buildings[_buildingID].terrainHeightUnk)), OpenSHC::Map::Units::UT_CAGEDOG)
;
if (_dog2ID != 0) {
DAT_UnitsState::instance.units[_dog2ID].workplaceBuildingID_1 = _buildingID_2;
DAT_UnitsState::instance.units[_dog2ID].workplaceBuildingUID =
this->buildings[_buildingID].uid;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_dog2ID);
variationIndex._0_2_ = (short)_dog2ID;
DAT_UnitsState::instance.units[_dog2ID].state.generic = OpenSHC::Map::Units::States::0xd2;
DAT_UnitsState::instance.units[_dog2ID].cagedogReleaseCheckMoment = 1;
this->buildings[_buildingID].insideUnitID2 = (short)variationIndex;
this->buildings[_buildingID].insideUnitUID2 = DAT_UnitsState::instance.units[_dog2ID].uid;
}
_dog3ID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID, (int)((int)(
this->buildings[_buildingID].buildingEntryX * 8)), (int)((int)(
this->buildings[_buildingID].buildingEntryY * 8)), (int)((int)(
this->buildings[_buildingID].terrainHeightUnk)), OpenSHC::Map::Units::UT_CAGEDOG)
;
if (_dog3ID != 0) {
DAT_UnitsState::instance.units[_dog3ID].workplaceBuildingID_1 = _buildingID_2;
DAT_UnitsState::instance.units[_dog3ID].workplaceBuildingUID =
this->buildings[_buildingID].uid;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_dog3ID);
variationIndex._0_2_ = (short)_dog3ID;
DAT_UnitsState::instance.units[_dog3ID].state.generic = OpenSHC::Map::Units::States::0xd2;
DAT_UnitsState::instance.units[_dog3ID].cagedogReleaseCheckMoment = 2;
this->buildings[_buildingID].insideUnitID3 = (short)variationIndex;
this->buildings[_buildingID].insideUnitUID3 = DAT_UnitsState::instance.units[_dog3ID].uid;
}
_dog4ID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, playerID, (int)((int)(
this->buildings[_buildingID].buildingEntryX * 8)), (int)((int)(
this->buildings[_buildingID].buildingEntryY * 8)), (int)((int)(
this->buildings[_buildingID].terrainHeightUnk)), OpenSHC::Map::Units::UT_CAGEDOG)
;
if (_dog4ID != 0) {
DAT_UnitsState::instance.units[_dog4ID].workplaceBuildingID_1 = _buildingID_2;
DAT_UnitsState::instance.units[_dog4ID].workplaceBuildingUID =
this->buildings[_buildingID].uid;
MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(_dog4ID);
DAT_UnitsState::instance.units[_dog4ID].state.generic = OpenSHC::Map::Units::States::0xd2;
DAT_UnitsState::instance.units[_dog4ID].cagedogReleaseCheckMoment = 3;
this->buildings[_buildingID].insideUnitID4 = (short)_dog4ID;
this->buildings[_buildingID].insideUnitUID4 = DAT_UnitsState::instance.units[_dog4ID].uid;
this->buildings[_buildingID].unitRefID = (short)_dog4ID;
this->buildings[_buildingID].unitRefUID = DAT_UnitsState::instance.units[_dog4ID].uid;
}
break;
case OpenSHC::Map::Buildings::BT_OUTPOST_EUROPEAN:
case OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN:
this->buildings[_buildingID].outpostRelatedUnk1 = 0xff;
this->buildings[_buildingID].outpostRelatedUnk2 = 1;
this->buildings[_buildingID].outpostRelatedUnk3 = 0;
_rng1 = (int)SEC_RNG::instance.currentNumber2 &0x80000001;
if ((int)_rng1 < 0) {
_rng1 = (_rng1 - 1 | 0xfffffffe) + 1;
}
this->buildings[_buildingID].randomOutpostField = (char)_rng1 + 6;
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
this->buildings[_buildingID].outpostRelatedUnk4 = 1200;
}
switchD_00421124_caseD_3:
this->field34_0x18e074 = 1;
_isFFBuilding = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isFearFactorBuilding, this)(_buildingID);
if (_isFFBuilding != 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAllFearFactors, this)();
}
_isReligiousBuilding = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isReligiousBuilding, this)(_buildingID);
if (_isReligiousBuilding != 0) {
MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recomputeReligionBonuses, DAT_GameState::ptr)();
}
return(int)( _buildingID);
switchD_00421124_caseD_1e:
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(_buildingID, 0);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea, this)(_buildingID, 1, FALSE);
goto switchD_00421124_caseD_3;
}


}
}
}