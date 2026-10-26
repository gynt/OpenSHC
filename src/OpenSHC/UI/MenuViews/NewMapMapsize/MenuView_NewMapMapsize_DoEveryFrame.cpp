#include "../NewMapMapsize.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0042F3F0
        void NewMapMapsize::MenuView_NewMapMapsize_DoEveryFrame()
        {
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            int local_20;
            int local_1c;
            char local_18[20];
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
            int iVar1 = DAT_MenuHandlerState::instance.y + 0x3b;
            iVar3 = DAT_MenuHandlerState::instance.x + 400;
            /*
              added by script: "Select New Map Size"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x14),
                iVar3, iVar1, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x10, FALSE, 0);
            iVar6 = DAT_MenuHandlerState::instance.x + 0x258;
            iVar3 = DAT_MenuHandlerState::instance.y + 0x122;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            iVar5 = DAT_TileMapState::instance.mapSize;
            DAT_MinimapViewState::instance.needsRedraw = 1;
            if (iVar5 == 0) {
                iVar5 = 400;
            }
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", iVar5, iVar5);
            int boxX = iVar6;
            local_1c = iVar3;
            switch (iVar5) {
            case 100:
                iVar3 = iVar3 + -0x32;
                iVar6 = iVar6 + -0x32;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
    iVar6, iVar3, iVar5, iVar5);
                local_20 = 100;
                break;
            default:
                iVar4 = 200;
                goto LAB_0042f577;
            case 0xa0:
                iVar3 = iVar3 + -0x50;
                iVar6 = iVar6 + -0x50;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
    iVar6, iVar3, iVar5, iVar5);
                local_20 = 0xa0;
                break;
            case 200:
                iVar4 = iVar5;
            LAB_0042f577:
                iVar3 = iVar3 + -0x64;
                iVar6 = iVar6 + -0x64;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
    iVar6, iVar3, iVar4, iVar4);
                local_20 = 200;
                break;
            case 300:
                iVar3 = iVar3 + -0x4b;
                iVar6 = iVar6 + -0x4b;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
    iVar6, iVar3, 0x96, 0x96);
                local_20 = 0x96;
            }
            iVar4 = local_1c;
            if (iVar5 == 0xa0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                DAT_PencilRenderCore::ptr)(boxX + -0x4e, iVar4 + -0x4f, boxX + 0x4e, iVar4 + 0x4d,
                    (ushort)(COL_BLACK::instance.shortValue));
                iVar5 = iVar4 + 0x4e;
                iVar2 = boxX + 0x4f;
                iVar4 = iVar4 + -0x50;
                iVar1 = boxX + -0x4f;
            } else if (iVar5 == 200) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                DAT_PencilRenderCore::ptr)(boxX + -0x62, iVar4 + -99, boxX + 0x63, iVar4 + 99,
                    (ushort)(COL_BLACK::instance.shortValue));
                iVar5 = iVar4 + 100;
                iVar2 = boxX + 0x64;
                iVar4 = iVar4 + -100;
                iVar1 = boxX + -0x63;
            } else if (iVar5 == 300) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                DAT_PencilRenderCore::ptr)(boxX + -0x4b, iVar4 + -0x4b, boxX + 0x49, iVar4 + 0x4a,
                    (ushort)(COL_BLACK::instance.shortValue));
                iVar5 = iVar4 + 0x4b;
                iVar2 = boxX + 0x4a;
                iVar4 = iVar4 + -0x4c;
                iVar1 = boxX + -0x4c;
            } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                DAT_PencilRenderCore::ptr)(boxX + -0x64, iVar4 + -100, boxX + 0x63, iVar4 + 100,
                    (ushort)(COL_BLACK::instance.shortValue));
                iVar5 = iVar4 + 0x65;
                iVar2 = boxX + 0x64;
                iVar4 = iVar4 + -0x65;
                iVar1 = boxX + -0x65;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar1, iVar4, iVar2, iVar5, (ushort)(COL_BLACK::instance.shortValue));
            iVar6 = iVar6 + local_20;
            iVar1 = iVar3 + -0xf;
            iVar5 = iVar6;
            iVar4 = iVar3;
            iVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                local_18, 0x13);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                (iVar6 - iVar2) + -0xf, iVar1, iVar5, iVar4);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                local_18, iVar6 + -5, iVar3 + -0xb, OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0x13, FALSE, 0);
            ;
            return;
        }

    }
}
}
