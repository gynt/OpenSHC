#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TriggerEvent.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerEvent.hpp"
#include "OpenSHC/Globals/Menu_TriggerEvent.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BF60
    void Init::Constructor_MenuModal_TriggerEvent()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerEvent::ptr)(
            UI::Enums::MMT_TRIGGER_EVENT, -1, -1, 0x198, 0x1ba, 0x200, 6,
            MACRO_CALL(UI::MenuModals::TriggerEvent_Func::MenuModalRenderFunction_TriggerEvent),
            Menu_TriggerEvent::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_TriggerEvent));
        return;
    }

}
}
