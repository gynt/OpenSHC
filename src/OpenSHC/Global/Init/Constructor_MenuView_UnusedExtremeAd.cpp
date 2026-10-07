#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedExtremeAd.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedExtremeAd.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A6A0
    void Init::Constructor_MenuView_UnusedExtremeAd()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedExtremeAd::ptr)(
            UI::Enums::MVT_UNUSED_EXTREME_AD,
            MACRO_CALL(UI::MenuViews::UnusedExtremeAd_Func::MenuView_UnusedExtremeAd_Prepare),
            MACRO_CALL(UI::MenuViews::UnusedExtremeAd_Func::MenuView_UnusedExtremeAd_DoInitial),
            MACRO_CALL(UI::MenuViews::UnusedExtremeAd_Func::MenuView_UnusedExtremeAd_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_UnusedExtremeAd));
        return;
    }

}
}
