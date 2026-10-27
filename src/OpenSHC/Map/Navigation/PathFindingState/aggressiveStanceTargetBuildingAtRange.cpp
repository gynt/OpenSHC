#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A1230
        void PathFindingState::aggressiveStanceTargetBuildingAtRange(int unitID, int maxDistance)
        {
            int _nextCandidate;
            int _tile;
            uint uVar5;
            int sVar1 = (int)DAT_UnitsState::instance.units[unitID].x;
            int sVar2 = (int)DAT_UnitsState::instance.units[unitID].y;
            this->calculations = this->calculations + 1;
            this->ALG_ResultTile = 0;
            this->ALG_ResultY = 0;
            this->ALG_ResultX = 0;
            if ((uint)sVar1 > 399 || (uint)sVar2 > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[sVar2 * 400 + sVar1] == '\0') {
                return;
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
            this->searchQueue.yQueue[0] = (short)sVar2;
            this->searchQueue.xQueue[0] = (short)sVar1;
            this->searchQueue.tilesQueue[0] = DAT_ViewportRenderState::instance.translationMatrix[sVar2].addXgetTile + sVar1;
            DAT_TileMapState::instance.SearchDistanceLayer[this->searchQueue.tilesQueue[0]]
                = (short)this->searchQueue.currentDistance;
            DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if ((DAT_TileMapState::instance.LogicLayer[this->searchQueue.tilesQueue[0]] & 0x30) == 0) {
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    _tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    if (_tile < 0) {
                        return;
                    }
                    if (_tile >= 0x13a10) {
                        return;
                    }
                    sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[_tile];
                    if (0x13a10 < (int)this->searchQueue.currentDistance) {
                        return;
                    }
                    if ((int)this->searchQueue.currentDistance > maxDistance) {
                        return;
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 2) {
                        _nextCandidate
                            = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + _tile;
                        uVar5 = DAT_TileMapState::instance.LogicLayer[_nextCandidate];
                        if (DAT_TileMapState::instance.SearchGenerationLayer[_nextCandidate] != this->searchGeneration) {
                            short sVar3 = DAT_TileMapState::instance.BuildingLayer[_nextCandidate];
                            if (sVar3 != 0) {
                                int uVar7 = (int)sVar3;
                                if (DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_UnitsState::instance.units[unitID].owner]
                                    != DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_BuildingsState::instance.buildings[uVar7].owner]) {
                                    switch (DAT_BuildingsState::instance.buildings[uVar7].buildingType) {
                                    case OpenSHC::Map::Buildings::BT_STOCKPILE:
                                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                                    case OpenSHC::Map::Buildings::BT_OILSMELTER_PART:
                                    case OpenSHC::Map::Buildings::BT_SIGNPOST:
                                    case OpenSHC::Map::Buildings::BT_PARADEGROUND:
                                    case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                                    case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                                    case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                                    case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                                    case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
                                    case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                                    case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
                                    case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
                                    case OpenSHC::Map::Buildings::BT_KEEPDOOR:
                                        break;
                                    default:
                                        BOOLEnum BVar3 = MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHasHealthProperty,
                                            DAT_BuildingsState::ptr)(uVar7, _nextCandidate);
                                        if (BVar3 != FALSE) {
                                            this->ALG_ResultTile = _nextCandidate;
                                            return;
                                        }
                                    }
                                }
                            } else {
                                /*
                                  Is wall or gatehouse
                                 */
                                /*
                                  TODO:FIXME: WallOwnerLayer contains player ids, not necessarily team ids
                                 */
                                if ((uVar5 & 0x100) != 0
                                    && (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                                        || (DAT_GameState::instance.mapAndTime.skirmishStrongWalls == 0))
                                    && DAT_GameState::instance.mapAndTime
                                            .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[_nextCandidate] & 7)
                                                + 1]
                                        != DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_UnitsState::instance.units[unitID].owner]) {
                                    this->ALG_ResultTile = _nextCandidate;
                                    return;
                                }
                            }
                            if ((uVar5 & 0x30) == 0) {
                                /*
                                  If not the border, enqueue next candidate
                                 */
                                DAT_TileMapState::instance.SearchDistanceLayer[_nextCandidate]
                                    = (short)this->searchQueue.currentDistance + 1;
                                DAT_TileMapState::instance.SearchGenerationLayer[_nextCandidate] = (short)this->searchGeneration;
                                this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                          .short_.xOffset
                                    + (short)sVar1;
                                this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                    = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                          .short_.yOffset
                                    + (short)sVar2;
                                this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _nextCandidate;
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
            }
            return;
        }

    }
}
}
