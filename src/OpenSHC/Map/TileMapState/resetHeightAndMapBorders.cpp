#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004F6CF0
    void TileMapState::resetHeightAndMapBorders(int mapSize)
    {
        int inset = (400 - mapSize) / 2;
        this->mapSize = mapSize;
        for (int tile = 0; tile < 80400; tile++) {
            if ((this->LogicLayer[tile] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            }
            this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_BORDER | L_BORDER_EDGE);
        }

        /* the two outer diagonals of the diamond carry the border flags */
        int row = 0;
        int tile = 0;
        do {
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BORDER;
            tile++;
            if (row > 0) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BORDER_EDGE;
            }
            tile = tile + row;
            if (row > 0 && (this->LogicLayer[tile - 1] & L_BORDER) == 0) {
                this->LogicLayer[tile - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[tile] = L_BORDER;
            row = row + 2;
            tile++;
        } while (row < 400);

        for (row = 398; row >= 0; row = row - 2) {
            this->LogicLayer[tile] = L_BORDER;
            tile++;
            if (row > 0) {
                this->LogicLayer[tile] = L_BORDER_EDGE;
            }
            tile = tile + row;
            if (row > 0 && (this->LogicLayer[tile - 1] & L_BORDER) == 0) {
                this->LogicLayer[tile - 1] = L_BORDER_EDGE;
            }
            this->LogicLayer[tile] = L_BORDER;
            tile++;
        }

        /* and again inset by (400 - mapSize) / 2 for a map smaller than the full diamond */
        row = 0;
        tile = 0;
        for (int skipped = 0; skipped < inset; skipped++) {
            tile = tile + row + 2;
            row = row + 2;
        }
        int startRow = row; // 0x4F6E72: saved once, before the upper-half loop advances row
        if (row < 400) {
            int edge = row - inset;
            do {
                this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER;
                tile++;
                if (edge > 0) {
                    this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER_EDGE;
                }
                tile = tile + row;
                if (edge > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                    this->LogicLayer[tile - inset - 1] = this->LogicLayer[tile - inset - 1] | L_BORDER_EDGE;
                }
                this->LogicLayer[tile - inset] = this->LogicLayer[tile - inset] | L_BORDER;
                row = row + 2;
                tile++;
                edge = edge + 2;
            } while (row < 400);
        }
        int back = 0x18e;
        if (startRow <= back) {
            int edge = back - inset;
            do {
                this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER;
                tile++;
                if (edge > 0) {
                    this->LogicLayer[tile + inset] = this->LogicLayer[tile + inset] | L_BORDER_EDGE;
                }
                tile = tile + back;
                if (edge > 0 && (this->LogicLayer[tile - inset] & L_BORDER) == 0) {
                    this->LogicLayer[tile - inset - 1] = this->LogicLayer[tile - inset - 1] | L_BORDER_EDGE;
                }
                this->LogicLayer[tile - inset] = this->LogicLayer[tile - inset] | L_BORDER;
                tile++;
                back = back - 2;
                edge = edge - 2;
            } while (back >= startRow);
        }
        if (mapSize != 400) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setWalkabilityBorderLogicLayerForSmallerMapSizes,
                DAT_PathFindingState::ptr)();
        }
        /* 0x4F6F64: every border tile gets height 8 */
        for (int t = 0; t < 80400; t++) {
            if ((this->LogicLayer[t] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                this->HeightLayer[t] = 8;
            }
        }
    }

}
}
