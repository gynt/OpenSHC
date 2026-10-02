#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059CAA0
    void Init::Constructor_MenuModalComposition3()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::Constructor_MenuModalComposition,
            DAT_MenuModalComposition3::ptr)(2);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d6a0));
        return;
    }

}
}
