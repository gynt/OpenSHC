#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"

#include "OpenSHC/Globals/DAT_UnknownStopwatch.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C940
    void Init::Constructor_Stopwatch_Unknown()
    {
        MACRO_CALL_MEMBER(OpenSHC::Util::Timing::Stopwatch_Func::Constructor_Stopwatch, DAT_UnknownStopwatch::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_Stopwatch_Unknown));
        return;
    }

}
}
