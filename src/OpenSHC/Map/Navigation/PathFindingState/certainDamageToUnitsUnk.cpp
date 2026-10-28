#include "../PathFindingState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A3B20
        undefined4 PathFindingState::damageEnemyUnitsInRadiusTacticalPower(
            int param_1, int param_2, int param_3, int param_4, undefined4 param_5)
        {
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            int _startY = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
            int _startX = param_1 - DAT_ViewportRenderState::instance.translationMatrix[_startY].addXgetTile;
            int _spreadDirection = 1;
            uint _probeX = _startX + 100;
            if (_probeX > 399 || (uint)_startY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_startY * 400 + _probeX] == '\0') {
                _spreadDirection = -1;
            }
            this->searchQueue.yQueue[0] = (short)_startY;
            this->searchQueue.tilesQueue[0] = param_1;
            this->searchQueue.xQueue[0] = (short)_startX;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            DAT_TileMapState::instance.SearchDistanceLayer[param_1] = 1;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            EntityType _entityType = OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT;
            if ((char)param_5 == '\0') {
                _entityType = OpenSHC::Map::Entities::ET_CATAPULT;
            }
            if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                return (undefined4)(0);
            }
            do {
                uint _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (_tile > 0x13a0f) {
                    return (undefined4)(0);
                }
                int _x = this->searchQueue.xQueue[this->searchQueue.readIndex];
                int _y = this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = DAT_TileMapState::instance.SearchDistanceLayer[_tile];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    return (undefined4)(0);
                }
                if ((int)this->searchQueue.currentDistance > param_2) {
                    return (undefined4)(0);
                }
                int _unitID = (short)DAT_TileMapState::instance.UnitLayer[_tile];
                while (_unitID != 0) {
                    if (param_3 != 0
                        && DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[_unitID].owner]
                            != DAT_GameState::instance.mapAndTime.playerTeams[param_3]
                        && DAT_UnitsState::instance.units[_unitID].unitType != OpenSHC::Map::Units::UT_LORD) {
                        DAT_UnitsState::instance.units[_unitID].health
                            = DAT_UnitsState::instance.units[_unitID].health - param_4;
                        if (DAT_UnitsState::instance.units[_unitID].health <= 0
                            && DAT_UnitsState::instance.units[_unitID].dying == 0) {
                            DAT_UnitsState::instance.units[_unitID].health = 0;
                            DAT_UnitsState::instance.units[_unitID].dying = 1;
                            DAT_UnitsState::instance.units[_unitID].animationCycleNumber = 0;
                            if ((char)param_5 != '\0') {
                                DAT_UnitsState::instance.units[_unitID].state.generic
                                    = OpenSHC::Map::Units::States::US_DEATH_01;
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                    DAT_SFXState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                                    (int)DAT_UnitsState::instance.units[_unitID].y, OpenSHC::DE::SHCDE::FX_DEATH_ARROW);
                            } else {
                                DAT_UnitsState::instance.units[_unitID].state.generic
                                    = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                    DAT_SFXState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                                    (int)DAT_UnitsState::instance.units[_unitID].y, OpenSHC::DE::SHCDE::FX_SPLAT);
                            }
                            DAT_UnitsState::instance.units[_unitID].movementState = 1;
                        }
                        int _healthPercentage;
                        if (DAT_UnitsState::instance.units[_unitID].maxHealth == 0) {
                            _healthPercentage = 100;
                        } else {
                            _healthPercentage = (DAT_UnitsState::instance.units[_unitID].health * 100)
                                / DAT_UnitsState::instance.units[_unitID].maxHealth;
                        }
                        DAT_UnitsState::instance.units[_unitID].healthPercentage = (short)_healthPercentage;
                        DAT_UnitsState::instance.units[_unitID].healthbar = (short)_healthPercentage / 10;
                    }
                    _unitID = (short)DAT_UnitsState::instance.units[_unitID].nextUnitOnTheSameTile;
                }
                int _random = SEC_RNG::instance.currentNumber2;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                if ((_random & 1) == 0) {
                    int _random2 = SEC_RNG::instance.currentNumber2;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnEntity, DAT_EntityState::ptr)(0,
                        (undefined4)((int)(param_3)), 0, ((_random >> 4) % 50 + 50) * _spreadDirection + _x * 8,
                        _y * 8 + _random2 % 50 - 25,
                        (int)DAT_TileMapState::instance.HeightLayer[_tile] + _random % 1000 + 500, _x * 8 + 4,
                        _y * 8 + 4, (int)(DAT_TileMapState::instance.HeightLayer[_tile]), _entityType, 0);
                }
                for (int _direction = 0; _direction < 8; _direction++) {
                    int _candidate = DAT_TileMapState::instance.directionTranslationMatrix[_y][_direction] + _tile;
                    if (DAT_TileMapState::instance.SearchGenerationLayer[_candidate] != this->searchGeneration
                        && (DAT_TileMapState::instance.LogicLayer[_candidate] & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[_candidate]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[_candidate] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.xOffset + _x;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].short_.yOffset + _y;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _candidate;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }
                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if ((int)this->searchQueue.readIndex >= 0x13a10) {
                    this->searchQueue.readIndex = 0;
                }
            } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            return (undefined4)(0);
        }

    }
}
}
