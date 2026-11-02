#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004398B0
        void BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_DoInitial()
        {
            Menu* pMVar1;
            int iVar2;
            int iVar3;
            char* pcVar4;
            int iVar5;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_640x480) {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                    = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            } else {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition = -0x2ba;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
                DAT_MenuHandlerState::instance.x = -0x2ba;
            }
            if ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    iVar5 = 7;
                } else {
                    iVar5 = 3;
                }
            } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                iVar5 = 6;
            } else {
                iVar5 = 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                DAT_TextureRenderCoreObject::ptr)(iVar5);
            if (DAT_WindowAndDirectDraw::instance.pendingMenuRedraw) {
                DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    DAT_MenuHandlerState::instance.y + 0x196, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)(COL_MAGENTA::instance.shortValue));
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1024L_TGX_005A25C0);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1024L_TGX_005A25C0;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1024R_TGX_005A25A8;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            iVar2 = 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                            iVar3 = 0x380;
                        } else {
                            iVar2 = 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                            iVar3 = 0x390;
                        }
                    } else {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1024L_TGX_005A2388;
                        } else {
                            pcVar4 = S_EDGE1024R_TGX_005A2418;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        iVar2 = 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1024L_TGX_005A25C0);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1024L_TGX_005A25C0;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1024R_TGX_005A25A8;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            iVar2 = 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                            iVar3 = 0x380;
                        } else {
                            iVar2 = 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                            iVar3 = 0x390;
                        }
                    } else {
                        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1024L_TGX_005A2388;
                        } else {
                            pcVar4 = S_EDGE1024R_TGX_005A2418;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(pcVar4);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            iVar5, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                        iVar2 = 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1280L_TGX_005A2590);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1280L_TGX_005A2590;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1280R_TGX_005A2578;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1280L_TGX_005A2378;
                        } else {
                            pcVar4 = S_EDGE1280R_TGX_005A2408;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x400;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x410;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x400 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1600L_TGX_005A2560);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1600L_TGX_005A2560;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1600R_TGX_005A2548;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1600L_TGX_005A2368;
                        } else {
                            pcVar4 = S_EDGE1600R_TGX_005A23F8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x4a0;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x4b0;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x4b0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1280L_TGX_005A2590);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1280L_TGX_005A2590;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1280R_TGX_005A2578;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1280L_TGX_005A2378;
                        } else {
                            pcVar4 = S_EDGE1280R_TGX_005A2408;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x400;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x410;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x2d0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1440L_TGX_005A2530);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1440L_TGX_005A2530;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1440R_TGX_005A2518;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1440L_TGX_005A2358);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1440L_TGX_005A2358;
                        } else {
                            pcVar4 = S_EDGE1440R_TGX_005A23E8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x450;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x460;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 900 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1920L_TGX_005A2500);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1920L_TGX_005A2500;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1920R_TGX_005A24E8;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1920L_TGX_005A2348;
                        } else {
                            pcVar4 = S_EDGE1920R_TGX_005A23D8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x540;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x550;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x438 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1920L_TGX_005A2500);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1920L_TGX_005A2500;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1920R_TGX_005A24E8;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1920L_TGX_005A2348;
                        } else {
                            pcVar4 = S_EDGE1920R_TGX_005A23D8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x540;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x550;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x4b0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_2560L_TGX_005A24D0);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_2560L_TGX_005A24D0;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_2560R_TGX_005A24B8;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE2560L_TGX_005A2338;
                        } else {
                            pcVar4 = S_EDGE2560R_TGX_005A23C8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x680;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x690;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x5a0 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_2560L_TGX_005A24D0);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_2560L_TGX_005A24D0;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_2560R_TGX_005A24B8;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE2560L_TGX_005A2338;
                        } else {
                            pcVar4 = S_EDGE2560R_TGX_005A23C8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x680;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x690;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x640 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1366L_TGX_005A24A0);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1366L_TGX_005A24A0;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1366R_TGX_005A2488;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1366L_TGX_005A2328);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1366L_TGX_005A2328;
                        } else {
                            pcVar4 = S_EDGE1366R_TGX_005A23B8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x42a;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x43a;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x300 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1360L_TGX_005A2470);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1360L_TGX_005A2470;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1360R_TGX_005A2458;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1360L_TGX_005A2318);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1360L_TGX_005A2318;
                        } else {
                            pcVar4 = S_EDGE1360R_TGX_005A23A8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x428;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x438;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x300 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1680L_TGX_005A2440);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1680L_TGX_005A2440;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1680R_TGX_005A2428;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1680L_TGX_005A2308);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1680L_TGX_005A2308;
                        } else {
                            pcVar4 = S_EDGE1680R_TGX_005A2398;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x4c8;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x4d8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 0x41a - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
                    DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
                    DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
                    if ((DAT_GameCore::instance.activeMenuTab.tabType
                            == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM)
                        || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)) {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1600L_TGX_005A2560);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE_MILITARY_1600L_TGX_005A2560;
                        } else {
                            pcVar4 = S_EDGE_MILITARY_1600R_TGX_005A2548;
                        }
                    } else {
                        iVar5 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                        if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                            pcVar4 = S_EDGE1600L_TGX_005A2368;
                        } else {
                            pcVar4 = S_EDGE1600R_TGX_005A23F8;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                        DAT_TextureRenderCoreObject::ptr)(pcVar4);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        iVar5, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5].height);
                    if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT))
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST))) {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x4a0;
                    } else {
                        iVar2 = DAT_TextureRenderCoreObject::instance.loadedGfxArray[iVar5 - 1].height;
                        iVar3 = 0x4b0;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(iVar5 - 1, iVar3, 900 - iVar2);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
            }
        }

    }
}
}
