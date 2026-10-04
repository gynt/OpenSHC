#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/EditScenario.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_EditScenario.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A6D0
    void Init::Constructor_MenuView_EditScenario()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_EditScenario::ptr)(
            UI::Enums::MVT_EDIT_SCENARIO, MACRO_CALL(UI::MenuViews::EditScenario_Func::MenuView_EditScenario_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_OnlySetMenuXY),
            MACRO_CALL(UI::MenuViews::EditScenario_Func::MenuView_EditScenario_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_EditScenario));
        return;
    }

}
}
