#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049FC00
        dword PathFindingState::findReachableTileWithLowestZoneDistance(int param_1, uint param_2, uint param_3, int param_4)
        {
            uint uVar5;
            int iVar8;
            dword dVar6 = 1000;
            int local_1c = 1000;
            dword local_14 = 0;
            int local_18 = 10000;
            if (param_2 > 399 || param_3 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return (dword)(dVar6);
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
            this->searchQueue.yQueue[0] = (short)param_3;
            this->searchQueue.xQueue[0] = (short)param_2;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2;
            int bVar1 = *(byte*)(param_4 * 0x13a10 + 0x1ee2998 + this->searchQueue.tilesQueue[0]);
            DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uVar5 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < uVar5)
                    break;
                int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int iVar7 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[uVar5];
                if ((0x13a10 < (int)this->searchQueue.currentDistance)
                    || ((int)this->searchQueue.currentDistance > param_1))
                    break;
                for (int iVar10 = 0; iVar10 < 8; iVar10 = iVar10 + 1) {
                    if ((DAT_TileMapState::instance.PathLinkageLayer[uVar5]
                            & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar10])
                        != 0) {
                        dVar6 = DAT_TileMapState::instance.directionTranslationMatrix[iVar7][iVar10] + uVar5;
                        if (DAT_TileMapState::instance.SearchGenerationLayer[dVar6] != this->searchGeneration) {
                            int uVar9 = (int)*(byte*)(param_4 * 0x13a10 + 0x1ee2998 + dVar6);
                            if (uVar9 <= 3) {
                                uVar9 = 0;
                            }
                            if (uVar9 != 0 && uVar9 < local_1c) {
                                iVar8 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(param_2, (int)(param_3),
                                    DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar10].int_.xOffset
                                        + sVar2,
                                    DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar10].int_.yOffset
                                        + iVar7);
                                local_1c = uVar9;
                                local_14 = dVar6;
                                local_18 = iVar8;
                            } else if (uVar9 == local_1c) {
                                iVar8 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                    DAT_DirectionAlgorithmState::ptr)(param_2, (int)(param_3),
                                    DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar10].int_.xOffset
                                        + sVar2,
                                    DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar10].int_.yOffset
                                        + iVar7);
                                if (iVar8 < local_18) {
                                    local_1c = uVar9;
                                    local_14 = dVar6;
                                    local_18 = iVar8;
                                }
                            }
                            DAT_TileMapState::instance.SearchDistanceLayer[dVar6]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.SearchGenerationLayer[dVar6] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar10].short_.xOffset
                                + (short)sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar10].short_.yOffset
                                + (short)iVar7;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = dVar6;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }
                }
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            this->zoneDistanceGain = bVar1 - local_1c;
            dVar6 = local_14;
            return (dword)(dVar6);
        }

    }
}
}
