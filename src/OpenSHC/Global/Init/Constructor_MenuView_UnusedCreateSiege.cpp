#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedCreateSiege.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedCreateSiege.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A580
    void Init::Constructor_MenuView_UnusedCreateSiege()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedCreateSiege::ptr)(
            UI::Enums::MVT_UNUSED_CREATE_SIEGE,
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::UnusedCreateSiege_Func::MenuView_UnusedCreateSiege_Prepare),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::UnusedCreateSiege_Func::MenuView_UnusedCreateSiege_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_UnusedCreateSiege));
        return;
    }

}
}
