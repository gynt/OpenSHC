#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/Unknown33.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown33.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059A310
    void Init::Constructor_MenuView_Unknown33()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown33::ptr)(
            OpenSHC::UI::Enums::MVT_UNKNOWN_33,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::Unknown33_Func::MenuView_Unknown33_DoEveryFrame));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_Unknown33));
        return;
    }

}
}
