#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"



#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




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


// FUNCTION: STRONGHOLDCRUSADER 0x0041C810
undefined4 BuildingsState::lightUpBuilding(int buildingID,int burnerPlayerID,int spareGrounds)

{
int *piVar1;
int _frParam;
int _frParam_2;
int _entityID;
uint uVar2;
int _owner;
int iVar3;
int _tile;
int iVar4;
int _buildingID;
BuildingTypeShort _buildingType;

_buildingID = buildingID;
_buildingType = this->buildings[buildingID].buildingType;
switch(_buildingType) {
case OpenSHC::Map::Buildings::BT_CAMPFIRE:
case OpenSHC::Map::Buildings::BT_PARADEGROUND:
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
break;
OpenSHC::Map::Buildings::default:
if (this->buildings[buildingID].cooldownTimer != 0) {
return(undefined4)( 0);
}
}
if (this->buildings[buildingID].fireDuration == 0) {
_frParam = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID);
if ((_frParam == 0) ||
((_owner = (int)this->buildings[buildingID].owner, _owner == burnerPlayerID &&
(_frParam_2 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID), _frParam_2 != 4
)))) {
return(undefined4)( 0);
}
if (spareGrounds != 0) {
switch(_buildingType) {
case OpenSHC::Map::Buildings::BT_CAMPFIRE:
case OpenSHC::Map::Buildings::BT_PARADEGROUND:
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
goto switchD_0041c89c_caseD_33;
}
}
this->buildings[buildingID].fireDuration = 1;
this->buildings[buildingID].ifFireThenResponsiblePlayer = (ushort)burnerPlayerID;
if ((_owner == DAT_GameSynchronyState::instance.currentPlayerSlotID) &&
(piVar1 = &DAT_GameState::instance.playerDataArray[_owner].ignitionTime,
800 < (int)(DAT_GameCore::instance.mapTimeInTicks - *piVar1))) {
*piVar1 = DAT_GameCore::instance.mapTimeInTicks;
/* 
  "Buildings are on fire sire"
 */

MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("General_Warning16.wav");
}
iVar4 = (int)(short)this->buildings[buildingID].x;
iVar3 = (int)(short)this->buildings[buildingID].y;
buildingID = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(buildingID, (int)((int)(
this->buildings[_buildingID].widthOrHeight)));
_tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.buildingY + iVar3].
addXgetTile + DAT_TileMapState::instance.buildingX + iVar4;
_entityID = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(_tile);
if ((_entityID == 0) &&
(uVar2 = MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(burnerPlayerID, (DAT_TileMapState::instance.buildingX + iVar4) * 8, 
(DAT_TileMapState::instance.buildingY + iVar3) * 8, (int)((int)(
DAT_TileMapState::instance.HeightLayer[_tile] - 8)), 2), uVar2 != 0)) {
DAT_EntityState::instance.entityArray[uVar2].someTracker = -(SEC_RNG::instance.currentNumber2 % 0x78);
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
}
buildingID = buildingID + 1;
} while (buildingID < DAT_TileMapState::instance.constructionTileCount);
}
switchD_0041c89c_caseD_33:
return(undefined4)( 1);
}


}
}
}