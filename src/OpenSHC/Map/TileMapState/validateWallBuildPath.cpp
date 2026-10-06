#include "../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;
    using Game::GameMode2;
    using Map::Buildings::BuildingFailReasonEnum;
    using Map::Units::UnitType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005029D0
    void TileMapState::validateWallBuildPath(int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command)
    {
        int iVar1;
        BOOLEnum BVar2;
        uint uVar3;
        int iVar4;
        int _castleBuildingRange;
        TileMapState* extraout_ECX;
        int extraout_ECX_00;
        TileMapState* _tileMapState;
        uint _y1;
        uint _x1;
        TileMapState* _tileMapState2;
        int* local_1c;
        int local_18;
        int local_14;
        int local_10;
        int local_c;
        int local_8;
        int local_4;
        uint _logic;
        _tileMapState = this;
        _tileMapState2 = this;
        local_c = 0;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            local_8 = 0x1e;
            local_4 = 0x1e;
        } else {
            local_8 = 0xf;
            local_4 = 7;
        }
        this->buildingPlacementFail = FALSE;
        this->illegalBuild = TRUE;
        this->field118_0x554920 = 0;
        if (((399 < x1) || (399 < y1)) || (*(char*)(y1 * 400 + 0x21aec98 + x1) == '\0')) {
            this->buildingPlacementFail = TRUE;
        }
        if (((399 < x2) || (399 < y2)) || (*(char*)(y2 * 400 + 0x21aec98 + x2) == '\0')) {
            this->buildingPlacementFail = TRUE;
        }
        local_1c = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
        iVar1 = *local_1c + x1;
        this->DAT_SomeY = y1;
        this->DAT_SomeTile = iVar1;
        if ((short)command == 0x1b) {
            BVar2 = MACRO_CALL_MEMBER(Map::TileMapState_Func::isTileEnclosedByWallsOrGates, this)(
                iVar1, (int)((int)(y1)));
            if (BVar2 == FALSE) {}
            this->maxWallHeightInPath
                = MACRO_CALL_MEMBER(Map::TileMapState_Func::getMaxWallHeightInBrushArea, this)(iVar1, y1);
            if (this->maxWallHeightInPath < 0x11) {}
            _tileMapState = this;
            local_c = this->maxWallHeightInPath;
        } else if (((short)command == 0x1a)
            && (iVar1 = MACRO_CALL_MEMBER(Map::TileMapState_Func::isTileEnclosedByWalls, this)(iVar1, (int)((int)(y1))),
                _tileMapState = extraout_ECX, !iVar1)) {
            extraout_ECX->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x13);
        }
        local_10 = 2;
        local_18 = y1 - y2;
        local_14 = y2 - y1;
        uVar3 = x2 - x1;
        _tileMapState->field118_0x554920 = 1;
        _y1 = y1;
        _x1 = x1;
        x1 = x1 - x2;
        y1 = uVar3;
        do {
            iVar1 = *local_1c + _x1;
            _logic = _tileMapState->LogicLayer[iVar1];
            if ((_logic & Map::LogicHelpers::L_PLAIN1_AND_FARM | Map::LogicHelpers::L_BORDER)) {}
            if ((_logic & Map::LogicHelpers::L_SEA | Map::LogicHelpers::L_BUILDING
                    | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE | Map::LogicHelpers::L_MARSH
                    | Map::LogicHelpers::L_MOAT)) {}
            if (_tileMapState->BuildingLayer[iVar1] != 0) {}
            if ((((_logic & Map::LogicHelpers::L_TREE | Map::LogicHelpers::L_TREE_VARIATION))
                    && (iVar4 = (int)_tileMapState->OrganismLayer[iVar1], iVar4))
                && (iVar4 < 2000)) {
                switch (DAT_LandscapeState::instance.trees[iVar4].treeType) {
                case ((TreeType)5):
                case ((TreeType)6):
                case ((TreeType)7):
                case ((TreeType)8):
                case ((TreeType)9):
                case ((TreeType)10):
                case ((TreeType)0xb):
                case ((TreeType)0xc):
                case ((TreeType)0xd):
                case ((TreeType)0xe):
                case ((TreeType)0x10):
                case ((TreeType)0x11):
                case ((TreeType)0x12):
                case ((TreeType)0x13):
                    break;
                    default:
                        return;
                }
            }
            if ((_logic & Map::LogicHelpers::L_RIVER | Map::LogicHelpers::L_FORD)) {}
            if ((char)_logic < '\0') {}
            if (((_tileMapState->UnitLayer[iVar1] != 0) && (!(_logic & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)))
                && (DAT_UnitsState::instance.units[(short)_tileMapState->UnitLayer[iVar1]].unitType
                    != Map::Units::UT_CHICKEN)) {}
            if (((DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR)
                    && (DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT))
                && (BVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk,
                        DAT_PathFindingState::ptr)(playerID, _x1, _y1, local_8),
                    BVar2 != FALSE)) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                iVar4 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                    DAT_PathFindingState::ptr)(playerID, (int)((int)(_x1)), (int)((int)(_y1)), local_4, -1, -1, -1);
                if (iVar4) {
                    if (this->buildingPlacementFailReason == ((BuildingFailReasonEnum)0x12)) {}
                    this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x13);
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                    _castleBuildingRange
                        = MACRO_CALL_MEMBER(Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                    iVar4 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isTileInRangeOfKeepRange,
                        DAT_PathFindingState::ptr)(playerID, _x1, _y1, _castleBuildingRange);
                    if (iVar4) {
                        if (this->buildingPlacementFailReason == ((BuildingFailReasonEnum)0x12)) {}
                        this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x13);
                    }
                }
            }
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR)
                && (iVar4
                    = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange,
                        DAT_PathFindingState::ptr)(playerID, (int)((int)(_x1)), (int)((int)(_y1)), 7, -1, -1, -1),
                    iVar4 != 0)) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
            }
            iVar4 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findSomeSuitableLocationUnk,
                DAT_PathFindingState::ptr)(playerID, _x1, _y1, 2);
            if (iVar4) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x11);
            }
            BVar2 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::isSignPostWithinDistance,
                DAT_PathFindingState::ptr)(_x1, _y1, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5);
            if (BVar2 != FALSE) {
                this->buildingPlacementFailReason = ((BuildingFailReasonEnum)0x15);
            }
            if ((short)command == 0x1a) {
                iVar1 = MACRO_CALL_MEMBER(Map::TileMapState_Func::isTileEnclosedByWalls, this)(
                    iVar1, (int)((int)(_y1)));
                if (!iVar1) {
                    *(undefined4*)(extraout_ECX_00 + 0x554938) = 0x13;
                }
            } else if (((short)command == 0x1b) && ((local_c < 0x11 || ((this->LogicLayer[iVar1] & 0x100U)))))
                break;
            uVar3 = x1;
            if ((int)_x1 < (int)x2) {
                uVar3 = y1;
            }
            iVar1 = local_18;
            if ((int)_y1 < (int)y2) {
                iVar1 = local_14;
            }
            if ((short)command == 0x1b) {
                if (iVar1 < (int)uVar3) {
                    if ((int)_x1 < (int)x2) {
                        x1 = x1 + 1;
                        _x1 = _x1 + 1;
                        y1 = y1 - 1;
                    } else {
                        x1 = x1 - 1;
                        _x1 = _x1 - 1;
                        y1 = y1 + 1;
                    }
                } else {
                    if (iVar1 < 1)
                        goto LAB_00502e46;
                    if ((int)_y1 < (int)y2) {
                        local_1c = local_1c + 3;
                        local_18 = local_18 + 1;
                        _y1 = _y1 + 1;
                        local_14 = local_14 + -1;
                    } else {
                        local_1c = local_1c + -3;
                        local_18 = local_18 + -1;
                        _y1 = _y1 - 1;
                        local_14 = local_14 + 1;
                    }
                }
            } else {
                if (uVar3) {
                    if ((int)_x1 < (int)x2) {
                        x1 = x1 + 1;
                        _x1 = _x1 + 1;
                        y1 = y1 - 1;
                    } else {
                        x1 = x1 - 1;
                        _x1 = _x1 - 1;
                        y1 = y1 + 1;
                    }
                }
                if (iVar1) {
                    if ((int)_y1 < (int)y2) {
                        local_1c = local_1c + 3;
                        local_18 = local_18 + 1;
                        _y1 = _y1 + 1;
                        local_14 = local_14 + -1;
                    } else {
                        local_1c = local_1c + -3;
                        local_18 = local_18 + -1;
                        _y1 = _y1 - 1;
                        local_14 = local_14 + 1;
                    }
                }
                if ((_x1 == x2) && (_y1 == y2)) {
                LAB_00502e46:
                    local_10 = local_10 + -1;
                }
            }
            if (0x10 < local_c) {
                local_c = local_c + -0x10;
            }
            _tileMapState = _tileMapState2;
        } while (((_x1 != x2) || (_y1 != y2)) || (local_10));
        this->illegalBuild = FALSE;
    }

}
}
