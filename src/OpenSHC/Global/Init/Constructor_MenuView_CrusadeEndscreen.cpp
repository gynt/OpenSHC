#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CrusadeEndscreen.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CrusadeEndscreen.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AA30
    void Init::Constructor_MenuView_CrusadeEndscreen()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CrusadeEndscreen::ptr)(
            UI::Enums::MVT_CRUSADE_ENDSCREEN,
            MACRO_CALL(UI::MenuViews::CrusadeEndscreen_Func::MenuView_CrusadeEndscreen_Prepare),
            MACRO_CALL(UI::MenuViews::CrusadeEndscreen_Func::MenuView_CrusadeEndscreen_DoInitial),
            MACRO_CALL(UI::MenuViews::CrusadeEndscreen_Func::MenuView_CrusadeEndscreen_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_CrusadeEndscreen));
        return;
    }

}
}
