#include "../UnusedChooseAvailableKeeps.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Rendering::Colors::BGR24;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042FAC0
        void UnusedChooseAvailableKeeps::MenuView_UnusedChooseAvailableKeeps_DoEveryFrame()
        {
            int iVar1;
            int iVar2;
            int iVar4;
            int iVar5;
            int local_20;
            char local_18[20];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_20;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner, DAT_PencilRenderCore::ptr)(
                DAT_MenuHandlerState::instance.x + 100, DAT_MenuHandlerState::instance.y + 0x1e, 600, 0x32);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x15),
                DAT_MenuHandlerState::instance.x + 400, DAT_MenuHandlerState::instance.y + 0x3b,
                OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x10, FALSE, 0);
            int minimapX = DAT_MenuHandlerState::instance.x + 0x258;
            int minimapY = DAT_MenuHandlerState::instance.y + 0x122;
            int centerX = minimapX;
            int centerY = minimapY;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            iVar5 = DAT_TileMapState::instance.mapSize;
            if (!DAT_TileMapState::instance.mapSize) {
                iVar5 = 400;
            }
            DAT_MinimapViewState::instance.needsRedraw = 1;
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", iVar5, iVar5);
            switch (iVar5) {
            case 100:
                minimapY = minimapY + -0x32;
                minimapX = minimapX + -0x32;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    minimapX, minimapY, iVar5, iVar5);
                local_20 = 100;
                break;
            default:
                iVar4 = 200;
                goto LAB_0042fc47;
            case 0xa0:
                minimapY = minimapY + -0x50;
                minimapX = minimapX + -0x50;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    minimapX, minimapY, iVar5, iVar5);
                local_20 = 0xa0;
                break;
            case 200:
                iVar4 = iVar5;
            LAB_0042fc47:
                minimapY = minimapY + -0x64;
                minimapX = minimapX + -0x64;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    minimapX, minimapY, iVar4, iVar4);
                local_20 = 200;
                break;
            case 300:
                minimapY = minimapY + -0x4b;
                minimapX = minimapX + -0x4b;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    minimapX, minimapY, 0x96, 0x96);
                local_20 = 0x96;
            }
            if (iVar5 == 0xa0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                    centerX + -0x4e, centerY + -0x4f, centerX + 0x4e, centerY + 0x4d, (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = centerY + 0x4e;
                iVar2 = centerX + 0x4f;
                iVar4 = centerY + -0x50;
                iVar1 = centerX + -0x4f;
            } else if (iVar5 == 200) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                    centerX + -0x62, centerY + -0x63, centerX + 0x63, centerY + 0x63, (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = centerY + 0x64;
                iVar2 = centerX + 0x64;
                iVar4 = centerY + -0x64;
                iVar1 = centerX + -0x63;
            } else if (iVar5 == 300) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                    centerX + -0x4b, centerY + -0x4b, centerX + 0x49, centerY + 0x4a, (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = centerY + 0x4b;
                iVar2 = centerX + 0x4a;
                iVar4 = centerY + -0x4c;
                iVar1 = centerX + -0x4c;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                    centerX + -0x64, centerY + -0x64, centerX + 0x63, centerY + 0x64, (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = centerY + 0x65;
                iVar2 = centerX + 0x64;
                iVar4 = centerY + -0x65;
                iVar1 = centerX + -0x65;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar1, iVar4, iVar2, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
            minimapX = minimapX + local_20;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                (minimapX
                    - MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        local_18, 0x13))
                    + -0xf,
                minimapY + -0xf, minimapX, minimapY);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                local_18, minimapX + -5, minimapY + -0xb, OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0x13, FALSE, 0);
            return;
        }

    }
}
}
