#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004036F0
        void EntityState::calculateEntityDrawOffset(int entityID)
        {
            int subTileX = (byte)this->entityArray[entityID].microX & 7;
            int subTileY = (byte)this->entityArray[entityID].microY & 7;
            if (DAT_TileMapState::instance.mapOrientation == 4) {
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
            }
            else if (DAT_TileMapState::instance.mapOrientation == 2) {
                subTileX = 7 - subTileX;
                subTileX = subTileX << 4;
                subTileY = subTileY * 2;
                goto lookup;
            }
            else if (DAT_TileMapState::instance.mapOrientation == 6) {
                subTileY = 7 - subTileY;
                subTileX = subTileX << 4;
                subTileY = subTileY * 2;
                goto lookup;
            }
            else if (DAT_TileMapState::instance.mapOrientation != 0) {
                subTileX = subTileX << 4;
                subTileY = subTileY * 2;
                goto lookup;
            }
            subTileX = subTileX * 2;
            subTileY = subTileY << 4;
        lookup:
            this->entityArray[entityID].x1
                = DAT_EntityDefinedData::instance.microPosDrawOffsets[subTileY + subTileX].x;
            this->entityArray[entityID].y1
                = DAT_EntityDefinedData::instance.microPosDrawOffsets[subTileY + subTileX + 1].x;
        }

    }
}
}
