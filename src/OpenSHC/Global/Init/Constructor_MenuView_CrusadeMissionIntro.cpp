#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CrusadeMissionIntro.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CrusadeMissionIntro.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A9A0
    void Init::Constructor_MenuView_CrusadeMissionIntro()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CrusadeMissionIntro::ptr)(
            UI::Enums::MVT_CRUSADE_MISSION_INTRO,
            MACRO_CALL(UI::MenuViews::CrusadeMissionIntro_Func::MenuView_CrusadeMissionIntro_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_CrusadeAndRankMenu),
            MACRO_CALL(UI::MenuViews::CrusadeMissionIntro_Func::MenuView_CrusadeMissionIntro_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_CrusadeMissionIntro));
        return;
    }

}
}
