#include "../../Map.func.hpp"
#include "../WildlifeState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Trees::TreeType;
    using OpenSHC::Map::Trees::TreeTypeShort;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052BA10
    void WildlifeState::updateWildlifeGrid(int _y10)
    {
        int* piVar1;
        BuildingTypeShort* pBVar2;
        TreeTypeShort TVar3;
        BuildingTypeShort BVar4;
        UnitTypeShort UVar5;
        uint uVar6;
        WildlifeGridElement* pWVar7;
        int iVar8;
        uint uVar9;
        int _areaID;
        int _unitID;
        int iVar10;
        int _tile;
        int _sepAreaID;
        int local_35c;
        int local_358;
        int local_354;
        int local_348;
        int local_344;
        int local_340;
        int local_33c;
        int local_338;
        int local_334;
        int local_330;
        int local_32c;
        int local_320[200];
        int _x10;
        local_348 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1) {
            local_348 = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[1].campground.tileEntry];
        }
        local_344 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1) {
            local_344 = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[2].campground.tileEntry];
        }
        local_340 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1) {
            local_340 = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[3].campground.tileEntry];
        }
        local_33c = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1) {
            local_33c = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[4].campground.tileEntry];
        }
        local_338 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1) {
            local_338 = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[5].campground.tileEntry];
        }
        local_334 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1) {
            local_334 = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[6].campground.tileEntry];
        }
        local_330 = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1) {
            local_330 = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[7].campground.tileEntry];
        }
        local_32c = -1;
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1) {
            local_32c = (int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_GameState::instance.playerDataArray[8].campground.tileEntry];
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            local_35c = 0;
            do {
                _x10 = local_35c / 10;
                pWVar7 = this->grid[_x10] + _y10;
                pWVar7->firstMember = 0;
                this->grid[_x10][_y10].separateAreaID = 0;
                this->grid[_x10][_y10].unclaimedArea = 0;
                this->grid[_x10][_y10].field3_0xc = 0;
                this->grid[_x10][_y10].keeps = 0;
                this->grid[_x10][_y10].field5_0x14 = 0;
                this->grid[_x10][_y10].trees = 0;
                this->grid[_x10][_y10].unitCount = 0;
                this->grid[_x10][_y10].field12_0x30 = 0;
                this->grid[_x10][_y10].field8_0x20 = 0;
                this->grid[_x10][_y10].camelCount = 0;
                this->grid[_x10][_y10].lionCount = 0;
                this->grid[_x10][_y10].deerCount = 0;
                this->grid[_x10][_y10].rabbitCount = 0;
                this->grid[_x10][_y10].field16_0x40 = 0;
                this->grid[_x10][_y10].field17_0x44 = 0;
                this->grid[_x10][_y10].field18_0x48 = 0;
                this->grid[_x10][_y10].field19_0x4c = 0;
                this->grid[_x10][_y10].chimps = 0;
                this->grid[_x10][_y10].castlebuildings = 0;
                this->grid[_x10][_y10].field28_0x70 = 0;
                iVar8 = 0;
                do {
                    local_320[iVar8 * 2] = -1;
                    local_320[iVar8 * 2 + 1] = 0;
                    iVar8 = iVar8 + 1;
                } while (iVar8 < 100);
                local_354 = 0;
                do {
                    uVar9 = local_354 + _y10 * 10;
                    local_358 = 0;
                    do {
                        if ((((uint)(local_358 + local_35c) < 400) && (uVar9 < 400))
                            && (*(char*)(uVar9 * 400 + 0x21aec98 + local_358 + local_35c) != '\0')) {
                            pWVar7->firstMember = pWVar7->firstMember + 1;
                            _tile = DAT_ViewportRenderState::instance.translationMatrix[uVar9].addXgetTile + local_358
                                + local_35c;
                            _areaID = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[_tile];
                            if (_areaID == 0) {
                                this->grid[_x10][_y10].unclaimedArea = this->grid[_x10][_y10].unclaimedArea + 1;
                            }
                            iVar8 = 0;
                            do {
                                if (local_320[iVar8 * 2] == _areaID) {
                                    local_320[iVar8 * 2 + 1] = local_320[iVar8 * 2 + 1] + 1;
                                    break;
                                }
                                if (local_320[iVar8 * 2] == -1) {
                                    local_320[iVar8 * 2] = _areaID;
                                    local_320[iVar8 * 2 + 1] = 1;
                                    break;
                                }
                                iVar8 = iVar8 + 1;
                            } while (iVar8 < 100);
                            if (_areaID != 0) {
                                if (_areaID == local_348) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_344) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_340) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_33c) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_338) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_334) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_330) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                                if (_areaID == local_32c) {
                                    this->grid[_x10][_y10].chimps = this->grid[_x10][_y10].chimps + 1;
                                }
                            }
                            this->grid[_x10][_y10].field28_0x70 = this->grid[_x10][_y10].field28_0x70
                                + (uint)DAT_TileMapState::instance.HeightLayer[_tile];
                            uVar6 = DAT_TileMapState::instance.LogicLayer[_tile];
                            if ((uVar6 & 0x100) != 0) {
                                this->grid[_x10][_y10].field5_0x14 = this->grid[_x10][_y10].field5_0x14 + 1;
                                this->grid[_x10][_y10].castlebuildings = this->grid[_x10][_y10].castlebuildings + 1;
                            }
                            if ((uVar6 & 0x20000000) != 0) {
                                this->grid[_x10][_y10].field16_0x40 = this->grid[_x10][_y10].field16_0x40 + 1;
                            }
                            if ((uVar6 & 0x20000) != 0) {
                                this->grid[_x10][_y10].field17_0x44 = this->grid[_x10][_y10].field17_0x44 + 1;
                            }
                            if ((char)uVar6 < '\0') {
                                this->grid[_x10][_y10].field17_0x44 = this->grid[_x10][_y10].field17_0x44 + 1;
                            }
                            if ((uVar6 & 0x40000) != 0) {
                                this->grid[_x10][_y10].field17_0x44 = this->grid[_x10][_y10].field17_0x44 + 1;
                            }
                            if ((uVar6 & 0x1000000) != 0) {
                                this->grid[_x10][_y10].field19_0x4c = this->grid[_x10][_y10].field19_0x4c + 1;
                            }
                            if ((uVar6 & 0x2000000) != 0) {
                                this->grid[_x10][_y10].field19_0x4c = this->grid[_x10][_y10].field19_0x4c + 1;
                            }
                            if (((int)DAT_TileMapState::instance.OrganismLayer[_tile] - 1U < 1999)
                                && (((TVar3 = DAT_LandscapeState::instance
                                             .trees[DAT_TileMapState::instance.OrganismLayer[_tile]]
                                             .treeType,
                                         TVar3 == ((TreeType)1) || (TVar3 == ((TreeType)2)))
                                    || ((TVar3 == ((TreeType)3) || (TVar3 == ((TreeType)4))))))) {
                                this->grid[_x10][_y10].trees = this->grid[_x10][_y10].trees + 1;
                            }
                            if (DAT_TileMapState::instance.BuildingLayer[_tile] != 0) {
                                pBVar2 = &DAT_BuildingsState::instance
                                              .buildings[DAT_TileMapState::instance.BuildingLayer[_tile]]
                                              .buildingType;
                                BVar4 = *pBVar2;
                                if (BVar4 == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                                    this->grid[_x10][_y10].keeps = this->grid[_x10][_y10].keeps + 1;
                                } else if (BVar4 == OpenSHC::Map::Buildings::BT_STONEKEEP) {
                                    this->grid[_x10][_y10].keeps = this->grid[_x10][_y10].keeps + 1;
                                } else if (BVar4 == OpenSHC::Map::Buildings::BT_STRONGHOLD) {
                                    this->grid[_x10][_y10].keeps = this->grid[_x10][_y10].keeps + 1;
                                } else if (BVar4 == OpenSHC::Map::Buildings::BT_KEEPFOUR) {
                                    this->grid[_x10][_y10].keeps = this->grid[_x10][_y10].keeps + 1;
                                } else if (BVar4 == OpenSHC::Map::Buildings::BT_KEEPFIVE) {
                                    this->grid[_x10][_y10].keeps = this->grid[_x10][_y10].keeps + 1;
                                } else if (BVar4 == OpenSHC::Map::Buildings::BT_CAMPGROUND) {
                                    this->grid[_x10][_y10].keeps = this->grid[_x10][_y10].keeps + 1;
                                } else if ((((BVar4 == OpenSHC::Map::Buildings::BT_GATEHOUSELARGE)
                                                || (BVar4 == OpenSHC::Map::Buildings::BT_GATEHOUSESMALL))
                                               || (((BVar4 == OpenSHC::Map::Buildings::BT_WOODGATE1
                                                        || ((((BVar4 == OpenSHC::Map::Buildings::BT_WOODGATE2
                                                                  || (BVar4 == OpenSHC::Map::Buildings::BT_DRAWBRIDGE))
                                                                 || (BVar4 == OpenSHC::Map::Buildings::BT_TOWER1))
                                                            || ((BVar4 == OpenSHC::Map::Buildings::BT_TOWER2
                                                                || (BVar4 == OpenSHC::Map::Buildings::BT_TOWER3))))))
                                                   || (BVar4 == OpenSHC::Map::Buildings::BT_TOWER4))))
                                    || (BVar4 == OpenSHC::Map::Buildings::BT_TOWER5)) {
                                    this->grid[_x10][_y10].castlebuildings = this->grid[_x10][_y10].castlebuildings + 1;
                                }
                                if (*pBVar2 != OpenSHC::Map::Buildings::BT_SIGNPOST) {
                                    this->grid[_x10][_y10].field3_0xc = this->grid[_x10][_y10].field3_0xc + 1;
                                }
                            }
                            _unitID = (int)(short)DAT_TileMapState::instance.UnitLayer[_tile];
                            if (_unitID != 0) {
                                this->grid[_x10][_y10].unitCount = this->grid[_x10][_y10].unitCount + 1;
                                if (DAT_UnitsState::instance.units[_unitID].isStalked == 0) {
                                    this->grid[_x10][_y10].field12_0x30 = this->grid[_x10][_y10].field12_0x30 + 1;
                                LAB_0052be68:
                                    this->grid[_x10][_y10].field18_0x48 = this->grid[_x10][_y10].field18_0x48 + 1;
                                } else {
                                    this->grid[_x10][_y10].field8_0x20 = this->grid[_x10][_y10].field8_0x20 + 1;
                                    UVar5 = DAT_UnitsState::instance.units[_unitID].unitType;
                                    if (UVar5 == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                                        this->grid[_x10][_y10].deerCount = this->grid[_x10][_y10].deerCount + 1;
                                        if (DAT_TribesState::instance
                                                .tribes[DAT_UnitsState::instance.units[_unitID].tribeID]
                                                .field133_0x278
                                            != 0)
                                            goto LAB_0052be68;
                                    } else if (UVar5 == OpenSHC::Map::Units::UT_RABBIT) {
                                        this->grid[_x10][_y10].rabbitCount = this->grid[_x10][_y10].rabbitCount + 1;
                                    } else if (UVar5 == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                                        this->grid[_x10][_y10].camelCount = this->grid[_x10][_y10].camelCount + 1;
                                    } else if (UVar5 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                                        this->grid[_x10][_y10].lionCount = this->grid[_x10][_y10].lionCount + 1;
                                    }
                                }
                            }
                        }
                        local_358 = local_358 + 1;
                    } while (local_358 < 10);
                    local_354 = local_354 + 1;
                } while (local_354 < 10);
                _sepAreaID = 0;
                iVar8 = 0;
                iVar10 = 0;
                do {
                    if (local_320[iVar10 * 2] == -1)
                        break;
                    if (iVar8 < local_320[iVar10 * 2 + 1]) {
                        _sepAreaID = local_320[iVar10 * 2];
                        iVar8 = local_320[iVar10 * 2 + 1];
                    }
                    if (local_320[iVar10 * 2 + 2] == -1)
                        break;
                    if (iVar8 < local_320[iVar10 * 2 + 3]) {
                        _sepAreaID = local_320[iVar10 * 2 + 2];
                        iVar8 = local_320[iVar10 * 2 + 3];
                    }
                    if (local_320[iVar10 * 2 + 4] == -1)
                        break;
                    if (iVar8 < local_320[iVar10 * 2 + 5]) {
                        _sepAreaID = local_320[iVar10 * 2 + 4];
                        iVar8 = local_320[iVar10 * 2 + 5];
                    }
                    if (local_320[iVar10 * 2 + 6] == -1)
                        break;
                    if (iVar8 < local_320[iVar10 * 2 + 7]) {
                        _sepAreaID = local_320[iVar10 * 2 + 6];
                        iVar8 = local_320[iVar10 * 2 + 7];
                    }
                    if (local_320[iVar10 * 2 + 8] == -1)
                        break;
                    if (iVar8 < local_320[iVar10 * 2 + 9]) {
                        _sepAreaID = local_320[iVar10 * 2 + 8];
                        iVar8 = local_320[iVar10 * 2 + 9];
                    }
                    iVar10 = iVar10 + 5;
                } while (iVar10 < 100);
                this->grid[_x10][_y10].separateAreaID = _sepAreaID;
                local_35c = local_35c + 10;
            } while (local_35c < 400);
        }
    }

}
}
