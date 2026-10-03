#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CB60
    void Init::Constructor_TribesState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::Constructor_TribesState, DAT_TribesState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d700));
        return;
    }

}
}
