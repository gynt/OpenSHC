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

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A250
    void Init::Constructor_MenuView_UnusedOldTitleMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedOldTitleMenu::ptr)(
            UI::Enums::MVT_UNUSED_OLD_TITLE_MENU,
            MACRO_CALL(UI::MenuViews::UnusedOldTitleMenu_Func::MenuView_UnusedOldTitleMenu_Prepare),
            MACRO_CALL(UI::MenuViews::UnusedOldTitleMenu_Func::MenuView_UnusedOldTitleMenu_DoInitial),
            MACRO_CALL(Global_Func::DoNothing));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_UnusedOldTitleMenu));
        return;
    }

}
}
