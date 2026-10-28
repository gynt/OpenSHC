#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Computes the distance to reach x and y, has a shortcut to basically return distance 1 if the area   of the
          destination is the same as the current area was   decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049B1D0
        void PathFindingState::findNearbyTileInConnectionArea(int originArea, uint destinationX, uint destinationY)
        {
            int _neswTile1;
            int _neswTile2;
            int _neswTile3;
            int _neswTile4;
            int _currentTile;
            int _currentX;
            int _currentY;
            if (destinationX <= 399 && destinationY <= 399
                && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[destinationY * 400 + destinationX]
                    != '\0') {
                this->climbX = destinationX;
                this->climbY = destinationY;
                this->calculations = this->calculations + 1;
                this->searchGeneration = this->searchGeneration + 1;
                if (32000 < this->searchGeneration) {
                    this->searchGeneration = 1;
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
                }
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                this->searchQueue.xQueue[0] = (short)destinationX;
                this->searchQueue.currentDistance = 1;
                this->searchQueue.yQueue[0] = (short)destinationY;
                this->searchQueue.tilesQueue[0]
                    = destinationX + DAT_ViewportRenderState::instance.translationMatrix[destinationY].addXgetTile;
                DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    _currentTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_currentTile < 0) {
                        return;
                    }
                    if (_currentTile >= 80400) {
                        return;
                    }
                    int const _currentArea = (short)DAT_TileMapState::instance.PathConnectionLayer[_currentTile];
                    _currentX = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    _currentY = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    if (_currentArea == originArea) {
                        this->climbX = (int)_currentX;
                        this->climbY = (int)_currentY;
                        return;
                    }
                    this->searchQueue.currentDistance
                        = (int)DAT_TileMapState::instance.SearchDistanceLayer[_currentTile];
                    if (6 < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                        _neswTile1
                            = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 0]
                            + _currentTile;
                        if ((DAT_TileMapState::instance.LogicLayer[_neswTile1] & 0x30) == 0) {
                            DAT_TileMapState::instance.SearchDistanceLayer[_neswTile1]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.SearchGenerationLayer[_neswTile1] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 0]
                                      .int_.xOffset
                                + _currentX;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 0]
                                      .int_.yOffset
                                + _currentY;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile1;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        _neswTile2
                            = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 1]
                            + _currentTile;
                        if ((DAT_TileMapState::instance.LogicLayer[_neswTile2] & 0x30) == 0) {
                            DAT_TileMapState::instance.SearchDistanceLayer[_neswTile2]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.SearchGenerationLayer[_neswTile2] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 1]
                                      .int_.xOffset
                                + _currentX;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 1]
                                      .int_.yOffset
                                + _currentY;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile2;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        _neswTile3
                            = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 2]
                            + _currentTile;
                        if ((DAT_TileMapState::instance.LogicLayer[_neswTile3] & 0x30) == 0) {
                            DAT_TileMapState::instance.SearchDistanceLayer[_neswTile3]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.SearchGenerationLayer[_neswTile3] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 2]
                                      .int_.xOffset
                                + _currentX;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 2]
                                      .int_.yOffset
                                + _currentY;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile3;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        _neswTile4
                            = DAT_TileMapState::instance.directionTranslationMatrix[_currentY][_direction + 3]
                            + _currentTile;
                        if ((DAT_TileMapState::instance.LogicLayer[_neswTile4] & 0x30) == 0) {
                            DAT_TileMapState::instance.SearchDistanceLayer[_neswTile4]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.SearchGenerationLayer[_neswTile4] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 3]
                                      .int_.xOffset
                                + _currentX;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance
                                      .clockwiseNeighbourOffsets[_direction + 3]
                                      .int_.yOffset
                                + _currentY;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _neswTile4;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a10 <= (int)this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    /*
                      the right hand side stops incrementing if no valid tiles are found, so the   left hand side
                      catches up breaking when finished. Very elegant
                     */
                }
            }
            return;
        }

    }
}
}
