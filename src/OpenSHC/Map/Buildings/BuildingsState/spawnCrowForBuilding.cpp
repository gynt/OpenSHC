#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"



#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {
namespace Buildings {

using OpenSHC::Map::Entities::EntityType;


/* 
  WARNING: Enum "MappersEnum": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0040A260
int BuildingsState::spawnCrowForBuilding(int buildingID)

{
BuildingTypeShort BVar1;
int iVar2;
uint _rngDiv5;
int iVar3;
int _rng;
int _buildingMicroX;
int _microY;
int _microX;
int _buildingMicroY;

iVar2 = buildingID;
BVar1 = this->buildings[buildingID].buildingType;
_rngDiv5 = (int)(short)BVar1 - 0x31;
switch(BVar1) {
case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
case OpenSHC::Map::Buildings::BT_TUNNEL:
case OpenSHC::Map::Buildings::BT_CAMPFIRE:
case OpenSHC::Map::Buildings::BT_SIGNPOST:
case OpenSHC::Map::Buildings::BT_PARADEGROUND:
case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
case OpenSHC::Map::Buildings::BT_CAMPGROUND:
case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
case OpenSHC::Map::Buildings::BT_KILLINGPIT:
case OpenSHC::Map::Buildings::BT_CATAPULT:
case OpenSHC::Map::Buildings::BT_TREBUCHET:
case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
case OpenSHC::Map::Buildings::BT_SIEGETOWER:
case OpenSHC::Map::Buildings::BT_SHIELD:
case OpenSHC::Map::Buildings::BT_UNKNOWN4:
case OpenSHC::Map::Buildings::BT_DANCINGBEAR:
break;
OpenSHC::Map::Buildings::default:
iVar3 = (int)this->buildings[buildingID].widthOrHeight / 2;
_buildingMicroY = ((short)this->buildings[buildingID].y + iVar3) * 8;
_buildingMicroX = ((short)this->buildings[buildingID].x + iVar3) * 8;
MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0, _buildingMicroX, _buildingMicroY, (int)((int)(
(uint)DAT_TileMapState::instance.DefaultHeightLayer
[this->buildings[buildingID].currentTilePositionAdjusted])), 
_buildingMicroX + 1, _buildingMicroY + 1, (int)((int)(
(uint)DAT_TileMapState::instance.DefaultHeightLayer
[this->buildings[buildingID].currentTilePositionAdjusted])), OpenSHC::Map::Entities::0x1e, 0);
buildingID = 0;
do {
MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(buildingID, (int)((int)(this->buildings[iVar2].widthOrHeight)));
_rng = (int)(short)DAT_TileMapState::instance.RandomLayer
[DAT_ViewportRenderState::instance.translationMatrix
[(short)this->buildings[iVar2].y + DAT_TileMapState::instance.buildingY
].addXgetTile + (int)(short)this->buildings[iVar2].x +
DAT_TileMapState::instance.buildingX];
_rngDiv5 = _rng / 5;
if (_rng % 5 == 0) {
_microY = ((short)this->buildings[iVar2].y + DAT_TileMapState::instance.buildingY) * 8;
_microX = ((short)this->buildings[iVar2].x + DAT_TileMapState::instance.buildingX) * 8;
_rngDiv5 = MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0, 0, 0, _microX, _microY, (int)((int)(
(uint)DAT_TileMapState::instance.DefaultHeightLayer
[this->buildings[iVar2].currentTilePositionAdjusted
])), _microX + 1, _microY + 1, (int)((int)(
(uint)DAT_TileMapState::instance.DefaultHeightLayer
[this->buildings[iVar2].currentTilePositionAdjusted
])), OpenSHC::Map::Entities::0x1e, -((_rng >> 4) % 0x14));
}
buildingID = buildingID + 1;
} while (buildingID < DAT_TileMapState::instance.constructionTileCount);
}
return(int)( _rngDiv5);
}


}
}
}