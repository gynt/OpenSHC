#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/BuildingAndStatusMenu.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_BuildingAndStatusMenu.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A430
    void Init::Constructor_MenuView_BuildingAndStatusMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_BuildingAndStatusMenu::ptr)(
            UI::Enums::MVT_BUILDING_AND_STATUS_MENU,
            MACRO_CALL(UI::MenuViews::BuildingAndStatusMenu_Func::MenuView_BuildingAndStatusMenu_Prepare),
            MACRO_CALL(UI::MenuViews::BuildingAndStatusMenu_Func::MenuView_BuildingAndStatusMenu_DoInitial),
            MACRO_CALL(UI::MenuViews::BuildingAndStatusMenu_Func::MenuView_BuildingAndStatusMenu_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuView_BuildingAndStatusMenu));
        return;
    }

}
}
