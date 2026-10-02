#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Input/ModifierKeyState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C780
    void Init::Constructor_ModifierKeyState()
    {
        MACRO_CALL_MEMBER(
            OpenSHC::Input::ModifierKeyState_Func::Constructor_ModifierKeyState, DAT_ModifierKeyState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d510));
        return;
    }

}
}
