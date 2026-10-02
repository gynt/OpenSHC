#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedEconomicGametypeSelect.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedEconomicGametypeSelect.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A790
    void Init::Constructor_MenuView_UnusedEconomicGametypeSelect()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedEconomicGametypeSelect::ptr)(
            OpenSHC::UI::Enums::MVT_UNUSED_ECONOMIC_GAMETYPE_SELECT,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::UI::MenuViews::
                    UnusedEconomicGametypeSelect_Func::MenuView_UnusedEconomicGametypeSelect_Prepare),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::UI::MenuViews::
                    UnusedEconomicGametypeSelect_Func::MenuView_UnusedEconomicGametypeSelect_DoInitial),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::General_Func::MenuView_General_DoEveryFrame_FirstGfxCentered));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_UnusedEconomicGametypeSelect));
        return;
    }

}
}
