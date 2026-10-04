#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047D4A0
    void GameSynchronyState::getGUIDForSelectedProvider(GUID* param_1)
    {
        GUID* pGVar1;
        if (this->useTCPIP != FALSE) {
            /*
              fixme: include check for steam provider
             */
            /* DirectPlay TCP/IP service provider {36E95EE0-8577-11CF-960C-0080C7534E82} */
            *(undefined4*)param_1 = 0x36e95ee0;
            *(undefined4*)((char*)param_1 + 4) = 0x11cf8577;
            *(undefined4*)((char*)param_1 + 8) = 0x80000c96;
            *(undefined4*)((char*)param_1 + 0xc) = 0x824e53c7;
        }
        pGVar1 = this->guids[this->selectedProviderIndex + this->scrollBarItemOffset];
        *(undefined4*)param_1 = *(undefined4*)pGVar1;
        *(undefined4*)((char*)param_1 + 0x4) = *(undefined4*)((char*)pGVar1 + 0x4);
        *(undefined4*)((char*)param_1 + 0x8) = *(undefined4*)((char*)pGVar1 + 0x8);
        *(undefined4*)((char*)param_1 + 0xc) = *(undefined4*)((char*)pGVar1 + 0xc);
    }

}
}
