#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/UnusedSiegeAttackingForceUnk.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedSiegeAttackingForceUnk.hpp"
#include "OpenSHC/Globals/Menu_UnusedSiegeAttackingForceUnk.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059B9E0
    void Init::Constructor_MenuModal_UnusedSiegeAttackingForceUnk()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal,
            MenuModal_UnusedSiegeAttackingForceUnk::ptr)(OpenSHC::UI::Enums::MMT_UNUSED_SIEGE_ATTACKING_FORCEUnk, -1,
            -1, 600, 0x1b8, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(OpenSHC::UI::MenuModals::
                    UnusedSiegeAttackingForceUnk_Func::MenuModalRenderFunction_UnusedSiegeAttackingForceUnk),
            Menu_UnusedSiegeAttackingForceUnk::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(
            MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_UnusedSiegeAttackingForceUnk));
        return;
    }

}
}
