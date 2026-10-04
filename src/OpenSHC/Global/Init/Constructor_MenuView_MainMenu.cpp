#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/MainMenu.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MainMenu.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A730
    void Init::Constructor_MenuView_MainMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MainMenu::ptr)(
            UI::Enums::MVT_MAIN_MENU,
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::MainMenu_Func::MenuView_MainMenu_Prepare),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoInitial),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_MainMenu));
        return;
    }

}
}
