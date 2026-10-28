#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401460
        void EntityState::unlinkEntityFromTile(uint entityID)
        {
            uint nextEntityID;
            uint currentEntityID;
            uint prevEntityID;
            int guardCounter = 0;
            int tile = this->entityArray[entityID].tile;
            int guardCounter2 = 0;
            if (tile != 0) {
                if ((int)entityID < 25) {
                    prevEntityID = DAT_TileMapState::instance.EntityLayerLT25[tile];
                    if (prevEntityID == entityID) {
                        DAT_TileMapState::instance.EntityLayerLT25[tile]
                            = (byte)this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                        return;
                    }
                    nextEntityID = prevEntityID;
                    if (prevEntityID != 0) {
                        while (currentEntityID = nextEntityID, ++guardCounter < 100
                            && (nextEntityID = this->entityArray[currentEntityID].nextEntityOnThisTileByID,
                                prevEntityID = currentEntityID, nextEntityID != entityID)) {
                            if (nextEntityID == 0) {
                                return;
                            }
                        }
                    }
                } else {
                    prevEntityID = DAT_TileMapState::instance.EntityLayer[tile];
                    if (prevEntityID == entityID) {
                        DAT_TileMapState::instance.EntityLayer[tile]
                            = this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                        return;
                    }
                    nextEntityID = prevEntityID;
                    if (prevEntityID != 0) {
                        while (currentEntityID = nextEntityID, ++guardCounter2 < 100
                            && (nextEntityID = this->entityArray[currentEntityID].nextEntityOnThisTileByID,
                                prevEntityID = currentEntityID, nextEntityID != entityID)) {
                            if (nextEntityID == 0) {
                                return;
                            }
                        }
                    }
                }
                this->entityArray[prevEntityID].nextEntityOnThisTileByID
                    = this->entityArray[entityID].nextEntityOnThisTileByID;
                this->entityArray[entityID].nextEntityOnThisTileByID = 0;
            }
        }

    }
}
}
