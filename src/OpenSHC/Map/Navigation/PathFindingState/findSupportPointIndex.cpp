#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049F2D0
        int PathFindingState::findSupportPointIndex(int max, uint x, uint y, int tribeID)
        {
            int iVar4;
            int iVar5;
            int tile;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return 0;
            }
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                iVar4 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (iVar4 < 0 || 0x13a10 <= iVar4) {
                    break;
                }
                int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[iVar4];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    break;
                }
                if ((int)this->searchQueue.currentDistance > max) {
                    break;
                }
                for (int iVar6 = 0; iVar6 < 8; iVar6 = iVar6 + 1) {
                    if ((DAT_TileMapState::instance.PathLinkageLayer[iVar4]
                            & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6])
                            != 0
                        && (tile = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][iVar6] + iVar4,
                            DAT_TileMapState::instance.SearchGenerationLayer[tile] != this->searchGeneration)) {
                        if (4 < (int)this->searchQueue.currentDistance
                            && (DAT_TileMapState::instance.AIInfoLayer[tile] & 0x40) != 0
                            && (iVar5
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getSupportPointIndex,
                                    DAT_TroopValueState::ptr)(tile),
                                iVar5 != 0)
                            && iVar5 != DAT_TribesState::instance.tribes[tribeID].supportPointIndex
                            && DAT_TroopValueState::instance.attackInfo.supportPointsArray[iVar5].tribeID == 0) {
                            return iVar5;
                        }
                        DAT_TileMapState::instance.SearchDistanceLayer[tile]
                            = (short)this->searchQueue.currentDistance + 1;
                        short sVar3 = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar6]
                                          .short_.xOffset;
                        DAT_TileMapState::instance.SearchGenerationLayer[tile] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar1;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar6]
                                  .short_.yOffset
                            + sVar2;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = tile;
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
            return 0;
        }

    }
}
}
