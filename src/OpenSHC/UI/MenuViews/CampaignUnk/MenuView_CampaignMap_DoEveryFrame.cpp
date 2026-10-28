#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuViews/CampaignUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace CampaignUnk {

            using OpenSHC::UI::Enums::MenuViewType;

            // FUNCTION: STRONGHOLDCRUSADER 0x004D6EF0
            void MenuView_CampaignMap_DoEveryFrame()
            {
                if (MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)() == 0) {
                    return;
                }
                if (DAT_GameCore::instance.missionNumber == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MISSION_INTRO_SEQUENCE, 0);
            }

        }
    }
}
}
