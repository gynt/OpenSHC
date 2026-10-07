#include "../../IO.func.hpp"
#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AB30
    void LowLevelMemory::copyData_0x010()
    {
        for (; 0xf < this->size; this->size = this->size + -0x10) {
            *(undefined4*)this->destination = *(undefined4*)this->src;
            *(undefined4*)((int)this->destination + 4) = *(undefined4*)((int)this->src + 4);
            *(undefined4*)((int)this->destination + 8) = *(undefined4*)((int)this->src + 8);
            *(undefined4*)((int)this->destination + 0xc) = *(undefined4*)((int)this->src + 0xc);
            this->src = (void*)((int)this->src + 0x10);
            this->destination = (void*)((int)this->destination + 0x10);
        }
    }

}
}
