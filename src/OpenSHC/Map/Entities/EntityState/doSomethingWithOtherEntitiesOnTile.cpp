#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401460
        void EntityState::doSomethingWithOtherEntitiesOnTile(uint entityID)
        {
            uint uVar1;
            uint uVar2;
            uint uVar3;
            int iVar4;
            int _tile;
            _tile = this->entityArray[entityID].tile;
            iVar4 = 0;
            if (_tile) {
                if ((int)entityID < 0x19) {
                    uVar3 = (uint)(byte)DAT_TileMapState::instance.EntityLayerLT25[_tile];
                    if (uVar3 == entityID) {
                        DAT_TileMapState::instance.EntityLayerLT25[_tile]
                            = (char)this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                    }
                    uVar1 = uVar3;
                    if (uVar3) {
                        while ((uVar2 = uVar1, iVar4 = iVar4 + 1,
                            iVar4 < 100
                                && (uVar1 = (uint)this->entityArray[uVar2].nextEntityOnThisTileByID, uVar3 = uVar2,
                                    uVar1 != entityID))) {
                            if (!uVar1) {}
                        }
                    }
                } else {
                    uVar3 = (uint)DAT_TileMapState::instance.EntityLayer[_tile];
                    if (uVar3 == entityID) {
                        DAT_TileMapState::instance.EntityLayer[_tile]
                            = this->entityArray[entityID].nextEntityOnThisTileByID;
                        this->entityArray[entityID].nextEntityOnThisTileByID = 0;
                    }
                    uVar1 = uVar3;
                    if (uVar3) {
                        while ((uVar2 = uVar1, iVar4 = iVar4 + 1,
                            iVar4 < 100
                                && (uVar1 = (uint)this->entityArray[uVar2].nextEntityOnThisTileByID, uVar3 = uVar2,
                                    uVar1 != entityID))) {
                            if (!uVar1) {}
                        }
                    }
                }
                this->entityArray[uVar3].nextEntityOnThisTileByID
                    = this->entityArray[entityID].nextEntityOnThisTileByID;
                this->entityArray[entityID].nextEntityOnThisTileByID = 0;
            }
        }

    }
}
}
