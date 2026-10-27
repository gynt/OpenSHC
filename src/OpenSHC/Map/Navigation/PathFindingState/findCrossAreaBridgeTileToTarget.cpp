#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          BFS from unit param_1's current tile, expanding within its own PathConnectionLayer area or   through
          walls/structures. When a tile in a different area is encountered, checks whether that   area connects to the
          target area (param_2, param_3) via   calculateCanPlayerUnitsNavigateToAreaFromArea. Selects the neighbour tile
          with the minimum   Chebyshev distance to the target. Stores the source tile in ALG_TargetTile and the bridge
          tile in   ALG_ResultTile. Returns 1 on success, 0 if no bridge found.      renamed by: Claude Sonnet 4.6
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A6AB0
        undefined4 PathFindingState::findCrossAreaBridgeTileToTarget(int param_1, uint param_2, uint param_3)
        {
            int _sourceTile = 0;
            int _bridgeTile = 0;
            int _bestDistance = 10000;
            if (param_2 > 399 || param_3 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[param_3 * 400 + param_2] == '\0') {
                return (undefined4)(0);
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.readIndex = 0;
            int _unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[param_1].tile];
            int _targetArea = (short)DAT_TileMapState::instance
                                  .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile
                                      + param_2];
            this->searchQueue.yQueue[0] = DAT_UnitsState::instance.units[param_1].y;
            this->searchQueue.xQueue[0] = DAT_UnitsState::instance.units[param_1].x;
            this->searchQueue.tilesQueue[0] = DAT_UnitsState::instance.units[param_1].tile;
            DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                return (undefined4)(0);
            }
            do {
                uint _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < _tile)
                    break;
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.SearchDistanceLayer[_tile];
                if (0x13a10 < (int)this->searchQueue.currentDistance)
                    break;
                for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[_candidate] == this->searchGeneration) {
                        continue;
                    }
                    if ((DAT_TileMapState::instance.LogicLayer[_candidate] & 0x400000U) != 0) {
                        continue;
                    }
                    int _area = (short)DAT_TileMapState::instance.PathConnectionLayer[_candidate];
                    if (_area == _unitArea || (DAT_TileMapState::instance.LogicLayer[_candidate] & 0x10000100U) != 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[_candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[_candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset
                            + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset
                            + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                                   DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[param_1].owner,
                                   (dword)_area, (dword)_targetArea,
                                   (int)(DAT_UnitsState::instance.units[param_1].unitCanClimb))
                        != 0) {
                        int _absY = abs(
                            DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset - param_3 + _y);
                        int _distance = abs(
                            DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset - param_2 + _x);
                        if (_distance <= _absY) {
                            _distance = _absY;
                        }
                        if (_distance < _bestDistance) {
                            _bestDistance = _distance;
                            _sourceTile = _tile;
                            _bridgeTile = _candidate;
                        }
                    }
                }
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            if (_bestDistance < 10000) {
                this->ALG_TargetTile = _sourceTile;
                this->ALG_ResultTile = _bridgeTile;
                return (undefined4)(1);
            }
            return (undefined4)(0);
        }

    }
}
}
