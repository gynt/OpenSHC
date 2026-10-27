#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Function Summary: Find Building Access Point   This function solves the problem: "Where should a unit walk to
          interact with this building?"   What It Does:   Phase 1: Find All Valid Access Points      Iterates through
          predefined perimeter positions around the building   Validates each position with three checks:      Height
          Check #1: Access tile within 32 units of building foundation   Navigation Check: Unit can path to this area
          Height Check #2: Access tile within 16 units of building's terrain height            Phase 2: Choose Closest
          Valid Point   3. Calculates distance from unit to each valid access point   4. Returns the closest one       *
          Finds the best accessible tile for a unit to approach a building.    * This function determines where a unit
          should walk to interact with a building    *     * Algorithm:    * 1. Get all potential access points around
          the building perimeter    * 2. Filter by height compatibility (< 32 units from building base, < 16 from
          terrain)    * 3. Filter by navigation area connectivity    * 4. Choose the closest valid access point to the
          unit    *     * @param this - PathFindingState object pointer    * @param unitID - ID of the unit trying to
          access the building    * @param buildingID - ID of the target building    * @param param_3 - Output parameter:
          returns the building tile adjacent to access point    * @return Tile index of best access point, or 0 if none
          found      decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8860
        int PathFindingState::findBuildingAccessPoint(int unitID, int buildingID, int* pResultTile)
        {
            int _direction;
            int _candidate2;
            int _closestDistance;
            int _closestIndex;
            int _entranceCandidate;
            int _counter;
            int _accessibleIndex;
            int _validAccessPointsCount;
            int _limit;
            int _pairsOfAccessAndAdjacent[200][2];
            int _accessibleTilesCount;
            int _yOffset;
            int _buildingDefHeight;
            int _buildingSize;
            int _cHeight;
            int _unitArea;
            int _unitOwner;
            int _y;
            /*
              === GET BUILDING INFORMATION ===
             */
            int _buildingY = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            int _buildingX = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            /*
              Default/base height of the building's foundation
             */
            _buildingDefHeight = (int)DAT_TileMapState::instance
                                     .DefaultHeightLayer[DAT_BuildingsState::instance.buildings[buildingID]
                                             .currentTilePositionAdjusted];
            /*
              === GET UNIT INFORMATION ===
             */
            _unitArea = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            _unitOwner = (int)DAT_UnitsState::instance.units[unitID].owner;
            /*
              Lookup table: building size -> number of accessible perimeter tiles
             */
            _buildingSize = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            _accessibleTilesCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[_buildingSize];
            _validAccessPointsCount = 0;
            _accessibleIndex = 0;
            if (0 < _accessibleTilesCount) {
                _limit = _accessibleTilesCount;
                do {
                    /*
                      === PHASE 1: FIND ALL VALID ACCESS POINTS ===
                      Access point: within 32 height units of the building base, reachable for the unit and
                      within 16 height units of the building's terrain height
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                        DAT_BuildingsState::ptr)(_buildingSize, 1, _accessibleIndex, 0);
                    _yOffset = DAT_BuildingsState::instance.DAT_TempYOffset;
                    _entranceCandidate = DAT_ViewportRenderState::instance.translationMatrix[_buildingY + _yOffset].addXgetTile
                        + DAT_BuildingsState::instance.DAT_TempXOffset + _buildingX;
                    _cHeight = (int)DAT_TileMapState::instance.HeightLayer[_entranceCandidate];
                    if (abs(_buildingDefHeight - _cHeight) < 32
                        && ((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_entranceCandidate] == _unitArea
                            || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                                   DAT_PathFindingState::ptr)(_unitOwner, (dword)_unitArea,
                                   (dword)(int)(short)DAT_TileMapState::instance.PathConnectionLayer[_entranceCandidate],
                                   0)
                                != 0)
                        && abs((int)DAT_BuildingsState::instance.buildings[buildingID].terrainHeight - _cHeight) < 16) {
                        /*
                          Store the access tile and the building tile adjacent to it (cardinal search, horizontal
                          first)
                         */
                        _pairsOfAccessAndAdjacent[_validAccessPointsCount][0] = _entranceCandidate;
                        _pairsOfAccessAndAdjacent[_validAccessPointsCount][1] = 0;
                        for (_direction = 0; _direction < 4; _direction++) {
                            _candidate2
                                = DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_ClimbLogicDefinedData::instance
                                                             .CardinalHorizontalFirstSearchOrder[_direction]
                                                             .y
                                          + _yOffset + _buildingY]
                                      .addXgetTile
                                + DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder[_direction].x
                                + DAT_BuildingsState::instance.DAT_TempXOffset + _buildingX;
                            if ((int)DAT_TileMapState::instance.BuildingLayer[_candidate2] == buildingID) {
                                _pairsOfAccessAndAdjacent[_validAccessPointsCount][1] = _candidate2;
                                break;
                            }
                        }
                        _validAccessPointsCount = _validAccessPointsCount + 1;
                    }
                    _accessibleIndex = _accessibleIndex + 1;
                    if (_accessibleIndex >= _accessibleTilesCount) {
                        _accessibleIndex = 0;
                    }
                    _limit = _limit - 1;
                } while (_limit != 0);
            }
            /*
              === PHASE 2: CHOOSE CLOSEST ACCESS POINT ===
             */
            _closestIndex = -1;
            *pResultTile = 0;
            _closestDistance = 10000;
            if (_validAccessPointsCount <= 0) {
                return 0;
            }
            for (_counter = 0; _counter < _validAccessPointsCount; _counter++) {
                _y = (int)DAT_ViewportRenderState::instance
                         .tileTranslationMatrix_YComponent[_pairsOfAccessAndAdjacent[_counter][0]];
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                    (int)DAT_UnitsState::instance.units[unitID].y,
                    _pairsOfAccessAndAdjacent[_counter][0]
                        - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile,
                    _y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < _closestDistance) {
                    _closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    _closestIndex = _counter;
                }
            }
            if (_closestIndex != -1) {
                *pResultTile = _pairsOfAccessAndAdjacent[_closestIndex][1];
                return _pairsOfAccessAndAdjacent[_closestIndex][0];
            }            return 0;
        }

    }
}
}
