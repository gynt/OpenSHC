#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ReceiveMapFrom.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_ReceiveMapFrom.hpp"
#include "OpenSHC/Globals/Menu_ReceiveMapFrom.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C060
    void Init::Constructor_MenuModal_ReceiveMapFrom()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ReceiveMapFrom::ptr)(
            OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM, -1, -1, 0x198, 200, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::ReceiveMapFrom_Func::MenuModalRenderFunction_ReceiveMapFrom),
            Menu_ReceiveMapFrom::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_ReceiveMapFromUnk));
        return;
    }

}
}
