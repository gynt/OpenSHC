#include "../MainMenu.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/g_mainMenuNextVideoSelector.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/g_mainMenuBackgroundGfxIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00424DA0
        void MainMenu::MenuView_MainMenu_DoEveryFrame()
        {
            char local_68[100];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_68;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                g_mainMenuBackgroundGfxIndex::instance = 1;
                if (DAT_BinkControlState::instance.binkObjPtrArray[0] != (HBINK)0x0) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(0);
                }
                goto LAB_00424eb2;
            }
            g_mainMenuBackgroundGfxIndex::instance = 0;
            if ((DAT_BinkControlState::instance.binkObjPtrArray[0] != (HBINK)0x0)
                || (DAT_GameCore::instance.menuViewToSwitchTo != DAT_GameCore::instance.currentMenuViewType))
                goto LAB_00424eb2;
            if (g_mainMenuNextVideoSelector::instance == 0) {
                g_mainMenuNextVideoSelector::instance = (int)SEC_RNG::instance.currentNumber1 % 3;
                if (0 < g_mainMenuNextVideoSelector::instance) {
                    g_mainMenuNextVideoSelector::instance = 0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                if (g_mainMenuNextVideoSelector::instance == 0)
                    goto LAB_00424e2e;
            } else {
                g_mainMenuNextVideoSelector::instance = 0;
            LAB_00424e2e:
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(
                    0, "richard_ambient.bik", 0, 0, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1fc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x16, 0);
            }
            if (g_mainMenuNextVideoSelector::instance == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(
                    0, "richard_swordswing.bik", 0, 0, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1fc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x16, 0);
            }
        LAB_00424eb2:
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(g_mainMenuBackgroundGfxIndex::instance,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[g_mainMenuBackgroundGfxIndex::instance].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[g_mainMenuBackgroundGfxIndex::instance].height)
                    / 2);
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_68, "V1.%d", 41);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(local_68,
                DAT_MenuHandlerState::instance.x + 2, (int)((int)(DAT_MenuHandlerState::instance.y + 588)),
                OpenSHC::Text::TTA_LEFT, 0x7caaaf, 0x13, FALSE, 0);
            ;
            return;
        }

    }
}
}
