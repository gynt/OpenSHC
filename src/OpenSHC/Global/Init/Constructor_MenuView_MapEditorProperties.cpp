#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuView.func.hpp"
#include "OpenSHC/UI/MenuViews/General.func.hpp"
#include "OpenSHC/UI/MenuViews/MapEditorProperties.func.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/MenuView_MapEditorProperties.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059A490
    void Init::Constructor_MenuView_MapEditorProperties()
    {
        MACRO_CALL_MEMBER(UI::MenuView_Func::Constructor_MenuView, MenuView_MapEditorProperties::ptr)(
            UI::Enums::MVT_MAP_EDITOR_PROPERTIES,
            MACRO_CALL(UI::MenuViews::MapEditorProperties_Func::MenuView_MapEditorProperties_Prepare),
            MACRO_CALL(UI::MenuViews::General_Func::MenuView_General_DoInitial_DefaultMainMenuStructure),
            MACRO_CALL(UI::MenuViews::MapEditorProperties_Func::MenuView_MapEditorProperties_DoEveryFrame));
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuView_MapEditorProperties));
        return;
    }

}
}
