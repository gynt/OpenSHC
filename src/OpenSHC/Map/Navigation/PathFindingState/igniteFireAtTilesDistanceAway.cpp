#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8ShortXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A2DD0
        undefined4 PathFindingState::igniteFireAtTilesDistanceAway(int tile, int maxDistance, int playerID)
        {
            short* psVar3;
            int* piVar4;
            int iVar5;
            int _index2;
            int _index;
            uint _tiles[100];
            uint _cTile;
            _index = 0;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            int _y = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int _x = tile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            this->searchQueue.yQueue[0] = (short)_y;
            this->searchQueue.tilesQueue[0] = tile;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.xQueue[0] = (short)_x;
            this->searchQueue.currentDistance = 1;
            DAT_TileMapState::instance.SearchDistanceLayer[tile] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < (uint)tile)
                    break;
                int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[tile];
                if ((0x13a10 < (int)this->searchQueue.currentDistance)
                    || ((int)this->searchQueue.currentDistance > maxDistance))
                    break;
                _tiles[_index] = tile;
                _index = _index + 1;
                for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                    /*
                      For every direction, queue tiles that are not a border tile
                     */
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                  .short_.yOffset
                            + sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 1] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 1]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 1]
                                  .short_.yOffset
                            + sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 2] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 2]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 2]
                                  .short_.yOffset
                            + sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction + 3] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 3]
                                  .short_.xOffset
                            + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 3]
                                  .short_.yOffset
                            + sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
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
            }
            _index2 = 0;
            if (0 < _index) {
                do {
                    _cTile = _tiles[_index2];
                    MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(playerID,
                        (_cTile
                            - DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_ViewportRenderState::instance
                                        .tileTranslationMatrix_YComponent[_cTile]]
                                .addXgetTile)
                            * 8,
                        (int)((short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_cTile] * 8),
                        (int)(DAT_TileMapState::instance.HeightLayer[_cTile]), 2);
                    _index2 = _index2 + 1;
                } while (_index2 < _index);
            }
            return (undefined4)(0);
        }

    }
}
}
