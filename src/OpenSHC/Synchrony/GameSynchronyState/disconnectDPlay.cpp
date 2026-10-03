#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::GameMode;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E240
    void GameSynchronyState::disconnectDPlay()
    {
        void* pvVar1;
        int iVar2;
        DAT_MouseState::instance.waitCursorToggle = 1;
        MACRO_CALL(OpenSHC::UI::Helpers_Func::SetCursorDependingOnProgramState)();
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::clearSessionsList, this)();
        iVar2 = 0;
        if (0 < this->scrollBarItemCount) {
            do {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)((void*)(this->providerNames[iVar2]));
                pvVar1 = GlobalHandle(this->guids[iVar2]);
                GlobalUnlock(pvVar1);
                pvVar1 = GlobalHandle(this->guids[iVar2]);
                GlobalFree(pvVar1);
                this->providerNames[iVar2] = (WCHAR*)0x0;
                this->guids[iVar2] = (GUID*)0x0;
                iVar2 = iVar2 + 1;
            } while (iVar2 < this->scrollBarItemCount);
        }
        iVar2 = 0;
        this->scrollBarItemCount = 0;
        if (0 < this->modemScrollbarCount) {
            do {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->stringPointerArray[iVar2]);
                iVar2 = iVar2 + 1;
            } while (iVar2 < this->modemScrollbarCount);
        }
        this->modemScrollbarCount = 0;
        if (this->DPLAYX_4A != (IDirectPlay4A**)0x0) {
            ((IDirectPlay4A*)this->DPLAYX_4A)->CancelMessage(0, 0);
            ((IDirectPlay4A*)this->DPLAYX_4A)->DestroyPlayer(this->DPLAYX_PlayerHandle);
            ((IDirectPlay4A*)this->DPLAYX_4A)->Close();
            this->DPLAYX_4A = (IDirectPlay4A**)0x0;
        }
        if (this->DPLAYX_LOBBY != (IDirectPlayLobby3**)0x0) {
            ((IDirectPlayLobby3*)this->DPLAYX_LOBBY)->Release();
            this->DPLAYX_LOBBY = (IDirectPlayLobby3**)0x0;
        }
        if (this->DPLAYX_Connection != 0) {
            pvVar1 = GlobalHandle((void*)this->DPLAYX_Connection);
            GlobalUnlock(pvVar1);
            pvVar1 = GlobalHandle((void*)this->DPLAYX_Connection);
            GlobalFree(pvVar1);
            this->DPLAYX_Connection = (undefined4)((void*)0x0);
        }
        this->scrollBarItemCount = 0;
        this->currentGameMode = OpenSHC::Game::GM_SOLITARY;
        this->DAT_GameHalted = 0;
        this->syncStatus = 0;
        this->flag_0xbec = 0;
        this->useTCPIP = FALSE;
        this->quitGameVoteRelated = 0;
        this->saveRelated = 0;
        DAT_MouseState::instance.waitCursorToggle = 0;
    }

}
}
