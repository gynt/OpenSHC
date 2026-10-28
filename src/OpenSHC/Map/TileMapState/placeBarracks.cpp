#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    using OpenSHC::Map::Buildings::BuildingType;

    /* yPosition_param is the y position (the header declares it int*), param_7 the height. The barracks (or
       mercenary post) gets three parade-ground parts at BuildingPartsOffsets[rot][0..2] relative to its own
       position; a part tile gets L_BUILDING only for footprint offset (2,2). */
    // FUNCTION: STRONGHOLDCRUSADER 0x005076A0
    void TileMapState::placeBarracks(int playerID, uint xPosition, int* yPosition_param, undefined4 buildingType,
        uint buildingSize, int buildingOrientation, undefined4 param_7)
    {
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int rot;
        if (buildingOrientation == 0xf) {
            rot = 0;
        } else {
            rot = buildingOrientation / 2;
        }
        uint x = xPosition;
        uint y = (uint)yPosition_param;

        /* ids are kept zero-extended for the layer stores and sign-extended for the array index */
        ushort barracks = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, param_7, (BuildingType)(int)(short)buildingType, buildingSize, playerID, 0xf);
        int barracksID = (short)barracks;
        this->placedBuildingID = barracksID;
        DAT_BuildingsState::instance.buildings[barracksID].uidWhenPlaced = uid;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            DAT_BuildingsState::instance.buildings[barracksID].tileRefs[index] = tile;
            this->HeightLayer[tile] = (byte)param_7;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = barracks;
            index++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(barracksID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(barracksID);

        uint partX = x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][0].x;
        uint partY = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][0].y;
        ushort part = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, partX, partY, param_7, OpenSHC::Map::Buildings::BT_PARADEGROUND3, 5, playerID, 0xf);
        int partID = (short)part;
        DAT_BuildingsState::instance.buildings[partID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[partID].linkedBuildingID = (short)this->placedBuildingID;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[partID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + partY].addXgetTile
                + this->buildingX + partX;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)param_7;
            if (this->buildingX == 2 && this->buildingY == 2) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            this->BuildingLayer[tile] = part;
            index++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(partID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(partID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, partX, partY);

        partX = x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][1].x;
        partY = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][1].y;
        part = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, partX, partY, param_7, OpenSHC::Map::Buildings::BT_PARADEGROUND4, 5, playerID, 0xf);
        partID = (short)part;
        DAT_BuildingsState::instance.buildings[partID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[partID].linkedBuildingID = (short)this->placedBuildingID;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[partID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + partY].addXgetTile
                + this->buildingX + partX;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)param_7;
            if (this->buildingX == 2 && this->buildingY == 2) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            this->BuildingLayer[tile] = part;
            index++;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(partID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(partID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, partX, partY);

        partX = x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][2].x;
        partY = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][2].y;
        part = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, partX, partY, param_7, OpenSHC::Map::Buildings::BT_PARADEGROUND2, 5, playerID, 0xf);
        partID = (short)part;
        DAT_BuildingsState::instance.buildings[partID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[partID].linkedBuildingID = (short)this->placedBuildingID;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[partID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + partY].addXgetTile
                + this->buildingX + partX;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)param_7;
            if (this->buildingX == 2 && this->buildingY == 2) {
                this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            }
            this->BuildingLayer[tile] = part;
            this->BuildingWasLayer[tile] = (uchar)buildingType;
            index++;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(partID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(partID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, partX, partY);

        if ((short)buildingType == OpenSHC::Map::Buildings::BT_MERCENARYPOST) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                DAT_BuildingsState::ptr)(playerID);
        }
        /* the employee count is read from the last parade-ground part (0x507B7C) */
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && (int)DAT_BuildingsState::instance.buildings[partID].buildingTypeBasedEmployeeCount
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
