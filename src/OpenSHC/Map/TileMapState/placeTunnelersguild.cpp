#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;

    using OpenSHC::Map::Buildings::BuildingType;

    /* param_2 is the x position (the header declares it int*), param_4 the building type, param_5 the size,
       param_6 the orientation and param_7 the height */
    // FUNCTION: STRONGHOLDCRUSADER 0x00507E00
    void TileMapState::placeTunnelersguild(
        int param_1, int* param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7)
    {
        int uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        int index = 0;
        int rot;
        if (param_6 == 0xf) {
            rot = 0;
        } else {
            rot = param_6 / 2;
        }
        uint x = (uint)param_2;
        uint y = param_3;

        /* the ids are kept zero-extended for the layer stores and sign-extended for the array index; the guild and
           its parade ground share the two id variables (same stack slots in the original) */
        ushort building = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, x, y, param_7, (BuildingType)(int)(short)param_4, param_5, param_1, 0xf);
        int buildingID = (short)building;
        this->placedBuildingID = buildingID;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uid;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, param_5);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            DAT_BuildingsState::instance.buildings[buildingID].tileRefs[index] = tile;
            this->HeightLayer[tile] = (byte)param_7;
            this->LogicLayer[tile] = this->LogicLayer[tile] | L_BUILDING;
            this->BuildingLayer[tile] = building;
            index++;
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);

        x = x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][1].x;
        y = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[rot][1].y;
        building = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            param_1, x, y, param_7, OpenSHC::Map::Buildings::BT_PARADEGROUND5, 5, param_1, 0xf);
        buildingID = (short)building;
        DAT_BuildingsState::instance.buildings[buildingID].uidWhenPlaced = uid;
        DAT_BuildingsState::instance.buildings[buildingID].linkedBuildingID = (short)this->placedBuildingID;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(tile);
            this->HeightLayer[tile] = (byte)param_7;
            this->BuildingLayer[tile] = building;
            index++;
            this->BuildingWasLayer[tile] = (uchar)param_4;
            this->ChangedLayer[tile] = 2;
        } while (index < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(8, x, y);
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupTunnelersGuildCampgroundPositions,
            DAT_BuildingsState::ptr)(param_1);
    }

}
}
