#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DebugDataAivStateUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DebugDataAivStateUnk.hpp"
#include "OpenSHC/Globals/Menu_DebugModals.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059C380
    void Init::Constructor_MenuModal_DebugDataAivStateUnk()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DebugDataAivStateUnk::ptr)(
            OpenSHC::UI::Enums::MMT_DEBUG_DATA_AIV_STATEUnk, 0x10b, 3, 400, 0xf2, 0xe,
            (int)((int)(COL_WHITE::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::DebugDataAivStateUnk_Func::MenuModalRenderFunction_DebugDataAivStateUnk),
            Menu_DebugModals::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_DebugDataAivStateUnk));
        return;
    }

}
}
