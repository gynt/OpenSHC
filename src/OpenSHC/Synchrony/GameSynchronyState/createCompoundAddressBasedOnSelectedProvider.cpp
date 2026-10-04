#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/GlobalAllocFlag.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_IPX.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_MODEM.hpp"
#include "OpenSHC/Globals/GUID_DPSPGUID_TCPIP.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

#include "stdlib.h"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;
    using WindowsHelper::Enums::GlobalAllocFlag;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D6A0
    int GameSynchronyState::createCompoundAddressBasedOnSelectedProvider(LPVOID* pCompoundAddress, SIZE_T* param_2)
    {
        char cVar1;
        int iVar2;
        BOOLEnum BVar3;
        uint uVar4;
        int _status;
        void* _pMemNoLock;
        void* _pMem;
        void* pvVar5;
        char* pcVar6;
        char* pcVar7;
        int iVar8;
        DWORD DVar9;
        DWORD _pSize;
        uint local_2bc;
        SIZE_T* local_2b8;
        GUID local_2b4;
        int local_2a4;
        GUID* local_2a0;
        GUID local_29c;
        int aiStack_28c[8];
        GUID local_26c;
        char local_25c[200];
        char local_194[200];
        char local_cc[200];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&_pSize;
        local_2b8 = param_2;
        _pSize = 0;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::getGUIDForSelectedProvider, this)(
            (GUID*)&local_26c);
        BVar3 = MACRO_CALL(OS_Func::isEqualGUID)(&local_26c, (GUID*)GUID_DPSPGUID_MODEM::ptr);
        if (BVar3 == FALSE) {
            BVar3 = MACRO_CALL(OS_Func::isEqualGUID)(&local_26c, (GUID*)GUID_DPSPGUID_TCPIP::ptr);
            if (BVar3 == FALSE) {
                BVar3 = MACRO_CALL(OS_Func::isEqualGUID)(&local_26c, (GUID*)GUID_DPSPGUID_IPX::ptr);
                local_2a4 = 0x10;
                DVar9 = 1;
                if (BVar3 == FALSE) {
                    local_2b4.Data1 = 0x7d916c0;
                    local_2b4.Data2 = 0xe0af;
                    local_2b4.Data3 = 0x11cf;
                    local_2a0 = &local_26c;
                    local_2b4.Data4[0] = 0x9c;
                    local_2b4.Data4[1] = 0x4e;
                    local_2b4.Data4[2] = 0;
                    local_2b4.Data4[3] = 0xa0;
                    local_2b4.Data4[4] = 0xc9;
                    local_2b4.Data4[5] = 5;
                    local_2b4.Data4[6] = 0x42;
                    local_2b4.Data4[7] = 0x5e;
                } else {
                    local_2b4.Data1 = 0x7d916c0;
                    local_2b4.Data2 = 0xe0af;
                    local_2b4.Data3 = 0x11cf;
                    local_2b4.Data4[0] = 0x9c;
                    local_2b4.Data4[1] = 0x4e;
                    local_2b4.Data4[2] = 0;
                    local_2b4.Data4[3] = 0xa0;
                    local_2b4.Data4[4] = 0xc9;
                    local_2b4.Data4[5] = 5;
                    local_2b4.Data4[6] = 0x42;
                    local_2b4.Data4[7] = 0x5e;
                    local_2a0 = (GUID*)GUID_DPSPGUID_IPX::ptr;
                }
            } else {
                local_2b4.Data1 = 0x7d916c0;
                local_2b4.Data4[4] = 0xc9;
                local_2b4.Data4[5] = 5;
                local_2b4.Data4[6] = 0x42;
                local_2b4.Data4[7] = 0x5e;
                local_2b4.Data2 = 0xe0af;
                local_2b4.Data3 = 0x11cf;
                local_2b4.Data4[0] = 0x9c;
                local_2b4.Data4[1] = 0x4e;
                local_2b4.Data4[2] = 0;
                local_2b4.Data4[3] = 0xa0;
                local_2a4 = 0x10;
                local_2a0 = (GUID*)GUID_DPSPGUID_TCPIP::ptr;
                pcVar6 = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5);
                pcVar7 = local_cc;
                do {
                    cVar1 = *pcVar6;
                    *pcVar7 = cVar1;
                    pcVar6 = pcVar6 + 1;
                    pcVar7 = pcVar7 + 1;
                } while (cVar1 != '\0');
                local_29c.Data1 = 0xc4a54da0;
                local_29c.Data2 = 0xe0af;
                local_29c.Data3 = 0x11cf;
                pcVar7 = local_cc;
                local_29c.Data4[4] = 0xc9;
                local_29c.Data4[5] = 5;
                local_29c.Data4[6] = 0x42;
                local_29c.Data4[7] = 0x5e;
                local_29c.Data4[0] = 0x9c;
                local_29c.Data4[1] = 0x4e;
                local_29c.Data4[2] = 0;
                local_29c.Data4[3] = 0xa0;
                do {
                    cVar1 = *pcVar7;
                    pcVar7 = pcVar7 + 1;
                } while (cVar1 != '\0');
                DVar9 = 2;
                pcVar7 = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(6);
                uVar4 = atol(pcVar7);
                local_2bc = uVar4 & 0xffff;
                if ((short)uVar4 != 0) {
                    DVar9 = 3;
                }
            }
        } else {
            local_2b4.Data2 = 0xe0af;
            local_2b4.Data3 = 0x11cf;
            local_2b4.Data1 = 0x7d916c0;
            local_2b4.Data4[0] = 0x9c;
            local_2b4.Data4[1] = 0x4e;
            local_2b4.Data4[2] = 0;
            local_2b4.Data4[3] = 0xa0;
            local_2b4.Data4[4] = 0xc9;
            local_2b4.Data4[5] = 5;
            local_2b4.Data4[6] = 0x42;
            local_2b4.Data4[7] = 0x5e;
            local_2a4 = 0x10;
            local_2a0 = (GUID*)GUID_DPSPGUID_MODEM::ptr;
            pcVar6 = this->stringPointerArray[this->modemScrollbarIndex + this->modemScrollBarOffset];
            iVar8 = 1;
            pcVar7 = local_25c;
            do {
                cVar1 = *pcVar6;
                *pcVar7 = cVar1;
                pcVar6 = pcVar6 + 1;
                pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            pcVar7 = local_25c;
            do {
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            if (pcVar7 != local_25c + 1) {
                local_29c.Data1 = 0xf6dcc200;
                local_29c.Data2 = 0xa2fe;
                local_29c.Data3 = 0x11d0;
                pcVar7 = local_25c;
                local_29c.Data4[4] = 0xc9;
                local_29c.Data4[5] = 5;
                local_29c.Data4[6] = 0x42;
                local_29c.Data4[7] = 0x5e;
                local_29c.Data4[0] = 0x9c;
                local_29c.Data4[1] = 0x4f;
                local_29c.Data4[2] = 0;
                local_29c.Data4[3] = 0xa0;
                do {
                    cVar1 = *pcVar7;
                    pcVar7 = pcVar7 + 1;
                } while (cVar1 != '\0');
                iVar8 = 2;
            }
            pcVar6 = MACRO_CALL_MEMBER(
                Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(7);
            pcVar7 = local_194;
            do {
                cVar1 = *pcVar6;
                *pcVar7 = cVar1;
                pcVar6 = pcVar6 + 1;
                pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            iVar2 = iVar8 * 0x18;
            *(undefined4*)((int)&local_2b4 + iVar2) = 0x78ec89a0;
            *(undefined4*)((int)&local_2b4 + iVar2 + 4) = 0x11cfe0af;
            *(undefined4*)((int)&local_2b4 + iVar2 + 8) = 0xa0004e9c;
            *(undefined4*)((int)&local_2b4 + iVar2 + 0xc) = 0x5e4205c9;
            pcVar7 = local_194;
            do {
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            (&local_2a4)[iVar8 * 6] = (int)(pcVar7 + (1 - (int)(local_194 + 1)));
            *(char**)((int)&local_29c + iVar2 + -4) = local_194;
            DVar9 = iVar8 + 1;
        }
        _status = this->DPLAYX_LOBBY->CreateCompoundAddress((LPCDPCOMPOUNDADDRESSELEMENT)&local_2b4, DVar9, (void*)0x0, &_pSize);
        if (_status == -2005467106) {
            _pMemNoLock = GlobalAlloc(WindowsHelper::Enums::GAF_GHND, _pSize);
            _pMem = GlobalLock(_pMemNoLock);
            if (_pMem == (void*)0x0) {
                _status = DPERR_NOMEMORY;
            } else {
                _status = this->DPLAYX_LOBBY->CreateCompoundAddress((LPCDPCOMPOUNDADDRESSELEMENT)&local_2b4, DVar9, _pMem, &_pSize);
                if (_status < DP_OK) {
                    pvVar5 = GlobalHandle(_pMem);
                    GlobalUnlock(pvVar5);
                    pvVar5 = GlobalHandle(_pMem);
                    GlobalFree(pvVar5);
                } else {
                    *pCompoundAddress = _pMem;
                    *local_2b8 = _pSize;
                    _status = DP_OK;
                }
            }
        };
        return _status;
    }

}
}
