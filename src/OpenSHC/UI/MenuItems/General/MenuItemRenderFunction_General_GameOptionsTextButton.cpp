#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004934F0
        void General::MenuItemRenderFunction_General_GameOptionsTextButton(int param_1, ...)
        {
            int xParam;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            blendStrength = 0;
            xParam = (int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            yParam = DAT_ButtonY::instance + 7;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            /*
              the original pushes this call's arguments inside each arm and converges only on
              the inner call (`push 0x4a` at 0x493544), so the call was written out twice
             */
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1),
                    xParam, yParam, alignment, 0xc2f0eb, fontSize, keepOffsetX, blendStrength);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, param_1),
                    xParam, yParam, alignment, 0xccfaff, fontSize, keepOffsetX, blendStrength);
            }
        }

    }
}
}
