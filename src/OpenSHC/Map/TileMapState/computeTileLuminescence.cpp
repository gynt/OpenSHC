#include "../../Map.func.hpp"
#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F7A80
    void TileMapState::computeTileLuminescence(int tile, int param_2)
    {
        int iVar1;
        uint uVar2;
        char cVar3;
        uint uVar4;
        uint uVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        uint local_2c;
        int local_28;
        int local_24;
        uint local_1c;
        uint local_18;
        int local_14;
        uint local_10;
        uint local_c;
        uint _logicTile;
        uVar5 = 0;
        _logicTile = this->LogicLayer[tile];
        local_24 = 0;
        local_14 = 0;
        local_28 = 2;
        local_c = 2;
        local_10 = 2;
        local_1c = 0;
        local_18 = 0;
        if ((_logicTile & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE | OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) != 0) {}
        switch (this->mapOrientation) {
        case 0:
            local_24 = 5;
            local_14 = 1;
            local_1c = 4;
            local_18 = 6;
            break;
        case 2:
            local_24 = 7;
            local_14 = 3;
            local_1c = 6;
            local_18 = 0;
            break;
        case 4:
            local_24 = 1;
            local_14 = 5;
            local_1c = 0;
            local_18 = 2;
            break;
        case 6:
            local_24 = 3;
            local_14 = 7;
            local_1c = 2;
            local_18 = 4;
        }
        uVar4 = (uint)this->HeightLayer[tile];
        iVar6 = tile;
        iVar7 = param_2;
        if ((_logicTile & OpenSHC::Map::LogicHelpers::L_TREE) == 0) {
            if ((_logicTile & OpenSHC::Map::LogicHelpers::L_TREE_VARIATION) != 0) {
                local_28 = 5;
                local_2c = 6;
                goto LAB_004f7ba5;
            }
        } else {
            iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                DAT_LandscapeState::ptr)((int)this->OrganismLayer[tile]);
            if (2 < iVar1) {
                local_28 = iVar1;
            }
        }
        local_2c = 6;
    LAB_004f7ba5:
        do {
            iVar6 = iVar6 + this->directionTranslationMatrix[iVar7][local_24];
            iVar7 = iVar7
                + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + local_24 * 8 + 4);
            if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE) != 0)
                break;
            if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) == 0) {
                uVar5 = (uint)this->HeightLayer[iVar6];
            } else {
                iVar8 = (int)this->BuildingLayer[iVar6];
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(iVar8);
                if (iVar1 == 0) {
                    iVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(iVar8);
                    if (iVar1 < 0x10) {
                        uVar5 = this->HeightLayer[iVar6] + 0x10;
                    } else {
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(iVar8);
                        uVar5 = (uint)this->HeightLayer[iVar6] + iVar1;
                    }
                }
            }
            if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_TREE) == 0) {
                if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_TREE_VARIATION) != 0) {
                    uVar5 = uVar5 + 0x28;
                }
            } else {
                iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                    DAT_LandscapeState::ptr)((int)this->OrganismLayer[iVar6]);
                uVar5 = uVar5 + iVar1 * 7;
            }
            iVar1 = uVar5 - uVar4;
            if (iVar1 < 1) {
                uVar2 = 2;
            } else if (iVar1 < 0x13) {
                uVar2 = local_2c;
                if (iVar1 < 0xf) {
                    if (iVar1 < 0xb) {
                        if (iVar1 < 7) {
                            if (iVar1 < 3) {
                                uVar2 = 0;
                            } else {
                                uVar2 = local_2c + -3;
                            }
                        } else {
                            uVar2 = local_2c + -2;
                        }
                    } else {
                        uVar2 = local_2c + -1;
                    }
                }
            } else {
                uVar2 = local_2c + 1;
            }
            if (local_28 < (int)uVar2) {
                local_28 = uVar2;
            }
            local_2c = local_2c + -1;
        } while (1 < (int)local_2c);
        iVar7 = this->directionTranslationMatrix[param_2][local_1c] + tile;
        iVar6 = local_1c * 8;
        local_1c = 4;
        iVar6 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar6 + 4) + param_2;
        local_2c = uVar5;
        do {
            if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE) != 0)
                break;
            if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) == 0) {
                local_2c = (uint)this->HeightLayer[iVar7];
            } else {
                iVar8 = (int)this->BuildingLayer[iVar7];
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(iVar8);
                if (iVar1 == 0) {
                    iVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(iVar8);
                    if (iVar1 < 0x10) {
                        local_2c = this->HeightLayer[iVar7] + 0x10;
                    } else {
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(iVar8);
                        local_2c = (uint)this->HeightLayer[iVar7] + iVar1;
                    }
                }
            }
            if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_TREE) == 0) {
                if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_TREE_VARIATION) != 0) {
                    local_2c = local_2c + 0x28;
                }
            } else {
                iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                    DAT_LandscapeState::ptr)((int)this->OrganismLayer[iVar7]);
                local_2c = local_2c + iVar1 * 7;
            }
            iVar1 = local_2c - uVar4;
            if (iVar1 < 1) {
                uVar5 = 2;
            } else if (iVar1 < 0x13) {
                uVar5 = local_1c;
                if (iVar1 < 0xd) {
                    if (iVar1 < 7) {
                        uVar5 = 0;
                    } else {
                        uVar5 = local_1c - 1;
                    }
                }
            } else {
                uVar5 = local_1c + 1;
            }
            if ((int)local_c < (int)uVar5) {
                local_c = uVar5;
            }
            iVar7 = iVar7 + this->directionTranslationMatrix[iVar6][local_24];
            local_1c = local_1c - 1;
            iVar6 = iVar6
                + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + local_24 * 8 + 4);
        } while (local_1c < 0x80000000);
        iVar6 = local_18 * 8;
        iVar7 = this->directionTranslationMatrix[param_2][local_18] + tile;
        local_18 = 4;
        iVar6 = *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + iVar6 + 4) + param_2;
        do {
            if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE) != 0)
                break;
            if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) == 0) {
                local_2c = (uint)this->HeightLayer[iVar7];
            } else {
                iVar8 = (int)this->BuildingLayer[iVar7];
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(iVar8);
                if (iVar1 == 0) {
                    iVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)(iVar8);
                    if (iVar1 < 0x10) {
                        local_2c = this->HeightLayer[iVar7] + 0x10;
                    } else {
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(iVar8);
                        local_2c = (uint)this->HeightLayer[iVar7] + iVar1;
                    }
                }
            }
            if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_TREE) == 0) {
                if ((this->LogicLayer[iVar7] & OpenSHC::Map::LogicHelpers::L_TREE_VARIATION) != 0) {
                    local_2c = local_2c + 0x28;
                }
            } else {
                iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getTreeGrowthTargetStage,
                    DAT_LandscapeState::ptr)((int)this->OrganismLayer[iVar7]);
                local_2c = local_2c + iVar1 * 7;
            }
            iVar1 = local_2c - uVar4;
            if (iVar1 < 1) {
                uVar5 = 2;
            } else if (iVar1 < 0x13) {
                uVar5 = local_18;
                if (iVar1 < 0xd) {
                    if (iVar1 < 7) {
                        uVar5 = 0;
                    } else {
                        uVar5 = local_18 - 1;
                    }
                }
            } else {
                uVar5 = local_18 + 1;
            }
            if ((int)local_10 < (int)uVar5) {
                local_10 = uVar5;
            }
            iVar7 = iVar7 + this->directionTranslationMatrix[iVar6][local_24];
            local_18 = local_18 - 1;
            iVar6 = iVar6
                + *(int*)((int)DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix + local_24 * 8 + 4);
        } while (local_18 < 0x80000000);
        if ((local_28 + -2 < (int)((local_10 - 4) + local_c)) && (local_28 = (local_10 - 2) + local_c, 6 < local_28)) {
            local_28 = 7;
        } else if (local_28 == 2) {
            iVar6 = this->directionTranslationMatrix[param_2][local_24] + tile;
            uVar5 = uVar4;
            if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE) == 0) {
                if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_BUILDING | OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE) == 0) {
                    uVar5 = (uint)this->HeightLayer[iVar6];
                } else {
                    iVar1 = (int)this->BuildingLayer[iVar6];
                    iVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlag3, DAT_BuildingsState::ptr)(iVar1);
                    uVar5 = local_2c;
                    if (iVar7 == 0) {
                        iVar7 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)(iVar1);
                        if (iVar7 < 0x10) {
                            uVar5 = this->HeightLayer[iVar6] + 0x10;
                        } else {
                            iVar7 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                DAT_BuildingsState::ptr)(iVar1);
                            uVar5 = (uint)this->HeightLayer[iVar6] + iVar7;
                        }
                    }
                }
            }
            iVar6 = this->directionTranslationMatrix[param_2][local_14] + tile;
            uVar2 = uVar4;
            if ((this->LogicLayer[iVar6] & OpenSHC::Map::LogicHelpers::L_BORDER | OpenSHC::Map::LogicHelpers::L_BORDER_EDGE) == 0) {
                uVar2 = (uint)this->HeightLayer[iVar6];
            }
            cVar3 = (int)uVar5 < (int)(uVar4 - 4);
            if (uVar4 + 4 < uVar2) {
                cVar3 = cVar3 + '\x01';
            }
            if ((this->LogicLayer[tile] & OpenSHC::Map::LogicHelpers::L_MOAT) == 0) {
                if (cVar3 == '\x01') {
                    local_28 = 1;
                } else if (cVar3 == '\x02') {
                    local_28 = 0;
                }
            }
        }
        this->LuminesenceLayer[tile] = (uchar)local_28;
    }

}
}
