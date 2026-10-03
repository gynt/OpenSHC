#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerEventOrInvasion.hpp"
#include "OpenSHC/Globals/Menu_TriggerEventOrInvasion.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BFA0
    void Init::Constructor_MenuModal_TriggerEventOrInvasion()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerEventOrInvasion::ptr)(
            OpenSHC::UI::Enums::MMT_TRIGGER_EVENT_OR_INVASION, -1, -1, 0x198, 0x90, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            Menu_TriggerEventOrInvasion::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_TriggerEventOrInvasion));
        return;
    }

}
}
