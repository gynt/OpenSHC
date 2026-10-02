#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC00
    void Init::Constructor_LandscapeState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::Construct_LandscapeState, DAT_LandscapeState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d750));
        return;
    }

}
}
