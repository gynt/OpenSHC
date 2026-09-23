#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Commands::MappersEnum;


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


// FUNCTION: STRONGHOLDCRUSADER 0x0040CAC0
uint BuildingsState::hasEnoughGoldForMoat()

{
int _pGold;
int local_4;

MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, this)(OpenSHC::Commands::M_MAPPER_MOAT, &local_4, &_pGold);
return (uint)(((DAT_TileMapState::instance.moatTileCount -
DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
moatTileCount) + 1) * _pGold <=
DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].
startResources[0xf]);
}


}
}
}