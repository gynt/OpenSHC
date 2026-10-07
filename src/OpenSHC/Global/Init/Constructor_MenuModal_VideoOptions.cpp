#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/VideoOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_VideoOptions.hpp"
#include "OpenSHC/Globals/Menu_VideoOptions.hpp"

namespace OpenSHC {
namespace Global {

    using UI::Enums::MenuModalType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B3E0
    void Init::Constructor_MenuModal_VideoOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_VideoOptions::ptr)(
            UI::Enums::MMT_VIDEO_OPTIONS, -1, -1, 500, 0x165, 0x200, (int)((int)(COL_WHITE::instance.shortValue)),
            MACRO_CALL(UI::MenuModals::VideoOptions_Func::MenuModalRenderFunction_VideoOptions),
            Menu_VideoOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_MenuModal_VideoOptions));
        return;
    }

}
}
