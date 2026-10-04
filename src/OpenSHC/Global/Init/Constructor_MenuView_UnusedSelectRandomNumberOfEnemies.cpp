#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedSelectRandomNumberOfEnemies.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_UnusedSelectRandomNumberOfEnemies.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A940
    void Init::Constructor_MenuView_UnusedSelectRandomNumberOfEnemies()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_UnusedSelectRandomNumberOfEnemies::ptr)(
            UI::Enums::MVT_UNUSED_SELECT_RANDOM_NUMBER_OF_ENEMIES,
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_Prepare_SwordShieldAndBorder),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            MACRO_CALL(UI::MenuViews::UnusedSelectRandomNumberOfEnemies_Func::
                    MenuView_UnusedSelectRandomNumberOfEnemies_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(
            MACRO_CALL(Meta_Func::Destructor_MenuView_UnusedSelectRandomNumberOfEnemies));
        return;
    }

}
}
