#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
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
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042DBB0
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader(int param_1, ...)
        {
            int iVar1;
            char* textAddress;
            int yParam;
            int xParam;
            int numInGroup;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            numInGroup = -1;
            /*
              the original dispatches with a `sub eax, K; je` chain (0x42dbb8), MSVC's
              sparse switch, and the `case 1` body sits first
             */
            switch (param_1) {
            case 1:
                /*
                  Date
                 */
                numInGroup = 0x1c;
                break;
            case 0:
                /*
                  Name
                 */
                numInGroup = 0x1b;
                break;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                DAT_ButtonCurrentlyInteracting::instance, 1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (numInGroup != -1) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar1 = (iVar1 / 32) + 0x20;
                yParam = DAT_ButtonY::instance + 3;
                xParam = DAT_ButtonX::instance + 8;
                keepOffsetX = FALSE;
                fontSize = 0x12;
                alignment = OpenSHC::Text::TTA_LEFT;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, numInGroup),
                        xParam, yParam, alignment, 0xccfaff, fontSize, keepOffsetX, iVar1);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, numInGroup),
                        xParam, yParam, alignment, 0xffffff, fontSize, keepOffsetX, iVar1);
                }
            }
        }

    }
}
}
