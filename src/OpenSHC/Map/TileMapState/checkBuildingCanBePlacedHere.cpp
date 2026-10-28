
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Navigation::Algorithms::XYPair;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /* inlined copy of ViewportRenderState::xyAreValid */
    static inline int isMapTileValid(uint x, uint y)
    {
        return x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x005037B0
    void TileMapState::checkBuildingCanBePlacedHere(
        int playerID, uint x, uint y, MappersEnum commandBuildingType, int buildingSize)
    {
        BuildingType buildingType;
        uint origX;
        uint origY;
        int extraRange;
        int sizeDefaulted;
        int boulderCount;
        int ironCount;
        int oilCount;
        int fertileCount;
        int grassCount;
        int distance;
        int range;
        int ok;
        int i;
        int j;
        int tile;
        uint tileY;
        int partX;
        int partY;
        int baseX;
        origX = x;
        origY = y;
        extraRange = 0;
        sizeDefaulted = 0;
        if (buildingSize < 0) {
            buildingSize = 2;
            sizeDefaulted = 1;
        }
        this->buildingPlacementResult = FALSE;
        this->placementWarning = 0;
        this->placementPreviewGfxOffset = 0;
        this->uiBuildingRotation = 0xf;
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingSpriteSheetID_1
            = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[buildingType].intValue;
        this->buildingSpriteID1 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID, DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingSpriteID2 = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::getSpriteID2, DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingHeightLimit = DAT_BuildingDefinedData::instance.BuildingPlacement_HeightLimit[buildingType];
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingMaxHeightDifference
            = DAT_BuildingDefinedData::instance.BuildingPlacement_MaxHeightDifference[buildingType];
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingPlacementProperty_3 = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_3[buildingType];
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingPlacementProperty_4 = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_4[buildingType];
        if (((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                || (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1))
            || (DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0)) {
            this->buildingPlacementProperty_4 = 0;
        }
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingPlacementProperty_5 = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_5[buildingType];
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingPlacementProperty_6 = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_6[buildingType];
        buildingType = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)(short)commandBuildingType);
        this->buildingPlacementProperty_7 = DAT_BuildingDefinedData::instance.BuildingPlacement_Property_7[buildingType];
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_SIEGE_TOWER_BASE) {
            return;
        }
        boulderCount = 0;
        ironCount = 0;
        oilCount = 0;
        fertileCount = 0;
        grassCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::storeMinAndMaxHeightOfArea, this)(x, y, buildingSize);
        if (sizeDefaulted == 0) {
            switch ((short)commandBuildingType) {
            case OpenSHC::Commands::M_MAPPER_WOODSMAN:
            case OpenSHC::Commands::M_MAPPER_OXENBASE:
            case OpenSHC::Commands::M_MAPPER_QUARRY:
            case OpenSHC::Commands::M_MAPPER_TUNNEL:
            case OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION:
            case OpenSHC::Commands::M_MAPPER_WHEATFARM:
            case OpenSHC::Commands::M_MAPPER_HOPSFARM:
            case OpenSHC::Commands::M_MAPPER_APPLEFARM:
            case OpenSHC::Commands::M_MAPPER_CATTLEFARM:
            case OpenSHC::Commands::M_MAPPER_IRON_MINE:
            case OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS:
            case OpenSHC::Commands::M_MAPPER_QUARRYPILE:
            case OpenSHC::Commands::M_MAPPER_POND1:
            case OpenSHC::Commands::M_MAPPER_POND2_SMALL:
            case OpenSHC::Commands::M_MAPPER_POND3_LARGE1:
            case OpenSHC::Commands::M_MAPPER_POND4_LARGE2:
                /* resource / farm buildings skip the enemy checks */
                goto checkTiles;
            case OpenSHC::Commands::M_MAPPER_STORES:
            case OpenSHC::Commands::M_MAPPER_GRANARY:
            case OpenSHC::Commands::M_MAPPER_ARMOURY:
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyUnitWithinDistance,
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, 3)
                            != FALSE) {
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                            this->buildingPlacementResult = TRUE;
                            break;
                        }
                        i = i + 1;
                    } while (i < this->constructionTileCount);
                }
                break;
            case OpenSHC::Commands::M_MAPPER_DOG_CAGE:
                if (DAT_GameState::instance.playerDataArray[playerID].dogCageCount >= 10) {
                    this->buildingPlacementResult = TRUE;
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)1000);
                    return;
                }
                /* fall through */
            case OpenSHC::Commands::M_MAPPER_KILLING_PIT:
            case OpenSHC::Commands::M_MAPPER_PITCH_DITCH:
            case OpenSHC::Commands::M_MAPPER_DRAWBRIDGE:
                extraRange = 5;
                /* fall through */
            case OpenSHC::Commands::M_MAPPER_GATEHOUSE:
            case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
            case OpenSHC::Commands::M_MAPPER_GATE_INNER:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD:
            case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
            case OpenSHC::Commands::M_MAPPER_MOAT:
            case OpenSHC::Commands::M_MAPPER_ANTIMOAT:
            case OpenSHC::Commands::M_MAPPER_TOWER1:
            case OpenSHC::Commands::M_MAPPER_TOWER2:
            case OpenSHC::Commands::M_MAPPER_TOWER3:
            case OpenSHC::Commands::M_MAPPER_TOWER4:
            case OpenSHC::Commands::M_MAPPER_TOWER5:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                    if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                DAT_GameSynchronyState::ptr)(playerID);
                            distance = 15;
                            range = 7;
                        } else {
                            distance = 30;
                            range = 30;
                        }
                        i = 0;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                                i, buildingSize);
                            if (MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyUnitWithinDistance,
                                    DAT_PathFindingState::ptr)(
                                    playerID, this->buildingX + x, this->buildingY + y, distance)
                                != FALSE) {
                                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                                ok = 0;
                                break;
                            }
                            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                                if (MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                                        DAT_PathFindingState::ptr)(
                                        playerID, this->buildingX + x, this->buildingY + y, range, -1, -1, -1)
                                    != 0) {
                                    this->buildingPlacementFailReason
                                        = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                                    ok = 0;
                                    break;
                                }
                                if (MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::PathFindingState_Func::isTileOutsideKeepRange,
                                        DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y,
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)()
                                            + extraRange)
                                    != 0) {
                                    this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_FAR_2;
                                    ok = 0;
                                    break;
                                }
                            }
                            ok = 1;
                            i = i + 1;
                        } while (i < this->constructionTileCount);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                                DAT_PathFindingState::ptr)(
                                x, y, DAT_GameState::instance.mapAndTime.signpostExclusionRadius + 5)
                            != FALSE) {
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_SIGNPOST;
                        } else if (ok != 0) {
                            break;
                        }
                        this->buildingPlacementResult = TRUE;
                        if (this->buildingPlacementFailReason
                            == OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE) {
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_FAR_2;
                        }
                    }
                } else {
                    i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                                DAT_PathFindingState::ptr)(
                                playerID, this->buildingX + x, this->buildingY + y, 7, -1, -1, -1)
                            != 0) {
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                            this->buildingPlacementResult = TRUE;
                            break;
                        }
                        i = i + 1;
                    } while (i < this->constructionTileCount);
                }
                break;
            case OpenSHC::Commands::M_MAPPER_CATAPULT:
            case OpenSHC::Commands::M_MAPPER_TREBUCHET:
            case OpenSHC::Commands::M_MAPPER_SIEGE_TOWER:
            case OpenSHC::Commands::M_MAPPER_BATTERING_RAM:
            case OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD:
            case OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA:
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                    i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyUnitWithinDistance,
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, 3)
                            != FALSE) {
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                            this->buildingPlacementResult = TRUE;
                            break;
                        }
                        i = i + 1;
                    } while (i < this->constructionTileCount);
                }
                break;
            default:
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
                    distance = DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY ? 15 : 30;
                    ok = 1;
                    i = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            i, buildingSize);
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyUnitWithinDistance,
                                DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, distance)
                            != FALSE) {
                            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                            ok = 0;
                            break;
                        }
                        i = i + 1;
                    } while (i < this->constructionTileCount);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                            DAT_PathFindingState::ptr)(
                            x, y, DAT_GameState::instance.mapAndTime.signpostExclusionRadius + 5)
                        != FALSE) {
                        this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_SIGNPOST;
                    } else if (ok != 0) {
                        break;
                    }
                    this->buildingPlacementResult = TRUE;
                }
                break;
            }
            if (this->buildingPlacementResult == FALSE) {
                i = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                        i, buildingSize);
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyBuildingOrWallWithinDistance,
                            DAT_PathFindingState::ptr)(playerID, this->buildingX + x, this->buildingY + y, 2)
                        != 0) {
                        this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_TOO_CLOSE_TO_ENEMY_2;
                        this->buildingPlacementResult = TRUE;
                        break;
                    }
                    i = i + 1;
                } while (i < this->constructionTileCount);
            }
        }
    checkTiles:
        if (((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_DRAWBRIDGE)
            && (12 < this->buildingMaxHeight)) {
            this->buildingPlacementResult = TRUE;
        }
        i = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, buildingSize);
            tileY = this->buildingY + y;
            if (isMapTileValid(this->buildingX + x, tileY) == 0) {
                this->buildingPlacementResult = 2;
                return;
            }
            tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
            uint logic = this->LogicLayer[tile];
            if ((logic & 0x30) != 0) {
                this->buildingPlacementResult = 2;
                return;
            }
            if ((logic & 0x20000) != 0) {
                boulderCount = boulderCount + 1;
            }
            if ((logic & 0x80000) != 0) {
                ironCount = ironCount + 1;
            }
            if ((logic & 0x80000000) != 0) {
                oilCount = oilCount + 1;
            }
            if ((logic & 0x100000) == 0) {
                byte logic2 = this->Logic2Layer[tile];
                /* grass */
                if ((logic2 & 0x10) != 0) {
                    fertileCount = fertileCount + 1;
                    grassCount = grassCount + 1;
                }
                /* thick scrub */
                if ((logic2 & 0x80) != 0) {
                    fertileCount = fertileCount + 1;
                    grassCount = grassCount + 1;
                }
                /* scrub */
                if ((logic2 & 1) != 0) {
                    fertileCount = fertileCount + 1;
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                    tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                != 0) {
                this->buildingPlacementResult = TRUE;
            }
            i = i + 1;
        } while (i < this->constructionTileCount);
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_CATTLEFARM
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_WHEATFARM
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_HOPSFARM
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_APPLEFARM) {
            if (fertileCount < this->constructionTileCount) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_FARM_NOT_ON_OASIS;
                this->buildingPlacementResult = TRUE;
                return;
            }
            if (grassCount < 50) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_LAND_NOT_FERTILE;
                this->buildingPlacementResult = TRUE;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_QUARRY) {
            if (boulderCount < 8) {
                this->buildingPlacementResult = TRUE;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP1
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP2
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP3) {
            int keepClass = (MappersEnum)(short)commandBuildingType - OpenSHC::Commands::M_MAPPER_KEEP1;
            /* the three door tiles */
            for (j = 0; j < 3; j++) {
                tileY = DAT_TerrainDefinedData::instance.keepDoorOffsets[keepClass][j].y + y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(DAT_TerrainDefinedData::instance.keepDoorOffsets[keepClass][j].x + x,
                        tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile
                    + DAT_TerrainDefinedData::instance.keepDoorOffsets[keepClass][j].x + x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
            }
            /* the campground */
            x = x + DAT_TerrainDefinedData::instance.unkXYOffsets_0x384[keepClass][0].xOffset;
            y = y + DAT_TerrainDefinedData::instance.unkXYOffsets_0x384[keepClass][0].yOffset;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 7);
                tileY = this->buildingY + y;
                if (isMapTileValid(this->buildingX + x, tileY) == 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            /* the stockpile */
            partX = DAT_TerrainDefinedData::instance.keepStockpileOffsets[keepClass][0].xOffset + origX;
            partY = DAT_TerrainDefinedData::instance.keepStockpileOffsets[keepClass][0].yOffset + origY;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                baseX = this->buildingX;
                tileY = this->buildingY + partY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(partX + baseX, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + baseX + partX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_GATE_WOOD1A
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_GATE_WOOD1B
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_GATE_WOOD1C
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_GATE_WOOD1D) {
            /* per wood gate (24 bytes): two (x, y, ?) part offsets at +0x56C / +0x578, then 6 (x, y) at +0x5CC */
            int(*gatePartOffsets)[6] = (int(*)[6]) & DAT_TerrainDefinedData::instance.field288_0x56c;
            XYPair(*gateEdgeOffsets)[6] = (XYPair(*)[6]) & DAT_TerrainDefinedData::instance.field370_0x5cc;
            int gate = (MappersEnum)(short)commandBuildingType - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A;
            x = x + gatePartOffsets[gate][0];
            y = y + gatePartOffsets[gate][1];
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 3);
                tileY = this->buildingY + y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            partX = gatePartOffsets[gate][3] + origX;
            partY = gatePartOffsets[gate][4] + origY;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 3);
                baseX = this->buildingX;
                tileY = this->buildingY + partY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(partX + baseX, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + baseX + partX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            for (j = 0; j < 6; j++) {
                partY = gateEdgeOffsets[gate][j].y;
                partX = gateEdgeOffsets[gate][j].x;
                tileY = partY + origY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(origX + partX, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + partX + origX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_IRON_MINE) {
            if (ironCount < 4) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_IRON_ORE;
                this->buildingPlacementResult = TRUE;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS) {
            if (oilCount < 1) {
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_OIL_MARSH;
                this->buildingPlacementResult = TRUE;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_STORES) {
            if (DAT_GameState::instance.playerDataArray[playerID].stockpile.id == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_STOCKPILE)
                >= 0x20) {
                this->buildingPlacementResult = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                    DAT_BuildingsState::ptr)(playerID, (int)x, (int)y, buildingSize, OpenSHC::Map::Buildings::BT_STOCKPILE)
                == FALSE) {
                this->buildingPlacementResult = TRUE;
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_STOCKPILE;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_GRANARY) {
            if (DAT_GameState::instance.playerDataArray[playerID].granary.id == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_GRANARY)
                >= 8) {
                this->buildingPlacementResult = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                    DAT_BuildingsState::ptr)(playerID, (int)x, (int)y, buildingSize, OpenSHC::Map::Buildings::BT_GRANARY)
                == FALSE) {
                this->buildingPlacementResult = TRUE;
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_GRANARY;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_ARMOURY) {
            if (DAT_GameState::instance.playerDataArray[playerID].armory.id == 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getEmptyBuildingCount,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_ARMORY)
                >= 8) {
                this->buildingPlacementResult = TRUE;
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingAsNeighbour,
                    DAT_BuildingsState::ptr)(playerID, (int)x, (int)y, buildingSize, OpenSHC::Map::Buildings::BT_ARMORY)
                == FALSE) {
                this->buildingPlacementResult = TRUE;
                this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_NOT_ADJ_ARMORY;
            }
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_BARRACKS_EURO) {
            x = x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][0].x;
            y = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][0].y;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                tileY = this->buildingY + y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            partX = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].x + origX;
            partY = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].y + origY;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                baseX = this->buildingX;
                tileY = this->buildingY + partY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(partX + baseX, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + baseX + partX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            partX = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][2].x + origX;
            partY = DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][2].y + origY;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                baseX = this->buildingX;
                tileY = this->buildingY + partY;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(partX + baseX, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + baseX + partX;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD
            || (undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD) {
            x = x + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].x;
            y = y + DAT_TerrainDefinedData::instance.BuildingPartsOffsets[this->DAT_TempBuildingRotation][1].y;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 5);
                tileY = this->buildingY + y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, (MappersEnum)(short)commandBuildingType, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_OIL_SMELTER) {
            x = x + DAT_TerrainDefinedData::instance.oilSmelterPartOffsetByRot[this->DAT_TempBuildingRotation].x;
            y = y + DAT_TerrainDefinedData::instance.oilSmelterPartOffsetByRot[this->DAT_TempBuildingRotation].y;
            i = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(i, 4);
                tileY = this->buildingY + y;
                if (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                        DAT_ViewportRenderState::ptr)(this->buildingX + x, tileY)
                    == FALSE) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + this->buildingX + x;
                if ((this->LogicLayer[tile] & 0x30) != 0) {
                    this->buildingPlacementResult = 2;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isBuildingPlacementBlockedAtTile, this)(
                        tile, playerID, OpenSHC::Commands::M_MAPPER_OIL_SMELTER, 0)
                    != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                i = i + 1;
            } while (i < this->constructionTileCount);
            return;
        }
        if ((undefined2)commandBuildingType == OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::algTunnelerFindTarget,
                DAT_PathFindingState::ptr)(playerID, 0, 76, (int)x, (int)y);
            if (DAT_PathFindingState::instance.ALG_TargetTile == 0) {
                this->buildingPlacementResult = TRUE;
            }
        }
    }

}
}
