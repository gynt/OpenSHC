#include "../NetworkSessions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonDisabled.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // regress_fix2: returns restored from the original machine code (every branch leaves with ret / tail jmp);
        // the Ghidra-derived version fell through into the scroll-arrow and Host/Join drawing for every button.
        // FUNCTION: STRONGHOLDCRUSADER 0x0047C670
        void NetworkSessions::MenuItemRenderFunction_NetworkSessions_Buttons(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 == -10000) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return; // 0x47c67e tail jmp
            }
            if (param_1 == 10000) {
                param_1 = 8;
                if (DAT_GameSynchronyState::instance.scrollBarIndex == -1) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    blendStrength = 0;
                    keepOffsetX = FALSE;
                    fontSize = 0x11;
                    color = 0x7f7f7f;
                    alignment = OpenSHC::Text::TTA_CENTER;
                    yParam = DAT_ButtonY::instance + 6;
                    xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    /*
                      Text:   0x8 => Join
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 8),
                        xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                    return; // 0x47c6f1 ret
                }
                goto LAB_0047c73a;
            }
            if ((param_1 == 9) || (param_1 == 10)) {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            if (param_1 == -10) {
                if (DAT_GameSynchronyState::instance.gameSpyArcadeInstalled != 0) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
                return; // 0x47c715 tail jmp / 0x47c85a ret
            }
            if (param_1 == -1000) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                return; // 0x47c731 ret
            }
            if (param_1 < 0) {
                // 0x47c823: scroll arrows (-1 = up, other negative = down)
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (param_1 == -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                        DAT_PencilRenderCore::ptr)(0, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                        DAT_PencilRenderCore::ptr)(1, 0);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
        LAB_0047c73a:
            DAT_ButtonDisabled::instance = 0;
            if ((((param_1 == 7) || (param_1 == 8))
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM))
                && (DAT_GameSynchronyState::instance.modemScrollbarCount == 0)) {
                DAT_ButtonDisabled::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                /*
                  Text:    7 => Host   8 => Join
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1,
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0x7f7f7f, 0x11, FALSE);
                return; // 0x47c7ab ret
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1,
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x11, FALSE);
                return; // 0x47c7f5 ret
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1,
                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x11, FALSE);
        }

    }
}
}
