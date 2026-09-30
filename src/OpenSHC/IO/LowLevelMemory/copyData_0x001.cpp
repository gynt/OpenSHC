#include "../../IO.func.hpp"
#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046AAF0
    void LowLevelMemory::copyData_0x001()
    {
        int iVar1;
        undefined1* puVar2;
        undefined1* puVar3;
        puVar2 = (undefined1*)(this->src);
        puVar3 = (undefined1*)(this->destination);
        for (iVar1 = this->size; 0 < iVar1; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
        }
    }

}
}
