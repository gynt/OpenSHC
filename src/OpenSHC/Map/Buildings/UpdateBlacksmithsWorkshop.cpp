#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"

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

    // Sword anvil states 1/3/5/6 share the same body (0x4131D2 / 0x4132B6).
#define BLACKSMITH_SWORD_ANVIL_STATE()                                                                           \
    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {                               \
        short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;                \
        if (animationIndex == 0x18 || animationIndex == 0x22 || animationIndex == 0x2c) {                        \
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(         \
                DAT_BuildingsState::instance.buildings[buildingID].x,                                            \
                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BS_ANVIL);          \
            buildingID = DAT_CurrentBuildingID::instance;                                                        \
        }                                                                                                        \
    }                                                                                                            \
    if ((char)DAT_BuildingDefinedData::instance                                                                  \
            .blacksmithSwordAnvilFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]       \
        <= 0) {                                                                                                  \
        goto swordCycleEnded;                                                                                    \
    }                                                                                                            \
    DAT_BuildingsState::instance.buildings[buildingID].animationFrame                                            \
        = (char)DAT_BuildingDefinedData::instance                                                                \
              .blacksmithSwordAnvilFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]     \
        + 0x18;

    // Sword: work states 0..7 (frames +0x18); the end of state 1 goes to 2 in GM_SOLITARY and to 6 otherwise
    // (setne; lea [ecx*4+2] at 0x4133C0), the end of state 7 completes a product. Mace: states 0..2 (frames +0x6e,
    // state 2 +0xaf). A table running out jumps straight to the end-of-cycle code (jle 0x41338d / 0x413604).
    // The forge overlay uses the visually-active flag read before updateVisuallyActiveState (movsx edi at
    // 0x413692). Frame tables are signed bytes (cmp al, bl; jle / cmp byte, bl; jg).
    // FUNCTION: STRONGHOLDCRUSADER 0x004130D0
    void Buildings::UpdateBlacksmithsWorkshop()
    {
        int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].isProductionWorkshop = 1;
        short firstWorker = DAT_BuildingsState::instance.buildings[buildingID].workers[0];
        DAT_GameState::instance.playerDataArray[owner].countArmorersAndBlacksmiths += 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = firstWorker != 0;
        if (((DAT_BuildingsState::instance.buildings[buildingID].uid + DAT_GameCore::instance.mapTimeInTicks) & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeWallFacingRotationAt, DAT_TileMapState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        {
            short itemType = DAT_BuildingsState::instance.buildings[buildingID].currentProducedItemType;
            if (itemType == OpenSHC::Game::Resources::RT_SWORD) {
                short state = DAT_BuildingsState::instance.buildings[buildingID].state;
                if (state == 0) {
                    if ((char)DAT_BuildingDefinedData::instance.blacksmithSwordPhase0Frames
                            [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        <= 0) {
                        goto swordCycleEnded;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.blacksmithSwordPhase0Frames
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x18;
                } else if (state == 1) {
                    BLACKSMITH_SWORD_ANVIL_STATE();
                } else if (state == 2) {
                    if ((char)DAT_BuildingDefinedData::instance.blacksmithSwordPhase2Frames
                            [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        <= 0) {
                        goto swordCycleEnded;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.blacksmithSwordPhase2Frames
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x18;
                } else if (state == 3) {
                    BLACKSMITH_SWORD_ANVIL_STATE();
                } else if (state == 4) {
                    if ((char)DAT_BuildingDefinedData::instance.blacksmithSwordPhase4Frames
                            [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        <= 0) {
                        goto swordCycleEnded;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance.blacksmithSwordPhase4Frames
                              [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x18;
                } else if (state == 5) {
                    BLACKSMITH_SWORD_ANVIL_STATE();
                } else if (state == 6) {
                    BLACKSMITH_SWORD_ANVIL_STATE();
                } else if (state == 7) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0x1e) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BS_COOL);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                    if ((char)DAT_BuildingDefinedData::instance
                            .blacksmithSwordCoolFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        <= 0) {
                        goto swordCycleEnded;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .blacksmithSwordCoolFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x18;
                }
                goto workerState;
            swordCycleEnded:
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                {
                    short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
                    if (phase == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 1;
                    } else if (phase == 1) {
                        DAT_BuildingsState::instance.buildings[buildingID].state
                            = (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) * 4 + 2;
                    } else if (phase == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 3;
                    } else if (phase == 3) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 4;
                    } else if (phase == 4) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 5;
                    } else if (phase == 5) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 6;
                    } else if (phase == 6) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 7;
                    } else if (phase == 7) {
                        DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                        DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                        DAT_BuildingsState::instance.buildings[buildingID].state = 0;
                    }
                }
            } else if (itemType == OpenSHC::Game::Resources::RT_MACE) {
                short state = DAT_BuildingsState::instance.buildings[buildingID].state;
                if (state == 0) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        if ((char)DAT_BuildingDefinedData::instance.blacksmithMacePhase0FramesSolitary
                                [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            <= 0) {
                            goto maceCycleEnded;
                        }
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.blacksmithMacePhase0FramesSolitary
                                  [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0x6e;
                    } else {
                        if ((char)DAT_BuildingDefinedData::instance.blacksmithMacePhase0Frames
                                [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            <= 0) {
                            goto maceCycleEnded;
                        }
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.blacksmithMacePhase0Frames
                                  [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0x6e;
                    }
                } else if (state == 1) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0x18) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BS_POUR);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0
                        && DAT_BuildingsState::instance.buildings[buildingID].animationIndex == 0x3c) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BS_OPEN);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                    if ((char)DAT_BuildingDefinedData::instance
                            .blacksmithMacePourFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        <= 0) {
                        goto maceCycleEnded;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                        = (char)DAT_BuildingDefinedData::instance
                              .blacksmithMacePourFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                        + 0x6e;
                } else if (state == 2) {
                    if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                        short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                        if (animationIndex == 5 || animationIndex == 0x1e || animationIndex == 0x37
                            || animationIndex == 0x50 || animationIndex == 0x6d) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                DAT_BuildingsState::instance.buildings[buildingID].x,
                                DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BS_FILE);
                            buildingID = DAT_CurrentBuildingID::instance;
                        }
                    }
                    if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        if ((char)DAT_BuildingDefinedData::instance.blacksmithMaceFileFramesSolitary
                                [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            <= 0) {
                            goto maceCycleEnded;
                        }
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.blacksmithMaceFileFramesSolitary
                                  [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0xaf;
                    } else {
                        if ((char)DAT_BuildingDefinedData::instance.blacksmithMaceFileFrames
                                [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            <= 0) {
                            goto maceCycleEnded;
                        }
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.blacksmithMaceFileFrames
                                  [DAT_BuildingsState::instance.buildings[buildingID].animationIndex]
                            + 0xaf;
                    }
                }
                goto workerState;
            maceCycleEnded:
                DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
                {
                    short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
                    if (phase == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 1;
                    } else if (phase == 1) {
                        DAT_BuildingsState::instance.buildings[buildingID].state = 2;
                    } else if (phase == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                        DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                        DAT_BuildingsState::instance.buildings[buildingID].state = 0;
                    }
                }
            }
        }
    workerState:
        {
            int workerID = DAT_BuildingsState::instance.buildings[buildingID].workerID[0];
            if (workerID != 0) {
                OpenSHC::Map::Units::States::UnitStateShort workerState = DAT_UnitsState::instance.units[workerID].state.generic;
                if (workerState == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    goto visualDone;
                }
                if (workerState == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 1;
                    goto visualDone;
                }
            }
            DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive = 0;
        }
    visualDone:
        int isActive = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState, DAT_BuildingsState::ptr)(
            buildingID);
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                buildingID);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[buildingID].buildingIsVisuallyActive;
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
        if (isActive == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = 0;
        } else {
            int forgeFrame;
            if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 += 1;
            }
            if (DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 == 0) {
                if ((char)DAT_BuildingDefinedData::instance
                        .blacksmithForgeIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                    short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
                    if (phase == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                        forgeFrame = (char)DAT_BuildingDefinedData::instance.blacksmithForgeIdleFrames
                            [DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
                    } else if (phase == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                        forgeFrame = (char)DAT_BuildingDefinedData::instance.blacksmithForgeIdleFrames
                            [DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = phase != 4;
                        forgeFrame = (char)DAT_BuildingDefinedData::instance.blacksmithForgeIdleFrames
                            [DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
                    }
                } else {
                    forgeFrame = (char)DAT_BuildingDefinedData::instance
                        .blacksmithForgeIdleFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
                }
            } else {
                int bellowsIndex = DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0;
                if (bellowsIndex == 0 || bellowsIndex == 0x10) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[buildingID].x,
                        DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_BS_BELLOW);
                    buildingID = DAT_CurrentBuildingID::instance;
                }
                if ((char)DAT_BuildingDefinedData::instance
                        .blacksmithBellowsFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0 = 0;
                    short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
                    if (phase == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                    } else if (phase == 2) {
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = 0;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex3 = phase != 4;
                    }
                }
                forgeFrame = (char)DAT_BuildingDefinedData::instance
                    .blacksmithBellowsFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex0];
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame0 = forgeFrame;
        }
        DAT_BuildingsState::instance.buildings[buildingID].tickDivider += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider > 3) {
            DAT_BuildingsState::instance.buildings[buildingID].tickDivider = 0;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].workerID[0] == 0) {
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = 0;
        } else {
            if (DAT_BuildingsState::instance.buildings[buildingID].tickDivider == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 += 1;
            }
            if ((char)DAT_BuildingDefinedData::instance
                    .chimneySmokeFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame1 = (char)DAT_BuildingDefinedData::instance
                .chimneySmokeFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayAnimIndex1]
                + 0x10;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 1;
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = (char)DAT_BuildingDefinedData::instance
                .ownerFlagFrames[DAT_BuildingsState::instance.buildings[buildingID].overlayFrame13 / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayFrame14 = 0;
    }

#undef BLACKSMITH_SWORD_ANVIL_STATE

}
}
