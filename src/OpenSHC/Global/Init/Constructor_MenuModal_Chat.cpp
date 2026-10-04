#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/Chat.func.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_Chat.hpp"
#include "OpenSHC/Globals/Menu_Chat.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BD60
    void Init::Constructor_MenuModal_Chat()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Chat::ptr)((UI::Enums::MenuModalType)27,
            0x10, 0x10, 0x300, 0xe0, 0x200, (int)((int)(COL_BLACK::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::Chat_Func::MenuModalRenderFunction_Chat), Menu_Chat::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_Chat));
        return;
    }

}
}
