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

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B160
    void Init::Constructor_MenuModal_UnusedWinCondition()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_UnusedWinCondition::ptr)(
            OpenSHC::UI::Enums::MMT_UNUSED_WIN_CONDITION, 0, 0, 0xf0, 0, 0, 0,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::Global_Func::DoNothing),
            Menu_UnusedWinCondition::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_UnusedWinCondition));
        return;
    }

}
}
