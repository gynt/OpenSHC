#include "../../Global.func.hpp"

#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C7E0
    void Init::Constructor_PencilRenderCoreObj()
    {
        MACRO_CALL(OpenSHC::Global::Init_Func::Constructor_Empty)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d540));
        return;
    }

}
}
