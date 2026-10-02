#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059CBE0
    void Init::Constructor_AICState()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::Constructor_AICState, DAT_AICState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d740));
        return;
    }

}
}
