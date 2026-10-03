#include "../../IO.func.hpp"
#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A890
    void LowLevelMemory::fillMemory_setMemoryToValue_0x002()
    {
        int iVar1;
        int iVar2;
        undefined2* puVar3;
        iVar1 = this->value;
        puVar3 = (undefined2*)(this->destination);
        for (iVar2 = this->size; 0 < iVar2; iVar2 = iVar2 + -2) {
            *puVar3 = (short)iVar1;
            puVar3 = puVar3 + 1;
        }
    }

}
}
