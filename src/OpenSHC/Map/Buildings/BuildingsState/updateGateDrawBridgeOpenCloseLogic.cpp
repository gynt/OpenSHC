#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Entities::EntityType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Map::Units::UnitType;


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


// FUNCTION: STRONGHOLDCRUSADER 0x004224F0
void BuildingsState::updateGateDrawBridgeOpenCloseLogic()

{
byte bVar1;
ushort uVar2;
short sVar3;
EntityTypeShort EVar4;
int _gateX;
int _gateY;
int iVar5;
short *psVar6;
int _enemyMicroY;
int iVar7;
int iVar8;
int _enemyMicroX;
int _enemyDistance;
int _enemyXDistance;
int iVar9;
int (*paiVar10) [2500];
int iVar11;
BOOLEnum BVar12;
int local_48;
int local_44;
int local_40;
int local_3c;
int local_24 [9];
short _gateOwner;
int _gateID;
short _enemyUnitID;

_gateX = (int)(short)this->buildings[DAT_CurrentBuildingID::instance].x;
_gateY = (int)(short)this->buildings[DAT_CurrentBuildingID::instance].y;
local_48 = 0;
local_3c = 0;
local_44 = 0;
local_40 = 0;
_gateOwner = this->buildings[DAT_CurrentBuildingID::instance].owner;
_gateID = DAT_CurrentBuildingID::instance;
if (DAT_GameState::instance.gameTicksLoadBalancer % 10 ==
(this->buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 + 5) % 10) {
local_24[0] = 0;
local_24[1] = 0;
local_24[2] = 0;
local_24[3] = 0;
local_24[4] = 0;
local_24[5] = 0;
local_24[6] = 0;
local_24[7] = 0;
local_24[8] = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(local_48, (int)((int)(this->buildings[_gateID].widthOrHeight)));
iVar9 = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.buildingY + _gateY].
addXgetTile + DAT_TileMapState::instance.buildingX + _gateX;
uVar2 = DAT_TileMapState::instance.UnitLayer[iVar9];
_gateID = DAT_CurrentBuildingID::instance;
iVar7 = local_3c;
while (iVar8 = (int)(short)uVar2, local_3c = iVar7, iVar8 != 0) {
if (DAT_UnitsState::instance.units[iVar8].isSelectable_OR_matchTime != 0) {
iVar11 = (int)DAT_UnitsState::instance.units[iVar8].owner;
iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)((int)(short)DAT_UnitsState::instance.units[iVar8].unitType);
local_24[iVar11] = local_24[iVar11] + iVar5;
sVar3 = this->buildings[DAT_CurrentBuildingID::instance].owner;
local_3c = (int)sVar3;
_gateID = DAT_CurrentBuildingID::instance;
if ((DAT_GameState::instance.mapAndTime.playerTeams[local_3c] !=
DAT_GameState::instance.mapAndTime.playerTeams[iVar11]) && (local_3c = iVar7, sVar3 != 0)) {
local_44 = iVar11;
}
}
iVar7 = local_3c;
uVar2 = DAT_UnitsState::instance.units[iVar8].nextUnitOnTheSameTile;
}
iVar5 = 0;
iVar8 = (int)DAT_TileMapState::instance.EntityLayer[iVar9];
if (DAT_TileMapState::instance.EntityLayer[iVar9] != 0) {
while (iVar5 = iVar5 + 1, iVar5 < 10) {
EVar4 = DAT_EntityState::instance.entityArray[iVar8].entityType;
if ((((EVar4 == OpenSHC::Map::Entities::ET_FLAG_1) || (EVar4 == OpenSHC::Map::Entities::ET_FLAG_4)) || (EVar4 == OpenSHC::Map::Entities::ET_FLAG_2)) ||
(EVar4 == OpenSHC::Map::Entities::ET_FLAG_3)) {
local_40 = iVar8;
}
iVar9 = (int)DAT_EntityState::instance.entityArray[iVar8].nextEntityOnThisTileByID;
if ((iVar8 == iVar9) || (iVar8 = iVar9, iVar9 == 0)) break;
}
}
local_48 = local_48 + 1;
} while (local_48 < DAT_TileMapState::instance.constructionTileCount);
if (iVar7 == 0) {
if (local_44 == 0) goto LAB_00422948;
if (local_40 == 0) {
iVar8 = (int)this->buildings[_gateID].owner;
iVar5 = DAT_TileMapState::instance.HeightLayer
[this->buildings[_gateID].currentTilePositionAdjusted] + 0x1e;
iVar7 = (short)this->buildings[_gateID].y * 8;
iVar9 = (short)this->buildings[_gateID].x * 8;
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, (undefined4)((int)(iVar8)), (uint)((int)(iVar8)), iVar9, iVar7, iVar5, iVar9, iVar7, iVar5, OpenSHC::Map::Entities::ET_FLAG_1, 0);
_gateID = DAT_CurrentBuildingID::instance;
}
iVar7 = (int)this->buildings[_gateID].owner;
iVar9 = 0;
if (0 < local_24[1]) {
iVar7 = 1;
iVar9 = local_24[1];
}
if (iVar9 < local_24[2]) {
iVar7 = 2;
iVar9 = local_24[2];
}
if (iVar9 < local_24[3]) {
iVar7 = 3;
iVar9 = local_24[3];
}
if (iVar9 < local_24[4]) {
iVar7 = 4;
iVar9 = local_24[4];
}
if (iVar9 < local_24[5]) {
iVar7 = 5;
iVar9 = local_24[5];
}
if (iVar9 < local_24[6]) {
iVar7 = 6;
iVar9 = local_24[6];
}
if (iVar9 < local_24[7]) {
iVar7 = 7;
iVar9 = local_24[7];
}
local_3c = iVar7;
if (iVar9 < local_24[8]) {
iVar7 = 8;
local_3c = iVar7;
}
}
else {
if ((this->buildings[_gateID].field244_0x2c6 != 0) && (local_44 != 0))
goto LAB_00422948;
this->buildings[_gateID].field244_0x2c6 = 0;
local_3c = 0;
}
if ((iVar7 != 0) && (local_40 != 0)) {
iVar9 = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(iVar9, (int)((int)(this->buildings[_gateID].widthOrHeight)));
iVar5 = 0;
iVar8 = (int)DAT_TileMapState::instance.EntityLayer
[DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.buildingY + _gateY]
.addXgetTile + DAT_TileMapState::instance.buildingX + _gateX];
if (iVar8 != 0) {
while (iVar5 = iVar5 + 1, iVar5 < 10) {
EVar4 = DAT_EntityState::instance.entityArray[iVar8].entityType;
if ((((EVar4 == OpenSHC::Map::Entities::ET_FLAG_1) || (EVar4 == OpenSHC::Map::Entities::ET_FLAG_4)) || (EVar4 == OpenSHC::Map::Entities::ET_FLAG_2)) ||
(EVar4 == OpenSHC::Map::Entities::ET_FLAG_3)) {
DAT_EntityState::instance.entityArray[iVar8].colorUnk = iVar7;
}
iVar11 = (int)DAT_EntityState::instance.entityArray[iVar8].nextEntityOnThisTileByID;
if ((iVar8 == iVar11) || (iVar8 = iVar11, iVar11 == 0)) break;
}
}
iVar9 = iVar9 + 1;
_gateID = DAT_CurrentBuildingID::instance;
} while (iVar9 < DAT_TileMapState::instance.constructionTileCount);
}
if (local_3c != 0) {
if ((this->buildings[_gateID].field244_0x2c6 != local_3c) &&
(this->buildings[_gateID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID)
) {
/* 
  "We have lost control of a gatehouse my lord"
 */

MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("General_Warning19.wav");
_gateID = DAT_CurrentBuildingID::instance;
}
this->buildings[_gateID].field244_0x2c6 = (short)local_3c;
this->buildings[_gateID].gateState = 0xb;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(_gateID, TRUE, FALSE);
}
}
LAB_00422948:
iVar7 = DAT_GameState::instance.gameTicksLoadBalancer;
sVar3 = this->buildings[_gateID].field244_0x2c6;
if (sVar3 == 0) {
sVar3 = this->buildings[_gateID].gateState2;
if ((0 < sVar3) &&
(iVar9 = DAT_GameState::instance.playerDataArray[_gateOwner].enemies,
this->buildings[_gateID].gateState2 = sVar3 + -1, iVar9 == 0)) {
this->buildings[_gateID].gateState2 = 0;
}
if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray
[this->buildings[_gateID].owner] == -1) &&
(((sVar3 = this->buildings[_gateID].field244_0x2c6, sVar3 == 0 ||
(DAT_GameSynchronyState::instance.currentPlayerFullIDArray[sVar3] == -1)) &&
(DAT_GameState::instance.playerDataArray[_gateOwner].aiPlayerState == 0)))) {
this->buildings[_gateID].gateCloseOpenTimer = 0;
}
sVar3 = this->buildings[_gateID].gateCloseOpenTimer;
if (-1 < sVar3) {
if (0 < sVar3) {
this->buildings[_gateID].gateCloseOpenTimer = sVar3 + -1;
return;
}
if (iVar7 % 0x32 == this->buildings[_gateID].fireRelatedRNG1 % 0x32) {
iVar7 = DAT_GameState::instance.playerDataArray[_gateOwner].enemies;
iVar9 = 0;
if (0 < iVar7) {
psVar6 = DAT_GameState::instance.playerDataArray[_gateOwner].enemyIDArray;
paiVar10 = DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList + _gateOwner;
do {
_enemyUnitID = *psVar6;
if (((DAT_UnitsState::instance.units[_enemyUnitID].uid == (*paiVar10)[0]) &&
(DAT_UnitsState::instance.units[_enemyUnitID].unitType != OpenSHC::Map::Units::UT_LIONSHWOLF)) &&
(DAT_UnitsState::instance.units[_enemyUnitID].isSelectable_OR_matchTime != 0)) {
_enemyMicroX = (int)DAT_UnitsState::instance.units[_enemyUnitID].microXPosition;
if (_enemyMicroX < _gateX * 8) {
_enemyXDistance = _gateX * 8 - _enemyMicroX;
}
else {
_enemyXDistance = _enemyMicroX + _gateX * -8;
}
_enemyMicroY = (int)DAT_UnitsState::instance.units[_enemyUnitID].microYPosition;
if (_enemyMicroY < _gateY * 8) {
_enemyDistance = _gateY * 8 - _enemyMicroY;
}
else {
_enemyDistance = _enemyMicroY + _gateY * -8;
}
if (_enemyDistance <= _enemyXDistance) {
_enemyDistance = _enemyXDistance;
}
if (_enemyDistance < 200) {
this->buildings[_gateID].gateState2 = 1200;
if (this->buildings[_gateID].pathLinkageRelated2 != 0)
goto LAB_00422b15;
this->buildings[_gateID].gateState = 10;
this->buildings[_gateID].field235_0x2b6 = 10;
BVar12 = FALSE;
goto LAB_00422b0b;
}
}
iVar9 = iVar9 + 1;
psVar6 = psVar6 + 1;
paiVar10 = (int (*) [2500])(*paiVar10 + 1);
} while (iVar9 < iVar7);
}
if ((this->buildings[_gateID].gateState2 == 0) &&
(this->buildings[_gateID].pathLinkageRelated2 == 2)) {
this->buildings[_gateID].gateState = 0xb;
BVar12 = TRUE;
LAB_00422b0b:
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(_gateID, BVar12, FALSE);
}
LAB_00422b15:
bVar1 = this->buildings[_gateID].pathLinkageRelated2;
if (bVar1 == 0) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(_gateID, TRUE, FALSE);
return;
}
if (bVar1 == 2) {
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(_gateID, FALSE, FALSE);
}
}
}
}
else if (sVar3 == this->buildings[_gateID].owner) {
this->buildings[_gateID].field244_0x2c6 = 0;
return;
}
return;
}


}
}
}