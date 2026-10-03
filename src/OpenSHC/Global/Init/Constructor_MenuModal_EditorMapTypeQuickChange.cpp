#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_EditorMapTypeQuickChange.hpp"
#include "OpenSHC/Globals/Menu_EditorMapTypeQuickChange.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BDE0
    void Init::Constructor_MenuModal_EditorMapTypeQuickChange()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_EditorMapTypeQuickChange::ptr)(
            OpenSHC::UI::Enums::MMT_EDITOR_MAP_TYPE_QUICK_CHANGE, -1, -1, 400, 300, 0x200,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            Menu_EditorMapTypeQuickChange::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_EditorMapTypeQuickChange));
        return;
    }

}
}
