#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedOldTitleMenu.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedOldTitleMenu.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059A250
    void Init::Constructor_MenuView_UnusedOldTitleMenu()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedOldTitleMenu::ptr)(
            OpenSHC::UI::Enums::MVT_UNUSED_OLD_TITLE_MENU,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::UnusedOldTitleMenu_Func::MenuView_UnusedOldTitleMenu_Prepare),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::UnusedOldTitleMenu_Func::MenuView_UnusedOldTitleMenu_DoInitial),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_UnusedOldTitleMenu));
        return;
    }

}
}
