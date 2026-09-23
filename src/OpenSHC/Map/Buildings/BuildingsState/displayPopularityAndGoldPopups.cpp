#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Entities::EntityType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


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


// FUNCTION: STRONGHOLDCRUSADER 0x0040A060
void BuildingsState::displayPopularityAndGoldPopups(int buildingID,int param_2,int param_3,undefined4 param_4)

{
int *piVar1;
int iVar2;
BOOLEnum BVar3;
int iVar4;
uint _id;
int iVar5;
int _playerID;
EntityType entityType;
int _buildingID;
int _currentGold;

_buildingID = buildingID;
_playerID = (int)this->buildings[buildingID].owner;
if (_playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
return;
}
switch(this->buildings[buildingID].buildingType) {
case OpenSHC::Map::Buildings::BT_MARKETPLACE:
buildingID = 0x50;
entityType = (param_2 != 0) + OpenSHC::Map::Entities::0x2a;
break;
case OpenSHC::Map::Buildings::BT_WELL:
case OpenSHC::Map::Buildings::BT_OILSMELTER:
case OpenSHC::Map::Buildings::BT_SIEGETENT:
case OpenSHC::Map::Buildings::BT_WHEATFARM:
case OpenSHC::Map::Buildings::BT_HOPFARM:
case OpenSHC::Map::Buildings::BT_APPLEFARM:
case OpenSHC::Map::Buildings::BT_DAIRYFARM:
case OpenSHC::Map::Buildings::BT_MILL:
case OpenSHC::Map::Buildings::BT_STABLES:
case OpenSHC::Map::Buildings::BT_CHAPEL:
case OpenSHC::Map::Buildings::BT_CHURCH:
case OpenSHC::Map::Buildings::BT_CATHEDRAL:
case OpenSHC::Map::Buildings::BT_UNKNOWN1:
case OpenSHC::Map::Buildings::BT_KEEPFOUR:
case OpenSHC::Map::Buildings::BT_KEEPFIVE:
case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
case OpenSHC::Map::Buildings::BT_WOODGATE1:
case OpenSHC::Map::Buildings::BT_WOODGATE2:
case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
case OpenSHC::Map::Buildings::BT_TUNNEL:
case OpenSHC::Map::Buildings::BT_CAMPFIRE:
case OpenSHC::Map::Buildings::BT_SIGNPOST:
case OpenSHC::Map::Buildings::BT_PARADEGROUND:
case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
goto switchD_0040a09e_caseD_1b;
case OpenSHC::Map::Buildings::BT_MANORHOUSE:
case OpenSHC::Map::Buildings::BT_STONEKEEP:
case OpenSHC::Map::Buildings::BT_STRONGHOLD:
entityType = ((EntityType)0x28);
buildingID = 0x78;
break;
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
entityType = ((EntityType)0x29);
buildingID = 0x28;
break;
OpenSHC::Map::Buildings::default:
return;
}
BVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::playerHasEntityOfType, DAT_EntityState::ptr)((int)this->buildings[_buildingID].owner, 
entityType);
if (BVar3 == FALSE) {
iVar5 = (int)(short)this->buildings[_buildingID].x;
iVar4 = (int)this->buildings[_buildingID].widthOrHeight / 2;
iVar2 = (short)this->buildings[_buildingID].y + iVar4;
_id = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, (undefined4)((int)((int)this->buildings[_buildingID].owner)), 0, 
(iVar5 + iVar4) * 8, iVar2 * 8, 
(uint)DAT_TileMapState::instance.HeightLayer
[DAT_ViewportRenderState::instance.translationMatrix[iVar2].addXgetTile + iVar5 +
iVar4] + buildingID, 0, 0, 0, entityType, 0);
if (_id != 0) {
if (entityType == ((EntityType)0x28)) {
_currentGold = DAT_GameState::instance.playerDataArray[_playerID].currentResources[0xf];
piVar1 = &DAT_EntityState::instance.entityArray[_id].displayValue;
*piVar1 = _currentGold;
if (_currentGold < 0) {
*piVar1 = 0;
return;
}
}
else {
if (entityType == ((EntityType)0x29)) {
DAT_EntityState::instance.entityArray[_id].displayValue =
DAT_GameState::instance.playerDataArray[_playerID].popularity / 100;
return;
}
if (entityType == OpenSHC::Map::Entities::0x2a) {
DAT_EntityState::instance.entityArray[_id].displayValue = param_3;
DAT_EntityState::instance.entityArray[_id].field83_0xc0 = (short)param_4 * 2 + 0x8d;
return;
}
if (entityType == OpenSHC::Map::Entities::0x2b) {
DAT_EntityState::instance.entityArray[_id].displayValue = param_3;
DAT_EntityState::instance.entityArray[_id].field83_0xc0 = (short)param_4 * 2 + 0x8d;
}
}
}
}
switchD_0040a09e_caseD_1b:
return;
}


}
}
}