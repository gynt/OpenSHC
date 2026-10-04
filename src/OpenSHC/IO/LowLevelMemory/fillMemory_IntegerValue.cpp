#include "../../IO.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471860
    void LowLevelMemory::fillMemory_IntegerValue(size_t size, int value, void* destination)
    {
        this->size = size;
        this->value = value;
        this->destination = destination;
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_setMemoryToValue_0x004, this)();
    }

}
}
