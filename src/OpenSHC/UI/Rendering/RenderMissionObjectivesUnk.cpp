#include "../Rendering.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0b24.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ec02e8.hpp"
#include "OpenSHC/Globals/INT_00ed27c4.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb1238.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2630.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2fc8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed3070.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      OpenSHC::UI::Rendering::
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004D76A0
    int Rendering::RenderMissionObjectivesUnk()
    {
        int iVar1;
        char* pcVar2;
        int* piVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int yParam;
        TextAlignment TVar7;
        BGR24 BVar8;
        int iVar9;
        uint color;
        BOOLEnum BVar10;
        int iVar11;
        int iVar12;
        int local_c;
        int local_8;
        int local_4;
        iVar6 = 0;
        iVar11 = 0;
        BVar10 = FALSE;
        iVar9 = 0x11;
        BVar8 = 0xccfaff;
        yParam = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
        iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32;
        TVar7 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e;
        local_c = 0;
        local_4 = -1;
        iVar5 = 200;
        local_8 = 300;
        DAT_TextManagerObject::instance.field9_0x24 = 1;
        if (DAT_GameCore::instance.section1095 == 2) {
            pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0x1a);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar2, iVar4, iVar1, TVar7, BVar8, iVar9, BVar10, iVar11);
        } else {
            pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar2, iVar4, iVar1, TVar7, BVar8, iVar9, BVar10, iVar11);
            do {
                if ((INT_ARRAY_00ed2630::instance[iVar6] != 0)
                    && (((iVar6 != 0x12 && (iVar6 != 0x13))
                        || (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)))) {
                    iVar1 = iVar6;
                    if (0x13 < iVar6) {
                        iVar1 = iVar6 + 1;
                    }
                    if (iVar1 == 0x11) {
                        iVar1 = 6;
                    } else if (iVar1 == 0xf) {
                        iVar1 = 8;
                    }
                    iVar4 = 0x12;
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, iVar1);
                    iVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(pcVar2, iVar4);
                    iVar1 = iVar4 + 0x1e;
                    if (local_8 + -5 < iVar1) {
                        local_8 = iVar4 + 0x23;
                    }
                    if (iVar6 - 1U < 0x17) {
                        /*
                          WARNING: Switch is manually overridden
                         */
                        switch (iVar6) {
                        case 1:
                        case 4:
                        case 20:
                        case 21:
                        case 22:
                        case 23:
                            if (iVar5 + -5 < iVar1) {
                                iVar5 = iVar4 + 0x23;
                            }
                            iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                                DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[iVar6], 0x12);
                            if (DAT_GameCore::instance.gameSuspended == 1) {
                                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                                    DAT_TextManagerObject::ptr)(" ()", 0x12);
                                /*
                                  WARNING: Switch is manually overridden
                                 */
                                switch (iVar6) {
                                case 1:
                                    local_c = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .currentPopulation;
                                    break;
                                case 4:
                                    local_c = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .currentResources[0xf];
                                    break;
                                case 20:
                                    local_c = (int)DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .previousBlessedPeoplePercentage;
                                    break;
                                case 21:
                                    local_c
                                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
                                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                    break;
                                case 22:
                                    local_c
                                        = -DAT_GameState::instance
                                               .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                               .fearFactorLevel;
                                    break;
                                case 23:
                                    local_c = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .fearFactorLevel;
                                }
                                iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                                    DAT_TextManagerObject::ptr)(local_c, 0x12);
                                iVar1 = iVar1 + iVar4 + iVar9;
                            }
                            if (local_8 + -5 < iVar1 + iVar5) {
                                local_8 = iVar1 + iVar5 + 5;
                            }
                            break;
                        case 5:
                        case 6:
                        case 7:
                        case 17:
                            if (iVar5 + -5 < iVar1) {
                                iVar5 = iVar4 + 0x23;
                            }
                            iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                                DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[iVar6], 0x12);
                            if (0 < INT_ARRAY_00eb1238::instance[iVar6]) {
                                iVar4 = 0x12;
                                pcVar2
                                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS,
                                        (int)((int)(INT_ARRAY_00eb1238::instance[iVar6])));
                                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                                    DAT_TextManagerObject::ptr)(pcVar2, iVar4);
                                iVar1 = iVar1 + 6 + iVar4;
                            }
                            if (DAT_GameCore::instance.gameSuspended == 1) {
                                iVar9 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                                    DAT_TextManagerObject::ptr)(" ()", 0x12);
                                iVar4 = INT_ARRAY_00eb1238::instance[iVar6];
                                if (iVar4 == 8) {
                                    iVar4 = 7;
                                }
                                local_c = DAT_GameState::instance
                                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                              .currentResources[iVar4];
                                iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeNumberTextWidth,
                                    DAT_TextManagerObject::ptr)(local_c, 0x12);
                                iVar1 = iVar1 + iVar9 + iVar4;
                            }
                            if (local_8 + -5 < iVar1 + iVar5) {
                                local_8 = iVar1 + iVar5 + 5;
                            }
                        }
                    }
                }
                iVar6 = iVar6 + 1;
            } while (iVar6 < 0x27);
            iVar1 = 0;
            do {
                if ((INT_ARRAY_00ed2630::instance[iVar1] != 0)
                    && (((iVar1 != 0x12 && (iVar1 != 0x13))
                        || (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)))) {
                    iVar4 = iVar1;
                    if (0x13 < iVar1) {
                        iVar4 = iVar1 + 1;
                    }
                    if (((iVar4 == 0x11) || (iVar4 == 5)) || (iVar4 == 6)) {
                        iVar4 = 7;
                    } else if (iVar4 == 0xf) {
                        iVar4 = 8;
                    } else if ((iVar4 == 3)
                        && (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)) {
                        if (DAT_GameCore::instance.missionNumber1to20 == 0xd) {
                            iVar4 = 0xc;
                        } else if (DAT_GameCore::instance.missionNumber1to20 == 0x12) {
                            iVar4 = 0xd;
                        } else if (DAT_GameCore::instance.missionNumber1to20 == 0x15) {
                            iVar4 = 0xe;
                        }
                    }
                    iVar12 = 0;
                    BVar10 = FALSE;
                    iVar11 = 0x12;
                    BVar8 = 0xc2f0eb;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e;
                    iVar6 = yParam;
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, iVar4);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        pcVar2, iVar9, iVar6, TVar7, BVar8, iVar11, BVar10, iVar12);
                    if (iVar1 - 1U < 0x17) {
                        /*
                          WARNING: Switch is manually overridden
                         */
                        switch (iVar1) {
                        case 1:
                        case 4:
                        case 20:
                        case 21:
                        case 22:
                        case 23:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[iVar1],
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5, yParam,
                                OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);
                            if (DAT_GameCore::instance.gameSuspended == 1) {
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                    DAT_TextManagerObject::ptr)(" (",
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5, yParam,
                                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                                /*
                                  WARNING: Switch is manually overridden
                                 */
                                switch (iVar1) {
                                case 1:
                                    local_c = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .currentPopulation;
                                    break;
                                case 4:
                                    local_c = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .currentResources[0xf];
                                    break;
                                case 20:
                                    local_c = (int)DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .previousBlessedPeoplePercentage;
                                    break;
                                case 21:
                                    local_c
                                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
                                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                    break;
                                case 22:
                                    local_c
                                        = -DAT_GameState::instance
                                               .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                               .fearFactorLevel;
                                    break;
                                case 23:
                                    local_c = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .fearFactorLevel;
                                    break;
                                default:
                                    break;
                                }
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                    DAT_TextManagerObject::ptr)(local_c,
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5, yParam,
                                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                            LAB_004d7c99:
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                    ")", iVar4 + iVar5, yParam, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                            }
                            break;
                        case 5:
                        case 6:
                        case 7:
                        case 17:
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                DAT_TextManagerObject::ptr)(INT_ARRAY_00ed2fc8::instance[iVar1],
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5, yParam,
                                OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE, 0);
                            if (0 < INT_ARRAY_00eb1238::instance[iVar1]) {
                                iVar11 = 0;
                                BVar10 = TRUE;
                                iVar9 = 0x12;
                                BVar8 = 0xc2f0eb;
                                TVar7 = OpenSHC::Text::TTA_LEFT;
                                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 6 + iVar5;
                                iVar6 = yParam;
                                pcVar2
                                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS,
                                        (int)((int)(INT_ARRAY_00eb1238::instance[iVar1])));
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                    pcVar2, iVar4, iVar6, TVar7, BVar8, iVar9, BVar10, iVar11);
                            }
                            if (DAT_GameCore::instance.gameSuspended == 1) {
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                                    DAT_TextManagerObject::ptr)(" (",
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 6 + iVar5, yParam,
                                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                                iVar4 = INT_ARRAY_00eb1238::instance[iVar1];
                                if (iVar4 == 8) {
                                    iVar4 = 7;
                                }
                                local_c = DAT_GameState::instance
                                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                              .currentResources[iVar4];
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                    DAT_TextManagerObject::ptr)(local_c,
                                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 6 + iVar5, yParam,
                                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 6;
                                goto LAB_004d7c99;
                            }
                        }
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (INT_ARRAY_00ed3070::instance[iVar1] == 0) {
                        iVar6 = 5;
                        iVar4 = yParam;
                    } else {
                        iVar6 = 6;
                        iVar4 = yParam + -0x19;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_BUTTONS, iVar6,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + local_8, iVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    yParam = yParam + 0x1e;
                }
                iVar4 = DAT_MapPropertiesState::instance.SEC_Section1090;
                iVar1 = iVar1 + 1;
            } while (iVar1 < 0x27);
            if ((INT_ARRAY_00ed2630::instance[0x27] != 0) && (DAT_MapPropertiesState::instance.SEC_Section1081)) {
                iVar11 = 0;
                BVar10 = FALSE;
                iVar9 = 0x12;
                iVar1 = DAT_MapPropertiesState::instance.SEC_Section1090
                    - DAT_MapPropertiesState::instance.SEC_Section1080;
                BVar8 = 0xc2f0eb;
                TVar7 = OpenSHC::Text::TTA_LEFT;
                iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e;
                iVar5 = yParam;
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, 0x19);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar6, iVar5, TVar7, BVar8, iVar9, BVar10, iVar11);
                iVar5 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x28
                    + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x12d;
                if (DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x12d < iVar5) {
                    iVar6 = iVar5;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 2, iVar6 + 2, yParam + 1, 0x18);
                if (iVar4 < iVar1) {
                    iVar1 = iVar4;
                }
                if (iVar1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, (iVar1 * 0xfa) / iVar4 + 2 + iVar6, DAT_WindowAndDirectDraw::instance.resolutionY);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 4, iVar6 + 2, yParam + 1);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                        DAT_TextureRenderCoreObject::ptr)();
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 1, iVar6,
                    yParam + -1, OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 3, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                yParam = yParam + 0x15;
            }
            iVar5 = 0xf;
            if ((((INT_ARRAY_00ed2630::instance[8] != 0) || (INT_ARRAY_00ed2630::instance[0xf] != 0))
                    || (INT_00ec02e8::instance))
                && (iVar1 = 0, 0 < DAT_MapPropertiesState::instance.eventsCount)) {
                piVar3 = &DAT_MapPropertiesState::instance.scenarioEvents[0].header.tl_type;
                iVar4 = local_4;
                do {
                    if ((((*piVar3 != 1) || (local_4 = iVar1, piVar3[0x1e] != 0))
                            && ((local_4 = iVar4, *piVar3 == 3 && (*(char*)((int)piVar3 + 0x17) != '\0'))))
                        && ((piVar3[3] == 1 || (piVar3[3] == 0x1b)))) {
                        if (iVar4 == -1) {
                            iVar5 = 0x11;
                            local_4 = iVar1;
                        }
                        break;
                    }
                    iVar1 = iVar1 + 1;
                    piVar3 = piVar3 + 0x39;
                    iVar4 = local_4;
                } while (iVar1 < DAT_MapPropertiesState::instance.eventsCount);
                if (-1 < local_4) {
                    iVar1 = DAT_MapPropertiesState::instance.SEC_StartingMonth
                        + DAT_MapPropertiesState::instance.SEC_StartingYear * 0xc;
                    iVar4 = (DAT_GameState::instance.mapAndTime.year * 0xc - iVar1)
                        + DAT_GameState::instance.mapAndTime.month;
                    iVar1 = (DAT_MapPropertiesState::instance.scenarioEvents[local_4].header.month
                                + DAT_MapPropertiesState::instance.scenarioEvents[local_4].header.year * 0xc)
                        - iVar1;
                    if (!DAT_GameCore::instance.gameSuspended) {
                        iVar4 = 0;
                    }
                    iVar12 = 0;
                    BVar10 = FALSE;
                    iVar11 = 0x12;
                    BVar8 = 0xc2f0eb;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e;
                    iVar6 = yParam;
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_OBJECTIVES, iVar5);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        pcVar2, iVar9, iVar6, TVar7, BVar8, iVar11, BVar10, iVar12);
                    iVar5 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x28
                        + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x12d;
                    if (DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x12d < iVar5) {
                        iVar6 = iVar5;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 2, iVar6 + 2, yParam + 1, 0x18);
                    if (iVar1 < iVar4) {
                        iVar4 = iVar1;
                    }
                    if (iVar4) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, (iVar4 * 0xfa) / iVar1 + 2 + iVar6, DAT_WindowAndDirectDraw::instance.resolutionY);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 4, iVar6 + 2, yParam + 1);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
                            DAT_TextureRenderCoreObject::ptr)();
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 1, iVar6,
                        yParam + -1, OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 3, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    yParam = yParam + 0x15;
                }
            }
        }
        if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk) {
            return yParam;
        }
        iVar5 = (yParam - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight) + -0x1e;
        pcVar2 = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(DAT_GameCore::instance.standaloneFilename, &local_4);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(pcVar2,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x11,
            FALSE, 0);
        iVar1 = -iVar5 + (399 - (-iVar5 + 399) % 0x17);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x2d + iVar5,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + iVar1 + 0x2d + iVar5);
        if (!DAT_GameCore::instance.descriptionUseStringTable) {
            iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                DAT_GameCore::instance.temporaryTextBufferOfSize1000, 0, 0, 0x2d0, 0, 0, 1);
            iVar11 = 0;
            iVar9 = 0x12;
            color = 0xc2f0eb;
            iVar6 = 0x2d0;
            INT_00ed27c4::instance = (iVar4 + -1) / iVar1 + 1;
            iVar5 = (DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight - DAT_00eb0b24::instance * iVar1) + 0x32
                + iVar5;
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28;
            pcVar2 = DAT_GameCore::instance.temporaryTextBufferOfSize1000;
        } else {
            if (!DAT_GameCore::instance.descriptionStringTableIndex)
                goto LAB_004d8182;
            iVar12 = 1;
            iVar11 = 0;
            BVar8 = 0;
            iVar9 = 0x2d0;
            iVar6 = 0;
            iVar4 = 0;
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, (int)((int)(DAT_GameCore::instance.descriptionStringTableIndex)));
            iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                pcVar2, iVar4, iVar6, iVar9, BVar8, iVar11, iVar12);
            iVar11 = 0;
            iVar9 = 0x12;
            color = 0xc2f0eb;
            iVar6 = 0x2d0;
            INT_00ed27c4::instance = (iVar4 + -1) / iVar1 + 1;
            iVar5 = (DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight - DAT_00eb0b24::instance * iVar1) + 0x32
                + iVar5;
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x28;
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, (int)((int)(DAT_GameCore::instance.descriptionStringTableIndex)));
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            pcVar2, iVar1, iVar5, iVar6, color, iVar9, iVar11);
    LAB_004d8182:
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
            DAT_TextureRenderCoreObject::ptr)();
        return yParam;
    }

}
}
