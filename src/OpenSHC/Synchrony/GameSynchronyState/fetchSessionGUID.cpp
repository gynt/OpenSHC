#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0047E010
    void GameSynchronyState::fetchSessionGUID(GUID* pGUID)
    {
        GUID* pGVar1;
        ushort uVar2;
        if ((this->scrollBarIndex != -1)
            && (this->scrollBarIndex + this->scrollBarItemOffset < this->DPLAY_SessionsCount)) {
            pGVar1 = this->DPLAY_SessionGUIDs[this->scrollBarIndex + this->scrollBarItemOffset];
            pGUID->Data1 = pGVar1->Data1;
            uVar2 = pGVar1->Data3;
            pGUID->Data2 = pGVar1->Data2;
            pGUID->Data3 = uVar2;
            *(undefined4*)pGUID->Data4 = *(undefined4*)pGVar1->Data4;
            *(undefined4*)(pGUID->Data4 + 4) = *(undefined4*)(pGVar1->Data4 + 4);
        }
    }

}
}
