#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/ScrollingHandler.func.hpp"

#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C7A0
    void Init::Constructor_ScrollingHandler()
    {
        MACRO_CALL_MEMBER(
            OpenSHC::UI::ScrollingHandler_Func::Constructor_ScrollingHandler, DAT_ScrollingHandler::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_ScrollingHandler));
        return;
    }

}
}
