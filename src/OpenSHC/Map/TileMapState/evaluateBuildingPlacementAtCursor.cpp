
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_STOCKPILE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00504A30
    void TileMapState::evaluateDemolishTargetAtCursor(int playerID, uint x, uint y)
    {
        uint anchorY = y;
        uint anchorX = x;
        int moatTile = 0;
        if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            this->buildingPlacementResult = TRUE;
            return;
        }
        this->buildingPlacementResult = FALSE;
        if (DAT_ViewportRenderState::instance.viewportState.mouseOnOwnMoat != 0) {
            moatTile = DAT_ViewportRenderState::instance.viewportState.mouseTargetTile;
            this->deleteTargetMoatTile = DAT_ViewportRenderState::instance.viewportState.mouseTargetTile;
        }

        /* the flat view has no ray hit, so the tile under the mouse is used directly */
        int buildingID;
        int wallTile = DAT_ViewportRenderState::instance.viewportState.mouseWallTile;
        if (this->flatViewToggleValue1 != 0) {
            int mouseTile = DAT_ViewportRenderState::instance.viewportState.mouseTile;
            buildingID = this->BuildingLayer[mouseTile];
            wallTile = 0;
            if ((DAT_TileMapState::instance.LogicLayer[mouseTile] & L_WALL_OR_GATEHOUSE) != 0
                && ((DAT_TileMapState::instance.LogicLayer[mouseTile] & L_STOCKPILE) == 0 || buildingID == 0)) {
                wallTile = mouseTile;
                DAT_ViewportRenderState::instance.viewportState.mouseWallTile = wallTile;
            }
        } else {
            buildingID = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
        }
        if (buildingID != 0) {
            anchorX = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            anchorY = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
        }

        int enemyDistance = DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY ? 0xf : 0x1e;
        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
            && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyUnitWithinDistance,
                   DAT_PathFindingState::ptr)(playerID, anchorX, anchorY, enemyDistance)
                != FALSE) {
            this->deleteBlockedByEnemy = 1;
            this->buildingPlacementResult = TRUE;
            this->buildingPlacementFailReason = (BuildingFailReasonEnum)0x14;
            if (buildingID != 0) {
                if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID && playerID != 0) {
                    this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                }
                return;
            }
            if (wallTile > 0) {
                if ((this->LogicLayer[wallTile] & L_WALL_OR_GATEHOUSE) != 0
                    && (this->WallOwnerLayer[wallTile] & 7) + 1 != playerID) {
                    this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                }
                return;
            }
            if (moatTile > 0 && (this->LogicLayer[moatTile] & L_MOAT) != 0) {
                int moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(moatTile);
                if (moatID == 0) {
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    return;
                }
            }
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
            return;
        }

        if (DAT_ViewportRenderState::instance.viewportState.hoverPitchDitchID != 0) {
            if (this->pitchDitches[DAT_ViewportRenderState::instance.viewportState.hoverPitchDitchID].owner
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                this->deleteTargetID = -DAT_ViewportRenderState::instance.viewportState.hoverPitchDitchID;
                return;
            }
            this->buildingPlacementResult = TRUE;
            return;
        }

        if (buildingID < 1
            || (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID && playerID != 0)) {
            this->buildingPlacementResult = TRUE;
        }

        if (wallTile > 0) {
            /* a stockpile tile carries the wall flag too, but nothing may be built on it */
            if ((this->LogicLayer[wallTile] & L_WALL_OR_GATEHOUSE) != 0
                && (this->LogicLayer[wallTile] & L_STOCKPILE) != 0) {
                this->buildingPlacementResult = TRUE;
                return;
            }
            if ((this->LogicLayer[wallTile] & L_WALL_OR_GATEHOUSE) != 0 && this->BuildingLayer[wallTile] == 0
                && this->deleteTargetIsMoat == 0) {
                if ((this->WallOwnerLayer[wallTile] & 7) + 1 != playerID) {
                    return;
                }
                this->buildingPlacementResult = FALSE;
                this->deleteTargetIsWall = 1;
                if ((this->MiscDisplayLayer[wallTile] & 0x400) != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                goto checkUnits;
            }
        }
        if (moatTile > 0 && (this->LogicLayer[moatTile] & L_MOAT) != 0 && buildingID == 0) {
            if (this->deleteTargetIsWall == 0) {
                int moatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(moatTile);
                if (moatID == 0) {
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[moatID].owner]
                    != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {
                    return;
                }
                this->buildingPlacementResult = FALSE;
                this->deleteTargetIsMoat = 1;
                if ((this->MiscDisplayLayer[moatTile] & 0x400) != 0) {
                    this->buildingPlacementResult = TRUE;
                }
                wallTile = moatTile;
            } else {
                this->buildingPlacementResult = TRUE;
            }
        } else if (this->deleteTargetIsWall != 0 || this->deleteTargetIsMoat != 0) {
            this->buildingPlacementResult = TRUE;
        }

    checkUnits:
        if (wallTile > 0 && this->UnitLayer[wallTile] != 0) {
            this->buildingPlacementResult = TRUE;
        }
        if (buildingID != 0) {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST) {
                        this->buildingPlacementResult = TRUE;
                    }
                } else {
                    switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                    case OpenSHC::Map::Buildings::BT_UNKNOWN1:
                    case OpenSHC::Map::Buildings::BT_MANORHOUSE:
                    case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    case OpenSHC::Map::Buildings::BT_SIGNPOST:
                    case OpenSHC::Map::Buildings::BT_CAMPGROUND:
                    case OpenSHC::Map::Buildings::BT_KEEPDOOR_LEFT:
                    case OpenSHC::Map::Buildings::BT_KEEPDOOR_RIGHT:
                    case OpenSHC::Map::Buildings::BT_KEEPDOOR:
                    case OpenSHC::Map::Buildings::BT_POND:
                        this->buildingPlacementResult = TRUE;
                    }
                }
            }
            if (buildingID < 0) {
                this->deleteTargetID = buildingID;
                return;
            }
        }

        if ((this->LogicLayer[DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted]
                & (L_BUILDING | L_KEEP_NON_MANOR_HOUSE))
                == 0
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSELARGE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_WOODGATE1
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_WOODGATE2
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KEEPDOOR
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_DRAWBRIDGE
            && DAT_BuildingsState::instance.buildings[buildingID].buildingType != OpenSHC::Map::Buildings::BT_KILLINGPIT
            && this->deleteTargetIsWall == 0 && this->deleteTargetIsMoat == 0) {
            this->buildingPlacementResult = TRUE;
        }
        this->deleteTargetID = buildingID;
    }

}
}
