#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_SEA;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FF080
    void TileMapState::updateMacroLayerRelated2()
    {
        /* the section map is read through the global instance; the 10-tile row walks are unrolled by the compiler */
        int startRow;
        startRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (int block = this->dirtySectionRowMin; block <= this->dirtySectionRowMax; block++) {
            for (int sub = this->dirtySectionColMin; sub <= this->dirtySectionColMax; sub++) {
                if (DAT_TileMapState::instance.mapping40x40[block][sub] == 0) {
                    continue;
                }
                for (int row = startRow; row < 10; row++) {
                    this->curTileY = block * 10 + row;
                    this->curTileX = sub * 10;
                    for (int column = 0; column < 10; column++) {
                        if ((uint)this->curTileX <= 399 && (uint)this->curTileY <= 399
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->curTileY * 400 + this->curTileX] != 0) {
                            this->curTileIndex = DAT_ViewportRenderState::instance.translationMatrix[this->curTileY].addXgetTile + this->curTileX;
                            if (this->ChangedLayer[this->curTileIndex] != 0 && (this->LogicLayer[this->curTileIndex] & L_SEA) != 0) {
                                this->MacroLayer[this->curTileIndex] = 0x800;
                            }
                        }
                        this->curTileX = this->curTileX + 1;
                    }
                }
                startRow = 0;
            }
        }
        startRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (int block = this->dirtySectionRowMin; block <= this->dirtySectionRowMax; block++) {
            for (int sub = this->dirtySectionColMin; sub <= this->dirtySectionColMax; sub++) {
                if (DAT_TileMapState::instance.mapping40x40[block][sub] == 0) {
                    continue;
                }
                for (int row = startRow; row < 10; row++) {
                    this->curTileY = block * 10 + row;
                    this->curTileX = sub * 10;
                    int column = 10;
                    do {
                        if ((uint)this->curTileX <= 399 && (uint)this->curTileY <= 399
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->curTileY * 400 + this->curTileX] != 0) {
                            this->curTileIndex = this->curTileX
                                + DAT_ViewportRenderState::instance.translationMatrix[this->curTileY].addXgetTile;
                            if (this->MacroLayer[this->curTileIndex] == 0x800
                                && (this->LogicLayer[this->curTileIndex] & L_SEA) != 0) {
                                ushort random = this->RandomLayer[this->curTileIndex];
                                int corner = this->curTileIndex
                                    - DAT_ViewportRenderState::instance.translationMatrix[this->curTileY].addXgetTile;
                                /* a wave sprite only fits where all sixteen of its tiles are still marked */
                                bool complete = true;
                                for (int i = 0; i < 0x10; i++) {
                                    if (this->MacroLayer[DAT_ViewportRenderState::instance
                                                             .translationMatrix[DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[i].y
                                                                 + this->curTileY]
                                                             .addXgetTile
                                            + DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[i].x + corner]
                                        != 0x800) {
                                        complete = false;
                                        break;
                                    }
                                }
                                if (complete) {
                                    for (int i = 0; i < 0x10; i++) {
                                        this->MacroLayer[DAT_ViewportRenderState::instance
                                                             .translationMatrix[DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[i].y
                                                                 + this->curTileY]
                                                             .addXgetTile
                                            + DAT_TerrainDefinedData::instance.macroBlock4x4Offsets[i].x + corner]
                                            = (ushort)(byte)random * 0x1000 + 0x10 + (short)(i << 6);
                                    }
                                }
                            }
                        }
                        this->curTileX = this->curTileX + 1;
                        column = column + -1;
                    } while (column != 0);
                }
                startRow = 0;
            }
        }

        startRow = DAT_PathFindingState::instance.dirtyMinY % 10;
        for (int block = this->dirtySectionRowMin; block <= this->dirtySectionRowMax; block++) {
            for (int sub = this->dirtySectionColMin; sub <= this->dirtySectionColMax; sub++) {
                if (DAT_TileMapState::instance.mapping40x40[block][sub] == 0) {
                    continue;
                }
                for (int row = startRow; row < 10; row++) {
                    this->curTileY = block * 10 + row;
                    this->curTileX = sub * 10;
                    for (int column = 0; column < 10; column++) {
                        if ((uint)this->curTileX <= 399 && (uint)this->curTileY <= 399
                            && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[this->curTileY * 400 + this->curTileX] != 0) {
                            this->curTileIndex = DAT_ViewportRenderState::instance.translationMatrix[this->curTileY].addXgetTile + this->curTileX;
                            if (this->MacroLayer[this->curTileIndex] == 0x800) {
                                this->MacroLayer[this->curTileIndex] = 2;
                            }
                        }
                        this->curTileX = this->curTileX + 1;
                    }
                }
                startRow = 0;
            }
        }
    }

}
}