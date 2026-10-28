#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00534240
        int UnitsState::stopUnitIfNextToTarget(int unitID)
        {
            int _isNear = 0;
            if (this->units[unitID].targetedBuildingTile == 0) {
                return 0;
            }
            if (this->units[unitID].occupiesNeighbourTiles == 0) {
                return 0;
            }
            uint _tile;
            for (int direction = 0; direction < 8; ++direction) {
                _tile = DAT_TileMapState::instance.directionTranslationMatrix[this->units[unitID].y][direction]
                    + this->units[unitID].tile;
                if (_tile == this->units[unitID].targetedBuildingTile) {
                    _isNear = 1;
                    break;
                }
            }
            if (!_isNear) {
                // The original scans all 8 directions even after a hit, so _tile ends up as the neighbour in the
                // last direction (0x005342B7..0x00534319, edx at 0x00534336), not the one next to the target.
                int _y = this->units[unitID].y;
                for (int direction = 0; direction < 8; ++direction) {
                    _tile = DAT_TileMapState::instance.directionTranslationMatrix[_y][direction]
                        + this->units[unitID].tile;
                    for (int secondDirection = 0; secondDirection < 8; ++secondDirection) {
                        if (DAT_TileMapState::instance.directionTranslationMatrix[_y
                                + DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[direction]
                                    .int_.yOffset][secondDirection]
                                + _tile
                            == this->units[unitID].targetedBuildingTile) {
                            _isNear = 1;
                            break;
                        }
                    }
                }
                if (!_isNear) {
                    return 0;
                }
            }
            if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x100U) != 0
                || DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::makeUnitStopWalkingByClearingPathProgressState, this)(unitID);
                return (uint)(this->units[unitID].subTileStepProgress >= 8);
            }
            return -1;
        }

    }
}
}
