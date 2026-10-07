#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/SelectCrusade.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_SelectCrusade.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A970
    void Init::Constructor_MenuView_SelectCrusade()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_SelectCrusade::ptr)(
            UI::Enums::MVT_SELECT_CRUSADE,
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_Prepare_SwordShieldAndBorder),
            MACRO_CALL(UI::MenuViews::SelectCrusade_Func::MenuView_SelectCrusade_DoInitial),
            MACRO_CALL(UI::MenuViews::SelectCrusade_Func::MenuView_SelectCrusade_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_SelectCrusade));
        return;
    }

}
}
