#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/Credits.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Credits.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A7F0
    void Init::Constructor_MenuView_Credits()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_Credits::ptr)(
            UI::Enums::MVT_CREDITS,
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::Credits_Func::MenuView_Credits_Prepare),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::Credits_Func::MenuView_Credits_DoInitial),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::Credits_Func::MenuView_Credits_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_Credits));
        return;
    }

}
}
