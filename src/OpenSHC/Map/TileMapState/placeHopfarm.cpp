#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FARM_FIELD_HOP;
    using OpenSHC::Map::LogicHelpers::L_NONE;
    using OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;

    // FUNCTION: STRONGHOLDCRUSADER 0x005151C0
    void TileMapState::placeHopfarm(int playerID, uint x, uint y, undefined4 buildingType, undefined4 param_5,
        int variation, int averageHeight)
    {
        int index = 0;
        int buildingID = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, x, y, averageHeight, (BuildingType)(short)buildingType, 3, playerID,
            variation);
        this->placedBuildingID = buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, y, 9);

        /* the 24 field tiles, from one of two alternating layouts */
        int layout = DAT_GameState::instance.playerDataArray[playerID].hopFarmLayoutToggle;
        for (int i = 0; i < 24; i++) {
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[i]
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_TerrainDefinedData::instance.hopFarmFieldTiles[layout][i].y + y]
                      .addXgetTile
                + x + DAT_TerrainDefinedData::instance.hopFarmFieldTiles[layout][i].x;
        }
        if (layout != 0) {
            *(short*)DAT_BuildingsState::instance.buildings[buildingID].hopFarmLayoutCode = 7;
        } else {
            *(short*)DAT_BuildingsState::instance.buildings[buildingID].hopFarmLayoutCode = 0x51;
        }

        /* the farm house */
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, 3);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->HeightLayer[tile] = (byte)averageHeight;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = (short)buildingID;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, tile, this->buildingY + y, 2, L_NONE, L2_THICK_SCRUB);
            index++;
        } while (index < this->constructionTileCount);

        for (int i = 0; i < 24; i++) {
            int tile = DAT_ViewportRenderState::instance
                           .translationMatrix[DAT_TerrainDefinedData::instance
                                                  .hopFarmFieldTiles[DAT_GameState::instance.playerDataArray[playerID]
                                                                         .hopFarmLayoutToggle][i]
                                                  .y
                               + y]
                           .addXgetTile
                + DAT_TerrainDefinedData::instance
                      .hopFarmFieldTiles[DAT_GameState::instance.playerDataArray[playerID].hopFarmLayoutToggle][i]
                      .x
                + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_FARM_FIELD_HOP;
            this->BuildingLayer[tile] = (short)buildingID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                DAT_TerrainDefinedData::instance
                        .hopFarmFieldTiles[DAT_GameState::instance.playerDataArray[playerID].hopFarmLayoutToggle][i]
                        .y
                    + y,
                tile);
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        DAT_GameState::instance.playerDataArray[playerID].hopFarmLayoutToggle++;
        if (DAT_GameState::instance.playerDataArray[playerID].hopFarmLayoutToggle > 1) {
            DAT_GameState::instance.playerDataArray[playerID].hopFarmLayoutToggle = 0;
        }

        /* not enough idle peasants for the workers: tell the local player */
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].buildingTypeBasedEmployeeCount
                > DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
            && (DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, 0, 100, 6000);
        }
    }

}
}
