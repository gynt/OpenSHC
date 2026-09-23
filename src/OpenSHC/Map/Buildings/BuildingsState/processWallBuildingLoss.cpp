#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"



#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Game::GameMode2;
using OpenSHC::Game::Resources::ResourceType;


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


// FUNCTION: STRONGHOLDCRUSADER 0x0041C190
void BuildingsState::processWallBuildingLoss(int playerID,int highCount,int lowCount,int zero)

{
uint _fullAmount;
int _amount;
byte *_ptrPartial;

if ((DAT_GameCore::instance.solitaryAllBuildingsAreFree == FALSE) && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR))
{
if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
DAT_TileMapState::instance.wallPlacementCost = highCount;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(playerID, OpenSHC::Game::Resources::RT_STONE, highCount, zero);
return;
}
_ptrPartial = &DAT_GameState::instance.playerDataArray[playerID].partialStoneCounter;
/* 
  total amount is the amount of low wall tiles, the amount of high wall tiles,
   and the part we should have added last time but wasnt processed because
   actual cost is divided by 4
 */

_fullAmount = lowCount + highCount * 2 + *(int *)_ptrPartial;
if (zero == 0) {
*(uint *)_ptrPartial = _fullAmount &3;
}
/* 
  fullAmount / 4 (signed division)
 */

_amount = (int)(_fullAmount + ((int)_fullAmount >> 0x1f &3U)) >> 2;
DAT_TileMapState::instance.wallPlacementCost = _amount;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(playerID, OpenSHC::Game::Resources::RT_STONE, _amount, zero);
if (((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) && (zero == 0)) && (_amount != 0))
{
DAT_WallAndPitchState::instance.flag = zero;
DAT_WallAndPitchState::instance.counter = _amount;
}
}
return;
}


}
}
}