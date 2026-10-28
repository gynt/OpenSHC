#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // First free slot 1..1998 (a busy slot 1999 gives 0, signed jge 0x4F1CFF). x/y are used as 16-bit values
    // (tile from movsx). visualVariation starts as stageRelatedValue and is then replaced per type (switch on
    // type - 1 at 0x4F1E89): chestnut / birch from rng1 & 15, oak rng1 & 15 capped at 8, pine treeID % 9 (signed),
    // shrubs 1A..1E, 2A and 3A..3D get fixed values and stage 4; 2B..2E and apple keep the argument.
    // FUNCTION: STRONGHOLDCRUSADER 0x004F1CE0
    int LandscapeState::createTree(undefined4 x, undefined4 y, TreeType treeType, undefined4 size,
        int stageRelatedValue, undefined4 param_6, int stage)
    {
        int treeID;
        for (treeID = 1; treeID < 2000; treeID++) {
            if (this->trees[treeID].state == 0) {
                break;
            }
            if (treeID >= 1999) {
                return 0;
            }
        }
        if (treeID >= this->maxTreeCount) {
            this->maxTreeCount = treeID + 1;
        }
        this->trees[treeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        DAT_GameCore::instance.uniqueGameObjectTracker++;
        switch (treeType) {
        case OpenSHC::Map::Trees::TT_SHRUB3A:
        case OpenSHC::Map::Trees::TT_SHRUB3B:
        case OpenSHC::Map::Trees::TT_SHRUB3C:
        case OpenSHC::Map::Trees::TT_SHRUB3D:
            this->trees[treeID].state = 4;
            break;
        default:
            this->trees[treeID].state = 1;
            break;
        }
        this->trees[treeID].size = (short)size;
        this->trees[treeID].xPosition = (ushort)x;
        this->trees[treeID].yPosition = (ushort)y;
        this->trees[treeID].treeType = (short)treeType;
        uint const tile = DAT_ViewportRenderState::instance.translationMatrix[(short)y].addXgetTile + (short)x;
        this->trees[treeID].microX = (short)(x * 8 + 3);
        this->trees[treeID].microY = (short)(y * 8 + 3);
        this->trees[treeID].tile = tile;
        this->trees[treeID].rng1 = DAT_TileMapState::instance.RandomLayer[tile] & 0x7ff;
        this->trees[treeID].visualVariation = stageRelatedValue;
        this->trees[treeID].unknownInitZero6E = (short)param_6;
        this->trees[treeID].gmImageIndex
            = (short)DAT_OrganismDefinedData::instance.TreeTypeBasedValueMapping[treeType];
        undefined2 const woodChunks = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated1[treeType][stage];
        this->trees[treeID].stageRelated4 = woodChunks;
        this->trees[treeID].woodChunksRemaining = woodChunks;
        undefined2 const hitPoints = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated2[treeType][stage];
        this->trees[treeID].maxHitPoints = hitPoints;
        this->trees[treeID].hitPoints = hitPoints;
        this->trees[treeID].gmOriginX = (short)DAT_TextureRenderCoreObject::instance
                                            .gmFileHeaderColorpaletteArray[this->trees[treeID].gmImageIndex]
                                            .originX;
        this->trees[treeID].gmOriginY = (short)DAT_TextureRenderCoreObject::instance
                                            .gmFileHeaderColorpaletteArray[this->trees[treeID].gmImageIndex]
                                            .originY;
        this->trees[treeID].animFrameIntervalMs = DAT_OrganismDefinedData::instance.treeAnimFrameIntervalMs[treeType];
        this->trees[treeID].zero = 0;
        this->trees[treeID].animationFrameIndex = DAT_TileMapState::instance.RandomLayer[tile] & 0x1f;
        this->trees[treeID].windState = 1;
        this->trees[treeID].stage = stage;
        this->trees[treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[treeType][stage];
        DAT_CurrentTreeID::instance = treeID;
        switch (treeType) {
        case OpenSHC::Map::Trees::TT_CHESTNUT: {
            int const variation = this->trees[treeID].rng1 & 0xf;
            this->trees[treeID].visualVariation = variation;
            if (variation >= 15) {
                this->trees[treeID].visualVariation = 4;
            } else if (variation >= 13) {
                this->trees[treeID].visualVariation = 6;
            } else if (variation >= 11) {
                this->trees[treeID].visualVariation = 1;
            } else if (variation > 8) {
                this->trees[treeID].visualVariation = 0;
            }
            break;
        }
        case OpenSHC::Map::Trees::TT_OAK: {
            int const variation = this->trees[treeID].rng1 & 0xf;
            this->trees[treeID].visualVariation = variation;
            if (variation > 8) {
                this->trees[treeID].visualVariation = 8;
            }
            break;
        }
        case OpenSHC::Map::Trees::TT_PINE:
            this->trees[treeID].visualVariation = treeID % 9;
            break;
        case OpenSHC::Map::Trees::TT_BIRCH: {
            int const variation = this->trees[treeID].rng1 & 0xf;
            this->trees[treeID].visualVariation = variation;
            if (variation >= 15) {
                this->trees[treeID].visualVariation = 4;
            } else if (variation >= 13) {
                this->trees[treeID].visualVariation = 6;
            } else if (variation >= 11) {
                this->trees[treeID].visualVariation = 1;
            } else if (variation > 8) {
                this->trees[treeID].visualVariation = 0;
            }
            if (this->trees[treeID].visualVariation > 8) {
                this->trees[treeID].visualVariation = 0;
            }
            break;
        }
        case OpenSHC::Map::Trees::TT_SHRUB1B:
            this->trees[treeID].visualVariation = 3;
            this->trees[treeID].stage = 4;
            break;
        case OpenSHC::Map::Trees::TT_SHRUB1C:
            this->trees[treeID].visualVariation = 4;
            this->trees[treeID].stage = 4;
            break;
        case OpenSHC::Map::Trees::TT_SHRUB1D:
            this->trees[treeID].visualVariation = 7;
            this->trees[treeID].stage = 4;
            break;
        case OpenSHC::Map::Trees::TT_SHRUB1E:
            this->trees[treeID].visualVariation = 8;
            this->trees[treeID].stage = 4;
            break;
        case OpenSHC::Map::Trees::TT_SHRUB1A:
        case OpenSHC::Map::Trees::TT_SHRUB2A:
        case OpenSHC::Map::Trees::TT_SHRUB3A:
        case OpenSHC::Map::Trees::TT_SHRUB3B:
        case OpenSHC::Map::Trees::TT_SHRUB3C:
        case OpenSHC::Map::Trees::TT_SHRUB3D:
            this->trees[treeID].stage = 4;
            this->trees[treeID].visualVariation = 0;
            break;
        }
        undefined4 const savedAnimFrozen = this->treeAnimFrozen;
        this->treeAnimFrozen = 0;
        DAT_OrganismDefinedData::instance.UpdateTree[this->trees[treeID].treeType]();
        this->treeAnimFrozen = savedAnimFrozen;
        return treeID;
    }

}
}
