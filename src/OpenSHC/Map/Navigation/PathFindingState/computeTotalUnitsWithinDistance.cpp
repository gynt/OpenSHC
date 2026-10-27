#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049C690
        void PathFindingState::computeTotalUnitsWithinDistance(
            int playerID, int sameTeamUnits, int someLogicalTileProperty, int tile, int distance)
        {
            int iVar5;
            int iVar6;
            this->calculations = this->calculations + 1;
            this->ALGO_TotalTroopValue = 0;
            this->ALGO_TotalTroopCount = 0;
            this->firstMatchingUnitID = 0;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0]
                = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            this->searchQueue.tilesQueue[0] = tile;
            DAT_TileMapState::instance.SearchDistanceLayer[tile] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < (uint)tile) {
                    return;
                }
                int sVar3 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                int uVar2 = (short)DAT_TileMapState::instance.UnitLayer[tile];
                while (iVar6 = (int)(short)uVar2, iVar6 != 0) {
                    if (sameTeamUnits == 1) {
                        if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                            == DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_UnitsState::instance.units[iVar6].owner])
                            goto LAB_countUnit;
                    } else if ((sameTeamUnits != 0)
                        || (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_UnitsState::instance.units[iVar6].owner])) {
                    LAB_countUnit:
                        if ((DAT_UnitsState::instance.units[iVar6].owner != 0)
                            && (DAT_UnitsState::instance.units[iVar6].dying == 0)) {
                            iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                DAT_TroopValueState::ptr)(
                                (OpenSHC::Map::Units::UnitType)(int)(short)DAT_UnitsState::instance.units[iVar6]
                                    .unitType);
                            this->ALGO_TotalTroopValue = this->ALGO_TotalTroopValue + iVar5;
                            this->ALGO_TotalTroopCount = this->ALGO_TotalTroopCount + 1;
                            if (this->firstMatchingUnitID == 0) {
                                this->firstMatchingUnitID = iVar6;
                            }
                        }
                    }
                    uVar2 = DAT_UnitsState::instance.units[iVar6].nextUnitOnTheSameTile;
                }
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[tile];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    return;
                }
                if ((int)this->searchQueue.currentDistance > distance) {
                    return;
                }
                byte bVar1 = DAT_TileMapState::instance.PathLinkageLayer[tile];
                iVar6 = 0;
                do {
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][iVar6] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration) {
                        if (someLogicalTileProperty != 0) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6] & bVar1) == 0)
                                goto LAB_nextDirection0;
                        } else if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) != 0) {
                            goto LAB_nextDirection0;
                        }
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar6].short_.yOffset
                            + sVar3;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                LAB_nextDirection0:
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][iVar6 + 1] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration) {
                        if (someLogicalTileProperty != 0) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6 + 1] & bVar1) == 0)
                                goto LAB_nextDirection1;
                        } else if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) != 0) {
                            goto LAB_nextDirection1;
                        }
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar6 + 1].short_.yOffset
                            + sVar3;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                LAB_nextDirection1:
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][iVar6 + 2] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration) {
                        if (someLogicalTileProperty != 0) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6 + 2] & bVar1) == 0)
                                goto LAB_nextDirection2;
                        } else if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) != 0) {
                            goto LAB_nextDirection2;
                        }
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar6 + 2].short_.yOffset
                            + sVar3;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                LAB_nextDirection2:
                    iVar5 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][iVar6 + 3] + tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar5] != this->searchGeneration) {
                        if (someLogicalTileProperty != 0) {
                            if ((DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[iVar6 + 3] & bVar1) == 0)
                                goto LAB_nextDirection3;
                        } else if ((DAT_TileMapState::instance.LogicLayer[iVar5] & 0x30) != 0) {
                            goto LAB_nextDirection3;
                        }
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar5]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar5] = (short)this->searchGeneration;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[iVar6 + 3].short_.yOffset
                            + sVar3;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar5;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                LAB_nextDirection3:
                    iVar6 = iVar6 + 4;
                } while (iVar6 < 8);
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return;
        }

    }
}
}
