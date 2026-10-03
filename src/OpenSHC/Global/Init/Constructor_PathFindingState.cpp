#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CB00
    void Init::Constructor_PathFindingState()
    {
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::Constructor_PathFindingState, DAT_PathFindingState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d6d0));
        return;
    }

}
}
