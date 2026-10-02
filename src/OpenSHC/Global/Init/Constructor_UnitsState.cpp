#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059CB20
    void Init::Constructor_UnitsState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::Constructor_UnitsState, DAT_UnitsState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d6e0));
        return;
    }

}
}
