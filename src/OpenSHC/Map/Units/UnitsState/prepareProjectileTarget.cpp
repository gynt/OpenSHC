#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053CBD0
        int UnitsState::prepareProjectileTarget(int shooterID, int targetID, int param_3)
        {
            int _targetFixedRng = 0;
            if (targetID == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setRandomShootLocation, this)(shooterID,
                    this->units[shooterID].shootTargetMicroX, this->units[shooterID].shootTargetMicroY,
                    this->units[shooterID].shootTargetZ);
            } else {
                _targetFixedRng = this->units[targetID].fixedRng;
                if (this->units[targetID].movementState != 2) {
                    this->units[shooterID].shootTargetMicroX = this->units[targetID].x * 8 + 4;
                    this->units[shooterID].shootTargetMicroY = this->units[targetID].y * 8 + 4;
                    this->units[shooterID].shootTargetZ
                        = this->units[targetID].buildingHeight + this->units[targetID].terrainOrClimbHeight;
                } else {
                    int _lead = (param_3 * 133) / 100;
                    int _adjustment;
                    /* todo:fixme:ucp: this if-else should be improved to also trigger when the
                       targetID has negative height (walking in pitch or moat) */
                    if (this->units[targetID].stateBasedSpeed != 0) {
                        _adjustment = _lead / 8;
                    } else if (this->units[targetID].calculatedMovementSpeed > 1) {
                        _adjustment = _lead / (this->units[targetID].calculatedMovementSpeed << 4);
                    } else {
                        _adjustment = _lead / 16;
                    }
                    this->units[shooterID].shootTargetMicroX = this->units[targetID].x * 8 + 4;
                    this->units[shooterID].shootTargetMicroY = this->units[targetID].y * 8 + 4;
                    this->units[shooterID].shootTargetZ
                        = this->units[targetID].buildingHeight + this->units[targetID].terrainOrClimbHeight;
                    if (this->units[targetID].facingDirection == 0) {
                        this->units[shooterID].shootTargetMicroY -= (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 1) {
                        this->units[shooterID].shootTargetMicroY -= (short)_adjustment;
                        this->units[shooterID].shootTargetMicroX += (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 2) {
                        this->units[shooterID].shootTargetMicroX += (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 3) {
                        this->units[shooterID].shootTargetMicroY += (short)_adjustment;
                        this->units[shooterID].shootTargetMicroX += (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 4) {
                        this->units[shooterID].shootTargetMicroY += (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 5) {
                        this->units[shooterID].shootTargetMicroY += (short)_adjustment;
                        this->units[shooterID].shootTargetMicroX -= (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 6) {
                        this->units[shooterID].shootTargetMicroX -= (short)_adjustment;
                    } else if (this->units[targetID].facingDirection == 7) {
                        this->units[shooterID].shootTargetMicroY -= (short)_adjustment;
                        this->units[shooterID].shootTargetMicroX -= (short)_adjustment;
                    }
                }
            }
            /* the original returns whatever the switch below left in the return register on
               the paths that adjust nothing, which is the type's index into it; the value is
               not a meaningful result, but callers of those paths are given it */
            int _unhandledTypeResult;
            int _scatter;
            if (this->units[shooterID].terrainOrClimbHeight > this->units[shooterID].shootTargetZ) {
                _unhandledTypeResult = (short)this->units[shooterID].unitType + -0x16;
                switch (this->units[shooterID].unitType) {
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                    _scatter = 0x14;
                    break;
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    _scatter = 10;
                    break;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    _scatter = 0x32;
                    break;
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                    _scatter = 0x3c;
                    break;
                case OpenSHC::Map::Units::UT_E_ARCHER:
                case OpenSHC::Map::Units::UT_E_ARCHER_DEBUG:
                    return _unhandledTypeResult;
                default:
                    return _unhandledTypeResult;
                }
            } else {
                _scatter = this->units[shooterID].shootTargetZ - this->units[shooterID].terrainOrClimbHeight;
                if (_scatter > 0x4b) {
                    _scatter = _scatter + _scatter / 2;
                }
                _unhandledTypeResult = (short)this->units[shooterID].unitType + -0x16;
                switch (this->units[shooterID].unitType) {
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                    _scatter = _scatter + 0x28;
                    break;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    _scatter = _scatter + 0x3c;
                    break;
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                    _scatter = _scatter + 0x46;
                    break;
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    return _unhandledTypeResult;
                case OpenSHC::Map::Units::UT_E_ARCHER:
                case OpenSHC::Map::Units::UT_E_ARCHER_DEBUG:
                    break;
                default:
                    break;
                }
                if (_scatter <= 0) {
                    return _unhandledTypeResult;
                }
                if (_scatter > 0x118) {
                    _scatter = 0x118;
                }
            }
            int _rng = (short)SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            int _rngHundreds = (_rng / 300) * 300;
            if (_rng - _rngHundreds >= _scatter) {
                return _rngHundreds;
            }
            if ((_rng & 7) < 2) {
                _scatter = _scatter / 4;
                if (_scatter == 0) {
                    _scatter = 1;
                }
                int _halfScatter = _scatter / 2;
                this->units[shooterID].shootTargetMicroX
                    += (short)(abs(_rng / 512 + (int)this->units[shooterID].fixedRng) % _scatter - _halfScatter);
                int _verticalRng = abs(_rng + _targetFixedRng);
                this->units[shooterID].shootTargetMicroY += (short)(_verticalRng % _scatter - _halfScatter);
                return _verticalRng / _scatter;
            }
            if ((_rng & 7) < 6) {
                _scatter = _scatter / 6;
                if (_scatter == 0) {
                    _scatter = 1;
                }
                int _heightOffset = abs((int)this->units[shooterID].fixedRng + _rng) % _scatter + 0x14;
                int _newZ;
                if ((int)this->units[shooterID].shootTargetZ < _heightOffset + 8) {
                    _newZ = (ushort)this->units[shooterID].shootTargetZ + _heightOffset;
                } else {
                    _newZ = (ushort)this->units[shooterID].shootTargetZ - _heightOffset;
                }
                this->units[shooterID].shootTargetZ = (short)_newZ;
                return _newZ;
            }
            _scatter = _scatter / 6;
            if (_scatter == 0) {
                _scatter = 1;
            }
            int _heightRng = abs(_rng + _targetFixedRng);
            this->units[shooterID].shootTargetZ = this->units[shooterID].shootTargetZ + (short)(_heightRng % _scatter) + 0x28;
            return _heightRng / _scatter;
        }

    }
}
}
