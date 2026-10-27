#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F260
        void UnitsState::setMoveDelayForUnitsOnSameTiles(int unitID, int unitIDCurrentTilePosition)
        {
            int _lowestMovementSpeed = 0x14;
            short _unitIDArray[2010];
            this->units[unitID].unitOrderWhenOnSameTile = 0;
            if (this->units[unitID].isHiddenInBuilding != 0) {
                return;
            }
            this->units[unitID].drawNeutralColor = 0;
            /* if current tile position is not occupied */
            if (DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] == 0) {
                DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] = (ushort)unitID;
                this->units[unitID].nextUnitOnTheSameTile = 0;
                return;
            }
            /* if current tile position is occupied: build the ID-sorted chain including unitID */
            int _isInserted = 0;
            int _unitIDOfAUnitOnSameTile = (short)DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition];
            int _index = 0;
            do {
                if (unitID < _unitIDOfAUnitOnSameTile && _isInserted == 0) {
                    _unitIDArray[_index] = (short)unitID;
                    _index++;
                    _isInserted = 1;
                }
                _unitIDArray[_index] = (short)_unitIDOfAUnitOnSameTile;
                _unitIDOfAUnitOnSameTile = (short)this->units[_unitIDOfAUnitOnSameTile].nextUnitOnTheSameTile;
                if (_unitIDOfAUnitOnSameTile <= 0) {
                    break;
                }
                _index++;
            } while (_index < 2000);
            _index++;
            if (_isInserted == 0) {
                _unitIDArray[_index] = (short)unitID;
                _index++;
            }
            _unitIDArray[_index] = 0;
            int _previousUnitID = _unitIDArray[0];
            DAT_TileMapState::instance.UnitLayer[unitIDCurrentTilePosition] = (ushort)_previousUnitID;
            this->units[_previousUnitID].unitOrderWhenOnSameTile = 0;
            for (int _order = 1; _order < 2001; ++_order) {
                int _id = _unitIDArray[_order];
                this->units[_previousUnitID].nextUnitOnTheSameTile = (ushort)_id;
                _previousUnitID = _id;
                if (_id <= 0) {
                    break;
                }
                this->units[_id].unitOrderWhenOnSameTile = (short)_order;
            }
            int i = 0;
            do {
                int _id = _unitIDArray[i];
                if (_id <= 0) {
                    break;
                }
                if (this->units[_id].movementState == 2 && this->units[_id].movementSpeed < _lowestMovementSpeed) {
                    _lowestMovementSpeed = this->units[_id].movementSpeed;
                }
                i++;
            } while (i < 2000);
            i = 0;
            do {
                int _id = _unitIDArray[i];
                if (_id <= 0) {
                    break;
                }
                if (this->units[_id].movementState == 2 && this->units[_id].moveDelay == 0) {
                    if (this->units[_id].movementSpeed > _lowestMovementSpeed) {
                        this->units[_id].moveDelay = this->units[_id].unitOrderWhenOnSameTile / 2 + 1;
                    } else {
                        _lowestMovementSpeed = 0;
                    }
                }
                i++;
            } while (i < 2000);
        }

    }
}
}
