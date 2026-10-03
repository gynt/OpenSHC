#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/IO/DecoderState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_DecoderState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C980
    void Init::Constructor_DecoderState()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::DecoderState_Func::Constructor_DecoderState, DAT_DecoderState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_Decoder));
        return;
    }

}
}
