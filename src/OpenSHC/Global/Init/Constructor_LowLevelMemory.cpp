#include "../../Global.func.hpp"

#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C880
    void Init::Constructor_LowLevelMemory()
    {
        MACRO_CALL(Global::Init_Func::Constructor_Empty)();
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_0059d590));
        return;
    }

}
}
