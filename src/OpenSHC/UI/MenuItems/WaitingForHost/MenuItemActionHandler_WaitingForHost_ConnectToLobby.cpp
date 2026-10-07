#include "../WaitingForHost.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DirectPlay/EnumSessionsFlagsEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DPLAY_CurrentSessionGUID.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/Menu_LobbyMenu.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using DirectPlay::EnumSessionsFlagsEnum;
        using DirectPlay::dplay::DPERR;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004914D0
        void WaitingForHost::MenuItemActionHandler_WaitingForHost_ConnectToLobby()
        {
            GUID* pGVar1;
            uint uVar2;
            HRESULT _status;
            int iVar3;
            int _sessionID;
            DPSESSIONDESC2 _enumDesc;
            uVar2 = MSVC_SecurityCookie::instance ^ (uint)&_enumDesc;
            DAT_GameSynchronyState::instance.scrollBarItemOffset = 0;
            if ((!DAT_GameSynchronyState::instance.multiplayerJoinStep)
                && (_status
                    = MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                        DAT_GameSynchronyState::ptr)(FALSE),
                    ~DP_OK < _status)) {
                DAT_GameSynchronyState::instance.multiplayerJoinStep = 1;
                DAT_GameSynchronyState::instance.unkEnumerationRelatedBool = false;
                DAT_GameSynchronyState::instance.scrollBarIndex = -1;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                    DAT_GameSynchronyState::ptr)(FALSE);
            }
            if (DAT_GameSynchronyState::instance.multiplayerJoinStep == 1) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::restartDPlaySessionEnumeration,
                    DAT_GameSynchronyState::ptr)(TRUE);
                for (_sessionID = 0; _sessionID < DAT_GameSynchronyState::instance.DPLAY_SessionsCount; _sessionID++) {
                    /*
                      todo:fixme: this comparison is probably for GameSpy and GameRanger, not   suitable for Steam,
                      we need to compare the session desc! Another reason to   store that info
                     */
                    iVar3 = MACRO_CALL(OS_Func::__wcsicmp)(L"Crusader",
                        (wchar_t*)((int)(DAT_GameSynchronyState::instance.DPLAY_SessionNames[_sessionID])));
                    if (!iVar3) {
                        pGVar1 = DAT_GameSynchronyState::instance.DPLAY_SessionGUIDs[_sessionID];
                        DPLAY_CurrentSessionGUID::instance.Data1 = pGVar1->Data1;
                        DPLAY_CurrentSessionGUID::instance.Data2 = pGVar1->Data2;
                        DPLAY_CurrentSessionGUID::instance.Data3 = pGVar1->Data3;
                        (*(int*)&DPLAY_CurrentSessionGUID::instance.Data4) = *(undefined4*)pGVar1->Data4;
                        (*(int*)((char*)&DPLAY_CurrentSessionGUID::instance.Data4 + 4)) = *(undefined4*)(pGVar1->Data4 + 4);
                        iVar3 = MACRO_CALL_MEMBER(
                            Synchrony::GameSynchronyState_Func::initializeDirectPlayAndCreateOrJoinSession,
                            DAT_GameSynchronyState::ptr)(TRUE);
                        if (-1 < iVar3) {
                            MACRO_CALL(OS_Func::_memset)(&_enumDesc, 0, (size_t)((int)(80)));
                            _enumDesc.guidApplication.Data1 = 0x1d5e2f48;
                            _enumDesc.guidApplication.Data4[0] = 0xae;
                            _enumDesc.guidApplication.Data4[1] = 0xd8;
                            _enumDesc.guidApplication.Data4[2] = 0xb1;
                            _enumDesc.guidApplication.Data4[3] = 0x24;
                            _enumDesc.guidApplication.Data4[4] = 0xda;
                            _enumDesc.guidApplication.Data4[5] = 0x9e;
                            _enumDesc.guidApplication.Data4[6] = 0x30;
                            _enumDesc.guidApplication.Data4[7] = 0x59;
                            _enumDesc.guidApplication.Data2 = 0xe8c0;
                            _enumDesc.guidApplication.Data3 = 0x49e5;
                            _enumDesc.dwSize = 80;
                            DAT_GameSynchronyState::instance.DPLAYX_4A->EnumSessions(&_enumDesc, 0,
                                MACRO_CALL(Synchrony_Func::EnumSessionsCallback_addSession_async), (void*)0x0,
                                DirectPlay::ESFE_ASYNC_ENUMERATION_STOP);
                            DAT_GameSynchronyState::instance.field225_0x106ee4 = 1;
                            DAT_GameCore::instance.menuTabToSwitchTo = (ActiveMenuTab)0x0;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_LOBBY_MENU, 0);
                            MACRO_CALL(Synchrony_Func::InitSkirmishLobbyData)();
                            Menu_LobbyMenu::instance.thousand = 0;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::waitForMultiplayerHost,
                                DAT_GameSynchronyState::ptr)();
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                            DAT_GameSynchronyState::instance.multiplayerJoinStep = 2;
                            /*
                              fixme: after this last statement we continue the while loop instead of   breaking
                             */
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                        }
                    }
                }
            };
            return;
        }

    }
}
}
