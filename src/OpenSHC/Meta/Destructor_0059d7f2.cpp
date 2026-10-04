#include "../Meta.func.hpp"

#include "OpenSHC/Globals/INTERNAL_Exception.hpp"
#include "OpenSHC/Globals/vftable.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D7F2
void Meta::Destructor_0059d7f2()
{
    _INTERNAL_Exception::instance = std::bad_alloc::vftable::instance;
    HoldStrong_lib::std::exception::~exception((exception*)INTERNAL_Exception::ptr);
}

}
