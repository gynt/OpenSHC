#include "../Meta.func.hpp"

#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"

namespace OpenSHC {

/*
  WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
 */
// FUNCTION: STRONGHOLDCRUSADER 0x0059D790
void Meta::Destructor_BinkControlClass()
{
    MACRO_CALL_MEMBER(
        OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlaybackThunk, DAT_BinkControlState::ptr)();
}

}
