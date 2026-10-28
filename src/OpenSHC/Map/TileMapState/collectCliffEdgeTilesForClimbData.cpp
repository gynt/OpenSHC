#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_STONES_OR_DRIVEN_SANDUnk;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_SEA;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FC340
    void TileMapState::collectDustCloudSourceTiles()
    {
        this->dustCloudSourceCount = 0;
        for (int tile = 0; tile < 80400; tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                continue;
            }

            if ((this->LogicLayer[tile] & L_RIVER) != 0
                && (this->Logic2Layer[tile] & L2_STONES_OR_DRIVEN_SANDUnk) != 0) {
                this->dustCloudSourceVariant[this->dustCloudSourceCount] = 1;
                this->dustCloudSourceTiles[this->dustCloudSourceCount] = tile;
                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int tileHeight = this->HeightLayer[tile];
                for (int index = 0; index < 8; index++) {
                    int neighbour
                        = this->directionTranslationMatrix[y][DAT_ClimbLogicDefinedData::instance.directionScanOrder[index]]
                        + tile;
                    if ((this->LogicLayer[neighbour] & L_RIVER) != 0
                        && this->HeightLayer[neighbour] > tileHeight + 0x50) {
                        this->dustCloudSourceVariant[this->dustCloudSourceCount] = 0;
                        break;
                    }
                }
                this->dustCloudSourceCount = this->dustCloudSourceCount + 1;
                if ((int)this->dustCloudSourceCount >= 1000) {
                    return;
                }
            }

            if (((this->LogicLayer[tile] & L_RIVER) != 0 && (this->Logic2Layer[tile] & L2_OASIS_GRASS) != 0)
                || ((this->LogicLayer[tile] & L_SEA) != 0 && (this->Logic2Layer[tile] & L2_PLATEAU_HIGH) != 0)) {
                this->dustCloudSourceVariant[this->dustCloudSourceCount] = 1;
                this->dustCloudSourceTiles[this->dustCloudSourceCount] = tile;
                this->dustCloudSourceCount = this->dustCloudSourceCount + 1;
                if ((int)this->dustCloudSourceCount >= 1000) {
                    return;
                }
            }
        }
    }

}
}
