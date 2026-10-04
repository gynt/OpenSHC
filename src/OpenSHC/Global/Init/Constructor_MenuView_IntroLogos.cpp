#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/IntroLogos.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_IntroLogos.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A190
    void Init::Constructor_MenuView_IntroLogos()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_IntroLogos::ptr)(
            UI::Enums::MVT_INTRO_LOGOS,
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::IntroLogos_Func::MenuView_IntroLogos_Prepare),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::IntroLogos_Func::MenuView_IntroLogos_DoInitial),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::IntroLogos_Func::MenuView_IntroLogos_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_IntroLogos));
        return;
    }

}
}
