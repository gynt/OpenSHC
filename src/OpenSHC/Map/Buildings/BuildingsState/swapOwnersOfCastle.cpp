#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Game::GameMode;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0041A8D0
void BuildingsState::swapOwnersOfCastle(int param_1,int param_2)

{
bool bVar1;
Building * psVar10;
int iVar2;

bVar1 = false;
psVar10 = &this->buildings[1];
iVar2 = 1999;
do {
if (psVar10->logicalState == OpenSHC::Map::Buildings::BLS_NORMAL) {
if (psVar10->owner == param_1) {
psVar10->owner = (short)param_2;
bVar1 = true;
if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
psVar10->playerColorUnk = param_2;
}
}
else if (psVar10->owner == param_2) {
psVar10->owner = (short)param_1;
bVar1 = true;
if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
psVar10->playerColorUnk = param_1;
}
}
}
psVar10 = psVar10 + 0x196;
iVar2 = iVar2 + -1;
} while (iVar2 != 0);
if (bVar1) {
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].keep.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].keep.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].keep.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].keep.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].keep.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].keep.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].keep.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].keep.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].keep.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].keep.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].marketplace.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].marketplace.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].marketplace.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].marketplace.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].marketplace.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].marketplace.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].marketplace.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].marketplace.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].marketplace.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].marketplace.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].engineersGuild.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].engineersGuild.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].tunnelersGuild.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].tunnelersGuild.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].stockpile.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].stockpile.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].stockpile.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].stockpile.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].stockpile.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].stockpile.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].stockpile.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].stockpile.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].stockpile.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].stockpile.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].armory.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].armory.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].armory.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].armory.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].armory.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].armory.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].armory.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].armory.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].armory.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].armory.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].granary.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].granary.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].granary.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].granary.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].granary.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].granary.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].granary.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].granary.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].granary.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].granary.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].barracks.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].barracks.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].barracks.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].barracks.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].barracks.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].barracks.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].barracks.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].barracks.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].barracks.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].barracks.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].mercenaryPost.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].mercenaryPost.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].campground.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].campground.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].campground.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].campground.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].campground.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].campground.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].campground.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].campground.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].campground.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].campground.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].unknown6.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].unknown6.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].unknown6.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].unknown6.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].unknown6.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].unknown6.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].unknown6.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].unknown6.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].unknown6.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].unknown6.areaEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.id, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.id)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.xEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.xEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.yEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.yEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.tileEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.tileEntry)));
MACRO_CALL(OpenSHC::IO_Func::SwapInts)(&DAT_GameState::instance.playerDataArray[param_2].oilSmelter.areaEntry, (undefined4 *)((int)(
&DAT_GameState::instance.playerDataArray[param_1].oilSmelter.areaEntry)));
}
return;
}


}
}
}