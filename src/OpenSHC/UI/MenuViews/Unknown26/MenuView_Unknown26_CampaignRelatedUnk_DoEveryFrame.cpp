#include "../Unknown26.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00b95954.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/INT_00ed3114.hpp"
#include "OpenSHC/Globals/INT_00ed3144.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004E1E70
        void Unknown26::MenuView_Unknown26_CampaignRelatedUnk_DoEveryFrame()
        {
            int iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar1 != 0) {
                if (DAT_MouseState::instance.rightClickStop != 0) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::StopCreditsPlaybackAndSounds)();
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::EndCreditsSegmentAndAdvanceToNext)();
                }
                MACRO_CALL(OpenSHC::Rendering_Func::ProcessCreditsScriptCommands)();
                if ((int)DAT_UnknownBinkIndex::instance < (int)DAT_UnknownBinkCount::instance) {
                    MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
                }
                INT_00ed3144::instance = INT_00ed3144::instance + 1;
                if (!((int)DAT_UnknownBinkIndex::instance < (int)DAT_UnknownBinkCount::instance)) {
                    if (DAT_GameCore::instance.missionNumber1to20 == 1000) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_INTRO_VIDEO, 0);
                        return;
                    }
                    if (DAT_GameCore::instance.section1066 == 2) {
                        if (0x15 < DAT_GameCore::instance.missionNumber1to20) {
                            if (INT_00ed3114::instance != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    OpenSHC::UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, 0);
                                return;
                            }
                            DAT_00b95954::instance = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_CREDITS, 0);
                            return;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, 0);
                        DAT_GameCore::instance.section1066 = 0;
                        return;
                    }
                    if (DAT_GameCore::instance.missionNumber1to20 == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_UNKNOWN_27_CAMPAIGNUnk, 0);
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
                }
            }
        }

    }
}
}
