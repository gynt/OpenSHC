#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DisableTroops.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_DisableEuroTroops.hpp"
#include "OpenSHC/Globals/Menu_DisableEuroTroops.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BBE0
    void Init::Constructor_MenuModal_DisableEuroTroops()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisableEuroTroops::ptr)(
            UI::Enums::MMT_DISABLE_EURO_TROOPS, -1, -1, 400, 0xf0, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::DisableTroops_Func::MenuModalRenderFunction_DisableTroops),
            Menu_DisableEuroTroops::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_DisableEuroTroops));
        return;
    }

}
}
