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

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A730
    void Init::Constructor_MenuView_MainMenu()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_MainMenu::ptr)(
            OpenSHC::UI::Enums::MVT_MAIN_MENU,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_Prepare),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoInitial),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::MainMenu_Func::MenuView_MainMenu_DoEveryFrame));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_MainMenu));
        return;
    }

}
}
