#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00401570
        int EntityState::updateAllFireEntitiesAtTile(int tile)
        {
            int _nextTile;
            int _tile;
            int _to10;
            _to10 = 0;
            _tile = (int)DAT_TileMapState::instance.EntityLayer[tile];
            if (DAT_TileMapState::instance.EntityLayer[tile] != 0) {
                while (_to10 = _to10 + 1, _to10 < 10) {
                    if (this->entityArray[_tile].entityType == OpenSHC::Map::Entities::ET_FIRE) {
                        this->entityArray[_tile].someTracker = 2;
                        this->entityArray[_tile].fireParameter_0xb6 = 1;
                        this->entityArray[_tile].unknownAnimationFrameRelated = 0;
                    }
                    _nextTile = (int)this->entityArray[_tile].nextEntityOnThisTileByID;
                    if (_tile == _nextTile) {
                        return 0;
                    }
                    _tile = _nextTile;
                    if (_nextTile == 0) {
                        return 0;
                    }
                }
            }
            return 0;
        }

    }
}
}
