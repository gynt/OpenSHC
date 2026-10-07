#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ProgressBarBox.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ProgressBarBox.hpp"
#include "OpenSHC/Globals/Menu_ProgressBarBox.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B6E0
    void Init::Constructor_MenuModal_ProgressBarBox()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ProgressBarBox::ptr)(
            UI::Enums::MMT_PROGRESS_BAR_BOX, -1, 0x32, 400, 100, 0x200, (int)((int)(COL_WHITE::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::ProgressBarBox_Func::MenuModalRenderFunction_ProgressBarBox),
            Menu_ProgressBarBox::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_ProgressBarBox));
        return;
    }

}
}
