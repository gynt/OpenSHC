#include "../FindingNetworkSessions.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Multiplayer/FindingNetworkSessions_ButtonParameters.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DPLAY_CurrentSessionGUID.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using DirectPlay::EnumSessionsFlagsEnum;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using UI::Multiplayer::FindingNetworkSessions_ButtonParameters;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00490D90
        void FindingNetworkSessions::MenuItemActionHandler_FindingNetworkSessions_Buttons(
            FindingNetworkSessions_ButtonParameters param_1, ...)
        {
            uint uVar1;
            int _status;
            DPSESSIONDESC2 local_54;
            uVar1 = MSVC_SecurityCookie::instance ^ (uint)&local_54;
            if (param_1 < ((FindingNetworkSessions_ButtonParameters)0x80000000)) {
                if (param_1 != ((FindingNetworkSessions_ButtonParameters)3)) {
                    if ((param_1 == UI::Multiplayer::FNSBP_JOIN)
                        && (DAT_GameSynchronyState::instance.scrollBarIndex != -1)) {
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::fetchSessionGUID,
                            DAT_GameSynchronyState::ptr)((GUID*)DPLAY_CurrentSessionGUID::ptr);
                        _status = MACRO_CALL_MEMBER(
                            Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                            DAT_GameSynchronyState::ptr)(TRUE);
                        if (-1 < _status) {
                            MACRO_CALL(OS_Func::_memset)(&local_54, 0, 0x50);
                            local_54.guidApplication.Data1 = 0x1d5e2f48;
                            local_54.guidApplication.Data2 = 0xe8c0;
                            local_54.guidApplication.Data3 = 0x49e5;
                            memcpy(local_54.guidApplication.Data4 + 4, "ڞ0Y", 4);
                            local_54.dwSize = 0x50;
                            local_54.guidApplication.Data4[0] = 0xae;
                            local_54.guidApplication.Data4[1] = 0xd8;
                            local_54.guidApplication.Data4[2] = 0xb1;
                            local_54.guidApplication.Data4[3] = 0x24;
                            DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&local_54, 0,
                                MACRO_CALL(Synchrony_Func::EnumSessionsCallback_addSession_async), (void*)0x0,
                                DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                            DAT_GameSynchronyState::instance.field225_0x106ee4 = 1;
                            DAT_GameCore::instance.menuTabToSwitchTo.tabType = ((BuildingsAndStatusMenuTabType)0);
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_LOBBY_MENU, 0);
                            MACRO_CALL(Synchrony_Func::InitSkirmishLobbyData)();
                            Menu_LobbyMenu::instance.thousand = 0;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::waitForMultiplayerHost,
                                DAT_GameSynchronyState::ptr)();
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                            ;
                            return;
                        }
                        /*
                          something went wrong, abort in a very weird way
                         */
                        MACRO_CALL(OS_Func::_memset)(&local_54, 0, 0x50);
                        local_54.guidApplication.Data2 = 0xe8c0;
                        local_54.guidApplication.Data3 = 0x49e5;
                        local_54.guidApplication.Data1 = 0x1d5e2f48;
                        local_54.dwSize = 0x50;
                        local_54.guidApplication.Data4[0] = 0xae;
                        local_54.guidApplication.Data4[1] = 0xd8;
                        local_54.guidApplication.Data4[2] = 0xb1;
                        local_54.guidApplication.Data4[3] = 0x24;
                        local_54.guidApplication.Data4[4] = 0xda;
                        local_54.guidApplication.Data4[5] = 0x9e;
                        local_54.guidApplication.Data4[6] = 0x30;
                        local_54.guidApplication.Data4[7] = 0x59;
                        if (DAT_GameSynchronyState::instance.DPLAYX_4A != (IDirectPlay4A*)0x0) {
                            DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&local_54, 0,
                                MACRO_CALL(Synchrony_Func::EnumSessionsCallback_addSession_async), (void*)0x0,
                                DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
                        }
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::disconnectDPlay,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby,
                            DAT_GameSynchronyState::ptr)();
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(
                            UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, FALSE);
                        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                        ;
                        return;
                    }
                    goto LAB_Return;
                }
            } else {
                if (param_1 == ((FindingNetworkSessions_ButtonParameters)0xffffffff)) {
                    if (0 < DAT_GameSynchronyState::instance.scrollBarItemOffset) {
                        DAT_GameSynchronyState::instance.scrollBarItemOffset
                            = DAT_GameSynchronyState::instance.scrollBarItemOffset + -1;
                        ;
                        return;
                    }
                    goto LAB_Return;
                }
                if (param_1 != ((FindingNetworkSessions_ButtonParameters)0xffffd8f0)) {
                    if ((param_1 == ((FindingNetworkSessions_ButtonParameters)0xfffffffe))
                        && (DAT_GameSynchronyState::instance.scrollBarItemOffset
                            < DAT_GameSynchronyState::instance.DPLAY_SessionsCount + -10)) {
                        DAT_GameSynchronyState::instance.scrollBarItemOffset
                            = DAT_GameSynchronyState::instance.scrollBarItemOffset + 1;
                        ;
                        return;
                    }
                    goto LAB_Return;
                }
            }
            MACRO_CALL(OS_Func::_memset)(&local_54, 0, 0x50);
            local_54.guidApplication.Data2 = 0xe8c0;
            local_54.guidApplication.Data3 = 0x49e5;
            local_54.guidApplication.Data1 = 0x1d5e2f48;
            local_54.dwSize = 0x50;
            local_54.guidApplication.Data4[0] = 0xae;
            local_54.guidApplication.Data4[1] = 0xd8;
            local_54.guidApplication.Data4[2] = 0xb1;
            local_54.guidApplication.Data4[3] = 0x24;
            local_54.guidApplication.Data4[4] = 0xda;
            local_54.guidApplication.Data4[5] = 0x9e;
            local_54.guidApplication.Data4[6] = 0x30;
            local_54.guidApplication.Data4[7] = 0x59;
            if (DAT_GameSynchronyState::instance.DPLAYX_4A != (IDirectPlay4A*)0x0) {
                DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&local_54, 0,
                    MACRO_CALL(Synchrony_Func::EnumSessionsCallback_addSession_async), (void*)0x0,
                    DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
            }
            MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::disconnectDPlay, DAT_GameSynchronyState::ptr)();
            MACRO_CALL_MEMBER(
                Synchrony::GameSynchronyState_Func::initializeMultiplayerLobby, DAT_GameSynchronyState::ptr)();
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, FALSE);
        LAB_Return:;
            return;
        }

    }
}
}
