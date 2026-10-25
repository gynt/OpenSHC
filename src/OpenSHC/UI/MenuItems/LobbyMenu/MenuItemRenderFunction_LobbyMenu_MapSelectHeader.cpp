#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00427740
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectHeader(int param_1, ...)
        {
            int yParam;
            int numInGroup;
            int iVar3;
            numInGroup = -1;
            iVar3 = 0;
            BOOLEnum BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if ((BVar1 == FALSE)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)) {
                /*
                  the original dispatches with a `sub eax, K; je` chain (0x427765), MSVC's
                  sparse switch, and the arm bodies sit in the order 2, 1, 0
                 */
                switch (param_1) {
                case 2:
                    numInGroup = 0x19a;
                    iVar3 = 2;
                    break;
                case 1:
                    numInGroup = 0x3d;
                    iVar3 = 2;
                    break;
                case 0:
                    numInGroup = 0x3e;
                    iVar3 = 8;
                    break;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                    DAT_PencilRenderCore::ptr)(FALSE, 1, (int)(DAT_ButtonBackgroundBlendStrength::instance));
                int iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar2 = (iVar2 / 32) + 0x20;
                yParam = DAT_ButtonY::instance + 5;
                iVar3 = DAT_ButtonX::instance + iVar3;
                BVar1 = FALSE;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, numInGroup),
                        iVar3, yParam, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13, BVar1, iVar2);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, numInGroup),
                        iVar3, yParam, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x13, BVar1, iVar2);
                }
            }
        }

    }
}
}
