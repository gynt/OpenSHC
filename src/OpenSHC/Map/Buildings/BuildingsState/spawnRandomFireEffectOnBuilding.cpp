#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"



#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Entities::EntityType;
using OpenSHC::DE::SHCDE::eSFX;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00410800
void BuildingsState::spawnRandomFireEffectOnBuilding(int buildingID,undefined4 playerID)

{
int iVar1;
int iVar2;
int _microX;
int _microY;
short _fireDuration;
uint _width;

_fireDuration = this->buildings[buildingID].fireDuration;
if (399 < _fireDuration) {
_width = this->buildings[buildingID].widthOrHeight;
if ((int)_width < 4) {
iVar2 = _width * -5 + 0x18;
iVar1 = this->buildings[buildingID].fireRelatedRNG1 + (int)_fireDuration;
}
else {
iVar1 = this->buildings[buildingID].fireRelatedRNG1 + (int)_fireDuration;
iVar2 = 8;
if (6 < (int)_width) {
iVar2 = 0x10;
}
iVar2 = (iVar2 - _width) * 5;
}
if (iVar1 % iVar2 == 0) {
_width = this->buildings[buildingID].widthOrHeight;
_microX = ((int)SEC_RNG::instance.currentNumber2 % (int)_width +
(int)(short)this->buildings[buildingID].x) * 8;
_microY = (((int)SEC_RNG::instance.currentNumber2 >> 8) % (int)_width +
(int)(short)this->buildings[buildingID].y) * 8;
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(5, (undefined4)((int)(playerID)), 0, _microX, _microY, (int)((int)(
(uint)DAT_TileMapState::instance.HeightLayer
[this->buildings[buildingID].currentTilePositionAdjusted])), 
_microX, _microY, (int)((int)(
(uint)DAT_TileMapState::instance.HeightLayer
[this->buildings[buildingID].currentTilePositionAdjusted])), ((EntityType)0x20), 0
);
MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
if (((byte)SEC_RNG::instance.currentNumber1 &1) != 0) {
MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)((int)(_microX + (_microX >> 0x1f &7U)) >> 3, 
(int)(_microY + (_microY >> 0x1f &7U)) >> 3, OpenSHC::DE::SHCDE::FX_FIRE_POP);
}
}
}
return;
}


}
}
}