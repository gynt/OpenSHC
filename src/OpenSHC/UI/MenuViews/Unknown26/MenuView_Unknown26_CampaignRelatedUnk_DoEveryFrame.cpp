#include "../Unknown26.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_CreditsAfterCampaignEnd.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_CreditsScriptCommandCount.hpp"
#include "OpenSHC/Globals/DAT_CreditsScriptCommandIndex.hpp"
#include "OpenSHC/Globals/INT_00ed3114.hpp"
#include "OpenSHC/Globals/INT_00ed3144.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004E1E70
        void Unknown26::MenuView_MissionIntroSequence_DoEveryFrame()
        {
            int iVar1;
            iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar1 != 0) {
                if (DAT_MouseState::instance.rightClickStop != 0) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::StopCreditsPlaybackAndSounds)();
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::EndCreditsSegmentAndAdvanceToNext)();
                }
                MACRO_CALL(OpenSHC::Rendering_Func::ProcessCreditsScriptCommands)();
                if (DAT_CreditsScriptCommandIndex::instance < DAT_CreditsScriptCommandCount::instance) {
                    MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
                }
                INT_00ed3144::instance = INT_00ed3144::instance + 1;
                if (DAT_CreditsScriptCommandCount::instance <= DAT_CreditsScriptCommandIndex::instance) {
                    if (DAT_GameCore::instance.missionNumber == 1000) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_INTRO_VIDEO, 0);
                    }
                    if (DAT_GameCore::instance.section1066 == 2) {
                        if (DAT_GameCore::instance.missionNumber < 0x16) {
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_CAMPAIGN_MAP, 0);
                            DAT_GameCore::instance.section1066 = 0;
                        }
                        if (INT_00ed3114::instance == 0) {
                            DAT_CreditsAfterCampaignEnd::instance = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_CREDITS, 0);
                        }
                    } else if (DAT_GameCore::instance.missionNumber != 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CAMPAIGN_MAP, 0);
                }
            }
        }

    }
}
}
