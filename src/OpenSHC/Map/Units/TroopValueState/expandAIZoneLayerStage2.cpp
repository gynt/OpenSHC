#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051AE00
        void TroopValueState::expandAIZoneLayerStage2()
        {
            for (int tile = 0; tile < 80400; ++tile) {
                if (DAT_TileMapState::instance.AIInfoLayer[tile] != 2) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                for (int direction = 0; direction < 4; ++direction) {
                    if ((DAT_TileMapState::instance
                                .AIInfoLayer[tile + DAT_TileMapState::instance.directionTranslationMatrix[y][direction * 2]]
                            & 0xF)
                        == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::floodFillAIZoneFlag,
                            DAT_PathFindingState::ptr)(15,
                            DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[direction * 2].int_.xOffset + x,
                            DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[direction * 2].int_.yOffset + y,
                            4);
                        break;
                    }
                }
            }
        }

    }
}
}
