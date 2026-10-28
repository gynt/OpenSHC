#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Computes the AI Zone Layer - a flood-fill from the player's keep that marks accessible areas.   This creates a
          "zone of control" or "accessible territory" map for strategic AI decisions.      The algorithm works in
          phases:   Phase 1: Flood-fill through walkable/connected areas (marks tiles with value 1)   Phase 2: Expand
          into surrounding tiles with weighted distances based on terrain difficulty      @param this - PathFindingState
          object pointer   @param attackedPlayerID - The player whose keep/territory to analyze   @param canReachKeep -
          If non-zero, limits expansion to 2000 tiles (early termination)      decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A4470
        void PathFindingState::computeAIZoneLayer(int attackedPlayerID, int canReachKeep, int param_3)
        {
            uint _logic;
            int _offsetTile;
            int _direction;
            int* _pDirectionTranslation;
            int _candidateTile;
            BuildingTypeShort _buildingType;
            int _candidateY;
            int _pathConnection;
            int _pass;
            /*
                 === VALIDATE PLAYER HAS A KEEP ===   Only compute AI zones if the player has a keep (main castle)
             */
            if (DAT_GameState::instance.playerDataArray[attackedPlayerID].keep.id != 0) {
                /*
                     === INITIALIZE BFS STARTING FROM KEEP ===
                 */
                this->searchQueue.currentDistance = 1;
                this->searchQueue.readIndex = 0;
                this->searchQueue.writeIndex = 1;
                /*
                     Get the keep's position (specifically the campfire tile inside the keep)
                 */
                this->searchQueue.yQueue[0]
                    = (short)DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.yEntry;
                this->searchQueue.tilesQueue[0]
                    = DAT_GameState::instance.playerDataArray[attackedPlayerID].campground.xEntry
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_GameState::instance.playerDataArray[attackedPlayerID]
                                  .campground.yEntry]
                          .addXgetTile;
                /*
                     Mark the keep tile as AI Zone with value 1 (the starting point)
                 */
                DAT_TileMapState::instance.AIZoneLayer[this->searchQueue.tilesQueue[0]] = (byte)this->searchQueue.currentDistance;
                /*
                     Repurpose variable as iteration counter (alternates between 0 and 1)
                 */
                _pass = 0;
                /*
                     Update path linkage (possibly opens gates or updates navigation mesh)
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
                while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                    /*
                        === PHASE 1: FLOOD-FILL THROUGH WALKABLE/CONNECTED AREAS ===
                     */
                    this->searchQueue.previousReadIndex = this->searchQueue.readIndex;
                    while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                        _candidateY = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                        _candidateTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _pDirectionTranslation = DAT_TileMapState::instance.directionTranslationMatrix[_candidateY];
                        for (_direction = 0; _direction < 8; _direction++) {
                            _offsetTile = *_pDirectionTranslation + _candidateTile;
                            /*
                              Add tile to AI zone if: not already marked, has path connection and either normal
                              pathfinding allows movement in this direction or there is a gatehouse on the tile
                             */
                            if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] <= 0) {
                                _pathConnection = (short)DAT_TileMapState::instance.PathConnectionLayer[_offsetTile];
                                if (_pathConnection != 0
                                    && ((DAT_TileMapState::instance.PathLinkageLayer[_candidateTile]
                                            & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[_direction])
                                            != 0
                                        || (DAT_TileMapState::instance.BuildingLayer[_offsetTile] != 0
                                            && ((_buildingType = DAT_BuildingsState::instance
                                                     .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                                     .buildingType,
                                                _buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
                                                    || _buildingType == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))))) {
                                    DAT_TileMapState::instance.AIZoneLayer[_offsetTile] = 1;
                                    this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                        = DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction]
                                              .short_.yOffset
                                        + (short)_candidateY;
                                    this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = _offsetTile;
                                    this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                                    if ((int)this->searchQueue.writeIndex >= 80400)
                                        goto LAB_004a4914;
                                }
                            }
                            _pDirectionTranslation = _pDirectionTranslation + 1;
                        }
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if ((int)this->searchQueue.readIndex >= 80400) {
                            this->searchQueue.readIndex = 0;
                        }
                        /*
                          === EARLY TERMINATION CONDITIONS ===
                         */
                        if (canReachKeep != 0 && (int)this->searchQueue.writeIndex >= 2000)
                            goto LAB_004a4914;
                        if ((int)this->searchQueue.writeIndex >= 6000)
                            goto LAB_004a4914;
                    }
                    /*
                      === PHASE 2: EXPAND INTO DIFFICULT TERRAIN ===   with distance penalties based on terrain type
                     */
                    this->searchQueue.readIndex = this->searchQueue.previousReadIndex;
                    this->searchQueue.nextWriteIndex = this->searchQueue.writeIndex;
                    while (this->searchQueue.readIndex != this->searchQueue.nextWriteIndex) {
                        _candidateTile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        this->searchQueue.currentDistance
                            = (char)DAT_TileMapState::instance.AIZoneLayer[_candidateTile] + 1;
                        _pDirectionTranslation = DAT_TileMapState::instance
                                                     .directionTranslationMatrix[this->searchQueue
                                                             .yQueue[this->searchQueue.readIndex]];
                        for (_direction = 0; _direction < 8; _direction++) {
                            _offsetTile = _pDirectionTranslation[_direction] + _candidateTile;
                            if ((char)DAT_TileMapState::instance.AIZoneLayer[_offsetTile] <= 0
                                && (_logic = DAT_TileMapState::instance.LogicLayer[_offsetTile], (_logic & 0x31) == 0)
                                && (DAT_TileMapState::instance.BuildingLayer[_offsetTile] == 0
                                    || DAT_BuildingsState::instance
                                            .buildings[DAT_TileMapState::instance.BuildingLayer[_offsetTile]]
                                            .blocksAIZoneSpread
                                        == '\0')) {
                                if ((_logic & 0x100) != 0) {
                                    /*
                                      wall or gatehouse: makes fortifications "farther" strategically
                                     */
                                    DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                        = (byte)this->searchQueue.currentDistance + 6;
                                } else if ((_logic & 0x40000000) != 0 && _pass != 0) {
                                    /*
                                      Moat discount making fortified areas closer in AI Zone calculations
                                     */
                                    DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                        = (byte)this->searchQueue.currentDistance - 1;
                                } else {
                                    DAT_TileMapState::instance.AIZoneLayer[_offsetTile]
                                        = (byte)this->searchQueue.currentDistance;
                                }
                            }
                        }
                        this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                        if ((int)this->searchQueue.readIndex >= 80400) {
                            this->searchQueue.readIndex = 0;
                        }
                    }
                    _pass = _pass + 1;
                    if (_pass >= 2) {
                        _pass = 0;
                    }
                }
            LAB_004a4914:
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
            }
            return;
        }

    }
}
}
