#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/MapEditorLandscaping.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MapEditorLandscaping.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A3D0
    void Init::Constructor_MenuView_MapEditorLandscaping()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MapEditorLandscaping::ptr)(
            UI::Enums::MVT_MAP_EDITOR_LANDSCAPING,
            MACRO_CALL(UI::MenuViews::MapEditorLandscaping_Func::MenuView_MapEditorLandscaping_Prepare),
            MACRO_CALL(UI::MenuViews::MapEditorLandscaping_Func::MenuView_MapEditorLandscaping_DoInitial),
            MACRO_CALL(UI::MenuViews::MapEditorLandscaping_Func::MenuView_MapEditorLandscaping_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_MapEditorLandscaping));
        return;
    }

}
}
