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

    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059A610
    void Init::Constructor_MenuView_ScenarioDescription()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_ScenarioDescription::ptr)(
            OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_Prepare),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_DoInitial),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::ScenarioDescription_Func::MenuView_ScenarioDescription_DoEveryFrame));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_ScenarioDescription));
        return;
    }

}
}
