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

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B960
    void Init::Constructor_MenuModal_TraderSettings()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TraderSettings::ptr)(
            OpenSHC::UI::Enums::MMT_TRADER_SETTINGS, -1, -1, 600, 0x186, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::TraderSettings_Func::MenuModalRenderFunction_TraderSettings),
            Menu_TraderSettings::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_TraderSettings));
        return;
    }

}
}
