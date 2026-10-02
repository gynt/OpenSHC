#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C9F0
    void Init::Constructor_AlphaAndButtonSurface()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::Constructor_AlphaAndButtonSurface,
            AlphaAndButtonSurfaceObj::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_AlphaAndButtonSurface));
        return;
    }

}
}
