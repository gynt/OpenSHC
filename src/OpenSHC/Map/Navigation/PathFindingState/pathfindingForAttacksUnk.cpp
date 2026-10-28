#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A75B0
        void PathFindingState::computeAttackDestinationsAroundBuilding(
            int tribeID, int buildingID, int param_3, dword param_4, int param_5)
        {
            int _x = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            int _y = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            int _size = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            int _baseHeight = DAT_TileMapState::instance
                                  .DefaultHeightLayer[DAT_BuildingsState::instance.buildings[buildingID]
                                          .currentTilePositionAdjusted];
            int _leaderUnitID = DAT_TribesState::instance.tribes[tribeID].leaderUnitID;
            int _count = 0;
            BOOLEnum _allAssassins = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, DAT_TribesState::ptr)(tribeID);
            param_3 = param_3 * 2;
            if (param_3 > 500) {
                param_3 = 500;
            } else if (param_3 < 50) {
                param_3 = 50;
            }
            int _tilesCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[_size];
            int _entrance = 0;
            for (int _i = 0; _i < _tilesCount; _i++) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                    DAT_BuildingsState::ptr)(_size, 1, _entrance, 0);
                int _tile = DAT_ViewportRenderState::instance
                                .translationMatrix[_y + DAT_BuildingsState::instance.DAT_TempYOffset]
                                .addXgetTile
                    + DAT_BuildingsState::instance.DAT_TempXOffset + _x;
                if (abs(_baseHeight - DAT_TileMapState::instance.HeightLayer[_tile]) < 0x20) {
                    int _area = (short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
                    if ((_area == param_4
                            || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                                   DAT_PathFindingState::ptr)(param_5, param_4, (dword)_area, 0)
                                != 0
                            || (_allAssassins != FALSE
                                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                         calculateCanReachUsingCachedAreaLogic,
                                       DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[_leaderUnitID].tile, _tile)
                                    != FALSE))
                        && abs(DAT_BuildingsState::instance.buildings[buildingID].terrainHeight
                               - DAT_TileMapState::instance.HeightLayer[_tile])
                            < 0x10) {
                        this->searchQueue.destinationsArray[_count].tile1 = _tile;
                        this->searchQueue.destinationsArray[_count].tile2OrAHelper = 0;
                        for (int _k = 0; _k < 4; _k++) {
                            XYPair* _offset = &DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder[_k];
                            int _tile2 = DAT_ViewportRenderState::instance
                                             .translationMatrix[_offset->y + DAT_BuildingsState::instance.DAT_TempYOffset
                                                 + _y]
                                             .addXgetTile
                                + _offset->x + DAT_BuildingsState::instance.DAT_TempXOffset + _x;
                            if ((DAT_TileMapState::instance.LogicLayer[_tile2] & 0xf000000U) == 0
                                && DAT_TileMapState::instance.BuildingLayer[_tile2] == buildingID) {
                                this->searchQueue.destinationsArray[_count].tile2OrAHelper = _tile2;
                                break;
                            }
                        }
                        _count = _count + 1;
                        if (_count >= param_3) {
                            return;
                        }
                    }
                }
                _entrance = _entrance + 1;
                if (_entrance >= _tilesCount) {
                    _entrance = 0;
                }
            }
            int _heightLimit = 0x20;
            for (int _sizeIndex = _size + 1; _sizeIndex < 0xe; _sizeIndex++) {
                int _tilesCount2 = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[_sizeIndex];
                int _entrance2 = 0;
                for (int _i = 0; _i < _tilesCount2; _i++) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                        DAT_BuildingsState::ptr)(_sizeIndex, 1, _entrance2, 0);
                    uint _tileY = _y + DAT_BuildingsState::instance.DAT_TempYOffset;
                    uint _tileX = DAT_BuildingsState::instance.DAT_TempXOffset + _x;
                    if (_tileX > 399 || _tileY > 399
                        || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[_tileY * 400 + _tileX] == '\0') {
                        continue;
                    }
                    int _tile = DAT_ViewportRenderState::instance.translationMatrix[_tileY].addXgetTile
                        + DAT_BuildingsState::instance.DAT_TempXOffset + _x;
                    if (abs(_baseHeight - DAT_TileMapState::instance.HeightLayer[_tile]) < 0x20) {
                        int _area = (short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
                        if ((_area == param_4
                                || MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                         calculateCanPlayerUnitsNavigateToAreaFromArea,
                                       DAT_PathFindingState::ptr)(param_5, param_4, (dword)_area, 0)
                                    != 0
                                || (_allAssassins != FALSE
                                    && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                             calculateCanReachUsingCachedAreaLogic,
                                           DAT_PathFindingState::ptr)(
                                           DAT_UnitsState::instance.units[_leaderUnitID].tile, _tile)
                                        != FALSE))
                            && abs(DAT_BuildingsState::instance.buildings[buildingID].terrainHeight
                                   - DAT_TileMapState::instance.HeightLayer[_tile])
                                < _heightLimit) {
                            this->searchQueue.destinationsArray[_count].tile1 = _tile;
                            this->searchQueue.destinationsArray[_count].tile2OrAHelper = 0;
                            _count = _count + 1;
                            if (_count >= param_3) {
                                return;
                            }
                        }
                    }
                    _entrance2 = _entrance2 + 1;
                    if (_entrance2 >= _tilesCount2) {
                        _entrance2 = 0;
                    }
                }
                _heightLimit = _heightLimit + 0x10;
            }
            this->searchQueue.destinationsArray[_count].tile1 = 0;
            this->searchQueue.destinationsArray[_count].tile2OrAHelper = 0;
        }

    }
}
}
