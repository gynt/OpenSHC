#include "../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Commands/MappersEnumInt.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::UnitType;
    using Map::Units::States::UnitState;
    using WindowsHelper::Enums::BOOLEnum;
    using Commands::MappersEnumInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x00502F30
    void TileMapState::placeWalls(
        int playerID, uint x1, uint y1, uint x2, uint y2, MappersEnum wallType, int tileCountUnk)
    {
        bool bVar1;
        bool bVar2;
        BOOLEnum BVar3;
        int _unitID;
        int _treeID;
        uint uVar4;
        int iVar5;
        int _tile;
        uint local_28;
        int* local_24;
        int local_20;
        int local_1c;
        uint local_18;
        int local_14;
        int local_10;
        int _normalWallCountUnk;
        int local_8;
        int _count1;
        int _count2;
        MappersEnumInt unionfacet2_503295;
        local_14 = 0;
        _normalWallCountUnk = 0;
        local_8 = 0;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::validateWallBuildPath, this)(
            playerID, x1, y1, x2, y2, (undefined4)((int)(wallType)));
        if (this->illegalBuild == FALSE) {
            this->constructionTileCount = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(playerID, 4);
            local_10 = 2;
            if ((undefined2)wallType == Commands::M_MAPPER_STAIR) {
                local_14 = this->maxWallHeightInPath;
            }
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(
                    Map::WallAndPitchState_Func::resetWallPlacementInfo, DAT_WallAndPitchState::ptr)();
            }
            local_20 = y1 - y2;
            local_1c = y2 - y1;
            local_28 = x2 - x1;
            local_24 = &DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
            local_18 = x1;
            x1 = x1 - x2;
            do {
                if (((undefined2)wallType == Commands::M_MAPPER_STAIR) && (local_14 < 0x18))
                    goto LAB_00503440;
                if ((tileCountUnk <= local_8) || (this->constructionTileCount < _normalWallCountUnk))
                    break;
                local_8 = local_8 + 1;
                _tile = *local_24 + local_18;
                bVar2 = false;
                if (((undefined2)wallType == Commands::M_MAPPER_STAIR)
                    && ((this->LogicLayer[_tile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)))
                    goto LAB_00503440;
                bVar1 = false;
                if (((undefined2)wallType == Commands::M_MAPPER_WALL)
                    && ((this->LogicLayer[_tile] & Map::LogicHelpers::L_CRENEL))) {
                    bVar1 = true;
                }
                if (((!(this->LogicLayer[_tile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE))
                        || (this->DamageLayer[_tile] != 0))
                    || (bVar1)) {
                    if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(Map::WallAndPitchState_Func::addWallPlacementInfoForTile,
                            DAT_WallAndPitchState::ptr)(_tile);
                    }
                    if ((this->DamageLayer[_tile] != 0) || (bVar1)) {
                        this->DamageLayer[_tile] = 0;
                        this->HeightLayer[_tile] = this->DefaultHeightLayer[_tile];
                        if (bVar1) {
                            this->LogicLayer[_tile]
                                = this->LogicLayer[_tile] & (~(Map::LogicHelpers::L_CRENEL | Map::LogicHelpers::L_CRENEL_VARIATIONUnk)) | 256;
                        }
                    }
                    if ((undefined2)wallType == Commands::M_MAPPER_WALL) {
                        this->HeightLayer[_tile] = this->HeightLayer[_tile] + 0x5a;
                    LAB_005031c3:
                        if (bVar1)
                            goto LAB_005031c7;
                        _normalWallCountUnk = _normalWallCountUnk + 1;
                        this->LogicLayer[_tile]
                            = this->LogicLayer[_tile] & (~(Map::LogicHelpers::L_UNKNOWN_WALL_RELATED | Map::LogicHelpers::L_BOULDERS | Map::LogicHelpers::L_PEBBLES | Map::LogicHelpers::L_IRON))
                            | 256;
                        if ((this->UnitLayer[_tile] != 0)
                            && (_unitID = (int)(short)this->UnitLayer[_tile],
                                DAT_UnitsState::instance.units[_unitID].unitType == Map::Units::UT_CHICKEN)) {
                            DAT_UnitsState::instance.units[_unitID].state.generic
                                = Map::Units::States::US_DISAPPEAR;
                            DAT_UnitsState::instance.units[_unitID].updateTickTracker = 0;
                            DAT_UnitsState::instance.units[_unitID].disappearFadeAlphaCountdown = 0;
                        }
                        if ((this->LogicLayer[_tile] & 8U)) {
                            this->LogicLayer[_tile] = this->LogicLayer[_tile] & ~(Map::LogicHelpers::L_PLAIN2_AND_PITCH);
                            this->HeightLayer[_tile] = this->HeightLayer[_tile] + 4;
                        }
                        if (((this->LogicLayer[_tile] & Map::LogicHelpers::L_TREE))
                            && (_treeID = (int)this->OrganismLayer[_tile], _treeID < 2000)) {
                            switch (DAT_LandscapeState::instance.trees[_treeID].treeType) {
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
                                DAT_LandscapeState::instance.trees[_treeID].state = 3;
                            }
                        }
                        if (((undefined2)wallType == Commands::M_MAPPER_WOODWALL) || (bVar2)) {
                            this->LogicLayer[_tile] = this->LogicLayer[_tile] | 65536;
                        }
                        this->WallOwnerLayer[_tile] = this->WallOwnerLayer[_tile] & 0xf8 | (char)playerID - 1U;
                    } else {
                        if ((undefined2)wallType == Commands::M_MAPPER_WOODWALL) {
                            this->HeightLayer[_tile] = this->HeightLayer[_tile] + 0x3c;
                            goto LAB_005031c3;
                        }
                        if ((undefined2)wallType == Commands::M_MAPPER_CRENAL) {
                            this->LogicLayer[_tile] = this->LogicLayer[_tile] | 512;
                            BVar3 = MACRO_CALL_MEMBER(Map::TileMapState_Func::hasOnlyTowerNeighborsNoWalls,
                                this)(_tile, (int)((int)(y1)));
                            if (BVar3 == FALSE) {
                                this->HeightLayer[_tile] = this->HeightLayer[_tile] + 0x62;
                            } else {
                                this->HeightLayer[_tile] = this->HeightLayer[_tile] + 0x44;
                            }
                            bVar2 = BVar3 != FALSE;
                            if ((!(local_18 & 1)) || ((y1 & 1))) {
                                if ((!(local_18 & 1)) && ((y1 & 1))) {
                                    this->LogicLayer[_tile] = this->LogicLayer[_tile] | 4194304;
                                }
                            } else {
                                this->LogicLayer[_tile] = this->LogicLayer[_tile] | 4194304;
                            }
                            goto LAB_005031c3;
                        }
                        if ((undefined2)wallType != Commands::M_MAPPER_STAIR)
                            goto LAB_005031c3;
                        /*
                          --stairs code--
                         */
                        iVar5 = (local_14 - (uint)this->HeightLayer[_tile]) + -0x10;
                        if (0 < iVar5) {
                            /*
                              Sets actual steps tiles
                             */
                            this->LogicLayer[_tile] = this->LogicLayer[_tile] | 2048;
                            this->HeightLayer[_tile] = this->HeightLayer[_tile] + (char)iVar5;
                            goto LAB_005031c3;
                        }
                    LAB_005031c7:
                        if (!bVar1)
                            goto LAB_005032fa;
                    }
                    MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                        DAT_PathFindingState::ptr)(y1, _tile);
                    MACRO_CALL_MEMBER(Map::TileMapState_Func::clearMoat, this)(_tile);
                    MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                        DAT_PathFindingState::ptr)(7, local_18, y1);
                }
            LAB_005032fa:
                uVar4 = x1;
                if ((int)local_18 < (int)x2) {
                    uVar4 = local_28;
                }
                _tile = local_20;
                if ((int)y1 < (int)y2) {
                    _tile = local_1c;
                }
                if ((undefined2)wallType == Commands::M_MAPPER_STAIR) {
                    if (_tile < (int)uVar4) {
                        if ((int)local_18 < (int)x2) {
                            x1 = x1 + 1;
                            local_18 = local_18 + 1;
                            local_28 = local_28 - 1;
                        } else {
                            x1 = x1 - 1;
                            local_18 = local_18 - 1;
                            local_28 = local_28 + 1;
                        }
                    } else if (_tile < 1) {
                        local_10 = local_10 + -1;
                    } else if ((int)y1 < (int)y2) {
                        y1 = y1 + 1;
                        local_24 = local_24 + 3;
                        local_20 = local_20 + 1;
                        local_1c = local_1c + -1;
                    } else {
                        y1 = y1 - 1;
                        local_24 = local_24 + -3;
                        local_20 = local_20 + -1;
                        local_1c = local_1c + 1;
                    }
                } else {
                    iVar5 = 1;
                    if (uVar4) {
                        if ((int)local_18 < (int)x2) {
                            x1 = x1 + 1;
                            local_28 = local_28 - 1;
                        } else {
                            x1 = x1 - 1;
                            iVar5 = -1;
                            local_28 = local_28 + 1;
                        }
                        local_18 = local_18 + iVar5;
                    }
                    if (_tile) {
                        if ((int)y1 < (int)y2) {
                            y1 = y1 + 1;
                            local_24 = local_24 + 3;
                            local_20 = local_20 + 1;
                            local_1c = local_1c + -1;
                        } else {
                            y1 = y1 - 1;
                            local_24 = local_24 + -3;
                            local_20 = local_20 + -1;
                            local_1c = local_1c + 1;
                        }
                    }
                    if ((local_18 == x2) && (y1 == y2)) {
                        local_10 = local_10 + -1;
                    }
                }
                if (0xf < local_14) {
                    local_14 = local_14 + -0x10;
                }
            } while (((local_18 != x2) || (y1 != y2)) || (local_10));
            if ((undefined2)wallType == Commands::M_MAPPER_WOODWALL) {
                _count2 = 0;
                _count1 = _normalWallCountUnk;
            } else {
            LAB_00503440:
                _count1 = 0;
                _count2 = _normalWallCountUnk;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processWallBuildingLoss,
                DAT_BuildingsState::ptr)(playerID, _count2, _count1, 0);
            DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
            this->field204_0x554a30 = 1;
            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
        }
    }

}
}
