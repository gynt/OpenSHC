#include "../IntroLogos.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOLEnum_00b98404.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_IntroBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_IntroStep.hpp"
#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_IntroTransitionStep.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00424990
        void IntroLogos::MenuItemActionHandler_IntroLogos_General(int unused, ...)
        {
            if (DAT_MouseState::instance.leftClickStart) {
                BOOLEnum_00b98404::instance = TRUE;
            }
            if ((DAT_MouseState::instance.draggingStopped != FALSE) && (BOOLEnum_00b98404::instance != FALSE)) {
                BOOLEnum_00b98404::instance = FALSE;
                if (!DAT_IntroStep::instance) {
                    DAT_IntroTransitionStep::instance = 0;
                    DAT_IntroBlendStrength::instance = 0;
                    DAT_IntroStep::instance = 1;
                    DAT_IntroTimestamp::instance = timeGetTime();
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_INTRO_LOGOS, 0);
                }
                if (DAT_IntroStep::instance == 1) {
                    DAT_IntroTransitionStep::instance = 0;
                    DAT_IntroBlendStrength::instance = 0;
                    DAT_IntroStep::instance = 2;
                    DAT_IntroTimestamp::instance = timeGetTime();
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        UI::Enums::MVT_INTRO_LOGOS, 0);
                }
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_INTRO_VIDEO, 0);
            }
        }

    }
}
}
