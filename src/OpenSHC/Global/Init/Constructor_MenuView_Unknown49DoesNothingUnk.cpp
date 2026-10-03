#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_Unknown49DoesNothingUnk.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A3A0
    void Init::Constructor_MenuView_Unknown49DoesNothingUnk()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_Unknown49DoesNothingUnk::ptr)(
            OpenSHC::UI::Enums::MVT_UNKNOWN_49_DOES_NOTHINGUnk,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_Unknown49DoesNothingUnk));
        return;
    }

}
}
