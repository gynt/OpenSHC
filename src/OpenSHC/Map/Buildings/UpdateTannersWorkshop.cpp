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

    // Tanner: work states 0..10, the end of state 10 completes a product; no player workshop counter. States
    // 1/3/5 and 2/4 jump straight to the end-of-cycle code when their table runs out (jle 0x414530) and leave the
    // fade alone otherwise; state 10 only animates in GM_SOLITARY (jne 0x414515). The sprite is offset by +1 while
    // state <= 6 (cmp 6; jg at 0x414148). Frame tables are signed bytes (cmp al, bl; jg/jle). Visually active for
    // worker unit states 6 and 5; updateVisuallyActiveState/updateBuildingGraphicsLayer get the cached id (push ebp).
    // FUNCTION: STRONGHOLDCRUSADER 0x004140B0
    void Buildings::UpdateTannersWorkshop()
    {
        int cycleEnded = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].isProductionWorkshop = 1;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation
            = DAT_BuildingsState::instance.buildings[buildingID].workers[0] != 0;
        if (((DAT_BuildingsState::instance.buildings[buildingID].uid + DAT_GameCore::instance.mapTimeInTicks) & 0xff)
            == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::computeWallFacingRotationAt, DAT_TileMapState::ptr)(
                DAT_BuildingsState::instance.buildings[buildingID].x,
                DAT_BuildingsState::instance.buildings[buildingID].y);
            buildingID = DAT_CurrentBuildingID::instance;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
                = (short)DAT_TileMapState::instance.uiBuildingRotation;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].state < 7) {
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX
                = DAT_BuildingDefinedData::instance
                      .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][0][0]
                + 1;
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY
                = DAT_BuildingDefinedData::instance
                      .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][1][0]
                + 1;
        } else {
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX = DAT_BuildingDefinedData::instance
                .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][0][0];
            DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY = DAT_BuildingDefinedData::instance
                .SpriteOffsets1[(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType][1][0];
        }
        {
            short value;
            char frame;
            short state = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (state == 0) {
                int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    frame = DAT_BuildingDefinedData::instance.AnimTannerSolitary[frameIndex];
                } else {
                    frame = DAT_BuildingDefinedData::instance.AnimTanner[frameIndex];
                }
                if (frame <= 0) {
                    cycleEnded = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex != 0) {
                    goto decrementFade;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                goto checkEnded;
            }
            if (state == 1 || state == 3 || state == 5) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                    short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 0 || animationIndex == 0xe || animationIndex == 0x1a
                        || animationIndex == 0x29) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_TANNER_BRUSH1);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                    animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 7 || animationIndex == 0x15 || animationIndex == 0x21
                        || animationIndex == 0x2f) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_TANNER_BRUSH2);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    frame = DAT_BuildingDefinedData::instance
                                .AnimTannerSolitary2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        goto endCycle;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0xc;
                } else {
                    frame = DAT_BuildingDefinedData::instance
                                .AnimTanner2[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                    if (frame <= 0) {
                        goto endCycle;
                    }
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0xc;
                }
                goto clampFade;
            }
            if (state == 2 || state == 4) {
                frame = DAT_BuildingDefinedData::instance
                            .AnimTanner3[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame <= 0) {
                    goto endCycle;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                goto clampFade;
            }
            if (state == 6) {
                frame = DAT_BuildingDefinedData::instance
                            .AnimTanner4[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame <= 0) {
                    goto markEnded;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame;
                goto storeIndexAsFade;
            }
            if (state == 7) {
                if (DAT_BuildingsState::instance.buildings[buildingID].animationActive != 0) {
                    short animationIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                    if (animationIndex == 0xf || animationIndex == 0x18 || animationIndex == 0x1e
                        || animationIndex == 0x28 || animationIndex == 0x2e) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                            DAT_BuildingsState::instance.buildings[buildingID].x,
                            DAT_BuildingsState::instance.buildings[buildingID].y, OpenSHC::DE::SHCDE::FX_TANNER_CUT);
                        buildingID = DAT_CurrentBuildingID::instance;
                    }
                }
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    if ((char)DAT_BuildingDefinedData::instance.tannerCutFramesSolitary[DAT_BuildingsState::instance.buildings[buildingID].animationIndex] <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.tannerCutFramesSolitary[DAT_BuildingsState::instance.buildings[buildingID].animationIndex] + 0x19;
                    }
                } else {
                    if ((char)DAT_BuildingDefinedData::instance.tannerCutFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex] <= 0) {
                        cycleEnded = 1;
                    } else {
                        DAT_BuildingsState::instance.buildings[buildingID].animationFrame
                            = (char)DAT_BuildingDefinedData::instance.tannerCutFrames[DAT_BuildingsState::instance.buildings[buildingID].animationIndex] + 0x19;
                    }
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex != 0) {
                    goto decrementFade;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                goto checkEnded;
            }
            if (state == 8) {
                frame = DAT_BuildingDefinedData::instance
                            .AnimTanner5[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
                if (frame <= 0) {
                    goto markEnded;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x19;
                goto storeIndexAsFade;
            }
            if (state == 9) {
                int frameIndex = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    frame = DAT_BuildingDefinedData::instance.AnimTannerSolitary4[frameIndex];
                } else {
                    frame = DAT_BuildingDefinedData::instance.AnimTanner6[frameIndex];
                }
                if (frame <= 0) {
                    cycleEnded = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x33;
                }
                if (DAT_BuildingsState::instance.buildings[buildingID].animationIndex != 0) {
                    goto decrementFade;
                }
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
                goto checkEnded;
            }
            if (state != 10) {
                goto clampFade;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                goto markEnded;
            }
            frame = DAT_BuildingDefinedData::instance
                        .AnimTanner7[DAT_BuildingsState::instance.buildings[buildingID].animationIndex];
            if (frame <= 0) {
                goto markEnded;
            }
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = frame + 0x33;
            goto storeIndexAsFade;

        decrementFade:
            value = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
            if (value <= 0) {
                goto checkEnded;
            }
            value = value - 1;
            goto storeFade;
        markEnded:
            cycleEnded = 1;
        storeIndexAsFade:
            value = DAT_BuildingsState::instance.buildings[buildingID].animationIndex;
        storeFade:
            DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = value;
        checkEnded:
            if (cycleEnded == 0) {
                goto clampFade;
            }
        endCycle:
            DAT_BuildingsState::instance.buildings[buildingID].animationIndex = 0;
            short phase = DAT_BuildingsState::instance.buildings[buildingID].state;
            if (phase == 0) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 1;
            } else if (phase == 1) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 2;
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
                DAT_BuildingsState::instance.buildings[buildingID].state = 8;
            } else if (phase == 8) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 9;
            } else if (phase == 9) {
                DAT_BuildingsState::instance.buildings[buildingID].state = 10;
            } else if (phase == 10) {
                DAT_BuildingsState::instance.buildings[buildingID].workCycleCount += 1;
                DAT_BuildingsState::instance.buildings[buildingID].workCycleJustEnded = 1;
                DAT_BuildingsState::instance.buildings[buildingID].state = 0;
            }
        }
    clampFade:
        {
            short fade = DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha;
            if (fade > 0x1f) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0x1f;
            } else if (fade < 0) {
                DAT_BuildingsState::instance.buildings[buildingID].animFadeAlpha = 0;
            }
        }
        DAT_BuildingsState::instance.buildings[buildingID].showOverlays = 0;
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

}
}
