#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitStateShort;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x004130D0
    void Buildings::UpdateBlacksmithsWorkshop()
    {
        int* piVar1;
        short sVar2;
        short sVar3;
        ResourceTypeShort RVar4;
        UnitStateShort UVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        bool bVar9;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar7 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field138_0x1c2 = 1;
        sVar3 = DAT_BuildingsState::instance.buildings[iVar7].workers[0];
        piVar1 = &DAT_GameState::instance.playerDataArray[sVar2].countArmorersAndBlacksmiths;
        *piVar1 = *piVar1 + 1;
        DAT_BuildingsState::instance.buildings[iVar7].renderAnimation = (ushort)(sVar3 != 0);
        if ((char)((char)DAT_BuildingsState::instance.buildings[iVar7].uid
                + (char)DAT_GameCore::instance.mapTimeInTicks)
            == '\0') {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingPlacementRotationPreview,
                DAT_TileMapState::ptr)((int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)));
            iVar7 = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        iVar8 = iVar7 * 0x32c;
        RVar4 = DAT_BuildingsState::instance.buildings[iVar7].producedItemTypeNext;
        if (RVar4 == OpenSHC::Game::Resources::RT_SWORD) {
            sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
            if (sVar2 == 0) {
                if ((char)DAT_BuildingDefinedData::instance
                        .field64_0x503c[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01')
                    goto LAB_0041338d;
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .field64_0x503c[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    + 0x18;
            } else if (sVar2 == 1) {
            LAB_004131d2:
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && (((sVar2 = DAT_BuildingsState::instance.buildings[iVar7].animationIndex,
                             sVar2 == 0x18 || (sVar2 == 0x22))
                        || (sVar2 == 0x2c)))) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        OpenSHC::DE::SHCDE::FX_BS_ANVIL);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                iVar8 = iVar7 * 0x32c;
                if ((char)DAT_BuildingDefinedData::instance
                        .field67_0x50cc[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01') {
                LAB_0041338d:
                    *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar8) = 0;
                    sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8);
                    if (sVar2 == 0) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 1;
                    } else if (sVar2 == 1) {
                        *(ushort*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8)
                            = (ushort)(DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                                * 4
                            + 2;
                    } else if (sVar2 == 2) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 3;
                    } else if (sVar2 == 3) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 4;
                    } else if (sVar2 == 4) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 5;
                    } else if (sVar2 == 5) {
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 6;
                    } else {
                        if (sVar2 != 6) {
                            bVar9 = sVar2 == 7;
                            goto LAB_0041363b;
                        }
                        *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 7;
                    }
                } else {
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field67_0x50cc[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                }
            } else if (sVar2 == 2) {
                if ((char)DAT_BuildingDefinedData::instance
                        .field65_0x5094[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01')
                    goto LAB_0041338d;
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .field65_0x5094[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    + 0x18;
            } else {
                if (sVar2 == 3)
                    goto LAB_004131d2;
                if (sVar2 == 4) {
                    if ((char)DAT_BuildingDefinedData::instance
                            .field66_0x50c0[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_0041338d;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field66_0x50c0[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                    goto LAB_00413651;
                }
                if (sVar2 == 5)
                    goto LAB_004131d2;
                if (sVar2 == 6) {
                    if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                        && (((sVar2 = DAT_BuildingsState::instance.buildings[iVar7].animationIndex,
                                 sVar2 == 0x18 || (sVar2 == 0x22))
                            || (sVar2 == 0x2c)))) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                            OpenSHC::DE::SHCDE::FX_BS_ANVIL);
                        iVar7 = DAT_CurrentBuildingID::instance;
                    }
                    iVar8 = iVar7 * 0x32c;
                    if ((char)DAT_BuildingDefinedData::instance
                            .field67_0x50cc[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_0041338d;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field67_0x50cc[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                } else if (sVar2 == 7) {
                    if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                        && (DAT_BuildingsState::instance.buildings[iVar7].animationIndex == 0x1e)) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                            (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                            OpenSHC::DE::SHCDE::FX_BS_COOL);
                        iVar7 = DAT_CurrentBuildingID::instance;
                    }
                    iVar8 = iVar7 * 0x32c;
                    if ((char)DAT_BuildingDefinedData::instance
                            .field68_0x510c[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_0041338d;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field68_0x510c[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x18;
                }
            }
        } else if (RVar4 == OpenSHC::Game::Resources::RT_MACE) {
            sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
            if (sVar2 == 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance
                            .field69_0x5144[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01') {
                    LAB_00413604:
                        *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].animationIndex + iVar8) = 0;
                        sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8);
                        if (sVar2 == 0) {
                            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 1;
                        } else if (sVar2 == 1) {
                            *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8) = 2;
                        } else {
                            bVar9 = sVar2 == 2;
                        LAB_0041363b:
                            if (bVar9) {
                                piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].field13_0x28 + iVar8);
                                *piVar1 = *piVar1 + 1;
                                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].field14_0x2c + iVar8)
                                    = 1;
                                *(undefined2*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8)
                                    = 0;
                            }
                        }
                    } else {
                        DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                            = (char)DAT_BuildingDefinedData::instance
                                  .field69_0x5144[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                            + 0x6e;
                    }
                } else {
                    if ((char)DAT_BuildingDefinedData::instance
                            .field72_0x52d0[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_00413604;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field72_0x52d0[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0x6e;
                }
            } else if (sVar2 == 1) {
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && (DAT_BuildingsState::instance.buildings[iVar7].animationIndex == 0x18)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        OpenSHC::DE::SHCDE::FX_BS_POUR);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && (DAT_BuildingsState::instance.buildings[iVar7].animationIndex == 0x3c)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        OpenSHC::DE::SHCDE::FX_BS_OPEN);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                iVar8 = iVar7 * 0x32c;
                if ((char)DAT_BuildingDefinedData::instance
                        .field70_0x518c[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    < '\x01')
                    goto LAB_00413604;
                DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                    = (char)DAT_BuildingDefinedData::instance
                          .field70_0x518c[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                    + 0x6e;
            } else if (sVar2 == 2) {
                if ((DAT_BuildingsState::instance.buildings[iVar7].animationActive != 0)
                    && ((((sVar2 = DAT_BuildingsState::instance.buildings[iVar7].animationIndex,
                              sVar2 == 5 || (sVar2 == 0x1e))
                             || (sVar2 == 0x37))
                        || ((sVar2 == 0x50 || (sVar2 == 0x6d)))))) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar7].x,
                        (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar7].y)),
                        OpenSHC::DE::SHCDE::FX_BS_FILE);
                    iVar7 = DAT_CurrentBuildingID::instance;
                }
                iVar8 = iVar7 * 0x32c;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance
                            .field71_0x51dc[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_00413604;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field71_0x51dc[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0xaf;
                } else {
                    if ((char)DAT_BuildingDefinedData::instance
                            .field73_0x52f4[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        < '\x01')
                        goto LAB_00413604;
                    DAT_BuildingsState::instance.buildings[iVar7].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .field73_0x52f4[DAT_BuildingsState::instance.buildings[iVar7].animationIndex]
                        + 0xaf;
                }
            }
        }
    LAB_00413651:
        iVar6 = (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar8);
        if (iVar6 == 0) {
        LAB_0041368b:
            *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 0;
        } else {
            UVar5 = DAT_UnitsState::instance.units[iVar6].state.generic;
            if (UVar5 == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
            } else {
                if (UVar5 != OpenSHC::Map::Units::States::US_AIM_WEAPONUnk)
                    goto LAB_0041368b;
                *(undefined2*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8) = 1;
            }
        }
        sVar2 = *(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8);
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(iVar7);
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].buildingIsVisuallyActive + iVar8)
            != *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x52)) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                iVar7);
            iVar7 = DAT_CurrentBuildingID::instance;
            iVar8 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar8) = 1;
        if (sVar2 == 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar8) = 0;
            goto LAB_00413819;
        }
        if (*(short*)((int)&DAT_BuildingsState::instance.buildings[0].animationActive + iVar8) != 0) {
            piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8);
            *piVar1 = *piVar1 + 1;
        }
        if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].field27_0x54 + iVar8) == 0) {
            if ((char)DAT_BuildingDefinedData::instance
                    .field62_0x4ffc[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8) = 0;
                sVar2 = *(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -8);
                if (sVar2 == 0) {
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field27_0x54 + iVar8) = 0;
                    iVar7 = (int)(char)DAT_BuildingDefinedData::instance.field62_0x4ffc[*(
                        int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)];
                } else {
                    if (sVar2 != 2) {
                        *(uint*)((int)&DAT_BuildingsState::instance.buildings[0].field27_0x54 + iVar8)
                            = (uint)(sVar2 != 4);
                        goto LAB_00413771;
                    }
                    *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field27_0x54 + iVar8) = 0;
                    iVar7 = (int)(char)DAT_BuildingDefinedData::instance.field62_0x4ffc[*(
                        int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)];
                }
            } else {
            LAB_00413771:
                iVar7 = (int)(char)DAT_BuildingDefinedData::instance.field62_0x4ffc[*(
                    int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8)];
            }
        } else {
            iVar6 = *(int*)((int)&DAT_BuildingsState::instance.buildings[0].campgroundVclock + iVar8);
            if ((iVar6 == 0) || (iVar6 == 0x10)) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x32),
                    (int)*(short*)((int)DAT_BuildingsState::instance.buildings[0].resources + iVar8 + -0x30),
                    OpenSHC::DE::SHCDE::FX_BS_BELLOW);
                iVar7 = DAT_CurrentBuildingID::instance;
            }
            iVar8 = iVar7 * 0x32c;
            if ((char)DAT_BuildingDefinedData::instance
                    .field63_0x5010[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock]
                < '\x01') {
                DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock = 0;
                sVar2 = DAT_BuildingsState::instance.buildings[iVar7].state;
                if (sVar2 == 0) {
                    DAT_BuildingsState::instance.buildings[iVar7].field27_0x54 = 0;
                } else if (sVar2 == 2) {
                    DAT_BuildingsState::instance.buildings[iVar7].field27_0x54 = 0;
                } else {
                    DAT_BuildingsState::instance.buildings[iVar7].field27_0x54 = (uint)(sVar2 != 4);
                }
            }
            iVar7 = (int)(char)DAT_BuildingDefinedData::instance
                        .field63_0x5010[DAT_BuildingsState::instance.buildings[iVar7].campgroundVclock];
        }
        *(int*)((int)&DAT_BuildingsState::instance.buildings[0].field20_0x38 + iVar8) = iVar7;
    LAB_00413819:
        piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].field28_0x58 + iVar8);
        *piVar1 = *piVar1 + 1;
        if (3 < *(int*)((int)&DAT_BuildingsState::instance.buildings[0].field28_0x58 + iVar8)) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field28_0x58 + iVar8) = 0;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].workerID + iVar8) == 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field21_0x3c + iVar8) = 0;
        } else {
            if (*(int*)((int)&DAT_BuildingsState::instance.buildings[0].field28_0x58 + iVar8) == 0) {
                piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].field25_0x4c + iVar8);
                *piVar1 = *piVar1 + 1;
            }
            if ((char)DAT_BuildingDefinedData::instance
                    .field81_0x55c0[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].field25_0x4c + iVar8)]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field25_0x4c + iVar8) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].field21_0x3c + iVar8)
                = (char)DAT_BuildingDefinedData::instance
                      .field81_0x55c0[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].field25_0x4c + iVar8)]
                + 0x10;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].displayOwnerFlag + iVar8) = 1;
            piVar1 = (int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar8);
            *piVar1 = *piVar1 + 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .field177_0x7e1c[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar8)
                        / 2]
                < '\x01') {
                *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar8) = 0;
            }
            *(int*)((int)&DAT_BuildingsState::instance.buildings[0].field39_0x84 + iVar8)
                = (int)(char)DAT_BuildingDefinedData::instance
                      .field177_0x7e1c[*(int*)((int)&DAT_BuildingsState::instance.buildings[0].ownerFlagFrame + iVar8)
                          / 2];
        }
        *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].field39_0x84 + iVar8) = 0;
    }

}
}
