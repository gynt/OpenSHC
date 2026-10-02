#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CA40
    void Init::Constructor_MiniMapView()
    {
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::Constructor_MinimapViewState, DAT_MinimapViewState::ptr)();
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_0059d670));
        return;
    }

}
}
