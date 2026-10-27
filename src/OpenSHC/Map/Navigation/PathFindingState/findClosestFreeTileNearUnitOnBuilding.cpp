#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049D880
        undefined4 PathFindingState::findClosestFreeTileNearUnitOnBuilding(
            int buildingID, int unitID, int x, int y, int* pX, int* pY)
        {
            int _lowestDist;
            uint _tile;
            int _unitArea;
            int _x;
            int _y;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            _lowestDist = 10000;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            _unitArea = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            *pX = (int)DAT_UnitsState::instance.units[unitID].x;
            *pY = (int)DAT_UnitsState::instance.units[unitID].y;
            this->searchQueue.yQueue[0] = DAT_UnitsState::instance.units[unitID].y;
            this->searchQueue.xQueue[0] = DAT_UnitsState::instance.units[unitID].x;
            this->searchQueue.tilesQueue[0] = DAT_UnitsState::instance.units[unitID].tile;
            DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < _tile) {
                    return (undefined4)(1);
                }
                _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                int _absDistX = abs(_x - x);
                int _absDistY = abs(_y - y);
                if (_absDistX > _absDistY) {
                    _absDistY = _absDistX;
                }
                if (_absDistY < _lowestDist) {
                    /*
                      lowest manhatten distance
                     */
                    *pX = _x;
                    *pY = _y;
                    _lowestDist = _absDistY;
                }
                this->searchQueue.currentDistance = DAT_TileMapState::instance.SearchDistanceLayer[_tile];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    break;
                }
                for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[_candidate] != this->searchGeneration
                        && (short)DAT_TileMapState::instance.PathConnectionLayer[_candidate] == _unitArea
                        && DAT_TileMapState::instance.BuildingLayer[_candidate] == buildingID
                        && DAT_TileMapState::instance.UnitLayer[_candidate] == 0) {
                        /*
                          queue free spaces in the same area as the unit on the same building as the   unit
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

                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            return (undefined4)(1);
        }

    }
}
}
