#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C9D0
    void Init::Constructor_SFXState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::Constructor_SFXState, DAT_SFXState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d630));
        return;
    }

}
}
