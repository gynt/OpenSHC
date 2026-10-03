#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x00423370
    void Buildings::UpdateHuntersPost()
    {
        int* piVar1;
        byte bVar2;
        UnitTypeShort UVar3;
        short sVar4;
        short sVar5;
        int iVar6;
        bool bVar7;
        bool bVar8;
        int iVar9;
        int iVar10;
        bVar7 = false;
        bVar8 = false;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar10 = DAT_CurrentBuildingID::instance;
        iVar9 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[0];
        if ((iVar9 != 0)
            && (DAT_UnitsState::instance.units[iVar9].uid
                == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[0])) {
            bVar8 = true;
        }
        iVar9 = (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerID[1];
        if (((iVar9 != 0)
                && (DAT_UnitsState::instance.units[iVar9].uid
                    == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workerUID[1]))
            && ((UVar3 = DAT_UnitsState::instance.units[iVar9].unitType,
                UVar3 == OpenSHC::Map::Units::UT_BURNINGMAN
                    || ((UVar3 == OpenSHC::Map::Units::UT_BURNING_ANIMAL_BIG
                        || (UVar3 == OpenSHC::Map::Units::UT_BURNING_ANIMAL_SMALL)))))) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field185_0x264 = 400;
        }
        sVar4 = DAT_BuildingsState::instance.buildings[iVar10].field185_0x264;
        if (0 < sVar4) {
            DAT_BuildingsState::instance.buildings[iVar10].field185_0x264 = sVar4 + -1;
        }
        DAT_BuildingsState::instance.buildings[iVar10].renderAnimation
            = (ushort)(DAT_BuildingsState::instance.buildings[iVar10].workers[0] != 0);
        DAT_BuildingsState::instance.buildings[iVar10].displayOwnerFlag = 1;
        if (((DAT_BuildingsState::instance.buildings[iVar10].numberOfAnimals == 0) && (bVar8))
            && (DAT_BuildingsState::instance.buildings[iVar10].field185_0x264 == 0)) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible, DAT_BuildingsState::ptr)(iVar10, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance, 2, FALSE);
            sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX;
            iVar10 = DAT_CurrentBuildingID::instance;
            if (((sVar4 != 0)
                    && (sVar5 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY,
                        sVar5 != 0))
                && (iVar9 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        (int)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner, 0,
                        (int)((int)(sVar4 * 8)), (int)((int)(sVar5 * 8)),
                        (int)((int)(DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                .terrainHeightUnk)),
                        OpenSHC::Map::Units::UT_HUNTERDOG),
                    iVar10 = DAT_CurrentBuildingID::instance, iVar9 != 0)) {
                sVar4 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryY;
                DAT_UnitsState::instance.units[iVar9].targetX_2
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingEntryX;
                DAT_UnitsState::instance.units[iVar9].targetY_2 = sVar4;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    DAT_BuildingsState::ptr)(iVar10, 1, FALSE);
                iVar10 = DAT_CurrentBuildingID::instance;
                DAT_UnitsState::instance.units[iVar9].workplaceBuildingUID
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid;
                iVar6 = DAT_UnitsState::instance.units[iVar9].uid;
                DAT_BuildingsState::instance.buildings[iVar10].workerID[1] = (short)iVar9;
                DAT_UnitsState::instance.units[iVar9].workplaceBuildingID_1 = (short)iVar10;
                DAT_UnitsState::instance.units[iVar9].state.generic
                    = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_UnitsState::instance.units[iVar9].substate = -1;
                DAT_UnitsState::instance.units[iVar9].facingDirection = 4;
                DAT_UnitsState::instance.units[iVar9].disappearFadeAlphaCountdown = 0x20;
                DAT_BuildingsState::instance.buildings[iVar10].workerUID[1] = iVar6;
                DAT_UnitsState::instance.units[iVar9].workerIndex = 1;
                DAT_UnitsState::instance.units[iVar9].buildingID = (short)iVar10;
            }
        }
        iVar9 = iVar10 * 0x32c;
        if (DAT_BuildingsState::instance.buildings[iVar10].renderAnimation == 0)
            goto LAB_004237a8;
        sVar4 = DAT_BuildingsState::instance.buildings[iVar10].state;
        if (sVar4 == 0) {
            bVar2 = DAT_BuildingDefinedData::instance
                        .field51_0x4b50[DAT_BuildingsState::instance.buildings[iVar10].animationIndex];
            if ('\0' < (char)bVar2) {
                DAT_BuildingsState::instance.buildings[iVar10].animationFrame = (int)(char)bVar2;
            }
            bVar7 = (char)bVar2 < '\x01';
            sVar4 = (0x10 - DAT_BuildingsState::instance.buildings[iVar10].animationIndex) * 2;
            DAT_BuildingsState::instance.buildings[iVar10].field66_0xbe = sVar4;
            if (0 < sVar4)
                goto LAB_004236b1;
            DAT_BuildingsState::instance.buildings[iVar10].field66_0xbe = 0;
        } else {
            if ((sVar4 < 1) || (6 < sVar4)) {
                if (sVar4 != 7)
                    goto LAB_004237a8;
                bVar2 = DAT_BuildingDefinedData::instance
                            .field53_0x4b90[DAT_BuildingsState::instance.buildings[iVar10].animationIndex];
                if ('\0' < (char)bVar2) {
                    DAT_BuildingsState::instance.buildings[iVar10].animationFrame = (int)(char)bVar2;
                }
                bVar7 = (char)bVar2 < '\x01';
                sVar4 = DAT_BuildingsState::instance.buildings[iVar10].animationIndex * 2;
                DAT_BuildingsState::instance.buildings[iVar10].field66_0xbe = sVar4;
                if (0x1f < sVar4) {
                    DAT_BuildingsState::instance.buildings[iVar10].field66_0xbe = 0x20;
                    goto LAB_004236b9;
                }
            } else {
                sVar4 = DAT_BuildingsState::instance.buildings[iVar10].animationIndex;
                if ((char)DAT_BuildingDefinedData::instance.field52_0x4b68[sVar4] < '\x01') {
                    bVar7 = true;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(iVar10, DAT_BuildingsState::instance.buildings[iVar10].uid,
                        OpenSHC::Game::Resources::RT_MEAT, 1, 6, 1);
                    iVar10 = DAT_CurrentBuildingID::instance;
                } else {
                    if ((DAT_BuildingsState::instance.buildings[iVar10].animationActive != 0) && (sVar4 == 4)) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar10].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar10].y)),
                            OpenSHC::DE::SHCDE::FX_HUNTER_CUT);
                        iVar10 = DAT_CurrentBuildingID::instance;
                    }
                    DAT_BuildingsState::instance.buildings[iVar10].animationFrame
                        = (int)(char)DAT_BuildingDefinedData::instance
                              .field52_0x4b68[DAT_BuildingsState::instance.buildings[iVar10].animationIndex];
                }
                iVar9 = iVar10 * 0x32c;
                DAT_BuildingsState::instance.buildings[iVar10].field66_0xbe = 0;
            }
        LAB_004236b1:
            if (!bVar7)
                goto LAB_004237a8;
        }
    LAB_004236b9:
        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar9) = 0;
        sVar4 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8);
        if (sVar4 == 0) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 1;
        } else if (sVar4 == 1) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 2;
        } else if (sVar4 == 2) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 3;
        } else if (sVar4 == 3) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 4;
        } else if (sVar4 == 4) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 5;
        } else if (sVar4 == 5) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 6;
        } else if (sVar4 == 6) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 7;
        } else if (sVar4 == 7) {
            piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].field13_0x28 + iVar9);
            *piVar1 = *piVar1 + 1;
            *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].field14_0x2c + iVar9) = 1;
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -8) = 0;
        }
    LAB_004237a8:
        sVar4 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62);
        if (sVar4 < 0x20) {
            if (sVar4 < 0) {
                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0;
            }
        } else {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + -0x62) = 0x1f;
        }
        iVar10 = *(int*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar9 + 0x30);
        if (iVar10 == 1) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar9) = 0x14;
        } else if (iVar10 == 2) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar9) = 0x15;
        } else if (iVar10 == 3) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar9) = 0x16;
        } else if (iVar10 == 4) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar9) = 0x17;
        } else if (iVar10 == 5) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar9) = 0x18;
        } else {
            *(uint*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar9) = (iVar10 != 6) - 1 & 0x19;
        }
        *(undefined1*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar9 + -0x33) = 0;
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar9 + 2) == 0) {
            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar9 + 2) = 0;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field39_0x84 + iVar9) = 0;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar9) = 1;
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9);
        *piVar1 = *piVar1 + 1;
        if ((char)DAT_BuildingDefinedData::instance
                .field177_0x7e1c[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9) / 2]
            < '\x01') {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9) = 0;
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].field39_0x84 + iVar9)
            = (int)(char)DAT_BuildingDefinedData::instance
                  .field177_0x7e1c[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar9) / 2];
    }

}
}
