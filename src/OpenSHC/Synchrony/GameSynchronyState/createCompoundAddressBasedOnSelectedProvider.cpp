#include "../../Synchrony.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/GlobalAllocFlag.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/GUID_DPAID_INet.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Modem.hpp"
#include "OpenSHC/Globals/GUID_DPAID_Phone.hpp"
#include "OpenSHC/Globals/GUID_DPAID_ServiceProvider.hpp"
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
        DPCOMPOUNDADDRESSELEMENT local_2b4[3];
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
        if (BVar3) {
            local_2b4[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
            local_2b4[0].dwDataSize = 0x10;
            local_2b4[0].lpData = GUID_DPSPGUID_MODEM::ptr;
            pcVar6 = this->stringPointerArray[this->modemScrollbarIndex + this->modemScrollBarOffset];
            iVar8 = 1;
            pcVar7 = local_25c;
            do {
                cVar1 = *pcVar6;
                *pcVar7 = cVar1;
                pcVar6 = pcVar6 + iVar8;
                pcVar7 = pcVar7 + iVar8;
            } while (cVar1 != '\0');
            pcVar7 = local_25c;
            do {
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            if ((int)(pcVar7 - (local_25c + 1)) != 0) {
                local_2b4[1].guidDataType = GUID_DPAID_Modem::instance;
                pcVar7 = local_25c;
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
            local_2b4[iVar8].guidDataType = GUID_DPAID_Phone::instance;
            pcVar7 = local_194;
            do {
                cVar1 = *pcVar7;
                pcVar7 = pcVar7 + 1;
            } while (cVar1 != '\0');
            local_2b4[iVar8].dwDataSize = (int)(pcVar7 + (1 - (int)(local_194 + 1)));
            local_2b4[iVar8].lpData = local_194;
            DVar9 = iVar8 + 1;
        } else {
            BVar3 = MACRO_CALL(OS_Func::isEqualGUID)(&local_26c, (GUID*)GUID_DPSPGUID_TCPIP::ptr);
            if (BVar3) {
                local_2b4[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
                local_2b4[0].dwDataSize = 0x10;
                local_2b4[0].lpData = GUID_DPSPGUID_TCPIP::ptr;
                pcVar6 = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(5);
                pcVar7 = local_cc;
                do {
                    cVar1 = *pcVar6;
                    *pcVar7 = cVar1;
                    pcVar6 = pcVar6 + 1;
                    pcVar7 = pcVar7 + 1;
                } while (cVar1 != '\0');
                local_2b4[1].guidDataType = GUID_DPAID_INet::instance;
                pcVar7 = local_cc;
                do {
                    cVar1 = *pcVar7;
                    pcVar7 = pcVar7 + 1;
                } while (cVar1 != '\0');
                local_2b4[1].dwDataSize = (int)(pcVar7 + (1 - (int)(local_cc + 1)));
                local_2b4[1].lpData = local_cc;
                DVar9 = 2;
                pcVar7 = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(6);
                uVar4 = atol(pcVar7);
                local_2bc = uVar4 & 0xffff;
                if ((ushort)uVar4 != 0) {
                    local_2b4[2].dwDataSize = 2;
                    local_2b4[2].lpData = &local_2bc;
                    DVar9 = 3;
                }
            } else {
                BVar3 = MACRO_CALL(OS_Func::isEqualGUID)(&local_26c, (GUID*)GUID_DPSPGUID_IPX::ptr);
                local_2b4[0].dwDataSize = 0x10;
                DVar9 = 1;
                if (BVar3) {
                    local_2b4[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
                    local_2b4[0].lpData = GUID_DPSPGUID_IPX::ptr;
                } else {
                    local_2b4[0].guidDataType = GUID_DPAID_ServiceProvider::instance;
                    local_2b4[0].lpData = &local_26c;
                }
            }
        }
        _status = this->DPLAYX_LOBBY->CreateCompoundAddress(local_2b4, DVar9, (void*)0x0, &_pSize);
        if (_status == -2005467106) {
            _pMemNoLock = GlobalAlloc(WindowsHelper::Enums::GAF_GHND, _pSize);
            _pMem = GlobalLock(_pMemNoLock);
            if (_pMem == (void*)0x0) {
                _status = DPERR_NOMEMORY;
            } else {
                _status = this->DPLAYX_LOBBY->CreateCompoundAddress(local_2b4, DVar9, _pMem, &_pSize);
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
