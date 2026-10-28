#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Entities::EntityType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC490
    void TileMapState::generateDustClouds()
    {
        int random = SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        this->dustCloudTick = this->dustCloudTick + 1;
        if (random % 500 == this->dustCloudTick % 500) {
            this->dustCloudVariant1PauseCountdown = random % 0xb4;
        }
        if (random % 0x4b0 == this->dustCloudTick % 0x4b0) {
            this->dustCloudVariant0PauseCountdown = random % 0xb4;
        }
        if (this->dustCloudVariant1PauseCountdown != 0) {
            this->dustCloudVariant1PauseCountdown = this->dustCloudVariant1PauseCountdown - 1;
        }
        if (this->dustCloudVariant0PauseCountdown != 0) {
            this->dustCloudVariant0PauseCountdown = this->dustCloudVariant0PauseCountdown - 1;
        }

        for (int i = 0; i < this->dustCloudSourceCount; i++) {
            int tile = this->dustCloudSourceTiles[i];
            /* one tile out of every 64 puffs, selected by the tile's own random value */
            if (((short)this->RandomLayer[tile] ^ random) % 64 != this->dustCloudTick % 64) {
                continue;
            }
            int tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int tileX = tile - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile;
            int stage = this->dustCloudSourceVariant[i];
            if (stage == 0) {
                if (this->dustCloudVariant0PauseCountdown == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0, 0,
                        0, tileX * 8 + 4, tileY * 8 + 4, this->HeightLayer[tile], 0, 0, 0,
                        OpenSHC::Map::Entities::ET_DUST_CLOUD, stage);
                }
            } else if (this->dustCloudVariant1PauseCountdown == 0) {
                if (stage == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0, 0,
                        0, tileX * 8 + 4, tileY * 8 + 4, this->HeightLayer[tile], 0, 0, 0,
                        OpenSHC::Map::Entities::ET_DUST_CLOUD, stage);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0, 0,
                        0, tileX * 8 + 4, tileY * 8 + 4, this->HeightLayer[tile], 0, 0, 0,
                        OpenSHC::Map::Entities::ET_DUST_CLOUD, 2);
                }
            }
        }
    }

}
}
