#include "../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/GlobalAllocFlag.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_IPX.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;
using WindowsHelper::Enums::GlobalAllocFlag;

// FUNCTION: STRONGHOLDCRUSADER 0x0047D5B0
BOOL __stdcall Synchrony::EnumConnectionsCallback(
    LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{
    WCHAR* pWVar1;
    WCHAR WVar2;
    ushort uVar3;
    BOOLEnum BVar4;
    WCHAR* pWVar5;
    WCHAR* pWVar6;
    void* hMem;
    GUID* pGVar7;
    WCHAR* pWVar7;
    int _index;
    _index = DAT_GameSynchronyState::instance.scrollBarItemCount;
    if (9 < DAT_GameSynchronyState::instance.scrollBarItemCount) {
        return 0;
    }
    BVar4 = MACRO_CALL(OS_Func::isEqualGUID)((GUID*)lpguidSP, (GUID*)GUID_DPSPGUID_TCPIP::ptr);
    if (BVar4 == FALSE) {
        BVar4 = MACRO_CALL(OS_Func::isEqualGUID)((GUID*)lpguidSP, (GUID*)GUID_DPSPGUID_IPX::ptr);
        if (BVar4 == FALSE) {
            BVar4 = MACRO_CALL(OS_Func::isEqualGUID)((GUID*)lpguidSP, (GUID*)GUID_DPSPGUID_MODEM::ptr);
            if (BVar4 == FALSE) {
                DAT_GameSynchronyState::instance.scrollBarItemCount = _index + 1;
            } else {
                _index = 2;
            }
        } else {
            _index = 1;
        }
    } else {
        _index = 0;
    }
    pWVar5 = lpName->lpszShortName;
    pWVar1 = pWVar5 + 1;
    do {
        WVar2 = *pWVar5;
        pWVar5 = pWVar5 + 1;
    } while (WVar2 != L'\0');
    pWVar6 = (WCHAR*)(MACRO_CALL(OS_Func::_malloc)(((int)pWVar5 - (int)pWVar1 >> 1) * 2 + 4));
    DAT_GameSynchronyState::instance.providerNames[_index] = pWVar6;
    pWVar7 = lpName->lpszShortName;
    do {
        WVar2 = *pWVar7;
        *pWVar6 = WVar2;
        pWVar7 = pWVar7 + 1;
        pWVar6 = pWVar6 + 1;
    } while (WVar2 != L'\0');
    hMem = GlobalAlloc(WindowsHelper::Enums::GAF_GHND, 0x10);
    pGVar7 = (GUID*)(GlobalLock(hMem));
    DAT_GameSynchronyState::instance.guids[_index] = (GUID*)pGVar7;
    if (pGVar7 != (GUID*)0x0) {
        pGVar7->Data1 = lpguidSP->Data1;
        uVar3 = lpguidSP->Data3;
        pGVar7->Data2 = lpguidSP->Data2;
        pGVar7->Data3 = uVar3;
        *(undefined4*)pGVar7->Data4 = *(undefined4*)lpguidSP->Data4;
        *(undefined4*)(pGVar7->Data4 + 4) = *(undefined4*)(lpguidSP->Data4 + 4);
    }
    return 1;
}

}
