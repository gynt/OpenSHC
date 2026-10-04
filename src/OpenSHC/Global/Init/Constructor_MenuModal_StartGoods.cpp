#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/StartGoods.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/MenuModal_StartGoods.hpp"
#include "OpenSHC/Globals/Menu_StartGoods.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B9A0
    void Init::Constructor_MenuModal_StartGoods()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_StartGoods::ptr)(
            UI::Enums::MMT_START_GOODS, -1, -1, 600, 0x186, 0x200, 6,
            (UI::MenuModalRenderFunction*)MACRO_CALL(
                UI::MenuModals::StartGoods_Func::MenuModalRenderFunction_StartGoods),
            Menu_StartGoods::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_StartGoods));
        return;
    }

}
}
