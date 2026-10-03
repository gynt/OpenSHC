#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/IO/BitMapState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_BitMapState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C8E0
    void Init::Constructor_BitMapState()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::BitMapState_Func::Constructor_BitMapState, DAT_BitMapState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d5c0));
        return;
    }

}
}
