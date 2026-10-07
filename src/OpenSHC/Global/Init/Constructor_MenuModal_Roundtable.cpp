#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/Roundtable.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_Roundtable.hpp"
#include "OpenSHC/Globals/Menu_Roundtable.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C140
    void Init::Constructor_MenuModal_Roundtable()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Roundtable::ptr)(
            UI::Enums::MMT_ROUNDTABLE, 4, 4, 0x318, 0x1b0, 0x1200, (int)((int)(COL_WHITE::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::Roundtable_Func::MenuModalRenderFunction_Roundtable), Menu_Roundtable::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_Roundtable));
        return;
    }

}
}
