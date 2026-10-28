
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005127B0
    void TileMapState::resetAreaBasedOnLogicalLayer()
    {
        for (int tile = 0; tile < 80400; tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) == 0) {
                continue;
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::useEraserBrush, this)(tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], 1);
            this->GfxLayer[tile] = 0;
            this->overlayImageOrStockpileIdLayer[tile] = 0;
            this->ConstructionGFXLayer[tile] = 0;
            this->PillarGFXLayer[tile] = 1;
            this->WallGfxOrAnimCounterLayer[tile] = 0;
            this->FloatingLayer[tile] = 0;
            this->UnitLayer[tile] = 0;
            this->EntityLayer[tile] = 0;
            this->EntityLayerLT25[tile] = 0;
            this->BuildingLayer[tile] = 0;
            this->LogicLayer[tile] = 0;
            this->Logic2Layer[tile] = 0;
            this->ChangedLayer[tile] = 0;
            this->OrganismLayer[tile] = 0;
            this->DamageOrCropStageLayer[tile] = 0;
            this->MacroLayer[tile] = 0;
            this->HeightLayer[tile] = 8;
            this->DefaultHeightLayer[tile] = 8;
            this->ShowHiLayer[tile] = 0;
            this->MiscDisplayLayer[tile] = 0;
            this->LuminesenceLayer[tile] = 0;
            this->WallOwnerLayer[tile] = 0;
            this->BuildingWasLayer[tile] = 0;
            this->OccupancyLayer[tile] = 0;
            this->AIZoneLayer[tile] = 0;
            this->AIInfoLayer[tile] = 0;
            this->unitDeathHeatMap[tile] = 0;
            this->SEC_TileMap1104[tile] = 0;
            this->aiZoneDistanceLayers[0][tile] = 0;
            this->aiZoneDistanceLayers[1][tile] = 0;
            this->aiZoneDistanceLayers[2][tile] = 0;
            this->aiZoneDistanceLayers[3][tile] = 0;
            this->aiZoneDistanceLayers[4][tile] = 0;
            this->aiZoneDistanceLayers[5][tile] = 0;
            this->aiZoneDistanceLayers[6][tile] = 0;
            this->aiZoneDistanceLayers[7][tile] = 0;
            this->aiZoneDistanceLayers[8][tile] = 0;
        }
    }

}
}
