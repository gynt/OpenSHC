#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"



#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Units::States::UnitState;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004106D0
void BuildingsState::processDamageToUnitsOnBuilding(int buildingID,int damageBonus)

{
short _healthPercentage;
int _damage;
int _buildingSizeTileIndex;
uint _buildingWidthOrHeight;
int _currentUnitID;
int _maxHealth;
int *_ptrHealth;
ushort _unitID;
ushort _x;
ushort _y;

_x = this->buildings[buildingID].x;
_buildingSizeTileIndex = 0;
_buildingWidthOrHeight = this->buildings[buildingID].widthOrHeight;
_y = this->buildings[buildingID].y;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(_buildingSizeTileIndex, (int)((int)(_buildingWidthOrHeight)));
_unitID = DAT_TileMapState::instance.UnitLayer
[DAT_ViewportRenderState::instance.translationMatrix[(short)_y + DAT_TileMapState::instance.buildingY].
addXgetTile + DAT_TileMapState::instance.buildingX + (int)(short)_x];
while (_currentUnitID = (int)(short)_unitID, _currentUnitID != 0) {
_maxHealth = DAT_UnitsState::instance.units[_currentUnitID].maxHealth;
_damage = (int)((ulonglong)((longlong)(_maxHealth * damageBonus) * -0x51eb851f) >> 0x20);
_ptrHealth = &DAT_UnitsState::instance.units[_currentUnitID].health;
*_ptrHealth = *_ptrHealth + ((_damage >> 5) - (_damage >> 0x1f));
if (DAT_UnitsState::instance.units[_currentUnitID].health < 1) {
DAT_UnitsState::instance.units[_currentUnitID].health = 0;
DAT_UnitsState::instance.units[_currentUnitID].dying = 1;
DAT_UnitsState::instance.units[_currentUnitID].animationCycleNumber = 0;
DAT_UnitsState::instance.units[_currentUnitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
}
if (_maxHealth == 0) {
_healthPercentage = 100;
}
else {
_healthPercentage =
(short)((DAT_UnitsState::instance.units[_currentUnitID].health * 100) / _maxHealth);
}
DAT_UnitsState::instance.units[_currentUnitID].healthPercentage = _healthPercentage;
DAT_UnitsState::instance.units[_currentUnitID].healthbar =
(_healthPercentage / 10 + (_healthPercentage >> 0xf)) -
(short)((longlong)(int)_healthPercentage * 0x66666667 >> 0x3f);
_unitID = DAT_UnitsState::instance.units[_currentUnitID].nextUnitOnTheSameTile;
}
_buildingSizeTileIndex = _buildingSizeTileIndex + 1;
} while (_buildingSizeTileIndex < DAT_TileMapState::instance.constructionTileCount);
return;
}


}
}
}