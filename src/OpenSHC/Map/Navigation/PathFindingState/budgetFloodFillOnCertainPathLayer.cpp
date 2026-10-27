#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Function: __alloca_probe replaced with injection: alloca_probe
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049DDC0
        void PathFindingState::budgetFloodFillOnSearchDistanceLayer(uint x, uint y, int marker, int budget)
        {
            uint _tilesQueue[1000];
            uint _ys[1000];
            uint _xs[1000];
            int _readIndex = 0;
            int _writeIndex = 1;
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return;
            }
            this->DAT_Mini_spreads = this->DAT_Mini_spreads + 1;
            _ys[0] = y;
            _xs[0] = x;
            _tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            do {
                uint _tile = _tilesQueue[_readIndex];
                if (_tile > 0x13a0f) {
                    return;
                }
                if (_writeIndex >= budget) {
                    return;
                }
                if (_writeIndex >= 999) {
                    return;
                }
                x = _xs[_readIndex];
                y = _ys[_readIndex];
                DAT_TileMapState::instance.SearchDistanceLayer[_tile] = (short)marker;
                for (int _direction = 0; _direction < 8; _direction++) {
                    uint _candidate = DAT_TileMapState::instance.directionTranslationMatrix[y][_direction] + _tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[_candidate] != this->searchGeneration) {
                        budget = budget - 1;
                    } else {
                        short _distance = DAT_TileMapState::instance.SearchDistanceLayer[_candidate];
                        if (_distance == marker) {
                            budget = budget - 1;
                        } else if (_distance > 0) {
                            _tilesQueue[_writeIndex] = _candidate;
                            _xs[_writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset + x;
                            _ys[_writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset + y;
                            _writeIndex = _writeIndex + 1;
                            DAT_TileMapState::instance.SearchDistanceLayer[_candidate] = (short)marker;
                            if (_writeIndex >= 1000) {
                                _writeIndex = 0;
                            }
                        }
                    }
                }
                _readIndex = _readIndex + 1;
                if (_readIndex >= 1000) {
                    _readIndex = 0;
                }
            } while (_readIndex != _writeIndex);
        }

    }
}
}
