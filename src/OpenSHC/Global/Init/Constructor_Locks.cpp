#include "../../Global.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Meta.func.hpp"

#include "OpenSHC/Globals/DAT_Locks.hpp"

#include "std/_Init_locks.func.hpp"
#include "../Init.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CCE6
    void Init::Constructor_Locks()
    {
MACRO_CALL_MEMBER(std::_Init_locks_Func::_Init_locks, (_Init_locks*)DAT_Locks::ptr)();
MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d7ca));
return;
    }

}
}
