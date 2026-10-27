
#include "OpenSHC/Game.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_MERLON;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005162D0
    void TileMapState::placeBuilding(
        PlayerID playerID, int x, int y, MappersEnum cbt, int buildingSize, int buildingOrientation)
    {
        int pitchDitchID = 0;
        int command = (short)cbt;
        if (this->forcePlaceBuilding == 0) {
            if (buildingOrientation == 0xf) {
                this->DAT_TempBuildingRotation = 0;
            } else {
                this->DAT_TempBuildingRotation = buildingOrientation / 2;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::checkBuildingCanBePlacedHere, this)(playerID, x, y, cbt, buildingSize);
            if (this->buildingPlacementResult != FALSE) {
                return;
            }
        }
        this->forcePlaceBuilding = 0;

        /* cbt is reused for the building type (0x516354 stores it into the argument slot): kept zero-extended for
           the place* calls and sign-extended for the switches */
        cbt = (MappersEnum)(ushort)MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
            DAT_BuildingsState::ptr)((MappersEnum)command);
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
            int tutorialType = (short)cbt;
            if (MACRO_CALL(OpenSHC::Game_Func::Tutorial_IsActionAllowed)(2, tutorialType) == FALSE) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                return;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(7, (BuildingType)tutorialType);
        }

        /* clear whatever the footprint was before the building goes down */
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, buildingSize);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
                && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                DAT_GameState::instance.playerDataArray[playerID].pendingResources[4] += 1;
            }
            if ((this->LogicLayer[tile] & L_ROCKY) != 0) {
                int organism = this->OrganismLayer[tile];
                if (organism >= 2000) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(
                        organism - 2000);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, buildingSize);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                        DAT_PathFindingState::ptr)(8, this->buildingX + x, this->buildingY + y);
                }
            }
            this->LogicLayer[tile] = this->LogicLayer[tile]
                & ~(L_CRENEL_MERLON | L_UNKNOWN_WALL_RELATED | L_STAIRS | L_CRENEL | L_WALL_OR_GATEHOUSE
                    | L_PLAIN2_AND_PITCH);
            /* 0x51644b: the default height is read from the global tile map, not through this */
            this->HeightLayer[tile] = DAT_TileMapState::instance.DefaultHeightLayer[tile];
            this->DamageOrCropStageLayer[tile] = 0;
            if ((this->LogicLayer[tile] & L_TREE) != 0) {
                int treeID = this->OrganismLayer[tile];
                if (treeID < 2000) {
                    /* every tree goes, apple or not; both arms are identical */
                    switch (DAT_LandscapeState::instance.trees[treeID].treeType) {
                    case OpenSHC::Map::Trees::TT_SHRUB1A:
                    case OpenSHC::Map::Trees::TT_SHRUB1B:
                    case OpenSHC::Map::Trees::TT_SHRUB1C:
                    case OpenSHC::Map::Trees::TT_SHRUB1D:
                    case OpenSHC::Map::Trees::TT_SHRUB1E:
                    case OpenSHC::Map::Trees::TT_SHRUB2A:
                    case OpenSHC::Map::Trees::TT_SHRUB2B:
                    case OpenSHC::Map::Trees::TT_SHRUB2C:
                    case OpenSHC::Map::Trees::TT_SHRUB2D:
                    case OpenSHC::Map::Trees::TT_SHRUB2E:
                    case OpenSHC::Map::Trees::TT_SHRUB3A:
                    case OpenSHC::Map::Trees::TT_SHRUB3B:
                    case OpenSHC::Map::Trees::TT_SHRUB3C:
                    case OpenSHC::Map::Trees::TT_SHRUB3D:
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(treeID);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                            DAT_PathFindingState::ptr)(3, x, y);
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            index, buildingSize);
                        break;
                    default:
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(treeID);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                            DAT_PathFindingState::ptr)(3, x, y);
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                            index, buildingSize);
                        break;
                    }
                }
            }
            int unitID = (short)this->UnitLayer[tile];
            if (unitID != 0) {
                /* a unit standing where a walkable building goes is left alone */
                switch ((short)cbt) {
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
                case OpenSHC::Map::Buildings::BT_OILSMELTER_PART:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND:
                case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND2:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND3:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND4:
                case OpenSHC::Map::Buildings::BT_PARADEGROUND5:
                case OpenSHC::Map::Buildings::BT_KILLINGPIT:
                case OpenSHC::Map::Buildings::BT_PITCHDITCH:
                case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                case OpenSHC::Map::Buildings::BT_TOWER1:
                case OpenSHC::Map::Buildings::BT_TOWER2:
                case OpenSHC::Map::Buildings::BT_TOWER3:
                case OpenSHC::Map::Buildings::BT_TOWER4:
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    break;
                default:
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(unitID);
                }
            }
            if ((this->LogicLayer[tile] & (L_MOAT | L_MOAT_DUG_OR_PLANNED)) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(this->buildingX + x, this->buildingY + y);
                this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_MOAT | L_MOAT_DUG_OR_PLANNED);
            }
            this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] & 0xfc3f;
            index++;
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
            DAT_TileMapState::instance.terrainChangedDirty = 1;
        } while (index < this->constructionTileCount);

        /* the building sits at the middle of the heights it covers */
        int lowest = 1000;
        int highest = 0;
        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, buildingSize);
            int tileHeight = this->HeightLayer[DAT_ViewportRenderState::instance
                                                    .translationMatrix[this->buildingY + y]
                                                    .addXgetTile
                + this->buildingX + x];
            if (tileHeight > highest) {
                highest = tileHeight;
            }
            if (tileHeight < lowest) {
                lowest = tileHeight;
            }
            index++;
        } while (index < this->constructionTileCount);
        int averageHeight = (highest - lowest) / 2 + lowest;

        if ((short)cbt == OpenSHC::Map::Buildings::BT_TUNNEL
            && playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::playTunnelerCommandSpeech, DAT_TribesState::ptr)();
        }

        int shortType = (short)cbt;
        switch (shortType) {
        case OpenSHC::Map::Buildings::BT_UNKNOWN1:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::stampBuildingOntoTileMap, this)(playerID, x, y, (BuildingType)cbt,
                command + ~OpenSHC::Commands::M_MAPPER_MP_KEEP8, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_GARDEN:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePositiveFearfactor, this)(playerID, x, y, (BuildingType)cbt,
                command - OpenSHC::Commands::M_MAPPER_GARDEN1, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_CESSPIT:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePositiveFearfactor, this)(playerID, x, y, (BuildingType)cbt,
                command - OpenSHC::Commands::M_MAPPER_CESS_PIT1, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_STATUE:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePositiveFearfactor, this)(playerID, x, y, (BuildingType)cbt,
                command - OpenSHC::Commands::M_MAPPER_STATUE1, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_SHRINE:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePositiveFearfactor, this)(playerID, x, y, (BuildingType)cbt,
                command - OpenSHC::Commands::M_MAPPER_SHRINE1, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_POND:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePositiveFearfactor, this)(playerID, x, y, (BuildingType)cbt,
                command - OpenSHC::Commands::M_MAPPER_POND1, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_STOCKPILE:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeStockpile, this)(playerID, x, y, cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_QUARRY:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeQuarry, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_WHEATFARM:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeWheatfarm, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_HOPFARM:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeHopfarm, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_DAIRYFARM:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeDairyfarm, this)(playerID, x, y, (BuildingType)cbt, buildingSize, (int*)buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_APPLEFARM:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeApplefarm, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, (int*)averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
        case OpenSHC::Map::Buildings::BT_BARRACKS:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeBarracks, this)(playerID, x, (int*)y, cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeEngineersguild, this)(playerID, (int*)x, y, cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeTunnelersguild, this)(playerID, (int*)x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_OILSMELTER:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeOilsmelter, this)(playerID, x, y, cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_MANORHOUSE:
        case OpenSHC::Map::Buildings::BT_STONEKEEP:
        case OpenSHC::Map::Buildings::BT_STRONGHOLD:
        case OpenSHC::Map::Buildings::BT_KEEPFOUR:
        case OpenSHC::Map::Buildings::BT_KEEPFIVE:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeKeep, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_TOWER1:
        case OpenSHC::Map::Buildings::BT_TOWER2:
        case OpenSHC::Map::Buildings::BT_TOWER3:
        case OpenSHC::Map::Buildings::BT_TOWER4:
        case OpenSHC::Map::Buildings::BT_TOWER5:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeTower, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeGatehouseLarge, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeGatehouseSmall, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeDrawbridge, this)(playerID, x, y, (BuildingType)cbt, buildingSize, (int*)buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
        case OpenSHC::Map::Buildings::BT_CATAPULT:
        case OpenSHC::Map::Buildings::BT_TREBUCHET:
        case OpenSHC::Map::Buildings::BT_SIEGETOWER:
        case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
        case OpenSHC::Map::Buildings::BT_SHIELD:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeSiegeTent, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_KILLINGPIT:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeKillingPit, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_PITCHDITCH:
            pitchDitchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placePitchDitch, this)(playerID, x, y);
            break;
        case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeSiegetowerPlaced, this)(playerID, x, y, cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        case OpenSHC::Map::Buildings::BT_WOODGATE1:
            break;
        default:
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::placeWorkshopOrHovel, this)(playerID, x, y, (BuildingType)cbt, buildingSize, buildingOrientation, averageHeight);
            break;
        }

        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            if ((short)cbt != OpenSHC::Map::Buildings::BT_PITCHDITCH) {
                MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::startBuildingPlacementUndoWindow,
                    DAT_WallAndPitchState::ptr)(this->placedBuildingID);
            } else if (pitchDitchID != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::WallAndPitchState_Func::recordPitchDitchForUndo, DAT_WallAndPitchState::ptr)(pitchDitchID);
            }
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::processPlacementResourceLossForBuildingType,
            DAT_BuildingsState::ptr)(playerID, (BuildingType)shortType, 0);
        if (MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::
                    hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
                DAT_BuildingsState::ptr)(playerID, shortType)
            != 0) {
            DAT_BuildingsState::instance.buildings[this->placedBuildingID].noRefundOnDestroy = 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
        int radius;
        if (buildingSize <= 5) {
            radius = 9;
        } else {
            radius = buildingSize + 5;
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(radius, x, y);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        DAT_TileMapState::instance.terrainChangedDirty = 1;
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            this->forceUpdateMacroLayerFlag = 1;
            this->macroLayerUpdateDelay = 200;
        }
    }

}
}
