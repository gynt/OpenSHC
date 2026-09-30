#include "../../IO.func.hpp"
#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A8D0
    void LowLevelMemory::fillMemory_setMemoryToValue_0x004()
    {
        int iVar1;
        int iVar2;
        int* piVar3;
        iVar1 = this->value;
        piVar3 = (int*)(this->destination);
        for (iVar2 = this->size; 0 < iVar2; iVar2 = iVar2 + -4) {
            *piVar3 = iVar1;
            piVar3 = piVar3 + 1;
        }
    }

}
}
