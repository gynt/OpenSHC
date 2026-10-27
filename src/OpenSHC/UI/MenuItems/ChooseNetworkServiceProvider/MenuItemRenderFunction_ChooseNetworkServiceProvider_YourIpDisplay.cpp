#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CF50
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_YourIpDisplay(
            int param_1, ...)
        {
            char local_68[100];
            if (DAT_GameSynchronyState::instance.displayYourIP != FALSE) {
                int yParam = DAT_ButtonY::instance + 5;
                /*
                  added by script: "Your IP:"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x24),
                    DAT_ButtonX::instance, yParam, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                if (DAT_GameSynchronyState::instance.lanOrWan != FALSE) {
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_68, "   %d.%d.%d.%d  /  %d.%d.%d.%d",
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b1,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b2,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b3,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b4,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b1,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b2,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b3,
                        (uint)DAT_GameSynchronyState::instance.wanIP.S_un.S_un_b.s_b4);
                } else {
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_68, "   %d.%d.%d.%d",
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b1,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b2,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b3,
                        (uint)DAT_GameSynchronyState::instance.lanIP.S_un.S_un_b.s_b4);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    local_68, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 5), OpenSHC::Text::TTA_LEFT,
                    0xccfaff, 0x12, TRUE, 0);
            };
        }

    }
}
}
