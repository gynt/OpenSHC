#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AlliesRequestGoods.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_AlliesRequestGoods.hpp"
#include "OpenSHC/Globals/Menu_AlliesRequestGoods.hpp"

namespace OpenSHC {
namespace Global {

    using OpenSHC::UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C200
    void Init::Constructor_MenuModal_AlliesRequestGoods()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModal_Func::Constructor_MenuModal, MenuModal_AlliesRequestGoods::ptr)(
            OpenSHC::UI::Enums::MMT_ALLIES_REQUEST_GOODS, -1, -1, 600, (int)((int)(408)), 0x200,
            (int)((int)(COL_BLACK::instance.shortValue)),
            (OpenSHC::UI::MenuModalRenderFunction*)MACRO_CALL(
                OpenSHC::UI::MenuModals::AlliesRequestGoods_Func::MenuModalRenderFunction_AlliesRequestGoods),
            Menu_AlliesRequestGoods::ptr);
        MACRO_CALL(OpenSHC::OS_Func::_atexit)(MACRO_CALL(OpenSHC::Meta_Func::Destructor_MenuModal_AlliesRequestGoods));
        return;
    }

}
}
