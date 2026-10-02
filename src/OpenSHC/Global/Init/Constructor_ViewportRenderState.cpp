#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CA20
    void Init::Constructor_ViewportRenderState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::Constructor_ViewportRenderState,
            DAT_ViewportRenderState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d660));
        return;
    }

}
}
