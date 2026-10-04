#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/GameLost.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_GameLost.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A670
    void Init::Constructor_MenuView_GameLost()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_GameLost::ptr)(
            UI::Enums::MVT_GAME_LOSTUnk,
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::GameLost_Func::MenuView_GameLost_Prepare),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::GameLost_Func::MenuView_GameLost_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_GameLost));
        return;
    }

}
}
