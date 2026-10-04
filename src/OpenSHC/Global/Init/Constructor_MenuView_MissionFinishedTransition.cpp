#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/MissionFinishedTransition.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MissionFinishedTransition.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A640
    void Init::Constructor_MenuView_MissionFinishedTransition()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MissionFinishedTransition::ptr)(
            UI::Enums::MVT_MISSION_FINISHED_TRANSITION,
            MACRO_CALL(UI::MenuViews::MissionFinishedTransition_Func::MenuView_MissionFinishedTransition_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::MissionFinishedTransition_Func::MenuView_MissionFinishedTransition_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Global::Init_Func::Destructor_MenuView_MissionFinishedTransition));
        return;
    }

}
}
