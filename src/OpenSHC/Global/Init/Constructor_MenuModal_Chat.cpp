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

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059BD60
    void Init::Constructor_MenuModal_Chat()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Chat::ptr)(
            (OpenSHC::UI::Enums::MenuModalType)27, 0x10, 0x10, 0x300, 0xe0, 0x200,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::Chat_Func::MenuModalRenderFunction_Chat),
            Menu_Chat::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_Chat));
        return;
    }

}
}
