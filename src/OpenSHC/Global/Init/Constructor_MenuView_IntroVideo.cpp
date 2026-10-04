#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/IntroVideo.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_IntroVideo.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A850
    void Init::Constructor_MenuView_IntroVideo()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_IntroVideo::ptr)(UI::Enums::MVT_INTRO_VIDEO,
            MACRO_CALL(UI::MenuViews::IntroVideo_Func::MenuView_IntroVideo_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_OnlySetMenuXY),
            MACRO_CALL(UI::MenuViews::IntroVideo_Func::MenuView_IntroVideo_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_IntroVideo));
        return;
    }

}
}
