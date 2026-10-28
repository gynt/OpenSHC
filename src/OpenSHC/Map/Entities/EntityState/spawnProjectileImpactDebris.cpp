#include "../EntityState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // Works on `this` (esi = &entityArray[entityID] built from ecx at 0x405DB0). The wall-side switch is the same as
        // handleProjectileWallBounce (jump table 0x40612C for orientations 0x3C..0x4B, inner byte tables verified per
        // flag value); other orientations leave the debris target at 0,0 (ja 0x406099). The debris count rng_1 % 8 + 5
        // is signed (and 0x80000007; jns) and re-evaluated every iteration (0x4060DA).
        // FUNCTION: STRONGHOLDCRUSADER 0x00405DA0
        void EntityState::spawnProjectileImpactDebris(int entityID)
        {
            int microY = this->entityArray[entityID].microY;
            int microX = this->entityArray[entityID].microX;
            int subTileX = microX & 7;
            int newTargetX = 0;
            int newTargetY = 0;
            int subTileY = microY & 7;
            int wallFlags = MACRO_CALL_MEMBER(
                OpenSHC::Map::TileMapState_Func::setBitFlagBasedOnWallTowerGatehouseOrKeep, DAT_TileMapState::ptr)(
                microX / 8, microY / 8);
            switch (this->entityArray[entityID].orientation) {
            case 0x3c:
            case 0x40:
            case 0x44:
            case 0x48:
            bounceBack:
                newTargetY = this->entityArray[entityID].y_2;
                newTargetX = this->entityArray[entityID].x_2;
                break;
            case 0x3d:
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 2:
                        subTileX = 100;
                        break;
                    case 0xa:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x3e:
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 2:
                        subTileX = 100;
                        break;
                    case 0xa:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x3f:
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa) {
                    case 0:
                    case 2:
                        subTileX = 100;
                        break;
                    case 8:
                        subTileY = 100;
                        break;
                    case 0xa:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x41:
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x82) {
                    case 0:
                    case 2:
                        subTileY = 100;
                        break;
                    case 0x80:
                        subTileX = 100;
                        break;
                    case 0x82:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x42:
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x82) {
                    case 0:
                    case 2:
                        subTileY = 100;
                        break;
                    case 0x80:
                        subTileX = 100;
                        break;
                    case 0x82:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x43:
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x82) {
                    case 0:
                    case 0x80:
                        subTileX = 100;
                        break;
                    case 2:
                        subTileY = 100;
                        break;
                    case 0x82:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x45:
                subTileX = 7 - subTileX;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa0) {
                    case 0:
                    case 0x80:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0xa0:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x46:
                subTileX = 7 - subTileX;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa0) {
                    case 0:
                    case 0x80:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0xa0:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x47:
                subTileX = 7 - subTileX;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0xa0) {
                    case 0:
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0x80:
                        subTileY = 100;
                        break;
                    case 0xa0:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x49:
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x28) {
                    case 0:
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 8:
                        subTileY = 100;
                        break;
                    case 0x28:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x4a:
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x28) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0x28:
                        goto bounceBack;
                    }
                }
                goto mirror;
            case 0x4b:
                subTileX = 7 - subTileX;
                subTileY = 7 - subTileY;
                if (subTileX == subTileY) {
                    switch (wallFlags & 0x28) {
                    case 0:
                    case 8:
                        subTileY = 100;
                        break;
                    case 0x20:
                        subTileX = 100;
                        break;
                    case 0x28:
                        goto bounceBack;
                    }
                }
            mirror:
                if (subTileX > subTileY) {
                    newTargetX = this->entityArray[entityID].microX * 2 - this->entityArray[entityID].x_2;
                    newTargetY = this->entityArray[entityID].y_2;
                }
                else {
                    newTargetY = this->entityArray[entityID].microY * 2 - this->entityArray[entityID].y_2;
                    newTargetX = this->entityArray[entityID].x_2;
                }
                break;
            }

            for (int i = 0; i < this->entityArray[entityID].rng_1 % 8 + 5; i++) {
                MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(0, 0, 0, microX, microY,
                    this->entityArray[entityID].height, newTargetX, newTargetY, 8, ET_WALL_DEBRIS, 0);
            }
            MACRO_CALL_MEMBER(EntityState_Func::spawnEntity, this)(0, 0, 0, microX, microY,
                this->entityArray[entityID].height, microX + 1, microY + 1, this->entityArray[entityID].height,
                ET_PUFF_EFFECT, 0);
        }

    }
}
}
