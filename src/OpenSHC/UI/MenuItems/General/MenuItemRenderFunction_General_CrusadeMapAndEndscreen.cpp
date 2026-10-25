#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_SkirmishTrailRelated1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed2bdc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8DF0
        void General::MenuItemRenderFunction_General_CrusadeMapAndEndscreen(int param_1, ...)
        {
            char* textAddress;
            int xParam;
            if (param_1 == 1000) {
                INT_00ed2bdc::instance = 0;
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    INT_00ed2bdc::instance = 1;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_SkirmishTrailRelated1::instance, (int)(DAT_ButtonX::instance + 0x35),
                    (int)(DAT_ButtonY::instance + 0x62), OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0xf, FALSE, 0);
                if (INT_00ed2bdc::instance != 0) {
                    int yParam = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x247;
                    xParam = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                    /*
                      added by script: "Skip Current Mission"
                     */
                    textAddress = MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_CHEATS, (int)((int)DAT_SkirmishTrailRelated1::instance <= 0));
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        textAddress, xParam, yParam, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 0);
                }
            } else if (param_1 == 10 || param_1 == 0xb || param_1 == 99) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
        }

    }
}
}
