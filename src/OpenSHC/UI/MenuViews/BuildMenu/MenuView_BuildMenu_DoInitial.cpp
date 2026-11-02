#include "../BuildMenu.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
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
        using OpenSHC::UI::Enums::BuildMenuTabType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00431B60
        void BuildMenu::MenuView_BuildMenu_DoInitial()
        {
            Menu* pMVar1;
            int iVar2;
            char* pcVar3;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition = 0;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
                DAT_MenuHandlerState::instance.x = 0;
            } else {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                    = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            }
            if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_SOLDIERS) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    iVar2 = 8;
                } else {
                    iVar2 = 4;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(iVar2);
                if (!DAT_WindowAndDirectDraw::instance.pendingMenuRedraw) {}
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    (int)(DAT_MenuHandlerState::instance.y + 406), DAT_WindowAndDirectDraw::instance.resolutionX - 1,
                    (int)(DAT_MenuHandlerState::instance.y + 471), (ushort)(COL_MAGENTA::instance.shortValue));
                DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = 0;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1024L_TGX_005A25C0);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        pcVar3 = S_EDGE_MILITARY_1024L_TGX_005A25C0;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1024R_TGX_005A25A8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        iVar2 = 0x380;
                    } else {
                        iVar2 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, iVar2, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1024L_TGX_005A25C0);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        pcVar3 = S_EDGE_MILITARY_1024L_TGX_005A25C0;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1024R_TGX_005A25A8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        iVar2 = 0x380;
                    } else {
                        iVar2 = 0x390;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, iVar2, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1280L_TGX_005A2590);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1280L_TGX_005A2590;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1280R_TGX_005A2578;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x410, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1600L_TGX_005A2560);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1600L_TGX_005A2560;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1600R_TGX_005A2548;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x4b0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1280L_TGX_005A2590);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1280L_TGX_005A2590;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1280R_TGX_005A2578;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x410, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1440L_TGX_005A2530);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1440L_TGX_005A2530;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1440R_TGX_005A2518;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x460, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1920L_TGX_005A2500);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1920L_TGX_005A2500;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1920R_TGX_005A24E8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x550, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1920L_TGX_005A2500);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1920L_TGX_005A2500;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1920R_TGX_005A24E8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x550, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_2560L_TGX_005A24D0);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_2560L_TGX_005A24D0;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_2560R_TGX_005A24B8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x690, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_2560L_TGX_005A24D0);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_2560L_TGX_005A24D0;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_2560R_TGX_005A24B8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x690, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1366L_TGX_005A24A0);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1366L_TGX_005A24A0;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1366R_TGX_005A2488;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x43a, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1360L_TGX_005A2470);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1360L_TGX_005A2470;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1360R_TGX_005A2458;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x438, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1680L_TGX_005A2440);
                    if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                        || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        pcVar3 = S_EDGE_MILITARY_1680L_TGX_005A2440;
                    } else {
                        pcVar3 = S_EDGE_MILITARY_1680R_TGX_005A2428;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar3);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, 0x4d8, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {}
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(S_EDGE_MILITARY_1600L_TGX_005A2560);
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    pcVar3 = S_EDGE_MILITARY_1600L_TGX_005A2560;
                } else {
                    pcVar3 = S_EDGE_MILITARY_1600R_TGX_005A2548;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(pcVar3);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                iVar2 = 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height;
            } else {
                if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == OpenSHC::UI::Enums::BMTT_MENU_HIDDEN) {}
                if (DAT_GameCore::instance.activeMenuTab.buildMenuTab == (OpenSHC::UI::Enums::BuildMenuTabType)0x3e) {}
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    iVar2 = 9;
                } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                    iVar2 = 5;
                } else {
                    iVar2 = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMenuTabIndexUnk,
                    DAT_TextureRenderCoreObject::ptr)(iVar2);
                if (!DAT_WindowAndDirectDraw::instance.pendingMenuRedraw) {}
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                    DAT_MenuHandlerState::instance.y + 0x196, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)(COL_MAGENTA::instance.shortValue));
                DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = 0;
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)) {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4b0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1440L_TGX_005A2358);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1440L_TGX_005A2358);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x460, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1366L_TGX_005A2328);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1366L_TGX_005A2328);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x43a, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1360L_TGX_005A2318);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1360L_TGX_005A2318);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x438, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1680L_TGX_005A2308);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1680L_TGX_005A2308);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4d8, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {}
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    iVar2 = 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height;
                } else {
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024R_TGX_005A2418);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024L_TGX_005A2388);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1024R_TGX_005A2418);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x390, 600 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280R_TGX_005A2408);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x400 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1600R_TGX_005A23F8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4b0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280L_TGX_005A2378);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1280R_TGX_005A2408);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x410, 0x2d0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1440L_TGX_005A2358);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1440R_TGX_005A23E8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x460, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920R_TGX_005A23D8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x438 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920L_TGX_005A2348);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1920R_TGX_005A23D8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x550, 0x4b0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560R_TGX_005A23C8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x5a0 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560L_TGX_005A2338);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE2560R_TGX_005A23C8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x690, 0x640 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1366L_TGX_005A2328);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1366R_TGX_005A23B8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x43a, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1360L_TGX_005A2318);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1360R_TGX_005A23A8);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x438, 0x300 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1680L_TGX_005A2308);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(S_EDGE1680R_TGX_005A2398);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            0, 0, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                            DAT_TextureRenderCoreObject::ptr)(
                            1, 0x4d8, 0x41a - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {}
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE1600L_TGX_005A2368);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(S_EDGE1600R_TGX_005A23F8);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        0, 0, 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height);
                    iVar2 = 900 - DAT_TextureRenderCoreObject::instance.loadedGfxArray[1].height;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(1, 0x4b0, iVar2);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
