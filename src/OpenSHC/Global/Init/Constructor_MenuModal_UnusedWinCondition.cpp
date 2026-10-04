#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedWinCondition.hpp"
#include "OpenSHC/Globals/Menu_UnusedWinCondition.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B160
    void Init::Constructor_MenuModal_UnusedWinCondition()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedWinCondition::ptr)(
            UI::Enums::MMT_UNUSED_WIN_CONDITION, 0, 0, 0xf0, 0, 0, 0,
            (UI::MenuModalRenderFunction*)MACRO_CALL(Global_Func::DoNothing),
            Menu_UnusedWinCondition::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_UnusedWinCondition));
        return;
    }

}
}
