#include "../PathFindingState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8AB0
        void PathFindingState::clearObstaclesAroundSignposts(int param_1)
        {
            int (*paiVar7)[8];
            int iVar8;
            int iVar9;
            int iVar10;
            int local_24;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.SearchGenerationLayer)));
            }
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            uint uVar6 = 0;
            local_24 = 0x9d08;
            if (DAT_GameState::instance.mapAndTime.signpostIDs[0] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[0]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[0]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[1] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[1]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[1]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[2] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[2]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[2]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[3] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[3]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[3]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[4] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[4]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[4]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[5] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[5]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[5]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[6] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[6]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[6]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            if (DAT_GameState::instance.mapAndTime.signpostIDs[7] != 0) {
                iVar8 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[7]].x;
                iVar10 = (int)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.mapAndTime.signpostIDs[7]].y;
                this->searchQueue.yQueue[uVar6] = (short)iVar10;
                this->searchQueue.xQueue[uVar6] = (short)iVar8;
                iVar9 = DAT_ViewportRenderState::instance.translationMatrix[iVar10].addXgetTile + iVar8;
                this->searchQueue.tilesQueue[uVar6] = iVar9;
                DAT_TileMapState::instance.SearchDistanceLayer[iVar9] = (short)this->searchQueue.currentDistance;
                DAT_TileMapState::instance.SearchGenerationLayer[this->searchQueue.tilesQueue[uVar6]]
                    = (short)this->searchGeneration;
                uVar6 = uVar6 + 1;
            }
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uVar6 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < uVar6)
                    break;
                int sVar3 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                int sVar4 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.SearchDistanceLayer[uVar6];
                if ((0x13a10 < (int)this->searchQueue.currentDistance)
                    || ((int)this->searchQueue.currentDistance > param_1))
                    break;
                for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                    iVar9 = DAT_TileMapState::instance.directionTranslationMatrix[sVar4][_direction] + uVar6;
                    uint uVar5 = DAT_TileMapState::instance.LogicLayer[iVar9];
                    if (DAT_TileMapState::instance.SearchGenerationLayer[iVar9] != this->searchGeneration
                        && (uVar5 & 0x30) == 0) {
                        DAT_TileMapState::instance.SearchDistanceLayer[iVar9]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.SearchGenerationLayer[iVar9] = (short)this->searchGeneration;
                        this->searchQueue.xQueue[this->searchQueue.writeIndex]
                            = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset
                            + (short)sVar3;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset
                            + (short)sVar4;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar9;
                        short sVar1 = DAT_TileMapState::instance.BuildingLayer[iVar9];
                        if (sVar1 != 0) {
                            iVar8 = (int)sVar1;
                            iVar10 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].buildingType;
                            switch (iVar10) {
                            case 10:
                            case 0xb:
                            case 0x13:
                            case 0x24:
                            case 0x25:
                            case 0x26:
                            case 0x28:
                            case 0x29:
                            case 0x2a:
                            case 0x34:
                            case 0x37:
                            case 0x47:
                            case 0x48:
                            case 0x49:
                                break;
                            default:
                                DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding
                                    = (int)(DAT_BuildingDefinedData::instance
                                                .BuildingShowRubbleWhenDestroyed[iVar10]
                                        == 0);
                                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding,
                                    DAT_BuildingsState::ptr)(iVar8);
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                    DAT_SFXState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar8].x,
                                    (int)((short)DAT_BuildingsState::instance.buildings[iVar8].y),
                                    OpenSHC::DE::SHCDE::FX_BUILDING_SMASH);
                            }
                        }
                        if ((uVar5 & 0x100) != 0 && (uVar5 & 2) == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile,
                                DAT_EntityState::ptr)(iVar9);
                            DAT_TileMapState::instance.LogicLayer[iVar9]
                                = DAT_TileMapState::instance.LogicLayer[iVar9] & 0xffbef4ff;
                            DAT_TileMapState::instance.HeightLayer[iVar9]
                                = DAT_TileMapState::instance.DefaultHeightLayer[iVar9];
                            DAT_TileMapState::instance.DamageOrCropStageLayer[iVar9] = 0;
                            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                            DAT_TileMapState::instance.terrainChangedDirty = 1;
                            this->searchQueue.xQueue[local_24]
                                = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset
                                + (short)sVar3;
                            this->searchQueue.yQueue[local_24]
                                = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset
                                + (short)sVar4;
                            this->searchQueue.tilesQueue[local_24] = iVar9;
                            local_24 = local_24 + 1;
                        }
                        if ((uVar5 & 0x40000000) != 0) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, DAT_TileMapState::ptr)(
                                DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset
                                    + sVar3,
                                DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset
                                    + sVar4);
                            DAT_TileMapState::instance.HeightLayer[iVar9] = 8;
                            DAT_TileMapState::instance.LogicLayer[iVar9]
                                = DAT_TileMapState::instance.LogicLayer[iVar9] & 0xbfffbfff;
                            this->searchQueue.xQueue[local_24]
                                = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.xOffset
                                + (short)sVar3;
                            this->searchQueue.yQueue[local_24]
                                = (short)DAT_TerrainDefinedData::instance.clockwiseNeighbourOffsets[_direction].int_.yOffset
                                + (short)sVar4;
                            this->searchQueue.tilesQueue[local_24] = iVar9;
                            local_24 = local_24 + 1;
                        }
                        if ((uVar5 & 8) != 0) {
                            DAT_TileMapState::instance.LogicLayer[iVar9]
                                = DAT_TileMapState::instance.LogicLayer[iVar9] & 0xfffffff7;
                        }
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= (int)this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                    }
                }

                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= (int)this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            }
            for (iVar8 = 0x9d08; iVar8 < local_24; iVar8 = iVar8 + 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                    DAT_PathFindingState::ptr)((int)this->searchQueue.yQueue[iVar8], this->searchQueue.tilesQueue[iVar8]);
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                    DAT_PathFindingState::ptr)(
                    7, (uint)(int)this->searchQueue.xQueue[iVar8], (uint)(int)this->searchQueue.yQueue[iVar8]);
            }
            return;
        }

    }
}
}
