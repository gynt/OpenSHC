
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_MERLON;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_UNKNOWN_WALL_RELATED;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00502F30
    void TileMapState::placeWalls(
        int playerID, uint x1, uint y1, uint x2, uint y2, MappersEnum wallType, int tileCountUnk)
    {
        int budget = 0;
        int wallCount = 0;
        int placed = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateWallBuildPath, this)(playerID, x1, y1, x2, y2, wallType);
        if (this->illegalBuild != FALSE) {
            return;
        }

        this->constructionTileCount = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(
            playerID, 4);
        int overshoot = 2;
        if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
            budget = this->stairStartHeight;
        }
        if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::resetWallPlacementInfo, DAT_WallAndPitchState::ptr)();
        }

        int upY = y1 - y2;
        int leftX = x1 - x2;
        int downY = y2 - y1;
        int rightX = x2 - x1;
        int* translation = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        uint x = x1;
        uint y = y1;
        do {
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR && budget < 0x18) {
                break;
            }
            if (placed >= tileCountUnk || wallCount > this->constructionTileCount) {
                break;
            }
            placed++;
            int tile = *translation + x;
            int towerNeighbours = 0;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR
                && (this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) != 0) {
                break;
            }
            /* a wall dragged over a crenel replaces it without counting against the tally */
            int applyWall = 0;
            int overCrenel = 0;
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_WALL && (this->LogicLayer[tile] & L_CRENEL) != 0) {
                overCrenel = 1;
            }
            if ((this->LogicLayer[tile] & L_WALL_OR_GATEHOUSE) == 0 || this->DamageOrCropStageLayer[tile] != 0
                || overCrenel != 0) {
                if (DAT_GameSynchronyState::instance.currentPlayerSlotID == playerID) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::addWallPlacementInfoForTile, DAT_WallAndPitchState::ptr)(tile);
                }
                if (overCrenel == 0) {
                    applyWall = 1;
                }
                if (this->DamageOrCropStageLayer[tile] != 0 || overCrenel != 0) {
                    this->DamageOrCropStageLayer[tile] = 0;
                    this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                    if (overCrenel != 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] & ~(L_CRENEL | L_CRENEL_MERLON)
                            | L_WALL_OR_GATEHOUSE;
                    }
                }

                if ((short)wallType == OpenSHC::Commands::M_MAPPER_WALL) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x5a;
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL) {
                    this->HeightLayer[tile] = this->HeightLayer[tile] + 0x3c;
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_CRENAL) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL;
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::hasOnlyTowerNeighborsNoWalls, this)(tile, y)
                        != FALSE) {
                        this->HeightLayer[tile] = this->HeightLayer[tile] + 0x44;
                        towerNeighbours = 1;
                    } else {
                        this->HeightLayer[tile] = this->HeightLayer[tile] + 0x62;
                    }
                    /* a crenel on an odd tile of one axis carries the alternate variation */
                    if ((x & 1) != 0 && (y & 1) == 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL_MERLON;
                    } else if ((x & 1) == 0 && (y & 1) != 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_CRENEL_MERLON;
                    }
                } else if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
                    int steps = budget - this->HeightLayer[tile] - 0x10;
                    if (steps > 0) {
                        this->LogicLayer[tile] = this->LogicLayer[tile] | L_STAIRS;
                        this->HeightLayer[tile] = this->HeightLayer[tile] + (char)steps;
                    } else {
                        applyWall = 0;
                    }
                }

                if (applyWall != 0 || overCrenel != 0) {
                    if (overCrenel == 0) {
                        wallCount++;
                        this->LogicLayer[tile]
                            = this->LogicLayer[tile] & ~(L_UNKNOWN_WALL_RELATED | L_BOULDERS | L_PEBBLES | L_IRON)
                            | L_WALL_OR_GATEHOUSE;
                        if (this->UnitLayer[tile] != 0) {
                            int unitID = (short)this->UnitLayer[tile];
                            if (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_CHICKEN) {
                                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                                DAT_UnitsState::instance.units[unitID].updateTickTracker = overCrenel;
                                DAT_UnitsState::instance.units[unitID].fadeLevel = 0;
                            }
                        }
                        if ((this->LogicLayer[tile] & L_PLAIN2_AND_PITCH) != 0) {
                            this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_PLAIN2_AND_PITCH;
                            this->HeightLayer[tile] = this->HeightLayer[tile] + 4;
                        }
                        int organism;
                        if ((this->LogicLayer[tile] & L_TREE) != 0 && (organism = this->OrganismLayer[tile]) < 2000) {
                            /* scrub is flattened by the wall, a real tree is left standing */
                            switch (DAT_LandscapeState::instance.trees[organism].treeType) {
                            case (TreeType)5:
                            case (TreeType)6:
                            case (TreeType)7:
                            case (TreeType)8:
                            case (TreeType)9:
                            case (TreeType)0xa:
                            case (TreeType)0xb:
                            case (TreeType)0xc:
                            case (TreeType)0xd:
                            case (TreeType)0xe:
                            case (TreeType)0x10:
                            case (TreeType)0x11:
                            case (TreeType)0x12:
                            case (TreeType)0x13:
                                DAT_LandscapeState::instance.trees[organism].state = 3;
                            }
                        }
                        if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL || towerNeighbours != 0) {
                            this->LogicLayer[tile] = this->LogicLayer[tile] | L_UNKNOWN_WALL_RELATED;
                        }
                        this->WallOwnerLayer[tile] = this->WallOwnerLayer[tile] & 0xf8 | (char)playerID - 1U;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections, DAT_PathFindingState::ptr)(
                        y, tile);
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoat, this)(tile);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(7, x, y);
                }
            }

            int stepX = leftX;
            if ((int)x < (int)x2) {
                stepX = rightX;
            }
            int stepY = upY;
            if ((int)y < (int)y2) {
                stepY = downY;
            }
            if ((short)wallType == OpenSHC::Commands::M_MAPPER_STAIR) {
                if (stepX > stepY) {
                    if ((int)x >= (int)x2) {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    } else {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    }
                } else if (stepY > 0) {
                    if ((int)y >= (int)y2) {
                        y = y - 1;
                        translation = translation - 3;
                        upY = upY - 1;
                        downY = downY + 1;
                    } else {
                        y = y + 1;
                        translation = translation + 3;
                        upY = upY + 1;
                        downY = downY - 1;
                    }
                } else {
                    overshoot = overshoot - 1;
                }
            } else {
                if (stepX != 0) {
                    if ((int)x >= (int)x2) {
                        leftX = leftX - 1;
                        x = x - 1;
                        rightX = rightX + 1;
                    } else {
                        leftX = leftX + 1;
                        x = x + 1;
                        rightX = rightX - 1;
                    }
                }
                if (stepY != 0) {
                    if ((int)y >= (int)y2) {
                        y = y - 1;
                        translation = translation - 3;
                        upY = upY - 1;
                        downY = downY + 1;
                    } else {
                        y = y + 1;
                        translation = translation + 3;
                        upY = upY + 1;
                        downY = downY - 1;
                    }
                }
                if (x == x2 && y == y2) {
                    overshoot = overshoot - 1;
                }
            }
            if (budget >= 0x10) {
                budget = budget - 0x10;
            }
        } while (x != x2 || y != y2 || overshoot != 0);

        /* a stair that ran out (only ever a stair) falls to the stone tally */
        if ((short)wallType == OpenSHC::Commands::M_MAPPER_WOODWALL) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss, DAT_BuildingsState::ptr)(
                playerID, 0, wallCount, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processWallBuildingLoss, DAT_BuildingsState::ptr)(
                playerID, wallCount, 0, 0);
        }
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        DAT_TileMapState::instance.terrainChangedDirty = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
