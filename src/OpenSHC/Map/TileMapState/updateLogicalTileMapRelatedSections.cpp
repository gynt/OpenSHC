#include "../../Map.func.hpp"
#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F70F0
    void TileMapState::updateLogicalTileMapRelatedSections()
    {
        byte bVar1;
        int iVar2;
        int iVar3;
        uint uVar4;
        bool bVar5;
        bool bVar6;
        bool bVar7;
        uint uVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        int (*paiVar12)[8];
        int (*paiVar13)[8];
        int iVar14;
        int iVar15;
        int _tile;
        bool bVar16;
        int* local_28;
        int local_20;
        int local_8;
        if (this->forceUpdateLogicalAndMiscDisplayLayers != 0) {
            this->forceUpdateLogicalAndMiscDisplayLayers = 0;
            _tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_PathFindingState::instance.mappingYRelated]
                        .firstTileOfRow;
            DAT_BuildingsState::instance.field34_0x18e074 = 1;
            for (iVar11 = DAT_PathFindingState::instance.mappingYRelated;
                (iVar11 < 400 && (iVar11 <= DAT_PathFindingState::instance.yLimit)); iVar11 = iVar11 + 1) {
                iVar2 = this->yArray1[iVar11];
                local_8 = 0;
                if (0 < iVar2) {
                    do {
                        if (((this->LogicLayer[_tile] & 0x30) == 0) && (this->ChangedLayer[_tile] != 0)) {
                            uVar8 = (uint)this->HeightLayer[_tile];
                            iVar3 = this->heightBasedScreenYOffset[uVar8];
                            this->ShowHiLayer[_tile] = '\0';
                            this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] & 0xffef;
                            if (uVar8 == 0) {
                                uVar4 = this->LogicLayer[_tile];
                                if ((((uVar4 & Map::LogicHelpers::L_RIVER) == 0)
                                        && ((this->Logic2Layer[_tile] & Map::LogicHelpers::L2_BEACH) != 0))
                                    || ((uVar4 & Map::LogicHelpers::L_MOAT) != 0)) {
                                LAB_004f71ea:
                                    this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                } else {
                                    this->LogicLayer[_tile]
                                        = uVar4 & ~(Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE);
                                }
                            } else {
                                if (uVar8 < 9)
                                    goto LAB_004f71ea;
                                bVar1 = this->Logic2Layer[_tile];
                                if ((bVar1 & 4) == 0) {
                                    if ((bVar1 & 8) == 0) {
                                        if ((bVar1 & 2) == 0) {
                                            if ((bVar1 & 0x10) == 0) {
                                                if ((bVar1 & 1) == 0) {
                                                    if ((char)bVar1 < '\0') {
                                                        this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                                    } else if ((bVar1 & 0x40) == 0) {
                                                        this->LogicLayer[_tile] = this->LogicLayer[_tile]
                                                            & ~(Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE);
                                                    } else {
                                                        this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                                    }
                                                } else {
                                                    this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                                }
                                            } else {
                                                this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                            }
                                        } else {
                                            this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                        }
                                    } else {
                                        this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                    }
                                } else {
                                    this->LogicLayer[_tile] = this->LogicLayer[_tile] | 32768;
                                }
                            }
                            iVar15 = 0;
                            paiVar13 = this->directionTranslationMatrix + iVar11;
                            paiVar12 = paiVar13;
                            do {
                                iVar9 = (*paiVar12)[0] + _tile;
                                if (((8 < uVar8) || (this->HeightLayer[iVar9] == 0))
                                    && (uVar8 != this->HeightLayer[iVar9])) {
                                    if ((this->LogicLayer[iVar9] & Map::LogicHelpers::L_RIVER
                                            | Map::LogicHelpers::L_MOAT)
                                        == 0) {
                                        this->LogicLayer[_tile] = this->LogicLayer[_tile]
                                            & ~(Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE);
                                    }
                                    break;
                                }
                                iVar15 = iVar15 + 1;
                                paiVar12 = (int (*)[8])(*paiVar12 + 1);
                            } while (iVar15 < 8);
                            if ((this->BuildingLayer[_tile] != 0)
                                && (DAT_BuildingsState::instance.buildings[this->BuildingLayer[_tile]].buildingType
                                    == Map::Buildings::BT_DRAWBRIDGE)) {
                                this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] | 0x10;
                            }
                            if (this->field93_0x5548c8 == 0) {
                                local_28 = this->directionTranslationMatrix[iVar11] + this->screenSouthEastDirection;
                                iVar9 = 0;
                                iVar15 = _tile;
                                do {
                                    iVar15 = iVar15 + *local_28;
                                    if ((this->LogicLayer[iVar15] & 0x30) != 0)
                                        break;
                                    if (iVar3 <= (this->heightBasedScreenYOffset[this->HeightLayer[iVar15]] - iVar9)
                                            + -0x10) {
                                        this->ShowHiLayer[_tile] = 0xff;
                                        break;
                                    }
                                    local_28 = local_28 + this->orientedRowStep * 8;
                                    iVar9 = iVar9 + 0x10;
                                } while (iVar9 < 0x80);
                                if ((uVar8 == 0) || (this->ShowHiLayer[_tile] == 0xff))
                                    goto LAB_004f793d;
                            } else {
                                this->ShowHiLayer[_tile] = '\b';
                            }
                            uVar4 = this->LogicLayer[_tile];
                            if ((uVar4 & Map::LogicHelpers::L_BUILDING
                                    | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                == 0) {
                                if ((uVar4 & Map::LogicHelpers::L_TREE_VARIATION) == 0) {
                                    if ((uVar4 & Map::LogicHelpers::L_FARM_FIELD_WHEAT) == 0) {
                                        if ((uVar4 & Map::LogicHelpers::L_FARM_FIELD_HOP) == 0) {
                                            if ((uVar4 & Map::LogicHelpers::L_CRENEL) == 0) {
                                                if ((uVar4 & Map::LogicHelpers::L_STAIRS) == 0) {
                                                    this->MiscDisplayLayer[_tile]
                                                        = this->MiscDisplayLayer[_tile] | 0x10;
                                                    bVar7 = false;
                                                } else {
                                                    bVar7 = true;
                                                }
                                            } else {
                                                bVar7 = true;
                                            }
                                        } else {
                                            bVar7 = true;
                                        }
                                    } else {
                                        bVar7 = true;
                                    }
                                } else {
                                    bVar7 = true;
                                }
                            } else {
                                bVar7 = true;
                            }
                            iVar15 = 0;
                            do {
                                iVar9 = (*paiVar13)[0] + _tile;
                                if (((8 < uVar8) && (uVar8 != this->HeightLayer[iVar9]))
                                    || (uVar4 = this->LogicLayer[iVar9],
                                        (uVar4 & Map::LogicHelpers::L_TREE_VARIATION) != 0)) {
                                    this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] & 0xffef;
                                    break;
                                }
                                if ((uVar4 & 0x1000000) != 0) {
                                    bVar7 = true;
                                }
                                if ((uVar4 & 0x2000000) != 0) {
                                    bVar7 = true;
                                }
                                iVar15 = iVar15 + 1;
                                paiVar13 = (int (*)[8])(*paiVar13 + 1);
                            } while (iVar15 < 8);
                            this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] & 0xfffc;
                            bVar6 = false;
                            bVar5 = false;
                            iVar9 = this->directionTranslationMatrix[iVar11][this->screenSouthEastDirection] + _tile;
                            iVar15 = this->heightBasedScreenYOffset[this->HeightLayer[iVar9]];
                            local_20 = 0xfa;
                            if (iVar15 < 0xfa) {
                                local_20 = iVar15;
                            }
                            iVar14 = iVar3 + 2;
                            if (iVar14 < iVar15) {
                                bVar7 = true;
                            }
                            if ((this->LogicLayer[_tile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE) == 0) {
                                if (((this->LogicLayer[iVar9] & Map::LogicHelpers::L_BUILDING
                                         | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                        != 0)
                                    && (iVar15 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                            DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar9]),
                                        iVar15 != 0)) {
                                    bVar7 = true;
                                }
                                iVar15 = this->directionTranslationMatrix[iVar11][this->screenSouthDirection] + _tile;
                                if ((((this->LogicLayer[iVar15] & Map::LogicHelpers::L_BUILDING
                                          | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        && (iVar10 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                                DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar15]),
                                            iVar10 != 0))
                                    || (((this->LogicLayer[iVar15] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                            != 0
                                        && ((this->LogicLayer[iVar15] & Map::LogicHelpers::L_STOCKPILEUnk)
                                            == 0)))) {
                                    bVar7 = true;
                                }
                                iVar15 = this->directionTranslationMatrix[iVar11][this->screenEastDirection] + _tile;
                                if ((((this->LogicLayer[iVar15] & Map::LogicHelpers::L_BUILDING
                                          | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        && (iVar10 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                                DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar15]),
                                            iVar10 != 0))
                                    || (((this->LogicLayer[iVar15] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                            != 0
                                        && ((this->LogicLayer[iVar15] & Map::LogicHelpers::L_STOCKPILEUnk)
                                            == 0)))) {
                                    bVar7 = true;
                                }
                                iVar15 = this->directionTranslationMatrix[this->orientedRowStep + iVar11]
                                                                         [this->screenSouthDirection]
                                    + iVar9;
                                if ((((this->LogicLayer[iVar15] & Map::LogicHelpers::L_BUILDING
                                          | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        && (iVar10 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                                DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar15]),
                                            iVar10 != 0))
                                    || (((this->LogicLayer[iVar15] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                            != 0
                                        && ((this->LogicLayer[iVar15] & Map::LogicHelpers::L_STOCKPILEUnk)
                                            == 0)))) {
                                    bVar7 = true;
                                }
                                iVar15 = this->directionTranslationMatrix[this->orientedRowStep + iVar11]
                                                                         [this->screenEastDirection]
                                    + iVar9;
                                if ((((this->LogicLayer[iVar15] & Map::LogicHelpers::L_BUILDING
                                          | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        && (iVar10 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                                DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar15]),
                                            iVar10 != 0))
                                    || (((this->LogicLayer[iVar15] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                            != 0
                                        && ((this->LogicLayer[iVar15] & Map::LogicHelpers::L_STOCKPILEUnk)
                                            == 0)))) {
                                    bVar7 = true;
                                }
                                iVar9 = iVar9
                                    + this->directionTranslationMatrix[this->orientedRowStep + iVar11]
                                                                      [this->screenSouthEastDirection];
                                if (((this->LogicLayer[iVar9] & Map::LogicHelpers::L_BUILDING
                                         | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                        != 0)
                                    && (iVar15 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                            DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar9]),
                                        iVar15 != 0)) {
                                    bVar7 = true;
                                }
                                iVar15 = this->directionTranslationMatrix[iVar11 + this->orientedRowStep * 2]
                                                                         [this->screenSouthDirection]
                                    + iVar9;
                                if ((((this->LogicLayer[iVar15] & Map::LogicHelpers::L_BUILDING
                                          | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        && (iVar10 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                                DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar15]),
                                            iVar10 != 0))
                                    || (((this->LogicLayer[iVar15] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                            != 0
                                        && ((this->LogicLayer[iVar15] & Map::LogicHelpers::L_STOCKPILEUnk)
                                            == 0)))) {
                                    bVar7 = true;
                                }
                                iVar15 = this->directionTranslationMatrix[iVar11 + this->orientedRowStep * 2]
                                                                         [this->screenEastDirection]
                                    + iVar9;
                                if ((((this->LogicLayer[iVar15] & Map::LogicHelpers::L_BUILDING
                                          | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        && (iVar10 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                                DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar15]),
                                            iVar10 != 0))
                                    || (((this->LogicLayer[iVar15] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                            != 0
                                        && ((this->LogicLayer[iVar15] & Map::LogicHelpers::L_STOCKPILEUnk)
                                            == 0)))) {
                                    bVar7 = true;
                                }
                                iVar9 = iVar9
                                    + this->directionTranslationMatrix[iVar11 + this->orientedRowStep * 2]
                                                                      [this->screenSouthEastDirection];
                                if ((this->LogicLayer[iVar9] & Map::LogicHelpers::L_BUILDING
                                        | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                    != 0) {
                                    iVar15 = MACRO_CALL_MEMBER(
                                        Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                        DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar9]);
                                    bVar16 = iVar15 == 0;
                                    goto LAB_004f77ae;
                                }
                            } else {
                                if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[iVar9]].flag2 != 0) {
                                    bVar7 = true;
                                }
                                if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[iVar9]].buildingType
                                    == Map::Buildings::BT_STOCKPILE) {
                                    bVar7 = true;
                                }
                                bVar16 = DAT_BuildingsState::instance
                                             .buildings[this->BuildingLayer
                                                     [this->directionTranslationMatrix[this->orientedRowStep + iVar11]
                                                                                      [this->screenSouthEastDirection]
                                                         + iVar9]]
                                             .flag2
                                    == 0;
                            LAB_004f77ae:
                                if (!bVar16) {
                                    bVar7 = true;
                                }
                            }
                            iVar9 = this->directionTranslationMatrix[iVar11][this->screenSouthDirection] + _tile;
                            iVar15 = this->heightBasedScreenYOffset[this->HeightLayer[iVar9]];
                            if (iVar15 < local_20) {
                                local_20 = iVar15;
                            }
                            if ((iVar3 <= iVar15) && (bVar5 = true, iVar14 < iVar15)) {
                                bVar7 = true;
                            }
                            if ((this->LogicLayer[_tile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE) == 0) {
                                if (((this->LogicLayer[iVar9] & Map::LogicHelpers::L_BUILDING
                                         | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                        != 0)
                                    && (iVar15 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                            DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar9]),
                                        iVar15 != 0)) {
                                    bVar7 = true;
                                }
                            } else {
                                if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[iVar9]].flag2 != 0) {
                                    bVar7 = true;
                                }
                                if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[iVar9]].buildingType
                                    == Map::Buildings::BT_STOCKPILE) {
                                    bVar7 = true;
                                }
                            }
                            iVar9 = this->directionTranslationMatrix[iVar11][this->screenEastDirection] + _tile;
                            iVar15 = this->heightBasedScreenYOffset[this->HeightLayer[iVar9]];
                            if (iVar15 < local_20) {
                                local_20 = iVar15;
                            }
                            if ((iVar3 <= iVar15) && (bVar6 = true, iVar14 < iVar15)) {
                                bVar7 = true;
                            }
                            if ((this->LogicLayer[_tile] & Map::LogicHelpers::L_WALL_OR_GATEHOUSE) == 0) {
                                if ((((this->LogicLayer[_tile] & Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                         != 0)
                                        || ((this->LogicLayer[iVar9] & Map::LogicHelpers::L_BUILDING
                                                | Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                            == 0))
                                    || (iVar15 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::getBuildingFlag1,
                                            DAT_BuildingsState::ptr)((int)this->BuildingLayer[iVar9]),
                                        iVar15 == 0))
                                    goto LAB_004f79a8;
                            LAB_004f78f0:
                                this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] & 0xffef;
                            } else {
                                if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[iVar9]].flag2 != 0) {
                                    bVar7 = true;
                                }
                                if (DAT_BuildingsState::instance.buildings[this->BuildingLayer[iVar9]].buildingType
                                    == Map::Buildings::BT_STOCKPILE)
                                    goto LAB_004f78f0;
                            LAB_004f79a8:
                                if (bVar7)
                                    goto LAB_004f78f0;
                                this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] | 0x10;
                            }
                            if (local_20 < iVar3) {
                                if (this->field93_0x5548c8 == 0) {
                                    this->ShowHiLayer[_tile] = (char)iVar3 - (char)local_20;
                                }
                                if ((this->LogicLayer[_tile] & Map::LogicHelpers::L_SEA) == 0) {
                                    if (bVar5) {
                                        this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] | 1;
                                    }
                                    if (bVar6) {
                                        this->MiscDisplayLayer[_tile] = this->MiscDisplayLayer[_tile] | 2;
                                    }
                                }
                            }
                        }
                    LAB_004f793d:
                        local_8 = local_8 + 1;
                        _tile = _tile + 1;
                    } while (local_8 < iVar2);
                }
            }
        }
    }

}
}
