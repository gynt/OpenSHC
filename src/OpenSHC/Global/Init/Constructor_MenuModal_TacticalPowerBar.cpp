#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TacticalPowerBar.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModa_TacticalPowerBar.hpp"
#include "OpenSHC/Globals/Menu_TacticalPowerBar.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C340
    void Init::Constructor_MenuModal_TacticalPowerBar()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModa_TacticalPowerBar::ptr)(
            UI::Enums::MMT_TACTICAL_POWER_BAR, 0x2e9, 0x32, 0x37, 0x140, 0x1000,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::TacticalPowerBar_Func::MenuModalRenderFunction_TacticalPowerBar),
            Menu_TacticalPowerBar::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_TacticalPowerBar));
        return;
    }

}
}
