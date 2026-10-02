#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/CreditsScroll.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_CreditsScroll.hpp"
#include "OpenSHC/Globals/Menu_Credits.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059BDA0
    void Init::Constructor_MenuModal_CreditsScroll()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_CreditsScroll::ptr)(
            OpenSHC::UI::Enums::MMT_CREDITS_SCROLL, 400, 0, 400, 600, 0x40,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::CreditsScroll_Func::MenuModalRenderFunction_CreditsScroll),
            Menu_Credits::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_CreditsScroll));
        return;
    }

}
}
