#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00418C80
    void Buildings::UpdateTower1()
    {
        int iVar1;
        short sVar2;
        uint uVar3;
        int iVar4;
        int iVar5;
        uint uVar6;
        uint uVar7;
        uint uVar8;
        int local_20[8];
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar1 = DAT_CurrentBuildingID::instance;
        iVar4 = DAT_CurrentBuildingID::instance * 0x32c;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar1].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar1].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar1].someX = DAT_BuildingsState::instance.buildings[iVar1].x + 1;
        DAT_BuildingsState::instance.buildings[iVar1].someY = DAT_BuildingsState::instance.buildings[iVar1].y + 1;
        DAT_BuildingsState::instance.buildings[iVar1].field20_0x38 = 0x7d;
        DAT_BuildingsState::instance.buildings[iVar1].shouldRenderRoof = 0x7c;
        DAT_BuildingsState::instance.buildings[iVar1].field21_0x3c = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field22_0x40 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field23_0x44 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field29_0x5c = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field33_0x6c = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field34_0x70 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field35_0x74 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field36_0x78 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field37_0x7c = 0;
        DAT_BuildingsState::instance.buildings[iVar1].ownerFlagFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field39_0x84 = 0;
        local_20[1] = 0;
        local_20[2] = 0;
        local_20[3] = 0;
        local_20[4] = 0;
        local_20[5] = 0;
        local_20[6] = 0;
        local_20[7] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].field40_0x88 = 0;
        local_20[0] = 0;
        iVar5 = 9
            - (DAT_BuildingsState::instance.buildings[iVar1].currentHealth * 9)
                / (int)DAT_BuildingsState::instance.buildings[iVar1].maxHealth;
        if (iVar5 < 9) {
            if (iVar5 == 0)
                goto LAB_00418e05;
        } else {
            iVar5 = 8;
        }
        if (0 < iVar5) {
            uVar8 = DAT_BuildingsState::instance.buildings[iVar1].fireRelatedRNG1;
            uVar3 = (int)uVar8 >> 8;
            do {
                uVar6 = uVar8 & 0xf;
                uVar7 = uVar3 & 7;
                uVar8 = uVar8 + 1;
                uVar3 = uVar3 + 1;
                iVar5 = iVar5 + -1;
                local_20[uVar7] = uVar6 + 1;
            } while (iVar5 != 0);
        }
        DAT_BuildingsState::instance.buildings[iVar1].field33_0x6c = local_20[0];
        DAT_BuildingsState::instance.buildings[iVar1].field34_0x70 = local_20[1];
        DAT_BuildingsState::instance.buildings[iVar1].field35_0x74 = local_20[2];
        DAT_BuildingsState::instance.buildings[iVar1].field36_0x78 = local_20[3];
        DAT_BuildingsState::instance.buildings[iVar1].field37_0x7c = local_20[4];
        DAT_BuildingsState::instance.buildings[iVar1].ownerFlagFrame = local_20[5];
        DAT_BuildingsState::instance.buildings[iVar1].field39_0x84 = local_20[6];
        DAT_BuildingsState::instance.buildings[iVar1].field40_0x88 = local_20[7];
    LAB_00418e05:
        sVar2 = DAT_BuildingsState::instance.buildings[iVar1].field261_0x2fa;
        if ((0 < sVar2)
            && (sVar2 = sVar2 + -1, DAT_BuildingsState::instance.buildings[iVar1].field261_0x2fa = sVar2, sVar2 == 0)) {
            iVar5 = 0;
            sVar2 = 0;
            do {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(iVar5, 3);
                iVar1 = DAT_CurrentBuildingID::instance;
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
                    sVar2 = 1;
                    break;
                }
                iVar5 = iVar5 + 1;
            } while (iVar5 < DAT_TileMapState::instance.constructionTileCount);
            iVar4 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].hasUnitsOntop = sVar2;
            DAT_BuildingsState::instance.buildings[iVar1].field261_0x2fa = 100;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar4 + 0x2e) != 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].shouldRenderRoof + iVar4) = 0x7e;
        }
    }

}
}
