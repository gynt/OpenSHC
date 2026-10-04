#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DisableTroops.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_DisableArabTroops.hpp"
#include "OpenSHC/Globals/Menu_DisableArabTroops.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BC20
    void Init::Constructor_MenuModal_DisableArabTroops()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DisableArabTroops::ptr)(
            UI::Enums::MMT_DISABLE_ARAB_TROOPS, -1, -1, 400, 0xf0, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::DisableTroops_Func::MenuModalRenderFunction_DisableTroops),
            Menu_DisableArabTroops::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_DisableArabTroops));
        return;
    }

}
}
