#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"



#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040E040
void BuildingsState::setupEngineersGuildParagroundPositions(int playerID)

{
Building * _pBuilding;
short *_pOffsets;
int _counter;
short *_pParagroundPositions;
int _paradegroundID;
int _id;
ushort _x;
ushort _y;

_paradegroundID = 0;
MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(100, '\0', (void *)((int)(
DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations)));
_id = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id;
DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocationsTotal = 0;
if ((0 < _id) && (_counter = 1, 1 < this->maxBuildingsCount)) {
_pBuilding = &this->buildings[1];
do {
if ((((_pBuilding->logicalState != ((BuildingLogicalState)0)) && (_pBuilding->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE))
&& (_pBuilding->owner == playerID)) &&
(_pBuilding->buildingType == OpenSHC::Map::Buildings::BT_PARADEGROUND)) {
_paradegroundID = _counter;
}
_counter = _counter + 1;
_pBuilding = _pBuilding + 0x196;
} while (_counter < this->maxBuildingsCount);
if (_paradegroundID != 0) {
DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocationsTotal = 25;
_x = this->buildings[_paradegroundID].x;
_y = this->buildings[_paradegroundID].y;
_pOffsets = &DAT_BuildingDefinedData::instance.EngineersParagroundOffsets[0].y;
_pParagroundPositions =
&DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[0].y;
do {
((XYPairShort *)(_pParagroundPositions + -1))->x = ((XYPairShort *)(_pOffsets + -1))->x + _x
;
*_pParagroundPositions = *_pOffsets + _y;
_pOffsets = _pOffsets + 2;
_pParagroundPositions = _pParagroundPositions + 2;
} while ((int)_pOffsets < 0x5c197e);
}
}
return;
}


}
}
}