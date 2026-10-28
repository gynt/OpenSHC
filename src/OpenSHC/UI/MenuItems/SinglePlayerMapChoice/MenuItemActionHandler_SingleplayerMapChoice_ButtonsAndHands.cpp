#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/g_mapDescriptionTextHeight.hpp"
#include "OpenSHC/Globals/DAT_MenuFadeState.hpp"
#include "OpenSHC/Globals/mapDescScrollOffset.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042D640
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_ButtonsAndHands(int param_1, ...)
        {
            int iVar1;
            MenuViewType menuID;
            // 0x42D642: `cmp [currentModalDialog],edx / jne ret`
            if (DAT_MenuTextInputState::instance.currentModalDialog != OpenSHC::UI::Enums::MMT_NO_MENU) {
                return;
            }
            DAT_StopHandlingMenuItems::instance = 0;
            if (param_1 < -100) {
                if (param_1 == -0x65) {
                    // 0x42D68B..0x42D6B9: scroll the description down by 14 px, clamped to the text height
                    iVar1 = g_mapDescriptionTextHeight::instance + -0xcc;
                    if (iVar1 <= mapDescScrollOffset::instance) {
                        return;
                    }
                    mapDescScrollOffset::instance = mapDescScrollOffset::instance + 0xe;
                    if (iVar1 < mapDescScrollOffset::instance) {
                        mapDescScrollOffset::instance = iVar1;
                    }
                    return;
                }
                if (param_1 == -1000) {
                    goto switchD_0042d6cf_caseD_2;
                }
                if (param_1 != -0x44c) {
                    return;  // other values below -100: nothing
                }
            switchD_0042d6cf_caseD_41:
                /*
                  Start game (0x42D6FC: `add eax,ecx / js ret` - signed)
                 */
                if (-1 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected) {
                    if ((DAT_MapMissionType::instance == 0) || (DAT_MapMissionType::instance == 3)) {
                        DAT_GameState::instance.mapAndTime.difficulty = 1;
                    }
                    MACRO_CALL(OpenSHC::UI::Actions_Func::LaunchStandaloneMapGame)(0);
                }
                return;
            switchD_0042d6cf_caseD_2:
                // back (case 2 and -1000)
                if (DAT_MapMissionType::instance == 0) {
                    menuID = OpenSHC::UI::Enums::MVT_MAIN_MENU;
                } else {
                    menuID = OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 10000);
                DWORD_00b95b1c::instance = timeGetTime();
                DAT_MenuFadeState::instance = 1;
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            } else {
                switch (param_1) {
                case 2:
                    goto switchD_0042d6cf_caseD_2;
                case 0x41:
                    goto switchD_0042d6cf_caseD_41;
                case 0x42:
                    /*
                      castle builder and landscape mode
                     */
                    if (DAT_MapMissionType::instance != 0) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 0;
                    }
                    break;
                case 0x43:
                    /*
                      unknown
                     */
                    if (DAT_MapMissionType::instance != 1) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 1;
                    }
                    break;
                case 0x44:
                    /*
                      siege mode
                     */
                    if (DAT_MapMissionType::instance != 2) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_MapMissionType::instance = 2;
                    }
                    break;
                case 0x45:
                    /*
                      difficulty button
                     */
                    if ((DAT_GameCore::instance.mapU4Int1_2 == 0) && (DAT_MapMissionType::instance != 0)) {
                        DAT_GameState::instance.mapAndTime.difficulty
                            = DAT_GameState::instance.mapAndTime.difficulty + 1;
                        if (4 <= DAT_GameState::instance.mapAndTime.difficulty) {
                            DAT_GameState::instance.mapAndTime.difficulty = 0;
                        }
                        MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadSiegeArmyFromSlot)(
                            DAT_GameState::instance.mapAndTime.difficulty);
                    }
                    break;
                case 0x4a:
                    /*
                      Advanced?
                     */
                    if (((DAT_GameCore::instance.mapU4Int1_2 == 0) && (DAT_MapMissionType::instance == 2))
                        && (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2)) {
                        DAT_SH1_SiegeAdvancedMode::instance = DAT_SH1_SiegeAdvancedMode::instance ^ 1;
                    }
                    break;
                case 0x4c:
                    if (DAT_MapMissionType::instance != 3) {
                        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                        DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        DAT_MapMissionType::instance = 3;
                    }
                    break;
                case 0x4d:
                    /*
                      "Attacking" or "Defending"
                     */
                    if ((DAT_MapMissionType::instance == 2) && (DAT_GameCore::instance.mapU4Int1_2 == 0)) {
                        // 0x42D841..0x42D85B: toggle attacker / defender
                        if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 2;
                        } else {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                            DAT_SH1_SiegeAdvancedMode::instance = 0;
                        }
                    }
                    break;
                case -100:
                    mapDescScrollOffset::instance = mapDescScrollOffset::instance + -0xe;
                    if (mapDescScrollOffset::instance < 0) {
                        mapDescScrollOffset::instance = 0;
                    }
                    break;
                case -0xb:
                    if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber + -0xd) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                            = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + 1;
                        MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                                MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                    }
                    break;
                case -10:
                    if (0 < DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                        DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                            = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + -1;
                        MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                                MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                            DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                    }
                }
            }
        }

    }
}
}
