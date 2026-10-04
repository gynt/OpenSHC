#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TraderSettings.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_TraderSettings.hpp"
#include "OpenSHC/Globals/Menu_TraderSettings.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B960
    void Init::Constructor_MenuModal_TraderSettings()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TraderSettings::ptr)(
            UI::Enums::MMT_TRADER_SETTINGS, -1, -1, 600, 0x186, 0x200, 6,
            MACRO_CALL(UI::MenuModals::TraderSettings_Func::MenuModalRenderFunction_TraderSettings),
            Menu_TraderSettings::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_TraderSettings));
        return;
    }

}
}
