
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_MEDIUM;
    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CLIMBABLE;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_APPLE;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_DAIRY;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_WHEAT;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILE;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      related to setting oasis type   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00502390
    void TileMapState::setLand(int tile, uint y, uint brushType)
    {
        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brushType];
        int index = 0;
        int curTile;
        int curY;
        if (brushSize > 0) {
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, &curTile, &curY, tile, y);
                int t = curTile;
                if ((this->LogicLayer[t] & (L_BORDER | L_BORDER_EDGE)) == 0
                    && (this->LogicLayer[t] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_KEEP_NON_MANOR_HOUSE)) == 0
                    && this->BuildingLayer[t] == 0 && (this->LogicLayer[t] & L_TREE) == 0
                    && ((this->LogicLayer[t] & L_ROCKY) == 0 || this->OrganismLayer[t] == 0)) {
                    if (this->DefaultHeightLayer[t] < 8) {
                        this->DefaultHeightLayer[t] = 8;
                    }
                    this->HeightLayer[t] = this->DefaultHeightLayer[t];
                    this->MiscDisplayLayer[t] = this->MiscDisplayLayer[t] & 0xffdf;
                    if ((this->LogicLayer[t] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(t
                                - DAT_ViewportRenderState::instance
                                    .translationMatrix[DAT_ViewportRenderState::instance
                                            .tileTranslationMatrix_YComponent[t]]
                                    .addXgetTile,
                            DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[t]);
                        this->LogicLayer[t] = this->LogicLayer[t] & ~(L_MOAT | L_MOAT_DUG_OR_PLANNED);
                    }
                    this->LogicLayer[t] = this->LogicLayer[t]
                        & (L_STOCKPILE | L_PLAIN1_AND_FARM | L_BORDER | L_BORDER_EDGE | L_BUILDING
                            | L_MOAT_DUG_OR_PLANNED | L_DEFAULT_EARTH_OR_TEXTURE | L_UNKNOWN_WALL_RELATED | L_CLIMBABLE
                            | L_FARM_FIELD_WHEAT | L_FARM_FIELD_HOP | L_FARM_FIELD_APPLE | L_FARM_FIELD_DAIRY
                            | L_KEEP_NON_MANOR_HOUSE | L_MOAT);
                    this->MiscDisplayLayer[t] = this->MiscDisplayLayer[t] & 0xf83f;
                    this->Logic2Layer[t] = 0;
                    /* the plateau test reads the global instance's HeightLayer */
                    if (DAT_TileMapState::instance.HeightLayer[t] == 80) {
                        this->Logic2Layer[t] = L2_PLATEAU_MEDIUM;
                    } else if (DAT_TileMapState::instance.HeightLayer[t] == 130) {
                        this->Logic2Layer[t] = L2_PLATEAU_HIGH;
                    }
                    this->WallOwnerLayer[t] = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(curY, t);
                }
                index++;
            } while (index < brushSize);
        }
    }

}
}
