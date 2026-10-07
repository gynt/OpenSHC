#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedChooseAvailableKeeps.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedChooseAvailableKeeps.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A520
    void Init::Constructor_MenuView_UnusedChooseAvailableKeeps()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedChooseAvailableKeeps::ptr)(
            UI::Enums::MVT_UNUSED_CHOOSE_AVAILABLE_KEEPS,
            MACRO_CALL(UI::MenuViews::UnusedChooseAvailableKeeps_Func::MenuView_UnusedChooseAvailableKeeps_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_ScreenToBlack),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::UnusedChooseAvailableKeeps_Func::MenuView_UnusedChooseAvailableKeeps_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuView_UnusedChooseAvailableKeeps));
        return;
    }

}
}
