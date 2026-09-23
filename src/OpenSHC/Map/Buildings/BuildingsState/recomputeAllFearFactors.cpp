#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingLogicalState;
using OpenSHC::Map::Buildings::BuildingType;
using OpenSHC::Map::Units::UnitLogicState;


/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B260
void BuildingsState::recomputeAllFearFactors()

{
int _goodOrBad;
int *_pGoodBadPlayerData;
int _goodMinusBadCount;
int _fearFactorLevel;
int _ceilingPopDiv16;
Building * _pBuilding;
PlayerData * _pPlayerData;
int _buildingIndex;
int _playerIndex;
int _lordID;
int _fearFactorLevel2;
BuildingTypeShort _buildingType;

_buildingIndex = 1;
DAT_GameState::instance.playerDataArray[1].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[1].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[1].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[2].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[2].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[2].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[3].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[3].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[3].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[4].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[4].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[4].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[5].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[5].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[5].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[6].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[6].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[6].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[7].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[7].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[7].fearFactorLevel = 0;
DAT_GameState::instance.playerDataArray[8].badStuffCount = 0;
DAT_GameState::instance.playerDataArray[8].goodStuffCount = 0;
DAT_GameState::instance.playerDataArray[8].fearFactorLevel = 0;
if (1 < this->maxBuildingsCount) {
_pBuilding = &this->buildings[1];
do {
if ((_pBuilding->logicalState != ((BuildingLogicalState)0)) && (_pBuilding->logicalState != OpenSHC::Map::Buildings::BLS_REMOVE)) {
_buildingType = _pBuilding->buildingType;
if (_buildingType == OpenSHC::Map::Buildings::BT_GALLOWS) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_STOCKS) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_WITCHHOIST) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_CESSPIT) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_BURNINGSTAKE) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_GIBBET) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_DUNGEON) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_STRETCHINGRACK) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_RACKFLOGGING) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK) {
_goodOrBad = -1;
}
else if (_buildingType == OpenSHC::Map::Buildings::BT_DUNKINGSTOOL) {
_goodOrBad = -1;
}
else {
if ((((_buildingType != OpenSHC::Map::Buildings::BT_MAYPOLE) && (_buildingType != OpenSHC::Map::Buildings::BT_GARDEN)) &&
(_buildingType != OpenSHC::Map::Buildings::BT_STATUE)) &&
((_buildingType != OpenSHC::Map::Buildings::BT_SHRINE && (_buildingType != OpenSHC::Map::Buildings::BT_DANCINGBEAR)))) goto LAB_0040b3f3;
_goodOrBad = 1;
}
if (_goodOrBad < 0) {
_pGoodBadPlayerData = &DAT_GameState::instance.playerDataArray[_pBuilding->owner].badStuffCount
;
}
else {
if (_goodOrBad < 1) goto LAB_0040b3f3;
_pGoodBadPlayerData =
&DAT_GameState::instance.playerDataArray[_pBuilding->owner].goodStuffCount;
}
*_pGoodBadPlayerData = *_pGoodBadPlayerData + 1;
}
LAB_0040b3f3:
_buildingIndex = _buildingIndex + 1;
_pBuilding = _pBuilding + 0x196;
} while (_buildingIndex < this->maxBuildingsCount);
}
_playerIndex = 1;
_pPlayerData = &DAT_GameState::instance.playerDataArray[1];
do {
/* 
  result = ceiling(currentPopulation/16)
 */

_ceilingPopDiv16 =
((int)(_pPlayerData->currentPopulation +
(_pPlayerData->currentPopulation >> 0x1f &0xfU)) >> 4) + 1;
_goodMinusBadCount = _pPlayerData->goodStuffCount - _pPlayerData->badStuffCount;
if (_goodMinusBadCount < 0) {
_fearFactorLevel = -(-_goodMinusBadCount / _ceilingPopDiv16);
_pPlayerData->fearFactorLevel = _fearFactorLevel;
_pPlayerData->objectsLeftUntilNextLevel =
_ceilingPopDiv16 - -_goodMinusBadCount % _ceilingPopDiv16;
if (_fearFactorLevel < -5) {
_pPlayerData->fearFactorLevel = -5;
}
}
else if (_goodMinusBadCount < 1) {
_pPlayerData->objectsLeftUntilNextLevel = 0;
}
else {
_pPlayerData->fearFactorLevel = _goodMinusBadCount / _ceilingPopDiv16;
_pPlayerData->objectsLeftUntilNextLevel =
_ceilingPopDiv16 - _goodMinusBadCount % _ceilingPopDiv16;
if (5 < _goodMinusBadCount / _ceilingPopDiv16) {
_pPlayerData->fearFactorLevel = 5;
}
}
_lordID = _pPlayerData->lordID;
if (((_lordID != 0) && (_pPlayerData->lordUID == DAT_UnitsState::instance.units[_lordID].uid)) &&
(DAT_UnitsState::instance.units[_lordID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)) {
_fearFactorLevel2 = _pPlayerData->fearFactorLevel;
if (_fearFactorLevel2 < 1) {
if ((_fearFactorLevel2 < 0) &&
(_fearFactorLevel2 <
(char)DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[_playerIndex])) {
DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[_playerIndex] =
(byte)_fearFactorLevel2;
}
}
else if ((char)DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[_playerIndex] <
_fearFactorLevel2) {
DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[_playerIndex] =
(byte)_fearFactorLevel2;
}
}
_pPlayerData = _pPlayerData + 0xe7d;
_playerIndex = _playerIndex + 1;
} while ((int)_pPlayerData < 0x117e8c0);
return;
}


}
}
}