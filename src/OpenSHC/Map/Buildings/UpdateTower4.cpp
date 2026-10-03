#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041EDA0
    void Buildings::UpdateTower4()
    {
        int iVar1;
        uint uVar2;
        int* piVar3;
        short sVar4;
        int iVar5;
        uint uVar6;
        uint uVar7;
        int iVar8;
        uint uVar9;
        int local_20[8];
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar5 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar5].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = 2;
        DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field22_0x40 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field23_0x44 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field29_0x5c = 0;
        DAT_BuildingsState::instance.buildings[iVar5].shouldRenderRoof = 0x7a;
        DAT_BuildingsState::instance.buildings[iVar5].shouldRenderSomeOverlay = 0;
        DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field33_0x6c = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field34_0x70 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field35_0x74 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field36_0x78 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field37_0x7c = 0;
        DAT_BuildingsState::instance.buildings[iVar5].ownerFlagFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field39_0x84 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].field40_0x88 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].someX = DAT_BuildingsState::instance.buildings[iVar5].x + 2;
        DAT_BuildingsState::instance.buildings[iVar5].someY = DAT_BuildingsState::instance.buildings[iVar5].y + 2;
        piVar3 = &DAT_BuildingsState::instance.buildings[iVar5].buildingProgress;
        *piVar3 = *piVar3 + 1;
        if (0x27 < DAT_BuildingsState::instance.buildings[iVar5].buildingProgress) {
            DAT_BuildingsState::instance.buildings[iVar5].buildingProgress = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeBuildingEntranceFlagsForOrientations,
                DAT_BuildingsState::ptr)(iVar5);
        }
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingExitFlagForOrientation,
            DAT_BuildingsState::ptr)(iVar5);
        if (iVar1 != 0) {
            DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c = 0x51;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 1;
        }
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingEntranceFlagForOrientation,
            DAT_BuildingsState::ptr)(iVar5);
        if (iVar1 != 0) {
            DAT_BuildingsState::instance.buildings[iVar5].field23_0x44 = 0x5a;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 1;
        }
        local_20[1] = 0;
        local_20[2] = 0;
        local_20[3] = 0;
        local_20[4] = 0;
        local_20[5] = 0;
        local_20[6] = 0;
        local_20[7] = 0;
        local_20[0] = 0;
        iVar1 = 9
            - (DAT_BuildingsState::instance.buildings[iVar5].currentHealth * 9)
                / (int)DAT_BuildingsState::instance.buildings[iVar5].maxHealth;
        if (iVar1 < 9) {
            if (iVar1 == 0)
                goto LAB_0041efa6;
        } else {
            iVar1 = 8;
        }
        iVar8 = iVar5;
        if (0 < iVar1) {
            uVar6 = DAT_BuildingsState::instance.buildings[iVar5].fireRelatedRNG1;
            uVar2 = (int)uVar6 >> 8;
            do {
                uVar7 = uVar6 & 0xf;
                uVar9 = uVar2 & 7;
                uVar6 = uVar6 + 1;
                uVar2 = uVar2 + 1;
                iVar1 = iVar1 + -1;
                local_20[uVar9] = uVar7 + 1;
                iVar8 = DAT_CurrentBuildingID::instance;
            } while (iVar1 != 0);
        }
        DAT_BuildingsState::instance.buildings[iVar5].field33_0x6c = local_20[0];
        DAT_BuildingsState::instance.buildings[iVar5].field34_0x70 = local_20[1];
        DAT_BuildingsState::instance.buildings[iVar5].field35_0x74 = local_20[2];
        DAT_BuildingsState::instance.buildings[iVar5].field36_0x78 = local_20[3];
        DAT_BuildingsState::instance.buildings[iVar5].field37_0x7c = local_20[4];
        DAT_BuildingsState::instance.buildings[iVar5].ownerFlagFrame = local_20[5];
        DAT_BuildingsState::instance.buildings[iVar5].field39_0x84 = local_20[6];
        DAT_BuildingsState::instance.buildings[iVar5].field40_0x88 = local_20[7];
        iVar5 = iVar8;
    LAB_0041efa6:
        iVar1 = 0;
        if (DAT_BuildingsState::instance.field34_0x18e074 != 0) {
            do {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(iVar1, 6);
                iVar5 = DAT_ViewportRenderState::instance
                            .translationMatrix
                                [(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                                    + DAT_TileMapState::instance.buildingY]
                            .addXgetTile
                    + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                    + DAT_TileMapState::instance.buildingX;
                iVar8 = 0;
                DAT_TileMapState::instance.MiscDisplayLayer[iVar5]
                    = DAT_TileMapState::instance.MiscDisplayLayer[iVar5] & 0xffef;
                piVar3 = DAT_BuildingDefinedData::instance.field421_0xa7dc
                    + (DAT_TileMapState::instance.mapOrientation / 2) * 8;
                do {
                    if (*piVar3 == iVar1) {
                        DAT_TileMapState::instance.MiscDisplayLayer[iVar5]
                            = DAT_TileMapState::instance.MiscDisplayLayer[iVar5] | 0x10;
                        break;
                    }
                    iVar8 = iVar8 + 1;
                    piVar3 = piVar3 + 1;
                } while (iVar8 < 8);
                iVar1 = iVar1 + 1;
                iVar5 = DAT_CurrentBuildingID::instance;
            } while (iVar1 < DAT_TileMapState::instance.constructionTileCount);
        }
        iVar1 = iVar5 * 0x32c;
        sVar4 = DAT_BuildingsState::instance.buildings[iVar5].field261_0x2fa;
        if ((0 < sVar4)
            && (sVar4 = sVar4 + -1, DAT_BuildingsState::instance.buildings[iVar5].field261_0x2fa = sVar4, sVar4 == 0)) {
            iVar5 = 0;
            sVar4 = 0;
            do {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(iVar5, 6);
                iVar8 = DAT_CurrentBuildingID::instance;
                if (DAT_TileMapState::instance
                        .UnitLayer[DAT_ViewportRenderState::instance
                                       .translationMatrix[(short)DAT_BuildingsState::instance
                                                              .buildings[DAT_CurrentBuildingID::instance]
                                                              .y
                                           + DAT_TileMapState::instance.buildingY]
                                       .addXgetTile
                            + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                            + DAT_TileMapState::instance.buildingX]
                    != 0) {
                    sVar4 = 1;
                    break;
                }
                iVar5 = iVar5 + 1;
            } while (iVar5 < DAT_TileMapState::instance.constructionTileCount);
            iVar1 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].hasUnitsOntop = sVar4;
            DAT_BuildingsState::instance.buildings[iVar8].field261_0x2fa = 100;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar1 + 0x2e) != 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].shouldRenderSomeOverlay + iVar1) = 0x7b;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].shouldRenderRoof + iVar1) = 0;
        }
    }

}
}
