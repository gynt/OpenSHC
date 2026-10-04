#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedCreateTimedMessageEvent.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedCreateTimedMessageEvent.hpp"
#include "OpenSHC/Globals/Menu_UnusedCreateTimedMessageEvent.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BA60
    void Init::Constructor_MenuModal_UnusedCreateTimedMessageEvent()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedCreateTimedMessageEvent::ptr)(
            UI::Enums::MMT_UNUSED_CREATE_TIMED_MESSAGE_EVENT, -1, -1, 700, 0x1fe, 0x200, 6,
            MACRO_CALL(UI::MenuModals::UnusedCreateTimedMessageEvent_Func::
                    MenuModalRenderFunction_UnusedCreateTimedMessageEvent),
            Menu_UnusedCreateTimedMessageEvent::ptr);
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuModal_UnusedCreateTimedMessageEvent));
        return;
    }

}
}
