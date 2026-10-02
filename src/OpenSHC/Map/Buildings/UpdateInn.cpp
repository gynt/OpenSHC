#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::States::UnitState;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004156F0
    void Buildings::UpdateInn()
    {
        int* piVar1;
        short* psVar2;
        byte bVar3;
        short sVar4;
        int iVar5;
        short sVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        iVar5 = DAT_CurrentBuildingID::instance;
        sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar5].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[iVar5].animationIncrement = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar5);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar5 = DAT_CurrentBuildingID::instance;
        iVar9 = DAT_CurrentBuildingID::instance * 0x32c;
        iVar7 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if (iVar7 == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        } else if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                           .flagonsOfAleOrCheeseOrReleaseDogs
                       == 0)
            && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field204_0x28a == 0)) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
        }
        sVar6 = DAT_BuildingsState::instance.buildings[iVar5].buildingIsVisuallyActive;
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(iVar5);
        if (sVar6 == 0) {
            DAT_BuildingsState::instance.buildings[iVar5].displayOwnerFlag = 0;
            DAT_BuildingsState::instance.buildings[iVar5].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field25_0x4c = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field26_0x50 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field27_0x54 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field22_0x40 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field23_0x44 = 0;
        } else {
            DAT_BuildingsState::instance.buildings[iVar5].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field22_0x40 = 0;
            DAT_BuildingsState::instance.buildings[iVar5].field23_0x44 = 0;
            bVar3 = DAT_BuildingDefinedData::instance
                        .field175_0x7da8[DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock];
            DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = (int)(char)bVar3;
            if ((char)bVar3 == 0) {
                iVar8 = (int)(char)DAT_BuildingDefinedData::instance.field175_0x7da8[0];
                DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = iVar8;
            } else if (DAT_BuildingsState::instance.buildings[iVar5].animationActive != 0) {
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].campgroundVclock;
                *piVar1 = *piVar1 + 1;
            }
            DAT_BuildingsState::instance.buildings[iVar5].field20_0x38 = 0;
            if (DAT_BuildingsState::instance.buildings[iVar5].field204_0x28a == 0) {
                DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field173_0x7c94[DAT_BuildingsState::instance.buildings[iVar5].field25_0x4c];
            } else {
                DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c
                    = (int)(char)DAT_BuildingDefinedData::instance
                          .field174_0x7d1c[DAT_BuildingsState::instance.buildings[iVar5].field25_0x4c];
            }
            if (DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c == 0) {
                iVar8 = (int)(char)DAT_BuildingDefinedData::instance.field173_0x7c94[0];
                DAT_BuildingsState::instance.buildings[iVar5].field25_0x4c = 0;
                DAT_BuildingsState::instance.buildings[iVar5].field21_0x3c = iVar8;
            } else if (DAT_BuildingsState::instance.buildings[iVar5].animationActive != 0) {
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].field25_0x4c;
                *piVar1 = *piVar1 + 1;
            }
            if (DAT_UnitsState::instance.units[iVar7].state.generic == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                bVar3 = DAT_BuildingDefinedData::instance
                            .field172_0x7c3c[DAT_BuildingsState::instance.buildings[iVar5].field26_0x50];
                DAT_BuildingsState::instance.buildings[iVar5].field22_0x40 = (int)(char)bVar3;
                if ((char)bVar3 == 0) {
                    iVar8 = (int)(char)DAT_BuildingDefinedData::instance.field172_0x7c3c[0];
                    DAT_BuildingsState::instance.buildings[iVar5].field26_0x50 = 0;
                    DAT_BuildingsState::instance.buildings[iVar5].field22_0x40 = iVar8;
                } else if (DAT_BuildingsState::instance.buildings[iVar5].animationActive != 0) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].field26_0x50;
                    *piVar1 = *piVar1 + 1;
                }
            }
            sVar6 = DAT_BuildingsState::instance.buildings[iVar5].field204_0x28a;
            if (sVar6 != 0) {
                sVar6 = sVar6 + -1;
                DAT_BuildingsState::instance.buildings[iVar5].field204_0x28a = sVar6;
                if (sVar6 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::spawnDrunkard, DAT_GameState::ptr)(
                        DAT_CurrentBuildingID::instance);
                }
                iVar5 = DAT_CurrentBuildingID::instance;
                iVar9 = DAT_CurrentBuildingID::instance * 0x32c;
                bVar3 = DAT_BuildingDefinedData::instance.field176_0x7dcc
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field27_0x54];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field23_0x44 = (int)(char)bVar3;
                if ((char)bVar3 == 0) {
                    iVar8 = (int)(char)DAT_BuildingDefinedData::instance.field176_0x7dcc[0];
                    DAT_BuildingsState::instance.buildings[iVar5].field27_0x54 = 0;
                    DAT_BuildingsState::instance.buildings[iVar5].field23_0x44 = iVar8;
                } else if (DAT_BuildingsState::instance.buildings[iVar5].animationActive != 0) {
                    piVar1 = &DAT_BuildingsState::instance.buildings[iVar5].field27_0x54;
                    *piVar1 = *piVar1 + 1;
                }
            }
        }
        if (0 < *(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9 + -0x1a)) {
            if ((iVar7 != 0)
                && (psVar2
                    = (short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9 + -0x18),
                    *psVar2 = *psVar2 + 1,
                    DAT_GameState::instance.playerDataArray[sVar4].aleRate
                        <= (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9
                            + -0x18))) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9 + -0x18)
                    = 0;
                psVar2 = (short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9 + -0x1a);
                *psVar2 = *psVar2 + -1;
            }
            if ((0 < *(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9 + -0x1a))
                && (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar9) != 0)) {
                piVar1 = &DAT_GameState::instance.playerDataArray[sVar4].workingInnsCount;
                *piVar1 = *piVar1 + 1;
            }
        }
        sVar6 = *(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar9);
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar4].countInns;
        *piVar1 = *piVar1 + 1;
        if (sVar6 != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x52)) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            iVar9 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar9) = 1;
            piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9);
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .field177_0x7e1c[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9)
                        / 2]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].field39_0x84 + iVar9)
                = (int)(char)DAT_BuildingDefinedData::instance
                      .field177_0x7e1c[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9)
                          / 2];
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field39_0x84 + iVar9) = 0;
    }

}
}
