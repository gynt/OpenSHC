#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C760
    void Init::Constructor_MouseState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::Constructor_MouseState, DAT_MouseState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d500));
        return;
    }

}
}
