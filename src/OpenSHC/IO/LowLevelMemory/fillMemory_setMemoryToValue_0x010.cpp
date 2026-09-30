#include "../../IO.func.hpp"
#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A910
    void LowLevelMemory::fillMemory_setMemoryToValue_0x010()
    {
        int iVar1;
        iVar1 = this->value;
        for (; 0xf < this->size; this->size = this->size + -0x10) {
            *(int*)this->destination = iVar1;
            *(int*)((int)this->destination + 4) = iVar1;
            *(int*)((int)this->destination + 8) = iVar1;
            *(int*)((int)this->destination + 0xc) = iVar1;
            this->destination = (void*)((int)this->destination + 0x10);
        }
    }

}
}
