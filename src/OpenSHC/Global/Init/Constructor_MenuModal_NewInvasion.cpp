#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/CreateOrTriggerInvasion.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_NewInvasion.hpp"
#include "OpenSHC/Globals/Menu_NewInvasion.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2026-05-02 18:15:17.059000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059BA20
    void Init::Constructor_MenuModal_NewInvasion()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_NewInvasion::ptr)(
            OpenSHC::UI::Enums::MMT_NEW_INVASION, -1, -1, 700, 0x1b8, 0x200, 6,
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::CreateOrTriggerInvasion_Func::MenuModalRenderFunction_CreateOrTriggerInvasion),
            Menu_NewInvasion::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_NewInvasion));
        return;
    }

}
}
