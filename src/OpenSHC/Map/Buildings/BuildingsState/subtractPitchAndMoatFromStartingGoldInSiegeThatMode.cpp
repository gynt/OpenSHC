#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"



#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Game::GameMode2;
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


// FUNCTION: STRONGHOLDCRUSADER 0x0040C9F0
void BuildingsState::subtractPitchAndMoatFromStartingGoldInSiegeThatMode()

{
PitchDitch * _ptrPlayerID;
int _pitchDitchCount;
int local_8;
int local_4;
int _moatTileCount;
int _playerID;
int *_ptrStartingGold;

if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
_pitchDitchCount = 0;
_ptrPlayerID = &DAT_TileMapState::instance.pitchDitches[2];
do {
if (_ptrPlayerID[-10] != 0) {
_pitchDitchCount = _pitchDitchCount + 1;
}
if (_ptrPlayerID->owner != 0) {
_pitchDitchCount = _pitchDitchCount + 1;
}
if (_ptrPlayerID[10] != 0) {
_pitchDitchCount = _pitchDitchCount + 1;
}
_ptrPlayerID = _ptrPlayerID + 0x1e;
} while ((int)_ptrPlayerID < 0x1fe5b28);
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, this)(OpenSHC::Commands::M_MAPPER_MOAT, &local_4, &local_8);
_moatTileCount = DAT_TileMapState::instance.moatTileCount;
_playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
_ptrStartingGold =
DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].startResources +
0xf;
*_ptrStartingGold =
*_ptrStartingGold -
(DAT_TileMapState::instance.moatTileCount -
DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].moatTileCount) *
local_8;
MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingCost, this)(OpenSHC::Commands::M_MAPPER_PITCH_DITCH, &local_4, &local_8);
_ptrStartingGold = DAT_GameState::instance.playerDataArray[_playerID].startResources + 0xf;
*_ptrStartingGold =
*_ptrStartingGold -
(_pitchDitchCount - DAT_GameState::instance.playerDataArray[_playerID].pitchDitchTileCount) * local_8
;
DAT_GameState::instance.playerDataArray[_playerID].pitchDitchTileCount = (short)_pitchDitchCount;
DAT_GameState::instance.playerDataArray[_playerID].moatTileCount = (short)_moatTileCount;
}
return;
}


}
}
}