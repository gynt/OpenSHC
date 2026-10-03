#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CBC0
    void Init::Constructor_AIVState()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AIVState_Func::Constructor_AIVState, DAT_AIVState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d730));
        return;
    }

}
}
