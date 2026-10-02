#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace Global {

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C8C0
    void Init::Constructor_ResourceManager()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::Constructor_ResourceManager, DAT_ResourceManager::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d5b0));
        return;
    }

}
}
