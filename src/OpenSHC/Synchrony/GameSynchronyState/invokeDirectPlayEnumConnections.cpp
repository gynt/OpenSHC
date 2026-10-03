#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"

#include "OpenSHC/Globals/GUID_CLSID_DirectPlay.hpp"
#include "OpenSHC/Globals/GUID_CLSID_DirectPlayLobby.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlay4.hpp"
#include "OpenSHC/Globals/GUID_IID_IDirectPlayLobby3.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      Source for DirectPlay API for example:
      https://github.com/lifthrasiir/w32api-directx-standalone/blob/master/include/dplay.h      --TheRedDaemon
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00487250
    void GameSynchronyState::invokeDirectPlayEnumConnections()
    {
        HRESULT HVar1;
        GUID** ppGVar2;
        int iVar3;
        IDirectPlay4A* _dplay4;
        IDirectPlayLobby3* _dplaylobby3;
        this->DPLAYX_4A = (IDirectPlay4A*)0x0;
        this->DPLAYX_LOBBY = (IDirectPlayLobby3*)0x0;
        _dplay4 = (IDirectPlay4A*)0x0;
        _dplaylobby3 = (IDirectPlayLobby3*)0x0;
        this->scrollBarItemCount = 3;
        HVar1 = CoCreateInstance(*GUID_CLSID_DirectPlay::ptr, (IUnknown*)0x0, 1, *GUID_IID_IDirectPlay4::ptr,
            (LPVOID*)&_dplay4);
        if (-1 < HVar1) {
            HVar1 = CoCreateInstance(*GUID_CLSID_DirectPlayLobby::ptr, (IUnknown*)0x0, 1,
                *GUID_IID_IDirectPlayLobby3::ptr, (LPVOID*)&_dplaylobby3);
            if (HVar1 < 0) {
                _dplay4->Release();
                return;
            }
            _dplay4->EnumConnections((GUID*)0x0, MACRO_CALL(OpenSHC::Synchrony_Func::EnumConnectionsCallback), (void*)0x0, 0);
            ppGVar2 = this->guids + 2;
            if (this->guids[2] == (GUID*)0x0) {
                iVar3 = 2;
                if (2 < this->scrollBarItemCount) {
                    do {
                        *ppGVar2 = ppGVar2[1];
                        ppGVar2[10] = ppGVar2[11];
                        iVar3 = iVar3 + 1;
                        ppGVar2 = ppGVar2 + 1;
                    } while (iVar3 < this->scrollBarItemCount);
                }
                this->scrollBarItemCount = this->scrollBarItemCount + -1;
            }
            ppGVar2 = this->guids;
            if (this->guids[1] == (GUID*)0x0) {
                iVar3 = 1;
                if (1 < this->scrollBarItemCount) {
                    do {
                        ppGVar2 = ppGVar2 + 1;
                        *ppGVar2 = ppGVar2[1];
                        ppGVar2[10] = ppGVar2[0xb];
                        iVar3 = iVar3 + 1;
                    } while (iVar3 < this->scrollBarItemCount);
                }
                this->scrollBarItemCount = this->scrollBarItemCount + -1;
            }
            ppGVar2 = this->guids;
            if (this->guids[0] == (GUID*)0x0) {
                iVar3 = 0;
                if (0 < this->scrollBarItemCount) {
                    do {
                        *ppGVar2 = ppGVar2[1];
                        ppGVar2[10] = ppGVar2[0xb];
                        iVar3 = iVar3 + 1;
                        ppGVar2 = ppGVar2 + 1;
                    } while (iVar3 < this->scrollBarItemCount);
                }
                this->scrollBarItemCount = this->scrollBarItemCount + -1;
            }
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::setMenuTypeBasedOnDirectPlayGUID, this)();
            this->DPLAYX_LOBBY = _dplaylobby3;
            _dplay4->Release();
        }
        return;
    }

}
}
