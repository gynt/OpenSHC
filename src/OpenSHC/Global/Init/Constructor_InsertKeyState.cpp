#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Input/InsertKeyState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_InsertKeyState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C7C0
    void Init::Constructor_InsertKeyState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Input::InsertKeyState_Func::Constructor_InsertKeyState, DAT_InsertKeyState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_InsertKeyState));
        return;
    }

}
}
