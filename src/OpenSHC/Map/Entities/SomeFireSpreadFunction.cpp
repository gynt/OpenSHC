#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Buildings::BuildingType;
    using Map::Buildings::BuildingTypeShort;
    using Map::Entities::EntityType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00405130
    uint Entities::SomeFireSpreadFunction(int param_1, int x, int y, int param_4, int param_5)
    {
        uint _y;
        int _entityID;
        uint _fireEntityID;
        uint _x;
        int microY;
        uint _rng;
        int _tile;
        int microX;
        short _buildingID;
        BuildingTypeShort _buildingType;
        _rng = (uint)SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        microX = x + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[_rng & 0x3f][0];
        microY = y + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[_rng & 0x3f][1];
        _x = microX / 8;
        _y = microY / 8;
        if (((399 < _x) || (399 < _y)) || (*(char*)(_y * 400 + 0x21aec98 + _x) == '\0')) {
            return 0;
        }
        _tile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x;
        _rng = DAT_TileMapState::instance.LogicLayer[_tile];
        if (!(_rng & 0x10300131)) {
            _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
            if (_buildingID) {
                _buildingType = DAT_BuildingsState::instance.buildings[_buildingID].buildingType;
                if (((_buildingType != Map::Buildings::BT_TUNNEL)
                        && (_buildingType != Map::Buildings::BT_KILLINGPIT))
                    && (_buildingType != Map::Buildings::BT_UNKNOWN4)) {
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::lightUpBuilding,
                        DAT_BuildingsState::ptr)((int)_buildingID, param_1, 0);
                    return 0;
                }
            }
            _entityID = MACRO_CALL_MEMBER(
                Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(_tile);
            if (!_entityID) {
                if ((_rng & 0x1000)) {
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(
                        _tile, param_1);
                }
                _fireEntityID = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, (undefined4)((int)(param_1)), 0, microX, microY, param_4, 0, 0, 0,
                    Map::Entities::ET_FIRE, 0);
                if ((2 < param_5) && (!(DAT_TileMapState::instance.RandomLayer[_tile] & 3))) {
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                        DAT_EntityState::ptr)(0, (undefined4)((int)(param_1)), 0, microX, microY, param_4, 0, 0, 0,
                        Map::Entities::EntityTypeInt__ET_EXPLOSION, 0);
                }
                if (_fireEntityID) {
                    DAT_EntityState::instance.entityArray[_fireEntityID].fireParameter_0xb6 = (short)param_5;
                }
                return _fireEntityID;
            }
            _buildingID = DAT_EntityState::instance.entityArray[_entityID].fireParameter_0xb6;
            DAT_EntityState::instance.entityArray[_entityID].someTracker = 0;
            if (_buildingID < param_5) {
                DAT_EntityState::instance.entityArray[_entityID].fireParameter_0xb6 = (short)param_5;
            }
            DAT_EntityState::instance.entityArray[_entityID].unknownAnimationFrameRelated = 0;
        }
        return 0;
    }

}
}
