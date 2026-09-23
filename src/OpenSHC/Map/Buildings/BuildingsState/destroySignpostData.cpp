#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040F240
void BuildingsState::destroySignpostData(int buildingID)

{
if (DAT_GameState::instance.mapAndTime.signpostIDs[0] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[0] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[0].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[0].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[0].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[0].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[1] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[1] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[1].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[1].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[1].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[1].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[2] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[2] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[2].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[2].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[2].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[2].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[3] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[3] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[3].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[3].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[3].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[3].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[4] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[4] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[4].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[4].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[4].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[4].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[5] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[5] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[5].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[5].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[5].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[5].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[6] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[6] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[6].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[6].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[6].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[6].unknown = 0;
}
if (DAT_GameState::instance.mapAndTime.signpostIDs[7] == buildingID) {
DAT_GameState::instance.mapAndTime.signpostIDs[7] = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[7].x = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[7].y = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[7].tile = 0;
DAT_GameState::instance.mapAndTime.signpostEntryData[7].unknown = 0;
}
return;
}


}
}
}