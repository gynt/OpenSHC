#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C860
    void Init::Constructor_RNGState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::Constructor_RNG, SEC_RNG::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d580));
        return;
    }

}
}
