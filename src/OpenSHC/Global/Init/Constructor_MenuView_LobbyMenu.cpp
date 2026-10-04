#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/LobbyMenu.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"

#include "OpenSHC/Globals/MenuView_LobbyMenu.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A2E0
    void Init::Constructor_MenuView_LobbyMenu()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_LobbyMenu::ptr)((UI::Enums::MenuViewType)20,
            MACRO_CALL(UI::MenuViews::LobbyMenu_Func::MenuView_LobbyMenu_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            MACRO_CALL(UI::MenuViews::LobbyMenu_Func::MenuView_LobbyMenu_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_LobbyMenu));
        return;
    }

}
}
