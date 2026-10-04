#include "../OS.func.hpp"

#include "HoldStrong_lib.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x005816EE
void OS::_srand(ulong param_1)
{
    _tiddata* p_Var1;
    p_Var1 = MACRO_CALL(HoldStrong_lib_Func::__getptd)();
    p_Var1->_holdrand = param_1;
    return;
}

}
