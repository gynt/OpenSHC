#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/CreateOrTriggerInvasion.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerInvasion.hpp"
#include "OpenSHC/Globals/Menu_TriggerInvasion.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BF20
    void Init::Constructor_MenuModal_TriggerInvasion()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerInvasion::ptr)(
            UI::Enums::MMT_CREATE_OR_TRIGGER_INVASION, -1, -1, 700, 0x1b8, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::CreateOrTriggerInvasion_Func::MenuModalRenderFunction_CreateOrTriggerInvasion),
            Menu_TriggerInvasion::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_TriggerInvasion));
        return;
    }

}
}
