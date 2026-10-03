#include "../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::Player::PlayerDataBuildingCategoryEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::Logic1;
    using OpenSHC::Map::LogicHelpers::Logic2;

    // FUNCTION: STRONGHOLDCRUSADER 0x005146D0
    void TileMapState::placeKeep(
        int playerID, uint x, uint y, BuildingType type, uint size, int orientation, int xyValue)
    {
        byte bVar1;
        uint uVar2;
        uint y_00;
        short sVar3;
        int _buildingID;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        uint y_01;
        uint x_00;
        uint uVar9;
        uint brushType;
        Logic2 LVar10;
        uint local_18;
        int _yOffset;
        int _xOffset;
        y_00 = y;
        uVar2 = x;
        if (this->field195_0x554a24 != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::demolishBuildingsInKeepsConstructionFootprint, this)(
                playerID, (int)((int)(x)), (int)((int)(y)), (undefined4)((int)(type)), (int)((int)(size)), orientation,
                xyValue);
            this->field195_0x554a24 = 0;
        }
        iVar6 = DAT_GameCore::instance.uniqueGameObjectTracker;
        local_18 = 0;
        y = 0;
        bVar1 = this->Logic2Layer[DAT_ViewportRenderState::instance.translationMatrix[y_00].addXgetTile + x];
        _buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y_00, (undefined4)((int)(xyValue)), (OpenSHC::Map::Buildings::BuildingType)type, size, playerID, 0xf);
        this->placedBuildingID = _buildingID;
        DAT_BuildingsState::instance.buildings[_buildingID].uidWhenPlaced = iVar6;
        sVar3 = (short)orientation;
        DAT_BuildingsState::instance.buildings[_buildingID].orientation = (short)orientation;
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
            DAT_GameState::ptr)(_buildingID, playerID, OpenSHC::Game::Player::PDBCE_KEEP);
        if (orientation == 0xf) {
            orientation = 0;
        }
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                y, (int)((int)(size)));
            iVar4 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y_00].addXgetTile
                + this->buildingX + uVar2;
            if ((int)y < 0x24) {
                *(int*)(DAT_BuildingsState::instance.buildings[_buildingID].workers + y * 2 + 8) = iVar4;
            }
            this->HeightLayer[iVar4] = (byte)xyValue;
            if ((undefined2)type == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                this->LogicLayer[iVar4] = this->LogicLayer[iVar4] | 1024;
            } else {
                this->LogicLayer[iVar4] = this->LogicLayer[iVar4] | 268435456;
            }
            (*(short*)&x) = (short)_buildingID;
            this->BuildingLayer[iVar4] = (short)x;
            this->BuildingWasLayer[iVar4] = (uchar)type;
            if ((bVar1 & 0x90) == 0) {
                LVar10 = OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
                uVar9 = 6;
            } else {
                LVar10 = OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
                uVar9 = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, iVar4, this->buildingY + y_00, uVar9, OpenSHC::Map::LogicHelpers::L_NONE, LVar10);
            this->ChangedLayer[iVar4] = 2;
            y = y + 1;
        } while ((int)y < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(_buildingID);
        if (((undefined2)type == OpenSHC::Map::Buildings::BT_MANORHOUSE) || ((undefined2)type == OpenSHC::Map::Buildings::BT_STONEKEEP)) {
            local_18 = 2;
        }
        iVar4 = orientation / 2 + -0xa0 + (short)(undefined2)type * 4;
        iVar8 = iVar4 * 0x18;
        uVar9 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 * 0x18 + 0x268) + y_00;
        iVar5 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x264);
        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[uVar9].addXgetTile + iVar5 + uVar2;
        iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, iVar5 + uVar2, uVar9, (undefined4)((int)(xyValue)),
            OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT, 1, playerID, 0xf);
        DAT_BuildingsState::instance.buildings[iVar5].uidWhenPlaced = iVar6;
        DAT_BuildingsState::instance.buildings[iVar5].unknownManorHouseOrStoneKeepRelated = local_18;
        DAT_BuildingsState::instance.buildings[iVar5].quarryStockpileID = (undefined2)this->placedBuildingID;
        DAT_BuildingsState::instance.buildings[iVar5].orientation = sVar3;
        this->LogicLayer[iVar7] = this->LogicLayer[iVar7] | 1024;
        this->BuildingLayer[iVar7] = (short)iVar5;
        this->ChangedLayer[iVar7] = 2;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar5].y, iVar7);
        iVar5 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x26c);
        uVar9 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x270) + y_00;
        iVar7 = DAT_ViewportRenderState::instance.translationMatrix[uVar9].addXgetTile + iVar5 + uVar2;
        iVar5 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID,
            iVar5 + uVar2, uVar9, (undefined4)((int)(xyValue)), OpenSHC::Map::Buildings::BT_KEEPDOOR, 1, playerID, 0xf);
        DAT_BuildingsState::instance.buildings[iVar5].uidWhenPlaced = iVar6;
        DAT_BuildingsState::instance.buildings[iVar5].unknownManorHouseOrStoneKeepRelated = local_18 / 2;
        DAT_BuildingsState::instance.buildings[iVar5].quarryStockpileID = (undefined2)this->placedBuildingID;
        (*(short*)&x) = (short)iVar5;
        DAT_BuildingsState::instance.buildings[iVar5].orientation = sVar3;
        this->MiscDisplayLayer[iVar7] = this->MiscDisplayLayer[iVar7] | 4;
        this->BuildingLayer[iVar7] = (short)x;
        this->ChangedLayer[iVar7] = 2;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar5].y, iVar7);
        iVar5 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x274);
        uVar9 = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar8 + 0x278) + y_00;
        iVar8 = DAT_ViewportRenderState::instance.translationMatrix[uVar9].addXgetTile + iVar5 + uVar2;
        iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData,
            DAT_BuildingsState::ptr)(playerID, iVar5 + uVar2, uVar9, (undefined4)((int)(xyValue)),
            OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT, 1, playerID, 0xf);
        DAT_BuildingsState::instance.buildings[iVar5].uidWhenPlaced = iVar6;
        DAT_BuildingsState::instance.buildings[iVar5].unknownManorHouseOrStoneKeepRelated = local_18;
        DAT_BuildingsState::instance.buildings[iVar5].quarryStockpileID = (undefined2)this->placedBuildingID;
        DAT_BuildingsState::instance.buildings[iVar5].orientation = sVar3;
        this->LogicLayer[iVar8] = this->LogicLayer[iVar8] | 1024;
        this->BuildingLayer[iVar8] = (short)iVar5;
        this->ChangedLayer[iVar8] = 2;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar5].y, iVar8);
        y_01 = y_00 + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 * 8 + 0x388);
        x_00 = uVar2 + *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 * 8 + 900);
        uVar9 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(playerID, x_00,
            y_01, (undefined4)((int)(xyValue)), OpenSHC::Map::Buildings::BT_CAMPGROUND, 7, playerID, 0xf);
        DAT_BuildingsState::instance.buildings[uVar9].uidWhenPlaced = iVar6;
        DAT_BuildingsState::instance.buildings[uVar9].quarryStockpileID = (undefined2)this->placedBuildingID;
        DAT_BuildingsState::instance.buildings[uVar9].orientation = sVar3;
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
            DAT_GameState::ptr)(uVar9, playerID, OpenSHC::Game::Player::PDBCE_CAMPGROUND);
        y = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(y, 7);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y_01].addXgetTile
                + this->buildingX + x_00);
            y = y + 1;
        } while ((int)y < this->constructionTileCount);
        y = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                y, (int)((int)(DAT_BuildingsState::instance.buildings[uVar9].widthOrHeight)));
            iVar6 = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y_01].addXgetTile
                + this->buildingX + x_00;
            if ((int)y < 0x18) {
                *(int*)(DAT_BuildingsState::instance.buildings[uVar9].workers + y * 2 + 8)
                    = DAT_ViewportRenderState::instance
                          .translationMatrix[(int)(short)DAT_BuildingsState::instance.buildings[uVar9].y
                              + DAT_TerrainDefinedData::instance.field197_0x444[y].y]
                          .addXgetTile
                    + (int)(short)DAT_BuildingsState::instance.buildings[uVar9].x
                    + DAT_TerrainDefinedData::instance.field197_0x444[y].x;
            }
            this->HeightLayer[iVar6] = (byte)xyValue;
            if (this->buildingX == 3) {
                if (this->buildingY == 3) {
                    this->LogicLayer[iVar6] = this->LogicLayer[iVar6] | 1024;
                }
                if (this->buildingX == 3) {
                    if (this->buildingY == 2) {
                        this->LogicLayer[iVar6] = this->LogicLayer[iVar6] | 1024;
                    }
                    if ((this->buildingX == 3) && (this->buildingY == 4)) {
                        this->LogicLayer[iVar6] = this->LogicLayer[iVar6] | 1024;
                    }
                }
            }
            if ((this->buildingX == 2) && (this->buildingY == 3)) {
                this->LogicLayer[iVar6] = this->LogicLayer[iVar6] | 1024;
            }
            if ((this->buildingX == 4) && (this->buildingY == 3)) {
                this->LogicLayer[iVar6] = this->LogicLayer[iVar6] | 1024;
            }
            (*(short*)&x) = (short)uVar9;
            this->BuildingLayer[iVar6] = (short)x;
            this->ChangedLayer[iVar6] = 2;
            if ((bVar1 & 0x90) == 0) {
                LVar10 = OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
                brushType = 6;
            } else {
                LVar10 = OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB;
                brushType = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(
                playerID, iVar6, this->buildingY + y_01, brushType, OpenSHC::Map::LogicHelpers::L_NONE, LVar10);
            y = y + 1;
        } while ((int)y < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(uVar9);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(uVar9);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(10, x_00, y_01);
        _xOffset = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 * 8 + 0x3e4);
        _yOffset = *(int*)((int)DAT_TerrainDefinedData::ptr + iVar4 * 8 + 1000);
        y = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(y, 5);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(
                DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + _yOffset + y_00].addXgetTile
                + this->buildingX + _xOffset + uVar2);
            y = y + 1;
        } while ((int)y < this->constructionTileCount);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeStockpile, this)(
            playerID, (int)((int)(_xOffset + uVar2)), (int)((int)(_yOffset + y_00)), 10, 5, 0xf, xyValue);
    }

}
}
