#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandParameterLocation;
    using Commands::GameCommandParameterReadWrite;

    // FUNCTION: STRONGHOLDCRUSADER 0x004805D0
    void GameSynchronyState::serializeOrDeserializeCommandParameter(void* destination, size_t size,
        GameCommandParameterLocation srcSwitch, GameCommandParameterReadWrite destSwitch)
    {
        byte* _addr;
        byte* _src;
        if ((0 < (int)size) && (destination != (void*)0x0)) {
            if (srcSwitch == Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS) {
                _src = this->DAT_GameCommandFixedParameterLocation;
            } else {
                _src = &this->DAT_GameCommandArray[this->DAT_CurrentGameCommandID].parameters;
            }
            _addr = _src + this->DAT_CommandParameterOffset;
            if (destSwitch == Commands::GCPRW_SERIALIZE_INTO_PARAM_1) {
                _addr = (byte*)(destination);
                destination = _src + this->DAT_CommandParameterOffset;
            }
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                size, (void*)((int)(_addr)), destination);
            this->DAT_CommandParameterOffset = this->DAT_CommandParameterOffset + size;
        }
    }

}
}
