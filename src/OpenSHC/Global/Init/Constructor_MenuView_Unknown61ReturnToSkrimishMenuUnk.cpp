#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/Unknown61ReturnToSkrimishMenuUnk.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown61ReturnToSkrimishMenuUnk.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A340
    void Init::Constructor_MenuView_Unknown61ReturnToSkrimishMenuUnk()
    {
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown61ReturnToSkrimishMenuUnk::ptr)(
            OpenSHC::UI::Enums::MVT_UNKNOWN_61_RETURN_TO_SKIRMISH_MENUUnk,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::UI::MenuViews::
                    Unknown61ReturnToSkrimishMenuUnk_Func::MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::UI::MenuViews::
                    Unknown61ReturnToSkrimishMenuUnk_Func::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoInitial),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::UI::MenuViews::
                    Unknown61ReturnToSkrimishMenuUnk_Func::MenuView_Unknown61ReturnToSkrimishMenuUnk_DoEveryFrame));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_Unknown61ReturnToSkrimishMenuUnk));
        return;
    }

}
}
