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

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059BA60
    void Init::Constructor_MenuModal_UnusedCreateTimedMessageEvent()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal,
            MenuModal_UnusedCreateTimedMessageEvent::ptr)(OpenSHC::UI::Enums::MMT_UNUSED_CREATE_TIMED_MESSAGE_EVENT, -1,
            -1, 700, 0x1fe, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::UI::MenuModals::
                    UnusedCreateTimedMessageEvent_Func::MenuModalRenderFunction_UnusedCreateTimedMessageEvent),
            Menu_UnusedCreateTimedMessageEvent::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_UnusedCreateTimedMessageEvent));
        return;
    }

}
}
