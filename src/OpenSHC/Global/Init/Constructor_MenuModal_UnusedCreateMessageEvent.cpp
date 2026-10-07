#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedCreateMessageEvent.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedCreateMessageEvent.hpp"
#include "OpenSHC/Globals/Menu_UnusedCreateMessageEvent.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BB60
    void Init::Constructor_MenuModal_UnusedCreateMessageEvent()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedCreateMessageEvent::ptr)(
            UI::Enums::MMT_UNUSED_CREATE_MESSAGE_EVENT, -1, -1, 700, 0x1cc, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(UI::MenuModals::UnusedCreateMessageEvent_Func::
                    MenuModalRenderFunction_UnusedCreateMessageEvent),
            Menu_UnusedCreateMessageEvent::ptr);
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuModal_UnusedCreateMessageEvent));
        return;
    }

}
}
