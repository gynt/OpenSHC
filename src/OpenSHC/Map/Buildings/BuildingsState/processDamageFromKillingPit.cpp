#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"



#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Units::UnitType;
using OpenSHC::Game::GameMode2;
using OpenSHC::Map::Buildings::BuildingType;
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


// FUNCTION: STRONGHOLDCRUSADER 0x00419800
void BuildingsState::processDamageFromKillingPit(int unitID)

{
int *piVar1;
UnitTypeShort UVar2;
short sVar3;
int _buildingID;
int iVar4;

_buildingID = (int)(short)DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile];
if (((((_buildingID != 0) && (UVar2 = DAT_UnitsState::instance.units[unitID].unitType, UVar2 != OpenSHC::Map::Units::UT_TRADER))
&& (UVar2 != OpenSHC::Map::Units::UT_TRADERHORSE)) &&
((((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER ||
(this->buildings[_buildingID].owner ==
DAT_GameSynchronyState::instance.currentPlayerSlotID)) ||
(DAT_UnitsState::instance.units[unitID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID)) &&
((this->buildings[_buildingID].buildingType == OpenSHC::Map::Buildings::BT_KILLINGPIT &&
(this->buildings[_buildingID].state == 0)))))) &&
((DAT_UnitsState::instance.units[unitID].isStalked == 0 &&
((DAT_GameState::instance.mapAndTime.playerTeams[this->buildings[_buildingID].owner] !=
DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[unitID].owner] &&
(DAT_UnitsState::instance.units[unitID].dying == 0)))))) {
piVar1 = &DAT_UnitsState::instance.units[unitID].health;
*piVar1 = *piVar1 + -18000;
if (DAT_UnitsState::instance.units[unitID].health < 1) {
DAT_UnitsState::instance.units[unitID].health = 0;
DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
DAT_UnitsState::instance.units[unitID].dying = 1;
DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging = 1;
}
iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage, DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].health, 
DAT_UnitsState::instance.units[unitID].maxHealth);
sVar3 = (short)iVar4;
DAT_UnitsState::instance.units[unitID].healthPercentage = sVar3;
DAT_UnitsState::instance.units[unitID].healthbar =
(sVar3 / 10 + (sVar3 >> 0xf)) - (short)((longlong)(int)sVar3 * 0x66666667 >> 0x3f);
this->buildings[_buildingID].state = 1;
}
return;
}


}
}
}