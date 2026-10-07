#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/BuildMenu.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_BuildMenu.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A400
    void Init::Constructor_MenuView_BuildMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_BuildMenu::ptr)(UI::Enums::MVT_BUILD_MENU,
            MACRO_CALL(UI::MenuViews::BuildMenu_Func::MenuView_BuildMenu_Prepare),
            MACRO_CALL(UI::MenuViews::BuildMenu_Func::MenuView_BuildMenu_DoInitial),
            MACRO_CALL(UI::MenuViews::BuildMenu_Func::MenuView_BuildMenu_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_BuildMenu));
        return;
    }

}
}
