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

    // FUNCTION: STRONGHOLDCRUSADER 0x0041E870
    void Buildings::UpdateTower2()
    {
        int iVar1;
        uint uVar2;
        int* piVar3;
        uint uVar4;
        uint uVar5;
        int iVar6;
        int iVar7;
        uint uVar8;
        int local_20[8];
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar6 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar6].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar6].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar6].someX = DAT_BuildingsState::instance.buildings[iVar6].x + 1;
        DAT_BuildingsState::instance.buildings[iVar6].someY = DAT_BuildingsState::instance.buildings[iVar6].y + 1;
        DAT_BuildingsState::instance.buildings[iVar6].field20_0x38 = 1;
        DAT_BuildingsState::instance.buildings[iVar6].field21_0x3c = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field22_0x40 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field23_0x44 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field29_0x5c = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field33_0x6c = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field34_0x70 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field35_0x74 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field36_0x78 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field37_0x7c = 0;
        DAT_BuildingsState::instance.buildings[iVar6].ownerFlagFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field39_0x84 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].field40_0x88 = 0;
        piVar3 = &DAT_BuildingsState::instance.buildings[iVar6].buildingProgress;
        *piVar3 = *piVar3 + 1;
        if (0x27 < DAT_BuildingsState::instance.buildings[iVar6].buildingProgress) {
            DAT_BuildingsState::instance.buildings[iVar6].buildingProgress = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeBuildingEntranceFlagsForOrientations,
                DAT_BuildingsState::ptr)(iVar6);
        }
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingExitFlagForOrientation,
            DAT_BuildingsState::ptr)(iVar6);
        if (iVar1 != 0) {
            DAT_BuildingsState::instance.buildings[iVar6].field21_0x3c = 0x51;
            DAT_BuildingsState::instance.buildings[iVar6].animationFrame = 1;
        }
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingEntranceFlagForOrientation,
            DAT_BuildingsState::ptr)(iVar6);
        if (iVar1 != 0) {
            DAT_BuildingsState::instance.buildings[iVar6].field23_0x44 = 0x5a;
            DAT_BuildingsState::instance.buildings[iVar6].animationFrame = 1;
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
            - (DAT_BuildingsState::instance.buildings[iVar6].currentHealth * 9)
                / (int)DAT_BuildingsState::instance.buildings[iVar6].maxHealth;
        if (iVar1 < 9) {
            if (iVar1 == 0)
                goto LAB_0041ea51;
        } else {
            iVar1 = 8;
        }
        if (0 < iVar1) {
            uVar4 = DAT_BuildingsState::instance.buildings[iVar6].fireRelatedRNG1;
            uVar2 = (int)uVar4 >> 8;
            do {
                uVar8 = uVar4 & 0xf;
                uVar5 = uVar2 & 7;
                uVar4 = uVar4 + 1;
                uVar2 = uVar2 + 1;
                iVar1 = iVar1 + -1;
                local_20[uVar5] = uVar8 + 1;
            } while (iVar1 != 0);
        }
        DAT_BuildingsState::instance.buildings[iVar6].field33_0x6c = local_20[0];
        DAT_BuildingsState::instance.buildings[iVar6].field34_0x70 = local_20[1];
        DAT_BuildingsState::instance.buildings[iVar6].field35_0x74 = local_20[2];
        DAT_BuildingsState::instance.buildings[iVar6].field36_0x78 = local_20[3];
        DAT_BuildingsState::instance.buildings[iVar6].field37_0x7c = local_20[4];
        DAT_BuildingsState::instance.buildings[iVar6].ownerFlagFrame = local_20[5];
        DAT_BuildingsState::instance.buildings[iVar6].field39_0x84 = local_20[6];
        DAT_BuildingsState::instance.buildings[iVar6].field40_0x88 = local_20[7];
    LAB_0041ea51:
        if (DAT_BuildingsState::instance.field34_0x18e074 != 0) {
            iVar6 = 0;
            do {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(iVar6, 4);
                iVar1 = DAT_ViewportRenderState::instance
                            .translationMatrix
                                [(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                                    + DAT_TileMapState::instance.buildingY]
                            .addXgetTile
                    + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                    + DAT_TileMapState::instance.buildingX;
                iVar7 = 0;
                DAT_TileMapState::instance.MiscDisplayLayer[iVar1]
                    = DAT_TileMapState::instance.MiscDisplayLayer[iVar1] & 0xffef;
                piVar3 = DAT_BuildingDefinedData::instance.field419_0xa73c
                    + (DAT_TileMapState::instance.mapOrientation / 2) * 4;
                do {
                    if (*piVar3 == iVar6) {
                        DAT_TileMapState::instance.MiscDisplayLayer[iVar1]
                            = DAT_TileMapState::instance.MiscDisplayLayer[iVar1] | 0x10;
                        break;
                    }
                    iVar7 = iVar7 + 1;
                    piVar3 = piVar3 + 1;
                } while (iVar7 < 4);
                iVar6 = iVar6 + 1;
            } while (iVar6 < DAT_TileMapState::instance.constructionTileCount);
        }
    }

}
}
