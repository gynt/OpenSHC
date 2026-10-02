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

    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059A550
    void Init::Constructor_MenuView_UnusedChooseGameType()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedChooseGameType::ptr)(
            OpenSHC::UI::Enums::MVT_UNUSED_CHOOSE_GAME_TYPE,
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::General_Func::MenuView_General_DoInitial_ScreenToBlack),
            (OpenSHC::WindowsHelper::cdeclVoidFunc*)MACRO_CALL(
                OpenSHC::UI::MenuViews::UnusedChooseGameType_Func::MenuView_UnusedChooseGameType_DoEveryFrame));
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuView_UnusedChooseGameType));
        return;
    }

}
}
