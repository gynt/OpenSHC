#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Type propagation algorithm not settling
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A83B0
        void PathFindingState::populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea(
            int tile, int maxDestinations, dword area, int playerID)
        {
            int iVar2;
            int* piVar3;
            XYPair* pXVar4;
            int _candidate;
            int _tile;
            int _dIndex;
            int _tileY;
            int _tileX;
            int _x;
            int _y;
            _tileY = (int)(short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            _tileX = tile - DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile;
            _dIndex = 0;
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.writeIndex = 1;
            maxDestinations = maxDestinations * 2;
            this->searchQueue.readIndex = 0;
            if (maxDestinations > 500) {
                maxDestinations = 500;
            } else if (maxDestinations < 50) {
                maxDestinations = 50;
            }
            this->searchQueue.tilesQueue[0] = tile;
            this->searchQueue.yQueue[0] = (short)_tileY;
            this->searchQueue.xQueue[0] = (short)_tileX;
            DAT_TileMapState::instance.SearchDistanceLayer[tile] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile < 0 || _tile >= 0x13a10)
                    break;
                _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[_tile];
                if ((80400 < (int)this->searchQueue.currentDistance) || (10 < (int)this->searchQueue.currentDistance))
                    break;
                for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                    _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[_candidate] != this->searchGeneration
                        && (area == (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate]
                            || (iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                              calculateCanPlayerUnitsNavigateToAreaFromArea,
                                    DAT_PathFindingState::ptr)(playerID, (dword)((int)(area)),
                                    (dword)((int)((
                                        int)(short)DAT_TileMapState::instance.PathConnectionLayer[_candidate])),
                                    0),
                                iVar2 != 0))) {
                        /*
                          queue tiles in area that are navigatible by this player without climbing
                         */
                        DAT_TileMapState::instance.SearchDistanceLayer[_candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[_candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                  .short_.xOffset
                            + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                  .short_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
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
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                piVar3 = &this->searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    /*
                      no wall tower gatehouse crenel nor keep
                     */
                    if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x10000300U) == 0) {
                        _y = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        _x = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                        pXVar4 = DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder;
                        do {
                            int _candidate2
                                = DAT_ViewportRenderState::instance.translationMatrix[pXVar4->y + _y].addXgetTile
                                + pXVar4->x + _x;
                            if ((DAT_TileMapState::instance.LogicLayer[_candidate2] & 0x300U) != 0
                                && (DAT_TileMapState::instance.LogicLayer[_candidate2] & 0x400000U) == 0
                                && (DAT_TileMapState::instance.WallOwnerLayer[_candidate2] & 7) + 1 != playerID) {
                                /*
                                  candidate 2 is wall tower gatehouse, or crenel (variation)
                                 */
                                if (_candidate2 != 0) {
                                    *piVar3 = _candidate2;
                                    _dIndex = _dIndex + 1;
                                    ((PathHelper12*)(piVar3 + -1))->tile1 = _tile;
                                    piVar3 = piVar3 + 3;
                                    if (_dIndex >= maxDestinations) {
                                        return;
                                    }
                                    this->searchQueue.tilesQueue[this->searchQueue.readIndex] = -1;
                                }
                                break;
                            }
                            pXVar4 = pXVar4 + 1;
                        } while ((int)pXVar4 < 0xb39238);
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
            }
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                piVar3 = &((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_dIndex].tile2OrAHelper;
                do {
                    iVar2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    /*
                      no wall tower gatehouse crenel nor keep
                     */
                    if ((DAT_TileMapState::instance.LogicLayer[iVar2] & 0x10000300U) == 0 && iVar2 != -1) {
                        ((PathHelper12*)(piVar3 + -1))->tile1 = iVar2;
                        *piVar3 = 0;
                        _dIndex = _dIndex + 1;
                        piVar3 = piVar3 + 3;
                        if (_dIndex >= maxDestinations) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
            }
            this->searchQueue.destinationsArray[_dIndex].tile1 = 0;
            ((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_dIndex].tile2OrAHelper = 0;
            return;
        }

    }
}
}
