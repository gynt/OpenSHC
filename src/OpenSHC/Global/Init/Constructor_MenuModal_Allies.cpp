#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/Allies.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/MenuModal_Allies.hpp"
#include "OpenSHC/Globals/Menu_Allies.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C180
    void Init::Constructor_MenuModal_Allies()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_Allies::ptr)(UI::Enums::MMT_ALLIES, -1,
            -1, (int)((int)(696)), (int)((int)(384)), (int)((int)(512)), (int)((int)(COL_BLACK::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::Allies_Func::MenuModalRenderFunction_Allies), Menu_Allies::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_Allies));
        return;
    }

}
}
