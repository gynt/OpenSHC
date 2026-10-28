#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049AF50
        void PathFindingState::setChangedLayerZeroBasedOn40x40Layer(uint flag_and_offset)
        {
            if ((this->forceFullDirtyReset == 0) && (flag_and_offset == 0)) {
                for (int row = DAT_TileMapState::instance.dirtySectionRowMin;
                     row <= DAT_TileMapState::instance.dirtySectionRowMax; row++) {
                    for (int col = DAT_TileMapState::instance.dirtySectionColMin;
                         col <= DAT_TileMapState::instance.dirtySectionColMax; col++) {
                        if (DAT_TileMapState::instance.mapping40x40[row][col] != '\0') {
                            /*
                              update this part
                             */
                            DAT_TileMapState::instance.mapping40x40[row][col] = 0;
                            for (int dy = 0; dy < 10; dy++) {
                                uint y = row * 10 + dy;
                                for (int dx = 0; dx < 10; dx++) {
                                    uint x = col * 10 + dx;
                                    /*
                                      is valid coordinate: set changed layer to 0
                                     */
                                    if (x <= 399 && y <= 399
                                        && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x]
                                            != '\0') {
                                        DAT_TileMapState::instance.ChangedLayer
                                            [DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                                            = 0;
                                    }
                                }
                            }
                        }
                    }
                }                this->dirtyMinY = 1000;
                this->dirtyMaxY = 0;
                DAT_TileMapState::instance.dirtySectionRowMin = 1000;
                DAT_TileMapState::instance.dirtySectionRowMax = 0;
                DAT_TileMapState::instance.dirtySectionColMin = 1000;
                DAT_TileMapState::instance.dirtySectionColMax = 0;
                return;
            }
            this->forceFullDirtyReset = 0;
            this->dirtyMinY = 0;
            this->dirtyMaxY = 399;
            DAT_TileMapState::instance.dirtySectionRowMin = 0;
            DAT_TileMapState::instance.dirtySectionRowMax = 39;
            DAT_TileMapState::instance.dirtySectionColMin = 0;
            DAT_TileMapState::instance.dirtySectionColMax = 0x27;
            return;
        }

    }
}
}
