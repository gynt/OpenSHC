#include "../Helpers.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00440430
    HCURSOR Helpers::SetCursorDependingOnProgramState()
    {
        HICON__* _previousCursor;
        BOOLEnum BVar1;
        if (DAT_MouseState::instance.waitCursorToggle != 0) {
            _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(3);
            return _previousCursor;
        }
        if (((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_TextEditorState::instance.helpDialogVariant == 0))
            && (DAT_TextEditorState::instance.isDialogStateInitialized == 0)) {
            if (((uint)DAT_MouseState::instance.field68_0x1dc < 1000)
                || (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_INTRO_LOGOS)) {
                _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(1);
                return _previousCursor;
            }
            if ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                && (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_DELETE)) {
                if (DAT_TileMapState::instance.field194_0x554a20 == 0) {
                    _previousCursor
                        = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(2);
                    return _previousCursor;
                }
                _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(5);
                return _previousCursor;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(4);
                return _previousCursor;
            }
        }
        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (BVar1 == FALSE) {
            if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
                    && (DAT_GameCore::instance.missionNumber1to20 - 6U < 5))
                && ((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_INTRO
                    || ((((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_OUTRO
                              || (DAT_GameCore::instance.currentMenuViewType
                                  == OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION))
                             || (DAT_GameCore::instance.currentMenuViewType
                                 == OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_PICTURE))
                        || (DAT_GameCore::instance.currentMenuViewType
                            == OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_INTRO)))))) {
            LAB_0044050c:
                _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(6);
                return _previousCursor;
            }
        } else if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
            if (DAT_GameCore::instance.selectedLordTypes[DAT_GameSynchronyState::instance.currentPlayerSlotID] == 1) {
                _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(6);
                return _previousCursor;
            }
        } else if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION)
            && (DAT_GameCore::instance.missionNumber1to20 - 6U < 5))
            goto LAB_0044050c;
        _previousCursor = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::setCursor, DAT_MouseState::ptr)(0);
        return _previousCursor;
    }

}
}
