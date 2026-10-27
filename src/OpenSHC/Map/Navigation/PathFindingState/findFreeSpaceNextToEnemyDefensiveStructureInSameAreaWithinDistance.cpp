#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004A7F50
        void PathFindingState::findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance(
            int tile, int maxDestinations, int* area, int playerID, int shortenedDistance, int direction)
        {
            int _areaC;
            int _candidate;
            int _candidate2;
            int* _dest;
            XYPair* _offset;
            BuildingTypeInt _buildingType;
            int _index;
            int _dIndex;
            int _maxDistance;
            int _tile2;
            int _origY;
            int _x;
            int _y;
            uint _tile;
            _origY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            _x = tile - DAT_ViewportRenderState::instance.translationMatrix[_origY].addXgetTile;
            _dIndex = 0;
            _maxDistance = 10;
            if (shortenedDistance == 1) {
                _maxDistance = 3;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    160800, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            maxDestinations = maxDestinations * 2;
            if (maxDestinations > 500) {
                maxDestinations = 500;
            } else if (maxDestinations < 50) {
                maxDestinations = 50;
            }
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.tilesQueue[0] = tile;
            this->searchQueue.yQueue[0] = (short)_origY;
            this->searchQueue.xQueue[0] = (short)_x;
            DAT_TileMapState::instance.SearchDistanceLayer[tile] = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < _tile) {
                    break;
                }
                _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.SearchDistanceLayer[_tile];
                if (80400 < (int)this->searchQueue.currentDistance) {
                    break;
                }
                if ((int)this->searchQueue.currentDistance > _maxDistance) {
                    break;
                }
                for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                    _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[_candidate] != this->searchGeneration) {
                        _areaC = (short)DAT_TileMapState::instance.PathConnectionLayer[_candidate];
                        if ((int)area == _areaC
                            || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                                   DAT_PathFindingState::ptr)(playerID, (dword)((int)(area)), (dword)_areaC, 0)
                                != 0) {
                            /*
                              queue tiles in same area that are pathable without climbing
                             */
                            DAT_TileMapState::instance.SearchDistanceLayer[_candidate]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.SearchGenerationLayer[_candidate] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.xOffset
                                + (short)_x;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.yOffset
                                + (short)_y;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
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
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                _dest = &this->searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    _tile2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if ((DAT_TileMapState::instance.LogicLayer[_tile2] & 0x10000300U) == 0) {
                        _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                        _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                        _candidate2 = 0;
                        _offset = DAT_ClimbLogicDefinedData::instance
                                      .OrderedOrientationBasedCardinalDirectionList[direction];
                        for (_index = 0; _index < 4; _index = _index + 1) {
                            _candidate = DAT_ViewportRenderState::instance.translationMatrix[_offset->y + _y].addXgetTile
                                + _offset->x + _x;
                            /*
                              if a wall gatehouse crenel keep and not a stockpile, and not a keep, and wall   is of
                              enemy... break
                             */
                            uint _logic = DAT_TileMapState::instance.LogicLayer[_candidate];
                            if ((_logic & 0x10000300U) != 0 && (_logic & 2U) == 0
                                && (DAT_TileMapState::instance.BuildingLayer[_candidate] == 0
                                    || ((_buildingType = (BuildingTypeInt)(short)DAT_BuildingsState::instance
                                             .buildings[DAT_TileMapState::instance.BuildingLayer[_candidate]]
                                             .buildingType,
                                        _buildingType != OpenSHC::Map::Buildings::BT_STOCKPILE
                                            && (2 < (uint)(_buildingType - OpenSHC::Map::Buildings::BT_MANORHOUSE)))))
                                && DAT_GameState::instance.mapAndTime
                                        .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[_candidate] & 7) + 1]
                                    != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                                _candidate2 = _candidate;
                                break;
                            }
                            _offset = _offset + 1;
                        }
                        if ((shortenedDistance != 1 || DAT_TileMapState::instance.UnitLayer[_candidate2] == 0)
                            && _candidate2 != 0) {
                            _dest[-1] = _tile2;
                            _dIndex = _dIndex + 1;
                            *_dest = _candidate2;
                            _dest = _dest + 3;
                            if (_dIndex >= maxDestinations) {
                                return;
                            }
                            this->searchQueue.tilesQueue[this->searchQueue.readIndex] = -1;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
            }
            this->searchQueue.readIndex = 0;
            if (0 < (int)this->searchQueue.writeIndex) {
                _dest = &this->searchQueue.destinationsArray[_dIndex].tile2OrAHelper;
                do {
                    _tile2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if ((DAT_TileMapState::instance.LogicLayer[_tile2] & 0x10000300U) == 0 && _tile2 != -1) {
                        _dest[-1] = _tile2;
                        *_dest = 0;
                        _dIndex = _dIndex + 1;
                        _dest = _dest + 3;
                        if (_dIndex >= maxDestinations) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while ((int)this->searchQueue.readIndex < (int)this->searchQueue.writeIndex);
            }
            this->searchQueue.destinationsArray[_dIndex].tile1 = 0;
            this->searchQueue.destinationsArray[_dIndex].tile2OrAHelper = 0;
            return;
        }

    }
}
}
