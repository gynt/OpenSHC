#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049AAD0
        void PathFindingState::updateWalkAndPathLayer(int param_1, uint xPosition, uint yPosition)
        {
            int iVar8;
            if (xPosition > 399 || yPosition > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[yPosition * 400 + xPosition] == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)yPosition;
            this->searchQueue.xQueue[0] = (short)xPosition;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[yPosition].addXgetTile + xPosition;
            DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint uVar3 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < uVar3)
                    break;
                int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                if (sVar1 < this->dirtyMinY) {
                    this->dirtyMinY = sVar1;
                }
                if (sVar1 > this->dirtyMaxY) {
                    this->dirtyMaxY = sVar1;
                }
                int iVar4 = sVar2 / 10;
                int iVar5 = sVar1 / 10;
                *(undefined1*)(iVar4 + 0x1f93438 + iVar5 * 0x28) = 2;
                if (iVar4 < DAT_TileMapState::instance.dirtySectionColMin) {
                    DAT_TileMapState::instance.dirtySectionColMin = iVar4;
                }
                if (iVar4 > DAT_TileMapState::instance.dirtySectionColMax) {
                    DAT_TileMapState::instance.dirtySectionColMax = iVar4;
                }
                if (iVar5 < DAT_TileMapState::instance.dirtySectionRowMin) {
                    DAT_TileMapState::instance.dirtySectionRowMin = iVar5;
                }
                if (iVar5 > DAT_TileMapState::instance.dirtySectionRowMax) {
                    DAT_TileMapState::instance.dirtySectionRowMax = iVar5;
                }
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[uVar3];
                if ((int)this->searchQueue.currentDistance > param_1)
                    break;
                DAT_TileMapState::instance.ChangedLayer[uVar3] = 2;
                for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                    iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction] + uVar3;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar8] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar8]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar8] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.xOffset
                            + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction + 1] + uVar3;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar8] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar8]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar8] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 1].short_.xOffset
                            + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 1].short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction + 2] + uVar3;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar8] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar8]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar8] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 2].short_.xOffset
                            + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 2].short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                    iVar8 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction + 3] + uVar3;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar8] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[iVar8] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar8]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar8] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 3].short_.xOffset
                            + sVar2;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction + 3].short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar8;
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
            DAT_TileMapState::instance.forceUpdateLogicalAndMiscDisplayLayers = 1;
            DAT_TileMapState::instance.forceUpdateTextureTilemap = 1;
            DAT_TileMapState::instance.forceUpdateGFXLayers = 1;
            return;
        }

    }
}
}
