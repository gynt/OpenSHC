#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"





namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Buildings::BuildingType;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040B5D0
void BuildingsState::setBuildingInitialEntryTileTry(int buildingID,undefined4 param_2)

{
int _direction;
BuildingTypeShort _buildingType;
short _var;

_var = this->buildings[buildingID].buildingVariation;
if (_var == 0xf) {
_buildingType = this->buildings[buildingID].buildingType;
_direction = 4;
if ((_buildingType == OpenSHC::Map::Buildings::BT_TUNNEL) || (_buildingType == OpenSHC::Map::Buildings::BT_UNKNOWN4)) {
_direction = 2;
}
if (_buildingType == OpenSHC::Map::Buildings::BT_OXTETHER) {
_direction = 4;
goto LAB_0040b630;
}
}
else {
_direction = _var + 4;
}
if (7 < _direction) {
_direction = _direction + -8;
}
LAB_0040b630:
_buildingType = this->buildings[buildingID].buildingType;
this->buildings[buildingID].entranceAttemptTileIndex =
(short)(_direction / 2) *
((short)this->buildings[buildingID].widthOrHeight + (short)param_2 * 2);
if (_buildingType == OpenSHC::Map::Buildings::BT_OXTETHER) {
this->buildings[buildingID].entranceAttemptTileIndex = 9;
}
return;
}


}
}
}