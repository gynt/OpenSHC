#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ChooseNetworkServiceProvider.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ChooseNetworkServiceProvider.hpp"
#include "OpenSHC/Globals/Menu_ChooseNetworkServiceProvider.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B7E0
    void Init::Constructor_MenuModal_ChooseNetworkServiceProvider()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal,
            MenuModal_ChooseNetworkServiceProvider::ptr)(OpenSHC::UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, 0x96,
            0x50, 500, 0x198, 0x200, (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::UI::MenuModals::
                    ChooseNetworkServiceProvider_Func::MenuModalRenderFunction_ChooseNetworkServiceProvider),
            Menu_ChooseNetworkServiceProvider::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_ChooseNetworkServiceProvider));
        return;
    }

}
}
