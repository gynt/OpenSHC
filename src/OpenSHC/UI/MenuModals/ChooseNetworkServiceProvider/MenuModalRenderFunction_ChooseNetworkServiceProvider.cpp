#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0047C860
        void ChooseNetworkServiceProvider::MenuModalRenderFunction_ChooseNetworkServiceProvider(
            int x, int y, int width, int height)
        {
            /*
              added by script: "Service Providers"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4c, 6, x, y, width, height);
            if (DAT_GameSynchronyState::instance.kickedAtTime != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x, y + -0x3c, x + width, y + -0x12, 0x10);
                /*
                  added by script: "You Were Ejected!"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5c),
                    width / 2 + x, y + -0x32, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x10, FALSE, 0);
                if (5000 < timeGetTime() - DAT_GameSynchronyState::instance.kickedAtTime) {
                    DAT_GameSynchronyState::instance.kickedAtTime = 0;
                }
            }
            int listBottom = y + 0xa5;
            int listTop = y + 0x55;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, listTop, x + 0x1b8, listBottom);
            int listLeft = x + 0x27;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                listLeft, listTop - 1, x + 0x1cd, listTop - 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                listLeft, listBottom + 1, x + 0x1cd, listBottom + 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                listLeft, listTop, listLeft, listBottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1cd, listTop, x + 0x1cd, listBottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x1b8, listTop, x + 0x1b8, listBottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                int modemTop = y + 0x109;
                y = y + 0x159;
                int modemRight = x + 0x1b8;
                int modemLeft = x + 0x28;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    modemLeft, modemTop, modemRight, y);
                x = x + 0x1cd;
                modemLeft = modemLeft - 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    modemLeft, modemTop - 1, x, modemTop - 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    modemLeft, y + 1, x, y + 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    modemLeft, modemTop, modemLeft, y, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x, modemTop, x, y, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    modemRight, modemTop, modemRight, y, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            }
        }
    }
}
}
