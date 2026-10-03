#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C8A0
    void Init::Constructor_GameCore()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::Constructor_GameCore, DAT_GameCore::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_GameCoreAndRendering));
        return;
    }

}
}
