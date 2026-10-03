#include "../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnum;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::LogicHelpers::Logic1;

    // FUNCTION: STRONGHOLDCRUSADER 0x00504A30
    void TileMapState::evaluateBuildingPlacementAtCursor(int playerID, uint x, uint y)
    {
        BuildingTypeShort BVar1;
        BOOLEnum BVar2;
        uint uVar3;
        int iVar4;
        int local_4;
        uVar3 = x;
        local_4 = 0;
        if (((399 < x) || (399 < y)) || (*(char*)(y * 400 + 0x21aec98 + x) == '\0')) {
            this->buildingPlacementFail = TRUE;
        }
        this->buildingPlacementFail = FALSE;
        if (DAT_ViewportRenderState::instance.viewportState.field15_0x3c != 0) {
            local_4 = DAT_ViewportRenderState::instance.viewportState.field24_0x60;
            this->field153_0x5549a0 = DAT_ViewportRenderState::instance.viewportState.field24_0x60;
        }
        if (this->flatViewToggleValue1 == 0) {
            x = DAT_ViewportRenderState::instance.viewportState.mouseRayBuildingID;
            iVar4 = DAT_ViewportRenderState::instance.viewportState.field21_0x54;
        LAB_00504ae2:
            if (x != 0)
                goto LAB_00504ae6;
        } else {
            x = (uint)this->BuildingLayer[DAT_ViewportRenderState::instance.viewportState.mouseTile];
            iVar4 = 0;
            if ((this->LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseTile] & 0x100U) == 0)
                goto LAB_00504ae2;
            if (((this->LogicLayer[DAT_ViewportRenderState::instance.viewportState.mouseTile] & 2U) == 0) || (x == 0)) {
                DAT_ViewportRenderState::instance.viewportState.field21_0x54
                    = DAT_ViewportRenderState::instance.viewportState.mouseTile;
                iVar4 = DAT_ViewportRenderState::instance.viewportState.mouseTile;
                goto LAB_00504ae2;
            }
        LAB_00504ae6:
            uVar3 = (uint)(short)DAT_BuildingsState::instance.buildings[x].x;
            y = (uint)(short)DAT_BuildingsState::instance.buildings[x].y;
        }
        if (((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
            && (BVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                    DAT_PathFindingState::ptr)(playerID, uVar3, y,
                    (int)((int)((-(uint)(DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                                    & 0xfffffff1)
                        + 0x1e))),
                BVar2 != FALSE)) {
            this->field194_0x554a20 = 1;
            this->buildingPlacementFail = TRUE;
            this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x14);
            if (x != 0) {
                if (DAT_BuildingsState::instance.buildings[x].owner == playerID) {
                    this->buildingPlacementFail = TRUE;
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x14);
                    this->field194_0x554a20 = 1;
                }
                if (playerID != 0) {
                    this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                }
                this->buildingPlacementFail = TRUE;
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x14);
                this->field194_0x554a20 = 1;
            }
            if (0 < iVar4) {
                if ((this->LogicLayer[iVar4] & OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE) == 0) {
                    this->buildingPlacementFail = TRUE;
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x14);
                    this->field194_0x554a20 = 1;
                }
                if ((this->WallOwnerLayer[iVar4] & 7) + 1 != playerID) {
                    this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
                }
                this->buildingPlacementFail = TRUE;
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x14);
                this->field194_0x554a20 = 1;
            }
            if ((0 < local_4) && ((this->LogicLayer[local_4] & OpenSHC::Map::LogicHelpers::L_MOAT) != 0)) {
                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(local_4);
                if (iVar4 == 0) {}
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[iVar4].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {}
            }
            this->buildingPlacementFailReason = OpenSHC::Map::Buildings::BFRE_DEFAULT_CANT_PLACE_THAT_THERE;
        }
        if (DAT_ViewportRenderState::instance.viewportState.somePitchDitchID != 0) {
            if (this->pitchDitches[DAT_ViewportRenderState::instance.viewportState.somePitchDitchID].owner
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                this->buildingPlacementFail = TRUE;
            }
            this->field131_0x554954 = -DAT_ViewportRenderState::instance.viewportState.somePitchDitchID;
        }
        if (((int)x < 1) || ((DAT_BuildingsState::instance.buildings[x].owner != playerID && (playerID != 0)))) {
            this->buildingPlacementFail = TRUE;
        }
        if (iVar4 < 1) {
        LAB_00504d0f:
            if (((local_4 < 1) || ((this->LogicLayer[local_4] & OpenSHC::Map::LogicHelpers::L_MOAT) == 0)) || (x != 0)) {
                if ((this->field151_0x554998 != 0) || (this->field152_0x55499c != 0))
                    goto LAB_00504da2;
            } else if (this->field151_0x554998 == 0) {
                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(local_4);
                if (iVar4 == 0) {}
                if (DAT_GameState::instance.mapAndTime.playerTeams[this->moats[iVar4].owner]
                    != DAT_GameState::instance.mapAndTime.playerTeams[playerID]) {}
                this->field152_0x55499c = 1;
                this->buildingPlacementFail = (BOOLEnum)((this->MiscDisplayLayer[local_4] & 0x400) != 0);
                iVar4 = local_4;
            } else {
            LAB_00504da2:
                this->buildingPlacementFail = TRUE;
            }
        } else {
            uVar3 = this->LogicLayer[iVar4] & OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;
            if ((uVar3 != 0) && ((this->LogicLayer[iVar4] & OpenSHC::Map::LogicHelpers::L_STOCKPILEUnk) != 0)) {
                this->buildingPlacementFail = TRUE;
            }
            if (((uVar3 == 0) || (this->BuildingLayer[iVar4] != 0)) || (this->field152_0x55499c != 0))
                goto LAB_00504d0f;
            if ((this->WallOwnerLayer[iVar4] & 7) + 1 != playerID) {}
            this->buildingPlacementFail = FALSE;
            this->field151_0x554998 = 1;
            if ((this->MiscDisplayLayer[iVar4] & 0x400) != 0) {
                this->buildingPlacementFail = TRUE;
            }
        }
        if ((0 < iVar4) && (this->UnitLayer[iVar4] != 0)) {
            this->buildingPlacementFail = TRUE;
        }
        if (x == 0)
            goto LAB_00504e15;
        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                if (DAT_BuildingsState::instance.buildings[x].buildingType == OpenSHC::Map::Buildings::BT_SIGNPOST)
                    goto switchD_00504ded_caseD_27;
            } else {
                switch (DAT_BuildingsState::instance.buildings[x].buildingType) {
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
                switchD_00504ded_caseD_27:
                    this->buildingPlacementFail = TRUE;
                }
            }
        }
        if ((int)x < 0) {
            this->field131_0x554954 = x;
        }
    LAB_00504e15:
        if ((((((((this->LogicLayer[DAT_BuildingsState::instance.buildings[x].currentTilePositionAdjusted] & OpenSHC::Map::LogicHelpers::L_BUILDING
                      | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                     == 0)
                    && (BVar1 = DAT_BuildingsState::instance.buildings[x].buildingType,
                        BVar1 != OpenSHC::Map::Buildings::BT_GATEHOUSELARGE))
                   && (BVar1 != OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))
                  && ((BVar1 != OpenSHC::Map::Buildings::BT_WOODGATE1
                      && (BVar1 != OpenSHC::Map::Buildings::BT_WOODGATE2))))
                 && ((BVar1 != OpenSHC::Map::Buildings::BT_KEEPDOOR
                     && ((BVar1 != OpenSHC::Map::Buildings::BT_DRAWBRIDGE
                         && (BVar1 != OpenSHC::Map::Buildings::BT_KILLINGPIT))))))
                && (this->field151_0x554998 == 0))
            && (this->field152_0x55499c == 0)) {
            this->buildingPlacementFail = TRUE;
        }
        this->field131_0x554954 = x;
    }

}
}
