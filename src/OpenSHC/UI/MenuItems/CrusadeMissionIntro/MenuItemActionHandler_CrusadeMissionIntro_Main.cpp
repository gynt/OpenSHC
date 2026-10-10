#include "../CrusadeMissionIntro.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::TrailType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8C10
        void CrusadeMissionIntro::MenuItemActionHandler_CrusadeMissionIntro_Main(int param_1, ...)
        {
            dword skirmishTrailMission;
            int missionCount;
            if (param_1 == 10) {
                if (DAT_GameCore::instance.field22_0x64 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                }
                /*
                  the original compares against the trail's own length inside each arm and
                  shares only the `jge` (0x4d8c65), so the bound travels with the mission
                 */
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    skirmishTrailMission = DAT_GameCore::instance.extremeTrailProgress;
                    missionCount = 20;
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    skirmishTrailMission = DAT_GameCore::instance.warchestTrailProgress;
                    missionCount = 30;
                } else {
                    skirmishTrailMission = DAT_GameCore::instance.skirmishTrailProgress;
                    missionCount = 50;
                }
                if ((int)skirmishTrailMission < missionCount) {
                    MACRO_CALL(OpenSHC::Game::Skirmish_Func::SetupSkirmishMode)(skirmishTrailMission);
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            }
            if (param_1 == 0xb) {
                if (DAT_GameCore::instance.field22_0x64 == 1) {
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CRUSADE_MAP, 0);
            }
        }
    }
}
}
