#include "../../IO.func.hpp"
#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A850
    void LowLevelMemory::fillMemory_setMemoryToValue_0x001()
    {
        int iVar1;
        int iVar2;
        undefined1* puVar3;
        iVar1 = this->value;
        puVar3 = (undefined1*)(this->destination);
        for (iVar2 = this->size; 0 < iVar2; iVar2 = iVar2 + -1) {
            *puVar3 = (char)iVar1;
            puVar3 = puVar3 + 1;
        }
    }

}
}
