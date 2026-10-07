#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/ScenarioDescription.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_ScenarioDescription.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A610
    void Init::Constructor_MenuView_ScenarioDescription()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_ScenarioDescription::ptr)(
            UI::Enums::MVT_SCENARIO_DESCRIPTION,
            MACRO_CALL(UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_Prepare),
            MACRO_CALL(UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_DoInitial),
            MACRO_CALL(UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_ScenarioDescription));
        return;
    }

}
}
