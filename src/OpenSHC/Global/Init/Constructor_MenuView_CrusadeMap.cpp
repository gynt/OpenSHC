#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/CrusadeMap.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_CrusadeMap.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A9D0
    void Init::Constructor_MenuView_CrusadeMap()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_CrusadeMap::ptr)(UI::Enums::MVT_CRUSADE_MAP,
            MACRO_CALL(UI::MenuViews::CrusadeMap_Func::MenuView_CrusadeMap_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_CrusadeAndRankMenu),
            MACRO_CALL(UI::MenuViews::CrusadeMap_Func::MenuView_CrusadeMap_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_CrusadeMap));
        return;
    }

}
}
