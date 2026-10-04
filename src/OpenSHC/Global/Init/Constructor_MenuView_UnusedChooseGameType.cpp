#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedChooseGameType.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedChooseGameType.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A550
    void Init::Constructor_MenuView_UnusedChooseGameType()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedChooseGameType::ptr)(
            UI::Enums::MVT_UNUSED_CHOOSE_GAME_TYPE,
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(Global_Func::DoNothing),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::General_Func::MenuView_General_DoInitial_ScreenToBlack),
            (WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                UI::MenuViews::UnusedChooseGameType_Func::MenuView_UnusedChooseGameType_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_UnusedChooseGameType));
        return;
    }

}
}
