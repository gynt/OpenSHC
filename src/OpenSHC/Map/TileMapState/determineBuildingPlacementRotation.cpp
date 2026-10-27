#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      One anchor probe. The original inlines this four times per rotation; the counters are passed by
      reference, which is why both stay in memory there (including the never-read total).
    */
    static inline void countUsableWallAt(TileMapState* map, int x, int y, int dx, int dy, int& count, int& total)
    {
        if ((uint)(dx + x) <= 399 && (uint)(dy + y) <= 399
            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[(dy + y) * 400 + dx + x] != 0
            && (map->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[dy + y].addXgetTile + dx + x]
                   & L_WALL_OR_GATEHOUSE)
                != 0
            && (map->LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[dy + y].addXgetTile + dx + x]
                   & (L_STOCKPILE | L_STAIRS))
                == 0) {
            count = count + 1;
            total = total + 1;
        }
    }

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FA000
    void TileMapState::determineBuildingPlacementRotation(int x, int y)
    {
        /* total is counted but never read (the original keeps the dead counter on the stack) */
        int total = 0;
        this->placementPreviewGfxOffset = 0x80;
        this->uiBuildingRotation = 8;
        if (this->buildingPlacementResult != FALSE) {
            return;
        }

        /* count, per rotation, how many of its four anchor tiles carry usable wall */
        int walls[4];
        for (int rotation = 0; rotation < 4; rotation++) {
            walls[rotation] = 0;
            int* probe = &DAT_TerrainDefinedData::instance.rotationProbeOffsets[rotation * 8];
            countUsableWallAt(this, x, y, probe[0], probe[1], walls[rotation], total);
            countUsableWallAt(this, x, y, probe[2], probe[3], walls[rotation], total);
            countUsableWallAt(this, x, y, probe[4], probe[5], walls[rotation], total);
            countUsableWallAt(this, x, y, probe[6], probe[7], walls[rotation], total);
        }
        this->uiBuildingRotation = 8;
        if (walls[0] == 4 && walls[3] == 4) {
            this->uiBuildingRotation = 7;
        } else if (walls[0] == 4 && walls[1] == 4) {
            this->uiBuildingRotation = 1;
        } else if (walls[2] == 4 && walls[3] == 4) {
            this->uiBuildingRotation = 5;
        } else if (walls[2] == 4 && walls[1] == 4) {
            this->uiBuildingRotation = 3;
        } else if (walls[0] == 4) {
            this->uiBuildingRotation = 0;
        } else if (walls[1] == 4) {
            this->uiBuildingRotation = 2;
        } else if (walls[2] == 4) {
            this->uiBuildingRotation = 4;
        } else if (walls[3] == 4) {
            this->uiBuildingRotation = 6;
        } else {
            this->uiBuildingRotation = 8;
        }

        int relative;
        if (this->uiBuildingRotation == 8) {
            relative = 8;
        } else {
            relative = this->uiBuildingRotation - this->mapOrientation;
            if (relative < 0) {
                relative = relative + 8;
            }
        }
        this->placementPreviewGfxOffset = relative << 4;
    }

}
}
