#include "../Meta.func.hpp"

#include "OpenSHC/Globals/INTERNAL_LocaleState.hpp"

#include "HoldStrong_lib/std/locale/_Locimp.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7D4
void Meta::Destructor_0059d7d4()
{
    MACRO_CALL_MEMBER(HoldStrong_lib::std::locale::_Locimp_Func::meth_0x467730, (_Locimp*)INTERNAL_LocaleState::ptr)();
}

}
